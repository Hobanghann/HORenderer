#pragma once

namespace HO{
    class Plane{
        public:
        Plane() = default;
        Plane(Vector3 InNormalVector, Vector3 InPoint, bool InIsTorawdOrigin): 
        mNormalVector(InNormalVector.GetNormalized()), 
        mPoint(InPoint), 
        mDValue(mNormalVector.Dot(mPoint)),
        mbIsTowardOrigin(InIsTorawdOrigin) {}

        inline float GetDistanceToOrigin() const;
        inline bool IsTowardOrigin() const;
        inline bool IsInPlane(const Vector3 &InPoint) const;

        private:
        Vector3 mNormalVector;
        Vector3 mPoint;
        float mDValue;
        bool mbIsTowardOrigin;
    };
}

float HO::Plane::GetDistanceToOrigin() const{
    return std::fabsf(mNormalVector.Dot(mPoint));
}

bool HO::Plane::IsTowardOrigin() const{
    return mbIsTowardOrigin;
}

bool HO::Plane::IsInPlane(const Vector3 &InPoint) const{
    float normalDotPoint = mNormalVector.Dot(InPoint);
    bool isIn;
    if(mbIsTowardOrigin){ 
        if(normalDotPoint >= mDValue){
            isIn = false;
        }
        else {
            isIn = true;
        }
    }
    else {
        if(normalDotPoint <= mDValue){
            isIn = true;
        }
        else {
            isIn = false;
        }
    }
    return isIn;
}
