#pragma once

namespace HO{
    class SphereBoundingVolume{
        public:
            SphereBoundingVolume(class Mesh *InMesh);

            SphereBoundingVolume(float InRadious, Vector3 InCenter):
            mRadious(InRadious),
            mCenter(InCenter)
            {}

            inline SphereBoundingVolume GetBuondingVolumeInViewSpace(const Matrix4x4 InVMMatrix) const;

            inline float GetRadious() const;
            inline Vector3 GetCenter() const;
        private:
            float mRadious = 0.f;
            Vector3 mCenter = Vector3::ZERO;            
    };
}

HO::SphereBoundingVolume HO::SphereBoundingVolume::GetBuondingVolumeInViewSpace(const Matrix4x4 InVMMatrix) const{
    return SphereBoundingVolume(mRadious * 100.f, (InVMMatrix * Vector4(mCenter)).ToVector3());
}
float HO::SphereBoundingVolume::GetRadious() const{
    return mRadious;
}
HO::Vector3 HO::SphereBoundingVolume::GetCenter() const{
    return mCenter;
}