#pragma once

namespace HO {
	class Transform {
	public:
		Transform(class Object* InObject) :
			mOwner(InObject) {}

		Transform(class Object* InObject, const Vector3& InPosition, float InAngle, float InScale) :
			mOwner(InObject),
			mPosition(InPosition),
			mRollAngle(InAngle),
			mPitchAngle(InAngle),
			mYawAngle(InAngle),
			mScale(InScale) {}

		Transform(class Object* InObject, const Vector3& InPosition, float InRollAngle, float InPitchAngle, float InYawAngle, float InScale) :
			mOwner(InObject),
			mPosition(InPosition),
			mRollAngle(InRollAngle),
			mPitchAngle(InPitchAngle),
			mYawAngle(InYawAngle),
			mScale(InScale) {}


		inline Matrix4x4 GetModelingMatrix() const;

		inline Matrix4x4 GetScaleMatrix() const;

		inline Matrix4x4 GetRotationMatrix() const;
		inline Matrix4x4 GetRollMatrix() const;
		inline Matrix4x4 GetPitchMatrix() const;
		inline Matrix4x4 GetYawMatrix() const;

		inline Matrix4x4 GetTranslationMatrix() const;

		inline Matrix4x4 GetInverseScaleMatrix() const;
		inline Matrix4x4 GetInverseRotationMatrix() const;
		inline Matrix4x4 GetInverseTranslationMatrix() const;

		inline Vector3 GetPosition() const;
		inline float GetRollAngle() const;
		inline float GetPitchAngle() const;
		inline float GetYawAngle() const;
		inline float GetScale() const;

		inline void SetPosition(const Vector3& InPosition);
		inline void SetRollAngle(float InAngle);
		inline void SetPitchAngle(float InAngle);
		inline void SetYawAngle(float InAngle);
		inline void SetScale(float InScale);

		inline void UpdatePositionZ(float InDeltaTime, float InInputStatus);
		inline void UpdateRollAngle(float InDeltaTime, float InInputStatus);
		inline void UpdatePitchAngle(float InDeltaTime, float InInputStatus);
		inline void UpdateYawAngle(float InDeltaTime, float InInputStatus);
		inline void UpdateScale(float InDeltaTime, float InInputStatus);

		inline Vector3 GetForwardVector() const;
		inline Vector3 GetRightVector() const;
		inline Vector3 GetUpVector() const;
	public:
		static const Matrix4x4 Pitch180Rotation;
		static const Matrix4x4 Yaw180Rotation;
		static const Matrix4x4 Roll180Rotation;
		class Object* mOwner = nullptr;

	private:
		Vector3 mPosition;
		float mRollAngle = 0.f;
		float mPitchAngle = 0.f;
		float mYawAngle = 0.f;
		float mScale = 1.f;

		float mMoveSpeed = 50.f;
		float mRotationSpeed = 3.f;
		float mScaleSpeed = 3.f;
	};
}

HO::Matrix4x4 HO::Transform::GetModelingMatrix() const {
	return GetTranslationMatrix() * GetRotationMatrix() * GetScaleMatrix();
}

HO::Matrix4x4 HO::Transform::GetScaleMatrix() const {
	return Matrix4x4(
		Vector4(mScale, 0.f, 0.f, 0.f),
		Vector4(0.f, mScale, 0.f, 0.f),
		Vector4(0.f, 0.f, mScale, 0.f),
		Vector4::UnitW
	);
}

HO::Matrix4x4 HO::Transform::GetRotationMatrix() const {
	return GetYawMatrix() * GetPitchMatrix() * GetRollMatrix();
}

HO::Matrix4x4 HO::Transform::GetRollMatrix() const {
	float Cos = cosf(mRollAngle), Sin = sinf(mRollAngle);
	return Matrix4x4(
		Vector4(Cos, Sin, 0.f, 0.f),
		Vector4(-Sin, Cos, 0.f, 0.f),
		Vector4::UnitZ,
		Vector4::UnitW
	);
}
HO::Matrix4x4 HO::Transform::GetPitchMatrix() const {
	float Cos = cosf(mPitchAngle), Sin = sinf(mPitchAngle);
	return Matrix4x4(
		Vector4::UnitX,
		Vector4(0.f, Cos, Sin, 0.f),
		Vector4(0.f, -Sin, Cos, 0.f),
		Vector4::UnitW
	);
}

