#include "../../Main/include/Headers.h"

using namespace HO;

bool Frustrum::IsInFrustrum(const SphereBoundingVolume &InSphere) const{
    for(const auto &plane : mPlanes){
        if(!plane.IsInPlane(InSphere)){
            return false;
        }
    }
    return true;
}

bool Frustrum::IsInFrustrum(const class BoxBoundingVolume &InBox) const{
    for(const Plane &plane : mPlanes){
        if(!plane.IsInPlane(InBox.GetNearPoint(plane), InBox.GetFarPoint(plane))){
            return false;
        }
    }
    return true;
}