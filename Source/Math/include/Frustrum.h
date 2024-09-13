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
            inline Frustrum(float InFOV, int InWindowWidth, int InWindowHeight, float InNearDistance, float InFarDistance);

            inline void UpdateFOV(float InFOV);

            inline void UpdateNearPlane(float InNearDistance);

            inline void UpdateFarPlane(float InFarDistance);

            //view space에서의 point를 검사
            inline bool IsInFrustrum(Vector3 InPoint) const;

        private:
            float mFOV = 0.f;
            float mNearDistance = 0.f;
            float mFarDistance = 0.f;
            int mWindowWidth = 0;
            int mWindowHeight = 0;
            float mAspectRatio = 0.f;
            std::vector<Plane> mPlanes;
    };
}

HO::Frustrum::Frustrum(float InFOV, int InWindowWidth, int InWindowHeight, float InNearDistance, float InFarDistance):
mFOV(InFOV),
mNearDistance(InNearDistance),
mFarDistance(InFarDistance),
mWindowWidth(InWindowWidth),
mWindowHeight(InWindowHeight),
mAspectRatio(static_cast<float>(InWindowWidth) / static_cast<float>(InWindowHeight))
{   
    float upDownCos = cosf(mFOV * 0.5f * mAspectRatio), upDownSin = sinf(mFOV * 0.5f * mAspectRatio);
    float leftRightCos = cosf(mFOV * 0.5f), leftRightSin = sinf(mFOV * 0.5f);
    //up plane
    mPlanes.push_back(Plane(Vector3(0.f, upDownCos, upDownSin), Vector3::ZERO, false));
    //down plane
    mPlanes.push_back(Plane(Vector3(0.f, -upDownCos, upDownSin), Vector3::ZERO, false));
    //left plane
    mPlanes.push_back(Plane(Vector3(-leftRightCos, 0.f, leftRightSin), Vector3::ZERO, false));
    //right plane
    mPlanes.push_back(Plane(Vector3(leftRightCos, 0.f, leftRightSin), Vector3::ZERO, false));
    //near plane
    mPlanes.push_back(Plane(Vector3::UnitZ, Vector3(0.f, 0.f, -mNearDistance), true));
    //far plane
    mPlanes.push_back(Plane(-Vector3::UnitZ, Vector3(0.f, 0.f, -mFarDistance), false));
}

void HO::Frustrum::UpdateFOV(float InFOV){
    mFOV = InFOV;
    float upDownCos = cosf(mFOV * 0.5f * mAspectRatio), upDownSin = sinf(mFOV * 0.5f * mAspectRatio);
    float leftRightCos = cosf(mFOV * 0.5f), leftRightSin = sinf(mFOV * 0.5f);
    mPlanes[eUP] = Plane(Vector3(0.f, upDownCos, upDownSin), Vector3::ZERO, false);
    mPlanes[eDOWN] = Plane(Vector3(0.f, -upDownCos, upDownSin), Vector3::ZERO, false);
    mPlanes[eLEFT] = Plane(Vector3(-leftRightCos, 0.f, leftRightSin), Vector3::ZERO, false);
    mPlanes[eRIGHT] = Plane(Vector3(leftRightCos, 0.f, leftRightSin), Vector3::ZERO, false);
}

void HO::Frustrum::UpdateNearPlane(float InNearDistance){
    mNearDistance = InNearDistance;
    mPlanes[eNEAR] = Plane(Vector3::UnitZ, Vector3(0.f, 0.f, -mNearDistance), true);
}

void HO::Frustrum::UpdateFarPlane(float InFarDistance){
    mFarDistance = InFarDistance;
    mPlanes[eFAR] = Plane(-Vector3::UnitZ, Vector3(0.f, 0.f, -mFarDistance), false);
}

bool HO::Frustrum::IsInFrustrum(Vector3 InPoint) const{
    for(const auto &plane : mPlanes){
        if(!plane.IsInPlane(InPoint)){
            return false;
        }
    }
    return true;
}