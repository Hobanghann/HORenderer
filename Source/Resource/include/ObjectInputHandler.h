#pragma once

namespace HO {
	class ObjectInputHandler {
	public:
		enum Keys {
			W,
			A,
			S,
			D,
			Q,
			E,
			UP,
			DOWN,
			LEFT,
			RIGHT
		};

	public:
		ObjectInputHandler(class Object* InObject) : mOwner(InObject) {}
		inline void ClearInputStatus();
		inline void SetInputs(const Uint8 *InKeyStatus);
		inline std::set<Keys> &GetInputs();

	public:
		static const float POSITIVE;
		static const float NEGATIVE;
		class Object* mOwner = nullptr;

	private:
		size_t mNumKeys = 8;
		std::set<Keys> mKeyStatus;
	};
}

void HO::ObjectInputHandler::ClearInputStatus() {
	mKeyStatus.clear();
}

void HO::ObjectInputHandler::SetInputs(const Uint8* InKeyStatus) {
	if (InKeyStatus[SDL_SCANCODE_W]) {
		mKeyStatus.insert(W);
	}
	if (InKeyStatus[SDL_SCANCODE_A]) {
		mKeyStatus.insert(A);
	}	
	if (InKeyStatus[SDL_SCANCODE_S]) {
		mKeyStatus.insert(S);
	}
	if (InKeyStatus[SDL_SCANCODE_D]) {
		mKeyStatus.insert(D);
	}
	if (InKeyStatus[SDL_SCANCODE_Q]) {
		mKeyStatus.insert(Q);
	}
	if (InKeyStatus[SDL_SCANCODE_E]) {
		mKeyStatus.insert(E);
	}
	if (InKeyStatus[SDL_SCANCODE_UP]) {
		mKeyStatus.insert(UP);
	}
	if (InKeyStatus[SDL_SCANCODE_DOWN]) {
		mKeyStatus.insert(DOWN);
	}
	if (InKeyStatus[SDL_SCANCODE_LEFT]) {
		mKeyStatus.insert(LEFT);
	}
	if (InKeyStatus[SDL_SCANCODE_RIGHT]) {
		mKeyStatus.insert(RIGHT);
	}	
}

std::set<HO::ObjectInputHandler::Keys> &HO::ObjectInputHandler::GetInputs(){
	return mKeyStatus;
}
