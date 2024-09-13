#pragma once

namespace HO{
    class Frustrum{
        public :
        enum PlanePosition{
            eUP,
            eDOWN,
            eLEFT,
            eRIGHT,
            eNEAR,
            eFAR
        };

        public:
            inline Frustrum(float InFOV, float InNearDistance, float InFarDistance);

            inline void UpdateFOV(float InFOV);

            inline void UpdateNearPlane(float InNearDistance);

            inline void UpdateFarPlane(float InFarDistance);

            //view space에서의 point를 검사
            inline bool IsInFrustrum(Vector3 InPoint) const;

        private:
            float mFOV = 0.f;
            float mNearDistance = 0.f;
            float mFarDistance = 0.f;

            std::vector<Plane> mPlanes;
    };
}

HO::Frustrum::Frustrum(float InFOV, float InNearDistance, float InFarDistance): 
mFOV(InFOV),
mNearDistance(InNearDistance),
mFarDistance(InFarDistance) {
    float cos = cosf(mFOV/2.f), sin(mFOV/2.f);
    //up plane
    mPlanes.push_back(Plane(Vector3(0.f, cos, sin), Vector3::ZERO));
    //down plane
    mPlanes.push_back(Plane(Vector3(0.f, -cos, sin), Vector3::ZERO));
    //left plane
    mPlanes.push_back(Plane(Vector3(-cos, 0.f, sin), Vector3::ZERO));
    //right plane
    mPlanes.push_back(Plane(Vector3(cos, 0.f, sin), Vector3::ZERO));
    //near plane
    mPlanes.push_back(Plane(Vector3(0.f, 0.f, -1.f), Vector3(0.f, 0.f, mNearDistance)));
    //far plane
    mPlanes.push_back(Plane(Vector3(0.f, 0.f, 1.f), Vector3(0.f, 0.f, mFarDistance)));
}

void HO::Frustrum::UpdateFOV(float InFOV){
    mFOV = InFOV;

    float cos = cosf(mFOV/2.f), sin(mFOV/2.f);
    mPlanes[eUP] = Plane(Vector3(0.f, cos, sin), Vector3::ZERO);
    mPlanes[eDOWN] =  Plane(Vector3(0.f, -cos, sin), Vector3::ZERO);
    mPlanes[eLEFT] = Plane(Vector3(-cos, 0.f, sin), Vector3::ZERO);
    mPlanes[eRIGHT] = Plane(Vector3(cos, 0.f, sin), Vector3::ZERO);
}

void HO::Frustrum::UpdateNearPlane(float InNearDistance){
    mNearDistance = InNearDistance;
    mPlanes[eNEAR] = Plane(Vector3(0.f, 0.f, -1.f), Vector3(0.f, 0.f, mNearDistance));
}

void HO::Frustrum::UpdateFarPlane(float InFarDistance){
    mFarDistance = InFarDistance;
    mPlanes[eFAR] = Plane(Vector3(0.f, 0.f, 1.f), Vector3(0.f, 0.f, mFarDistance));
}

bool HO::Frustrum::IsInFrustrum(Vector3 InPoint) const{
    for(const auto &plane : mPlanes){
        if(!plane.IsInPlane(InPoint)){
            return false;
        }
    }
    return true;
}