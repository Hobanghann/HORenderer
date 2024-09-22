#include "../../Main/include/Headers.h"

//#define DEBUG

using namespace HO;

bool GameEngine::Initialize()
{	

#ifdef DEBUG
	SDL_Log("start initialization");
#endif

	bool bSuccess = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		SDL_Log("Failed to initialize\n");
		bSuccess = false;
	}
	else
	{
		mWindow = SDL_CreateWindow("HORenderer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, mWindowWidth, mWindowHeight, 0);
		if (mWindow == nullptr)
		{
			SDL_Log("Failed to create window\n");
			bSuccess = false;
		}
		else
		{
			mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (mRenderer == nullptr)
			{
				SDL_Log("Failed to create renderer\n");
				bSuccess = false;
			}
			else
			{
				mLoadResources();
				mLoadScene();
				mTickCount = SDL_GetTicks();
			}
		}
	}

#ifdef DEBUG
	SDL_Log("finish initialization");
#endif
	return bSuccess;
}

void GameEngine::RunLoop()
{	

#ifdef DEBUG
	SDL_Log("enter main loop");
#endif

	while (mbIsRunning)
	{
		mProcessInput();
		mUpdate();
		mRender();
	}
}

void GameEngine::Quit()
{
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void GameEngine::mLoadResources()
{	
#ifdef DEBUG
	SDL_Log("start load resources");
#endif

	const Mesh *Box = new Mesh(Mesh::BOX);

	mAddMesh("BOX_MESH", Box);
	SDL_Log("Center : %f %f %f, Radious : %f", Box->GetSphereBoundingVolume()->GetCenter().X, Box->GetSphereBoundingVolume()->GetCenter().Y, Box->GetSphereBoundingVolume()->GetCenter().Z, Box->GetSphereBoundingVolume()->GetRadious());
}

void GameEngine::mLoadScene()
{	
#ifdef DEBUG
	SDL_Log("start load main object");
#endif

	GameObject *newObject = new GameObject("MainBOX", mGetMesh("BOX_MESH"));
	newObject->SetMainObject();
	auto &transform = newObject->GetTransform();
	transform.SetPosition(Vector3(0.f, 0.f, -1000.f));
	transform.SetScale(100.f);

#ifdef DEBUG
	SDL_Log("finish load main object");
#endif

	mAddGameObject(newObject);

	std::mt19937 randomEngine(0);
	std::uniform_real_distribution<float> distributionZ(-3000.f, -1000.f);
	std::uniform_real_distribution<float> distributionXY(-3000.f, 3000.f);

#ifdef DEBUG
	SDL_Log("start load subobject");
#endif

	for (int i = 1; i <= 50; i++)
	{
		char objectName[10];
		sprintf(objectName, "BOX%d", i);
		GameObject *newObject = new GameObject(objectName, mGetMesh("BOX_MESH"));
		auto &transform = newObject->GetTransform();
		transform.SetPosition(Vector3(distributionXY(randomEngine), distributionXY(randomEngine), distributionZ(randomEngine)));
		transform.SetScale(100.f);
		mAddGameObject(newObject);
	}

#ifdef DEBUG
	SDL_Log("finish load subobject");
#endif

	Transform &CameraTransform = mMainCamera.GetTransform();
	CameraTransform.SetPosition(Vector3(0.f, 0.f, 500.f));
	CameraTransform.SetYawAngle(PI);
}

void GameEngine::mProcessInput()
{	
#ifdef DEBUG
	SDL_Log("start process input");
#endif

	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_QUIT:
			mbIsRunning = false;
		}
	}

	ObjectInputHandler &boxInputHandler = mGetGameObject("MainBOX")->GetInputHandler();
	ObjectInputHandler &cameraInputHandler = mMainCamera.GetInputHandler();

	mEngineInputHandler.ClearInputStatus();
	boxInputHandler.ClearInputStatus();
	cameraInputHandler.ClearInputStatus();

	const Uint8 *keyboard = SDL_GetKeyboardState(nullptr);

	mEngineInputHandler.SetInputs(keyboard);
	boxInputHandler.SetInputs(keyboard);
	cameraInputHandler.SetInputs(keyboard);

#ifdef DEBUG
	SDL_Log("finish process input");
#endif
}

void GameEngine::mUpdate()
{
#ifdef DEBUG
	SDL_Log("start update");
#endif

	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTickCount + 16));

	float deltaTime = (SDL_GetTicks() - mTickCount) / 1000.f;
	if (deltaTime > 0.5f)
	{
		deltaTime = 0.0016f;
	}

	mTickCount = SDL_GetTicks();

	this->mUpdateEngineStatus();

	GameObject *box = mGetGameObject("MainBOX");
	box->Update(deltaTime);
	mMainCamera.Update(deltaTime);

