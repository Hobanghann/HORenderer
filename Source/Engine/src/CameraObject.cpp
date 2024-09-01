#include "../../Main/include/Headers.h"

using namespace HO;

void CameraObject::Update(float InDeltaTime) {
	for (const auto &key : mInputHandler.GetInputs()) {
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
			break;
		case ObjectInputHandler::RIGHT:
			break;
		case ObjectInputHandler::UP:
			mFOV += ObjectInputHandler::POSITIVE * mFOVSpeed * InDeltaTime;
			break;
		case ObjectInputHandler::DOWN:
			mFOV += ObjectInputHandler::NEGATIVE * mFOVSpeed * InDeltaTime;
			break;
		default:
			break;
		}
	}
}

Matrix4x4 CameraObject::GetViewMatrixTowardObject(class GameObject* InGameObject) const {
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
	return rotationMatrix.Transpose() * mTransformComponent.GetInverseTranslationMatrix();
}

Matrix4x4 CameraObject::GetProjectionMatrix() const {
	float foctalLength = tanf(mFOV * 0.5f);
	float InvAspectRatio = 1.f / (static_cast<float>(mOwner->mWindowWidth) / static_cast<float>(mOwner->mWindowHeight));
	float InvNearMinusFar = 1.f / (mNearPlane - mFarPlane);
	return Matrix4x4(
		Vector4(foctalLength * InvAspectRatio, 0.f, 0.f, 0.f),
		Vector4(0.f, foctalLength, 0.f, 0.f),
		Vector4(0.f, 0.f, (mNearPlane + mFarPlane) / InvNearMinusFar, -1.f),
		Vector4(0.f, 0.f, (2.f * mNearPlane * mFarPlane) * InvNearMinusFar, 0.f)
	);
}