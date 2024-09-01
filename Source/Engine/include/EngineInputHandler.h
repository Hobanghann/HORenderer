#pragma once
#pragma once

namespace HO {
	class EngineInputHandler {
	public:
		enum Keys {
			F1,
			F2,
			F3,
			F4,
			F5,
			F6,
			F7,
			F8,
			F9,
			F10,
			F11,
			F12
		};

	public:
		EngineInputHandler(class GameEngine* InEngine) : mOwner(InEngine) {}
		inline void ClearInputStatus();
		inline void SetInputs(const Uint8* InKeyStatus);
		inline std::set<Keys>& GetInputs();

	public:
		static const float POSITIVE;
		static const float NEGATIVE;
		class GameEngine* mOwner = nullptr;

	private:
		size_t mNumKeys = 8;
		std::set<Keys> mKeyStatus;
	};
}

void HO::EngineInputHandler::ClearInputStatus() {
	mKeyStatus.clear();
}

void HO::EngineInputHandler::SetInputs(const Uint8* InKeyStatus) {
	if (InKeyStatus[SDL_SCANCODE_F1]) {
		mKeyStatus.insert(F1);
	}
	if (InKeyStatus[SDL_SCANCODE_F2]) {
		mKeyStatus.insert(F2);
	}
	if (InKeyStatus[SDL_SCANCODE_F3]) {
		mKeyStatus.insert(F3);
	}
	if (InKeyStatus[SDL_SCANCODE_F4]) {
		mKeyStatus.insert(F4);
	}
	if (InKeyStatus[SDL_SCANCODE_F5]) {
		mKeyStatus.insert(F5);
	}
	if (InKeyStatus[SDL_SCANCODE_F6]) {
		mKeyStatus.insert(F6);
	}
	if (InKeyStatus[SDL_SCANCODE_F7]) {
		mKeyStatus.insert(F7);
	}
	if (InKeyStatus[SDL_SCANCODE_F8]) {
		mKeyStatus.insert(F8);
	}
	if (InKeyStatus[SDL_SCANCODE_F9]) {
		mKeyStatus.insert(F9);
	}
	if (InKeyStatus[SDL_SCANCODE_F10]) {
		mKeyStatus.insert(F10);
	}
	if (InKeyStatus[SDL_SCANCODE_F11]) {
		mKeyStatus.insert(F11);
	}
	if (InKeyStatus[SDL_SCANCODE_F12]) {
		mKeyStatus.insert(F12);
	}
}

std::set<HO::EngineInputHandler::Keys>& HO::EngineInputHandler::GetInputs() {
	return mKeyStatus;
}