#ifdef DEBUG
	SDL_Log("finish update");
#endif
}

void GameEngine::mRender()
{	
	int numCulled = 0;
	
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
	SDL_RenderClear(mRenderer);

	if(mbUseDepthTesting){
		mRenderingPipeline.ResetBuffer();
	}

	Matrix4x4 projectionMatrix = mMainCamera.GetProjectionMatrix();
	Matrix4x4 viewMatrix = mMainCamera.GetViewMatrix();

	for (GameObject *box : mScene) {

		Matrix4x4 vmMatrix = viewMatrix * box->GetTransform().GetModelingMatrix();

		if(mbUseFrustrumCulling){
			mRenderingPipeline.BoxBoundingVolumeFrustrumCulling(box, vmMatrix);
			if(!box->IsInFrustrum()){
				numCulled++;
				continue;
			}
		}
		
		std::vector<Vertex> vertexBuffer = box->GetMesh()->GetVertexBuffer();

		Matrix4x4 PVMMatrix = projectionMatrix * vmMatrix;

#ifdef DEBUG
		SDL_Log("start transform vertices");
#endif
		

		
		for (Vertex &vertex : vertexBuffer)
		{
			//transform point from local space to clip space
			vertex = mRenderingPipeline.VertexShader(vertex, PVMMatrix);
			// perspective divide
			vertex = mRenderingPipeline.PerspectiveDivide(vertex);

			vertex.SetPixel(mRenderingPipeline.DenormalizeNDC(vertex, mWindowWidth, mWindowHeight));

			vertex.SetPixel(mRenderingPipeline.Rasterize(vertex, mWindowWidth, mWindowHeight));
		}

#ifdef DEBUG
		SDL_Log("finish transform vertices");
#endif

		std::list<Mesh::Triangle> indexBuffer = box->GetMesh()->GetIndexBuffer();

		if (mbUseBackfaceCulling)
		{

#ifdef DEBUG
			SDL_Log("start backface culling");
#endif

			for (auto itr = indexBuffer.begin(); itr != indexBuffer.end();)
			{
				if (mRenderingPipeline.IsBackface(vertexBuffer, *itr, Vector3::UnitZ))
				{
					itr = indexBuffer.erase(itr);
				}
				else
				{
					itr++;
				}
			}

#ifdef DEBUG
			SDL_Log("finish backface culling");
#endif

		}

		//set color
		if (box->IsMainObject())
		{
			mRenderingPipeline.SetRenderingColor("PURPLE");
		}
		else
		{
			mRenderingPipeline.SetRenderingColor("BLUE");
		}

		//draw in color buffer
		for (Mesh::Triangle &triangle : indexBuffer)
		{

#ifdef DEBUG
			SDL_Log("start drawing triangle");
#endif

			mRenderingPipeline.DrawTriangle(vertexBuffer, triangle, static_cast<RenderingPipeline::RenderingMode>(mGetRenderingMode()));

#ifdef DEBUG
			SDL_Log("finish drawing triangle");
#endif
		}
	}

#ifdef DEBUG
	SDL_Log("start reset frustrum state");
#endif

	if(mbUseFrustrumCulling){
		mResetFrustrumState();	
	}

#ifdef DEBUG
		SDL_Log("finish resetting frustrum state");
#endif

	//swap color buffer
#ifdef DEBUG
	SDL_Log("swap buffer");
#endif

	SDL_Log("culled object : %d", numCulled);

	SDL_RenderPresent(mRenderer);

#ifdef DEBUG
	SDL_Log("%s", SDL_GetError());
#endif
}

GameObject *GameEngine::mGetGameObject(const std::string &InString) const{
	for(GameObject *gameObject : mScene){
		if(gameObject->GetName() == InString){
			return gameObject;
		}
	}
	return nullptr;
}

void GameEngine::mAddGameObject(GameObject *InGameObject)
{
	mScene.push_back(InGameObject);
}

void GameEngine::mRemoveGameObject(const std::string &InString){
	for(auto itr = mScene.begin(); itr != mScene.end(); itr++){
		if((*itr)->GetName() == InString){
			mScene.erase(itr);
			return;
		}
	}
	return;
}

const Mesh *GameEngine::mGetMesh(const std::string &InName) const
{
	auto foundObject = mMeshes.find(InName);
	if (foundObject == mMeshes.end())
	{
		return nullptr;
	}
	return foundObject->second;
}

void GameEngine::mAddMesh(const std::string &InName, const Mesh *InMesh)
{
	mMeshes.insert({InName, InMesh});
}

void GameEngine::mRemoveMesh(const std::string &InName)
{
	mMeshes.erase(InName);
}
