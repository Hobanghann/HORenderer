#pragma once

namespace HO {
	class Plane {
	public:
		Plane() = default;
		Plane(Vector3 InNormalVector, Vector3 InPoint) :
			mNormalVector(InNormalVector.GetNormalized()),
			mPoint(InPoint),
			mDValue(-mNormalVector.Dot(mPoint)) 
		{}

		Plane(Vector4 InCoefficient) :
			mNormalVector(Vector3(InCoefficient.X, InCoefficient.Y, InCoefficient.Z)),
			mDValue(InCoefficient.W)
		{
			Normalize();
		}

		inline bool IsInPlane(const Vector3& InPoint) const;

		bool IsInPlane(const class SphereBoundingVolume &) const;

		inline bool IsInPlane(const Vector3& InNearPoint, const Vector3 InFarPoint) const;

		inline Vector3 GetNormalVector() const;

		inline float GetDValue() const;
		
		inline void Normalize();

	private:
		Vector3 mNormalVector;
		Vector3 mPoint;
		float mDValue;
	};
}


bool HO::Plane::IsInPlane(const Vector3& InPoint) const {
	float normalDotPoint = mNormalVector.Dot(InPoint);
	bool isIn;
	if (normalDotPoint + mDValue > 0.f) {
		isIn = false;
	}
	else {
		isIn = true;
	}
	return isIn;
}

bool HO::Plane::IsInPlane(const Vector3& InNearPoint, const Vector3 InFarPoint) const{
	float normalDotNear = mNormalVector.Dot(InNearPoint);
	bool isIn;
	//outside
	if(normalDotNear + mDValue > 0.f){
		isIn = false;
	}
	else {
		float normalDotFar = mNormalVector.Dot(InFarPoint);
		//intersect
		if(normalDotFar + mDValue > 0.f){
			isIn = true;
		}
		//fully inside
		else {
			isIn = true;
		}
	}
	return isIn;
}

HO::Vector3 HO::Plane::GetNormalVector() const{
	return mNormalVector;
}

void HO::Plane::Normalize() {
	float normalVectorLength = mNormalVector.GetMagnitude();
	float invLength = 1.f / normalVectorLength;
	mNormalVector *= invLength;
	mDValue *= invLength;
}

float HO::Plane::GetDValue() const {
	return mDValue;
}