#include "../../Main/include/Headers.h"

using namespace HO;

bool GameEngine::Initialize()
{	
	SDL_Log("start initialization");
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
	SDL_Log("finish initialization");
	return bSuccess;
}

void GameEngine::RunLoop()
{	
	SDL_Log("enter main loop");
	while (mbIsRunning)
	{
		mFrameCount++;
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
	SDL_Log("start load resources");
	Mesh *Box = new Mesh(Mesh::BOX);
	mAddMesh("BOX_MESH", Box);
}

void GameEngine::mLoadScene()
{	
	SDL_Log("start load main object");
	GameObject *newObject = new GameObject("MainBOX", mGetMesh("BOX_MESH"));
	newObject->SetMainObject();
	auto &transform = newObject->GetTransform();
	transform.SetPosition(Vector3(0.f, 0.f, 500.f));
	transform.SetScale(100.f);
	SDL_Log("finish load main object");
	mAddGameObject(newObject);

	std::mt19937 randomEngine(0);
	std::uniform_real_distribution<float> distributionZ(500.f, 1000.f);
	std::uniform_real_distribution<float> distributionXY(-500.f, 500.f);
	SDL_Log("start load subobject");
	for (int i = 1; i <= 10; i++)
	{
		char objectName[10];
		sprintf(objectName, "BOX%d", i);
		GameObject *newObject = new GameObject(objectName, mGetMesh("BOX_MESH"));
		auto &transform = newObject->GetTransform();
		transform.SetPosition(Vector3(distributionXY(randomEngine), distributionXY(randomEngine), distributionZ(randomEngine)));
		transform.SetScale(100.f);
		mAddGameObject(newObject);
	}
	SDL_Log("finish load subobject");

	Transform &CameraTransform = mMainCamera.GetTransform();
	CameraTransform.SetPosition(Vector3(0.f, 30.f, -500.f));
	CameraTransform.SetYawAngle(PI);
}

void GameEngine::mProcessInput()
{	
	SDL_Log("start process input");
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
	SDL_Log("finish process input");
}

void GameEngine::mUpdate()
{	
	SDL_Log("start update");
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTickCount + 16))
		;

	float deltaTime = (SDL_GetTicks() - mTickCount) / 1000.f;
	/*if (deltaTime > 0.5f)
	{
		deltaTime = 0.0016f;
	}*/

	mTickCount = SDL_GetTicks();

	this->mUpdateEngineStatus();

	GameObject *box = mGetGameObject("MainBOX");
	box->Update(deltaTime);
	mMainCamera.Update(deltaTime);
	SDL_Log("finish update");
}

void GameEngine::mRender()
{
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
	SDL_RenderClear(mRenderer);

	for (GameObject *box : mScene)
	{
		std::vector<Vertex> vertexBuffer = box->GetMesh()->GetVertexBuffer();

		SDL_Log("start load matrix");
		//Matrix4x4 PVMMatrix = mMainCamera.GetProjectionMatrix() * mMainCamera.GetViewMatrixTowardObject(mGetGameObject("MainBOX")) * box->GetTransform().GetModelingMatrix();
		Matrix4x4 PVMMatrix = mMainCamera.GetProjectionMatrix() * mMainCamera.GetViewMatrix() * box->GetTransform().GetModelingMatrix();
		//Matrix4x4 PVMMatrix = mMainCamera.GetProjectionMatrix() * mMainCamera.GetViewMatrixFromLocalAxis() * box->GetTransform().GetModelingMatrix();
		SDL_Log("finish load matrix");

		SDL_Log("start transform vertices");
		for (Vertex &vertex : vertexBuffer)
		{
			// transform point from local space to clip space
			vertex = mRenderingPipeline.VertexShader(vertex, PVMMatrix);
			// perspective divide
			vertex = mRenderingPipeline.PerspectiveDivide(vertex);

			vertex.SetPixel(mRenderingPipeline.DenormalizeNDC(vertex, mWindowWidth, mWindowHeight));

			vertex.SetPixel(mRenderingPipeline.Rasterize(vertex, mWindowWidth, mWindowHeight));
		}
		SDL_Log("finish transform vertices");

		std::list<Mesh::Triangle> indexBuffer = box->GetMesh()->GetIndexBuffer();

		if (mbUseBackfaceCulling)
		{
			SDL_Log("start backface culling");
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
			SDL_Log("finish backface culling");
		}

		if (box->IsMainObject())
		{
			mRenderingPipeline.SetRenderingColor("PURPLE");
		}
		else
		{
			mRenderingPipeline.SetRenderingColor("BLUE");
		}

		for (Mesh::Triangle &triangle : indexBuffer)
		{
			SDL_Log("start drawing triangle");
			mRenderingPipeline.DrawTriangle(vertexBuffer, triangle, static_cast<RenderingPipeline::RenderingMode>(mGetRenderingMode()));
			SDL_Log("finish drawing triangle");
		}
	}

	SDL_RenderPresent(mRenderer);
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

Mesh *GameEngine::mGetMesh(const std::string &InName) const
{
	auto foundObject = mMeshes.find(InName);
	if (foundObject == mMeshes.end())
	{
		return nullptr;
	}
	return foundObject->second;
}

void GameEngine::mAddMesh(const std::string &InName, Mesh *InMesh)
{
	mMeshes.insert({InName, InMesh});
}

void GameEngine::mRemoveMesh(const std::string &InName)
{
	mMeshes.erase(InName);
}
