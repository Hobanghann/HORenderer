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