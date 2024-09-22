#include "../../Main/include/Headers.h"

using namespace HO;

bool Plane::IsInPlane(const SphereBoundingVolume &InSphere) const{
    float normalDotCenter = mNormalVector.Dot(InSphere.GetCenter());
	bool isIn;
	if (normalDotCenter + mDValue < 0.f) {
		isIn = true;
	}
	else {
		if (std::fabsf(normalDotCenter + mDValue) < InSphere.GetRadious()) {
			isIn = true;
		}
		else {
			isIn = false;
		}
	}
	return isIn;
}