#include "../../Main/include/Headers.h"

using namespace HO;

CameraObject::CameraObject(class GameEngine* InGameEngine) :
	Object(this),
	mOwner(InGameEngine)
{
	mFrustrum = new Frustrum(GetProjectionMatrix());
}

void CameraObject::Update(float InDeltaTime) {
	for (const auto& key : mInputHandler.GetInputs()) {
		switch (key) {
		case ObjectInputHandler::W:
			break;
		case ObjectInputHandler::A:
			break;
		case ObjectInputHandler::S:
			break;
		case ObjectInputHandler::D:
			break;
		case ObjectInputHandler::Q:
			break;
		case ObjectInputHandler::E:
			break;
		case ObjectInputHandler::LEFT:
			mTransformComponent.UpdateYawAngle(InDeltaTime, ObjectInputHandler::NEGATIVE);
			break;
		case ObjectInputHandler::RIGHT:
			mTransformComponent.UpdateYawAngle(InDeltaTime, ObjectInputHandler::POSITIVE);
			break;
		case ObjectInputHandler::UP:
			mTransformComponent.UpdatePitchAngle(InDeltaTime, ObjectInputHandler::POSITIVE);
			break;
		case ObjectInputHandler::DOWN:
			mTransformComponent.UpdatePitchAngle(InDeltaTime, ObjectInputHandler::NEGATIVE);
			break;
		case ObjectInputHandler::PAGEUP:
			mFOV += ObjectInputHandler::POSITIVE * mFOVSpeed * InDeltaTime;
			break;
		case ObjectInputHandler::PAGEDOWN:
			mFOV += ObjectInputHandler::NEGATIVE * mFOVSpeed * InDeltaTime;
			break;
		default:
			break;
		}
	}
	//update frustrum
	mFrustrum->UpdatePlane(GetProjectionMatrix());
}

Matrix4x4 CameraObject::GetViewMatrixTowardObject(class GameObject* InGameObject) const {
	//SDL_Log("load view Matrix from %p", InGameObject);
	Vector3 forwardVector = (InGameObject->GetTransform().GetPosition() - mTransformComponent.GetPosition()).GetNormalized();
	Vector3 rightVector = forwardVector.Cross(Vector3::UnitY);

	if (MathFunctions::IsAlmostZero(rightVector.GetSqrdMagnitude())) {
		rightVector = Vector3::UnitX;
	}

	if (rightVector.Dot(forwardVector) > 0) {
		rightVector *= -1.f;
	}

	Vector3 upVector = rightVector.Cross(forwardVector);
	Matrix4x4 rotationMatrix(
		Vector4(rightVector.X, rightVector.Y, rightVector.Z, 0.f),
		Vector4(upVector.X, upVector.Y, upVector.Z, 0.f),
		Vector4(forwardVector.X, forwardVector.Y, forwardVector.Z, 0.f),
		Vector4::UnitW
	);
	//SDL_Log("loading view Matrix finished");
	return rotationMatrix.Transpose() * mTransformComponent.GetInverseTranslationMatrix();
}

Matrix4x4 CameraObject::GetProjectionMatrix() const {
	//SDL_Log("load projection Matrix");
	float foctalLength = 1.f / tanf(mFOV * 0.5f);
	float InvAspectRatio = 1.f / (static_cast<float>(mOwner->mWindowWidth) / static_cast<float>(mOwner->mWindowHeight));
	float InvNearMinusFar = 1.f / (mNearPlane - mFarPlane);
	//SDL_Log("loading projection Matrix finished");
	return Matrix4x4(
		Vector4(foctalLength * InvAspectRatio, 0.f, 0.f, 0.f),
		Vector4(0.f, foctalLength, 0.f, 0.f),
		Vector4(0.f, 0.f, (mNearPlane + mFarPlane) * InvNearMinusFar, -1.f),
		Vector4(0.f, 0.f, (2.f * mNearPlane * mFarPlane) * InvNearMinusFar, 0.f)
	);
}