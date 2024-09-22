#pragma once

namespace HO{
    class BoxBoundingVolume {
        public: 
            BoxBoundingVolume(const Mesh *InMesh);
            BoxBoundingVolume(const Mesh *InMesh, const Vector3 &InMaxPoint, const Vector3 &InMinPoint) :
            mOwner(InMesh),
            mMaxPoint(InMaxPoint),
            mMinPoint(InMinPoint)
            {}

            inline Vector3 GetNearPoint(const Plane &InPlane) const;
            inline Vector3 GetFarPoint(const Plane &InPlane) const;
            inline BoxBoundingVolume GetBoundingVolumeInViewSpace(const Matrix4x4 &InVMMatrix) const;
        private:
            Vector3 mMaxPoint = Vector3::ZERO;
            Vector3 mMinPoint = Vector3::ZERO;
            const Mesh *mOwner = nullptr; 
    };
}

HO::Vector3 HO::BoxBoundingVolume::GetNearPoint(const Plane &InPlane) const{
    Vector3 nearPoint;
    Vector3 planeNormalVector = InPlane.GetNormalVector();

    if(planeNormalVector.X < 0){
        nearPoint.X = mMaxPoint.X;
    }
    else {
        nearPoint.X = mMinPoint.X;
    }

    if(planeNormalVector.Y < 0){
        nearPoint.Y = mMaxPoint.Y;
    }
    else {
        nearPoint.Y = mMinPoint.Y;
    }

    if(planeNormalVector.Z < 0){
        nearPoint.Z = mMaxPoint.Z;
    }
    else {
        nearPoint.Z = mMinPoint.Z;
    }

    return nearPoint;
}

HO::Vector3 HO::BoxBoundingVolume::GetFarPoint(const Plane &InPlane) const{
    Vector3 farPoint;
    Vector3 planeNormalVector = InPlane.GetNormalVector();

    if(planeNormalVector.X > 0){
        farPoint.X = mMaxPoint.X;
    }
    else {
        farPoint.X = mMinPoint.X;
    }

    if(planeNormalVector.Y > 0){
        farPoint.Y = mMaxPoint.Y;
    }
    else {
        farPoint.Y = mMinPoint.Y;
    }

    if(planeNormalVector.Z > 0){
        farPoint.Z = mMaxPoint.Z;
    }
    else {
        farPoint.Z = mMinPoint.Z;
    }

    return farPoint;
}

HO::BoxBoundingVolume HO::BoxBoundingVolume::GetBoundingVolumeInViewSpace(const Matrix4x4 &InVMMatrix) const{
    return BoxBoundingVolume(mOwner, (InVMMatrix * mMaxPoint).ToVector3(), (InVMMatrix * mMinPoint).ToVector3());
}