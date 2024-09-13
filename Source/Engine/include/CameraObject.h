#pragma once

namespace HO {
	class CameraObject : public Object{
	public:
		CameraObject(class GameEngine *InGameEngine):
		Object(this), 
		mOwner(InGameEngine) {
			mFrustrum = new Frustrum(mFOV, mNearPlane, mFarPlane);
		}
		void Update(float InDeltaTime) override;
		inline Matrix4x4 GetViewMatrix() const;
		Matrix4x4 GetViewMatrixTowardObject(class GameObject*) const;

		Matrix4x4 GetProjectionMatrix() const;
		inline Vector3 GetForwardVector() const;

		inline const Frustrum *GetFrustrum() const;
	private:
		float mFOVSpeed = PI * 0.1f;
		float mFOV = PI / 3.f;
		float mNearPlane = 5.5f;
		float mFarPlane = 1000.f;
		class GameEngine* mOwner = nullptr;
		class Frustrum* mFrustrum = nullptr;
	};
}


//180rotation 추가하면 에러 발생 --> why?
HO::Matrix4x4 HO::CameraObject::GetViewMatrix() const {
	return Transform::Yaw180Rotation * mTransformComponent.GetInverseRotationMatrix() * mTransformComponent.GetInverseTranslationMatrix();
}

HO::Vector3 HO::CameraObject::GetForwardVector() const {
	return (GetViewMatrix() * Vector4::UnitZ).ToVector3() * -1.f;
}

const HO::Frustrum *HO::CameraObject::GetFrustrum() const{
	return mFrustrum;
}