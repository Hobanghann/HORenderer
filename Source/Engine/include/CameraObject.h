#pragma once

namespace HO {
	class CameraObject : public Object{
	public:
		CameraObject(class GameEngine *InGameEngine):Object(this), mOwner(InGameEngine) {}
		void Update(float InDeltaTime) override;
		inline Matrix4x4 GetViewMatrix() const;
		Matrix4x4 GetViewMatrixTowardObject(class GameObject*) const;
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

HO::Matrix4x4 HO::CameraObject::GetViewMatrix() const {
	return Transform::Yaw180Rotation * mTransformComponent.GetInverseRotationMatrix() * mTransformComponent.GetTranslationMatrix();
}

HO::Vector3 HO::CameraObject::GetForwardVector() const {
	return (GetViewMatrix() * Vector4::UnitZ).ToVector3() * -1.f;
}