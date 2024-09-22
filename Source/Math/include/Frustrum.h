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

            inline Frustrum(Matrix4x4 InProjectionMatrix);

            inline void UpdatePlane(float InFOV);

            inline void UpdatePlane(Matrix4x4 InprojectionPlane);

            inline void UpdateNearPlane(float InNearDistance);

            inline void UpdateFarPlane(float InFarDistance);

            //view space에서의 point를 검사
            inline bool IsInFrustrum(Vector3 InPoint) const;

            bool IsInFrustrum(const class SphereBoundingVolume &) const;
        private:
            float mFOV = 0.f;
            float mNearDistance = 5.5f;
            float mFarDistance = 5000.f;
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
    mPlanes.push_back(Plane(Vector3(0.f, upDownCos, upDownSin), Vector3::ZERO));
    //down plane
    mPlanes.push_back(Plane(Vector3(0.f, -upDownCos, upDownSin), Vector3::ZERO));
    //left plane
    mPlanes.push_back(Plane(Vector3(-leftRightCos, 0.f, leftRightSin), Vector3::ZERO));
    //right plane
    mPlanes.push_back(Plane(Vector3(leftRightCos, 0.f, leftRightSin), Vector3::ZERO));
    //near plane
    mPlanes.push_back(Plane(Vector3::UnitZ, Vector3(0.f, 0.f, -mNearDistance)));
    //far plane
    mPlanes.push_back(Plane(-Vector3::UnitZ, Vector3(0.f, 0.f, -mFarDistance)));
    SDL_Log("left plane projection matrix frustrum\nNormal vector : %f, %f, %f, dvalue : %f", mPlanes[eLEFT].GetNormalVector().X, mPlanes[eLEFT].GetNormalVector().Y, mPlanes[eLEFT].GetNormalVector().Z, mPlanes[eLEFT].GetDValue());
    SDL_Log("near plane fov frustrum\nNormal vector : %f, %f, %f, dvalue : %f", mPlanes[eNEAR].GetNormalVector().X, mPlanes[eNEAR].GetNormalVector().Y, mPlanes[eNEAR].GetNormalVector().Z, mPlanes[eNEAR].GetDValue());
    SDL_Log("far plane fov frustrum\nNormal vector : %f, %f, %f, dvalue : %f", mPlanes[eFAR].GetNormalVector().X, mPlanes[eFAR].GetNormalVector().Y, mPlanes[eFAR].GetNormalVector().Z, mPlanes[eFAR].GetDValue());
}

HO::Frustrum::Frustrum(Matrix4x4 InProjectionMatrix) {
    //up plane
    mPlanes.push_back(Plane(-(InProjectionMatrix.GetRow4() - InProjectionMatrix.GetRow2())));
    //down plane
    mPlanes.push_back(Plane(-(InProjectionMatrix.GetRow4() + InProjectionMatrix.GetRow2())));    
    //left plane
    mPlanes.push_back(Plane(-(InProjectionMatrix.GetRow4() + InProjectionMatrix.GetRow1())));
    //right plane
    mPlanes.push_back(Plane(-(InProjectionMatrix.GetRow4() - InProjectionMatrix.GetRow1())));  
    //near plane
    mPlanes.push_back(Plane(-(InProjectionMatrix.GetRow4() + InProjectionMatrix.GetRow3())));
    //far plane
    mPlanes.push_back(Plane(-(InProjectionMatrix.GetRow4() - InProjectionMatrix.GetRow3())));
    SDL_Log("left plane projection matrix frustrum\nNormal vector : %f, %f, %f, dvalue : %f", mPlanes[eLEFT].GetNormalVector().X, mPlanes[eLEFT].GetNormalVector().Y, mPlanes[eLEFT].GetNormalVector().Z, mPlanes[eLEFT].GetDValue());
    SDL_Log("near plane projection matrix frustrum\nNormal vector : %f, %f, %f, dvalue : %f", mPlanes[eNEAR].GetNormalVector().X, mPlanes[eNEAR].GetNormalVector().Y, mPlanes[eNEAR].GetNormalVector().Z, mPlanes[eNEAR].GetDValue());
    SDL_Log("far plane projection matrix frustrum\nNormal vector : %f, %f, %f, dvalue : %f", mPlanes[eFAR].GetNormalVector().X, mPlanes[eFAR].GetNormalVector().Y, mPlanes[eFAR].GetNormalVector().Z, mPlanes[eFAR].GetDValue());
}

void HO::Frustrum::UpdatePlane(float InFOV){
    mFOV = InFOV;
    float upDownCos = cosf(mFOV * 0.5f * mAspectRatio), upDownSin = sinf(mFOV * 0.5f * mAspectRatio);
    float leftRightCos = cosf(mFOV * 0.5f), leftRightSin = sinf(mFOV * 0.5f);
    mPlanes[eUP] = Plane(Vector3(0.f, upDownCos, upDownSin), Vector3::ZERO);
    mPlanes[eDOWN] = Plane(Vector3(0.f, -upDownCos, upDownSin), Vector3::ZERO);
    mPlanes[eLEFT] = Plane(Vector3(-leftRightCos, 0.f, leftRightSin), Vector3::ZERO);
    mPlanes[eRIGHT] = Plane(Vector3(leftRightCos, 0.f, leftRightSin), Vector3::ZERO);
}

void HO::Frustrum::UpdatePlane(Matrix4x4 InProjectionMatrix) {
    mPlanes[eUP] = Plane(-(InProjectionMatrix.GetRow4() - InProjectionMatrix.GetRow2()));
    mPlanes[eDOWN] = Plane(-(InProjectionMatrix.GetRow4() + InProjectionMatrix.GetRow2()));
    mPlanes[eLEFT] = Plane(-(InProjectionMatrix.GetRow4() + InProjectionMatrix.GetRow1()));
    mPlanes[eRIGHT] = Plane(-(InProjectionMatrix.GetRow4() - InProjectionMatrix.GetRow1()));
}

void HO::Frustrum::UpdateNearPlane(float InNearDistance){
    mNearDistance = InNearDistance;
    mPlanes[eNEAR] = Plane(Vector3::UnitZ, Vector3(0.f, 0.f, -mNearDistance));
}

void HO::Frustrum::UpdateFarPlane(float InFarDistance){
    mFarDistance = InFarDistance;
    mPlanes[eFAR] = Plane(-Vector3::UnitZ, Vector3(0.f, 0.f, -mFarDistance));
}

bool HO::Frustrum::IsInFrustrum(Vector3 InPoint) const{
    for(const auto &plane : mPlanes){
        if(!plane.IsInPlane(InPoint)){
            return false;
        }
    }
    return true;
}