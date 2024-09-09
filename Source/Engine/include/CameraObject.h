#pragma once

namespace HO {
	class CameraObject : public Object{
	public:
		CameraObject(class GameEngine *InGameEngine):Object(this), mOwner(InGameEngine) {}
		void Update(float InDeltaTime) override;
		inline Matrix4x4 GetViewMatrix() const;
		Matrix4x4 GetViewMatrixTowardObject(class GameObject*) const;

		inline Matrix4x4 GetViewMatrixFromLocalAxis() const;

		Matrix4x4 GetProjectionMatrix() const;
		inline Vector3 GetForwardVector() const;
	private:
		float mFOVSpeed = PI * 0.1f;
		float mFOV = PI / 3.f;
		float mNearPlane = 5.5f;
		float mFarPlane = 10000.f;
		class GameEngine* mOwner = nullptr;
	};
}


//180rotation 추가하면 에러 발생 --> why?
HO::Matrix4x4 HO::CameraObject::GetViewMatrix() const {
	return mTransformComponent.GetInverseRotationMatrix() * mTransformComponent.GetInverseTranslationMatrix();
}

HO::Vector3 HO::CameraObject::GetForwardVector() const {
	return (GetViewMatrix() * Vector4::UnitZ).ToVector3() * -1.f;
}

HO::Matrix4x4 HO::CameraObject::GetViewMatrixFromLocalAxis() const{
	float cosPitch = cosf(mTransformComponent.GetPitchAngle());
	float sinPitch = sinf(mTransformComponent.GetPitchAngle());
	float cosYaw = cosf(mTransformComponent.GetYawAngle());
	float sinYaw = sinf(mTransformComponent.GetYawAngle());
	float cosRoll = cosf(mTransformComponent.GetRollAngle());
	float sinRoll = sinf(mTransformComponent.GetRollAngle());
	
	Vector4 rightVector = Vector4(
		cosYaw * cosRoll + sinYaw * sinPitch * sinRoll,
		cosPitch * sinRoll,
		-sinYaw * cosRoll + cosYaw * sinPitch * sinRoll,
		0.f) * -1.f;
	Vector4 upVector = Vector4(
		-cosYaw * sinRoll + sinYaw * sinPitch * cosRoll,
		cosPitch * cosRoll,
		sinYaw * sinRoll + cosYaw * sinPitch * cosRoll,
		0.f);
	Vector4 forwardVector = Vector4(
		sinYaw * cosPitch,
		-sinPitch,
		cosYaw * cosPitch,
		0.f) * -1.f;
	Vector4 translationVector = mTransformComponent.GetPosition();
	
	return Matrix4x4(
		Vector4(rightVector.X, upVector.X, forwardVector.X, 0.f),
		Vector4(rightVector.Y, upVector.Y, forwardVector.Y, 0.f),
		Vector4(rightVector.Z, upVector.Z, forwardVector.Z, 0.f),
		Vector4(-translationVector.X, -translationVector.Y, -translationVector.Z, 1.f)
	);
}