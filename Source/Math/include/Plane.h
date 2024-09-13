namespace HO{
    class Plane{
        public:
        Plane() = default;
        Plane(Vector3 InNormalVector, Vector3 InPoint): 
        mNormalVector(InNormalVector.GetNormalized()), 
        mPoint(InPoint), 
        mDValue(mNormalVector.Dot(mPoint)),
        mbIsTowardOrigin((mDValue > 0) ? false : true) {}

        inline float GetDistance() const;
        inline bool IsTowardOrigin() const;
        inline bool IsInPlane(const Vector3 &InPoint) const;

        private:
        Vector3 mNormalVector;
        Vector3 mPoint;
        float mDValue;
        bool mbIsTowardOrigin;
    };
}

float HO::Plane::GetDistance() const{
    return std::fabsf(mNormalVector.Dot(mPoint));
}

bool HO::Plane::IsTowardOrigin() const{
    return mbIsTowardOrigin;
}

bool HO::Plane::IsInPlane(const Vector3 &InPoint) const{
    float normalDotPoint = mNormalVector.Dot(InPoint);
    if(mbIsTowardOrigin){ 
        if(normalDotPoint > mDValue){
            return true;
        }
        else {
            return false;
        }
    }
    else {
        if(normalDotPoint < mDValue){
            return true;
        }
        else {
            return false;
        }
    }
}
