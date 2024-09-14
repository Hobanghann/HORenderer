#pragma once

namespace HO {
	class Plane {
	public:
		Plane() = default;
		Plane(Vector3 InNormalVector, Vector3 InPoint) :
			mNormalVector(InNormalVector.GetNormalized()),
			mPoint(InPoint),
			mDValue(mNormalVector.Dot(mPoint)) 
		{}

		inline bool IsInPlane(const Vector3& InPoint) const;

		Plane(Vector4 InCoefficient) :
			mNormalVector(-InCoefficient.X, -InCoefficient.Y, -InCoefficient.Z),
			mDValue(-InCoefficient.Z)
		{}

	private:
		Vector3 mNormalVector;
		Vector3 mPoint;
		float mDValue;
	};
}


bool HO::Plane::IsInPlane(const Vector3& InPoint) const {
	float normalDotPoint = mNormalVector.Dot(InPoint);
	bool isIn;
	if (normalDotPoint < mDValue) {
		isIn = true;
	}
	else {
		isIn = false;
	}

	return isIn;
}
