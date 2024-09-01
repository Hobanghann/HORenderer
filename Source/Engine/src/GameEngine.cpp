#include "../../Main/include/Headers.h"

using namespace HO;

bool GameEngine::Initialize() {
	bool bSuccess = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		SDL_Log("Failed to initialize\n");
		bSuccess = false;
	}
	else {
		mWindow = SDL_CreateWindow("HORenderer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, mWindowWidth, mWindowHeight, 0);
		if (mWindow == nullptr) {
			SDL_Log("Failed to create window\n");
			bSuccess = false;
		}
		else {
			mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (mRenderer == nullptr) {
				SDL_Log("Failed to create renderer\n");
				bSuccess = false;
			}
			else {
				mLoadResources();
				mLoadScene();
				mTickCount = SDL_GetTicks();
			}
		}
	}
	return bSuccess;
}

void GameEngine::RunLoop() {
	while (mbIsRunning) {
		mFrameCount++;
		mProcessInput();
		mUpdate();
		mRender();
	}
}

void GameEngine::Quit() {
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}




void GameEngine::mLoadResources() {
	Mesh* Box = new Mesh(Mesh::BOX);
	mAddMesh("BOX_MESH", Box);
}

void GameEngine::mLoadScene() {
	GameObject* newObject = new GameObject("BOX", mGetMesh("BOX_MESH"));
	auto& transform = newObject->GetTransform();
	transform.SetPosition(Vector3(0.f, 0.f, 500.f));
	transform.SetScale(100.f);

	mAddGameObject("BOX", newObject);

	Transform &CameraTransform = mMainCamera.GetTransform();
	CameraTransform.SetPosition(Vector3(0.f, 500.f, 0.f));
	CameraTransform.SetYawAngle(PI);
}





void GameEngine::mProcessInput() {
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		switch (e.type) {
		case SDL_QUIT:
			mbIsRunning = false;
		}
	}

	ObjectInputHandler& boxInputHandler = mGetGameObject("BOX")->GetInputHandler();
	ObjectInputHandler& cameraInputHandler = mMainCamera.GetInputHandler();

	mEngineInputHandler.ClearInputStatus();
	boxInputHandler.ClearInputStatus();
	cameraInputHandler.ClearInputStatus();

	const Uint8* keyboard = SDL_GetKeyboardState(nullptr);

	
	mEngineInputHandler.SetInputs(keyboard);
	boxInputHandler.SetInputs(keyboard);
	cameraInputHandler.SetInputs(keyboard);
}

void GameEngine::mUpdate() {
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTickCount + 16));

	float deltaTime = (SDL_GetTicks() - mTickCount) / 1000.f;
	if (deltaTime > 0.5f) {
		deltaTime = 0.0016f;
	}

	mTickCount = SDL_GetTicks();

	this->mUpdateEngineStatus();

	GameObject* box = mGetGameObject("BOX");
	box->Update(deltaTime);
	mMainCamera.Update(deltaTime);
	
}

void GameEngine::mRender() {
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
	SDL_RenderClear(mRenderer);

	GameObject* box = mGetGameObject("BOX");
	const std::vector<Vertex>& vertexBuffer = box->GetMesh()->GetVertexBuffer();

	std::vector<Vector3> NDCBuffer;
	Matrix4x4 PVMMatrix = mMainCamera.GetProjectionMatrix() * mMainCamera.GetViewMatrixTowardObject(box) * box->GetTransform().GetModelingMatrix();

	Matrix4x4 projectionMatrix = mMainCamera.GetProjectionMatrix();
	for (Vertex vertex : vertexBuffer) {
		//transform point from local space to clip space
		Vector4 transformedPoint = mRenderingPipeline.VertexShader(vertex, PVMMatrix);

		//perspective divide
		Vector3 NDC = mRenderingPipeline.PerspectiveDivide(transformedPoint);

		NDCBuffer.push_back(NDC);
	}
	
	std::list<Mesh::Triangle> indexBuffer = box->GetMesh()->GetIndexBuffer();

	
	if (mbUseBackfaceCulling) {
		
		for (auto itr = indexBuffer.begin(); itr != indexBuffer.end();) {
			if (mRenderingPipeline.IsBackface(NDCBuffer, *itr, Vector3::UnitZ)) {
				itr = indexBuffer.erase(itr);
			}
			else {
				itr++;
			}
		}
	}

	std::vector<Vector2> pixelBuffer;

	for (Vector3& ndc : NDCBuffer) {
		//NDC denormalize
		ndc = mRenderingPipeline.DenormalizeNDC(ndc, mWindowWidth, mWindowHeight);
		//points to screen coordinate(pixel)
		ndc = mRenderingPipeline.Rasterize(ndc, mWindowWidth, mWindowHeight);

		pixelBuffer.push_back(ndc.ToVector2());
	}
	
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255);

	for (Mesh::Triangle &triangle : indexBuffer) {
		if (mbUseBackfaceCulling) {
			if (triangle.IsBackface) {
				continue;
			}
		}
		if (mbUseWireFrameMode) {
			mRenderingPipeline.DrawTriangle(pixelBuffer, triangle, RenderingPipeline::eWireFrame);
		}
		else {
			mRenderingPipeline.DrawTriangle(pixelBuffer, triangle, RenderingPipeline::eFill);
		}
	}

	SDL_RenderPresent(mRenderer);
}





GameObject* GameEngine::mGetGameObject(const std::string& InName) const {
	auto foundObject = mScene.find(InName);
	if (foundObject == mScene.end()) {
		return nullptr;
	}
	return foundObject->second;
}

void GameEngine::mAddGameObject(const std::string& InName, GameObject* InGameObject) {
	mScene.insert({ InName, InGameObject });
}

void GameEngine::mRemoveGameObject(const std::string& InName) {
	mScene.erase(InName);
}

Mesh* GameEngine::mGetMesh(const std::string& InName) const {
	auto foundObject = mMeshes.find(InName);
	if (foundObject == mMeshes.end()) {
		return nullptr;
	}
	return foundObject->second;
}

void GameEngine::mAddMesh(const std::string& InName, Mesh* InMesh) {
	mMeshes.insert({ InName, InMesh });
}

void GameEngine::mRemoveMesh(const std::string& InName) {
	mScene.erase(InName);
}
