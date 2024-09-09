#pragma once

namespace HO {
	class GameEngine {

		friend class RenderingPipeline;
		friend class CameraObject;

	public:
		GameEngine() :
			mMainCamera(this),
			mRenderingPipeline(this),
			mEngineInputHandler(this)
		{}

		bool Initialize();
		void RunLoop();
		void Quit();

	private:
		void mLoadResources();
		void mLoadScene();
		void mProcessInput();
		void mUpdate();
		void mRender();

		GameObject* mGetGameObject(const std::string&) const;
		void mAddGameObject(GameObject*);
		void mRemoveGameObject(const std::string&);

		Mesh* mGetMesh(const std::string&) const;
		void mAddMesh(const std::string&, Mesh*);
		void mRemoveMesh(const std::string&);

	private:
		inline void mUpdateEngineStatus();
		inline int mGetRenderingMode() const;

	private:
		SDL_Window* mWindow = nullptr;
		SDL_Renderer* mRenderer = nullptr;
		unsigned mWindowWidth = 1280;
		unsigned mWindowHeight = 720;
		bool mbIsRunning = true;
		Uint32 mTickCount = 0;
		Uint32 mFrameCount = 0;

		std::vector<GameObject*> mScene;
		std::unordered_map<std::string, Mesh*> mMeshes;

		CameraObject mMainCamera;
		RenderingPipeline mRenderingPipeline;
		EngineInputHandler mEngineInputHandler;

	private:
		bool mbUseWireFrameMode = true;
		bool mbUseBackfaceCulling = true;
		bool mbUseDepthTesting = true;
	};
}

void HO::GameEngine::mUpdateEngineStatus() {
	for (const auto& key : mEngineInputHandler.GetInputs()) {
		switch (key) {
			case EngineInputHandler::F1:
				mbUseWireFrameMode = !mbUseWireFrameMode;
				break;
			case EngineInputHandler::F2:
				mbUseBackfaceCulling = !mbUseBackfaceCulling;
				break;
			case EngineInputHandler::F3:
				mbUseDepthTesting = !mbUseDepthTesting;
				break;
			case EngineInputHandler::F4:
				break;
			case EngineInputHandler::F5:
				break;
			case EngineInputHandler::F6:
				break;
			case EngineInputHandler::F7:
				break;
			case EngineInputHandler::F9:
				break;
			case EngineInputHandler::F10:
				break;
			case EngineInputHandler::F11:
				break;
			case EngineInputHandler::F12:
				break;
			default:
				break;
		}
	}
}

int HO::GameEngine::mGetRenderingMode() const{
	int renderingMode = 0;
	if(mbUseWireFrameMode){
		renderingMode |= 0b0001;
	}
	if(mbUseBackfaceCulling){
		renderingMode |= 0b0010;
	}
	if(mbUseDepthTesting){
		renderingMode |= 0b0100;
	}
	return renderingMode;
}