//->디버깅 한 부분
HO::Matrix4x4 HO::Transform::GetYawMatrix() const {
	float Cos = cosf(mYawAngle), Sin = sinf(mYawAngle);
	return Matrix4x4(
		Vector4(Cos, 0.f, -Sin, 0.f),
		Vector4::UnitY,
		Vector4(Sin, 0.f, Cos, 0.f),
		Vector4::UnitW
	);
}

HO::Matrix4x4 HO::Transform::GetTranslationMatrix() const {
	return Matrix4x4(
		Vector4::UnitX,
		Vector4::UnitY,
		Vector4::UnitZ,
		mPosition
	);
}

HO::Matrix4x4 HO::Transform::GetInverseScaleMatrix() const {
	float InvScale = 1.f / mScale;
	return Matrix4x4(
		Vector4(InvScale, 0.f, 0.f, 0.f),
		Vector4(0.f, InvScale, 0.f, 0.f),
		Vector4(0.f, 0.f, InvScale, 0.f),
		Vector4::UnitW
	);
}

HO::Matrix4x4 HO::Transform::GetInverseRotationMatrix() const {
	return GetRotationMatrix().Transpose();
}

HO::Matrix4x4 HO::Transform::GetInverseTranslationMatrix() const {
	Vector4 newCol4(mPosition);
	newCol4 *= -1.f;
	newCol4.W = 1.f;
	return Matrix4x4(
		Vector4::UnitX,
		Vector4::UnitY,
		Vector4::UnitZ,
		newCol4
	);
}

HO::Vector3 HO::Transform::GetPosition() const {
	return mPosition;
}
float HO::Transform::GetRollAngle() const {
	return mRollAngle;
}
float HO::Transform::GetPitchAngle() const {
	return mPitchAngle;
}
float HO::Transform::GetYawAngle() const {
	return mYawAngle;
}
float HO::Transform::GetScale() const {
	return mScale;
}

void HO::Transform::SetPosition(const Vector3& InPosition) {
	mPosition = InPosition;
}
void HO::Transform::SetRollAngle(float InAngle) {
	mRollAngle = InAngle;
}
void HO::Transform::SetPitchAngle(float InAngle) {
	mPitchAngle = InAngle;
}
void HO::Transform::SetYawAngle(float InAngle) {
	mYawAngle = InAngle;
}
void HO::Transform::SetScale(float InScale) {
	mScale = InScale;
}

void HO::Transform::UpdatePositionZ(float InDeltaTime, float InInputStatus) {
	Vector3 currentPosition = mPosition;
	mPosition = Vector3(currentPosition.X, currentPosition.Y, currentPosition.Z + InDeltaTime * InInputStatus * mMoveSpeed);
}
void HO::Transform::UpdateRollAngle(float InDeltaTime, float InInputStatus) {
	mRollAngle += InInputStatus * mRotationSpeed * InDeltaTime;
}
void HO::Transform::UpdatePitchAngle(float InDeltaTime, float InInputStatus) {
	mPitchAngle += InInputStatus * mRotationSpeed * InDeltaTime;
}
void HO::Transform::UpdateYawAngle(float InDeltaTime, float InInputStatus) {
	mYawAngle += InInputStatus * mRotationSpeed * InDeltaTime;
}
void HO::Transform::UpdateScale(float InDeltaTime, float InInputStatus) {

}

HO::Vector3 HO::Transform::GetForwardVector() const {
	return GetRotationMatrix().ToMatrix3x3() * Vector3::UnitZ;
}
HO::Vector3 HO::Transform::GetRightVector() const {
	return GetRotationMatrix().ToMatrix3x3() * Vector3::UnitX;
}
HO::Vector3 HO::Transform::GetUpVector() const {
	return GetRotationMatrix().ToMatrix3x3() * Vector3::UnitY;
}