#include "../../Main/include/Headers.h"
using namespace HO;

void GameObject::Update(float InDeltaTime) {
	for (const auto &key : mInputHandler.GetInputs()) {
		switch (key) {
		case ObjectInputHandler::W:
			mTransformComponent.UpdatePitchAngle(InDeltaTime, ObjectInputHandler::NEGATIVE);
			break;
		case ObjectInputHandler::A:
			mTransformComponent.UpdateYawAngle(InDeltaTime, ObjectInputHandler::NEGATIVE);
			break;
		case ObjectInputHandler::S:
			mTransformComponent.UpdatePitchAngle(InDeltaTime, ObjectInputHandler::POSITIVE);
			break;
		case ObjectInputHandler::D:
			mTransformComponent.UpdateYawAngle(InDeltaTime, ObjectInputHandler::POSITIVE);
			break;
		case ObjectInputHandler::Q:
			mTransformComponent.UpdateRollAngle(InDeltaTime, ObjectInputHandler::NEGATIVE);
			break;
		case ObjectInputHandler::E:
			mTransformComponent.UpdateRollAngle(InDeltaTime, ObjectInputHandler::POSITIVE);
			break;
		case ObjectInputHandler::LEFT:
			break;
		case ObjectInputHandler::RIGHT:
			break;
		case ObjectInputHandler::UP:
			break;
		case ObjectInputHandler::DOWN:
			break;
		default:
			break;
		}
	}
}

bool GameObject::IsItInView(const GameObject* InObject, float InFOV) const {
	float cosFOV = cosf(InFOV * 0.5f);
	Vector3 forwardVector = mTransformComponent.GetForwardVector().GetNormalized();
	Vector3 fromThisToObject = (InObject->GetPosition() - this->GetPosition()).GetNormalized();
	if (forwardVector.Dot(fromThisToObject) >= cosFOV) {
		return true;
	}
	return false;
}

bool GameObject::IsItOutOfView(const GameObject* InObject, float InFOV) const {
	float cosFOV = cosf(InFOV * 0.5f);
	Vector3 forwardVector = mTransformComponent.GetForwardVector().GetNormalized();
	Vector3 fromThisToObject = (InObject->GetPosition() - this->GetPosition()).GetNormalized();
	if (forwardVector.Dot(fromThisToObject) >= cosFOV) {
		return false;
	}
	return true;
}

bool GameObject::IsItOnFront(const GameObject* InObject) const {
	Vector3 forwardVector = mTransformComponent.GetForwardVector();
	Vector3 fromThisToObject = InObject->GetPosition() - this->GetPosition();
	if (forwardVector.Dot(fromThisToObject) > 0) {
		return true;
	}
	return false;
}

bool GameObject::IsItOnBehind(const GameObject* InObject) const {
	Vector3 forwardVector = mTransformComponent.GetForwardVector();
	Vector3 fromThisToObject = InObject->GetPosition() - this->GetPosition();
	if (forwardVector.Dot(fromThisToObject) > 0) {
		return false;
	}
	return true;
}
