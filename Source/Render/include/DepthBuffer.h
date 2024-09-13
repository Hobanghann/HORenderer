#pragma once

namespace HO{
    class DepthBuffer{
        public:
            inline DepthBuffer(int InWindowWidth, int InWindowHeight);

            inline void ResetBuffer();
            inline bool IsDeeper(const Vector2 &InPixel, const float depth) const;
            inline float GetDepth(const std::vector<Vertex> &InVertexBuffer, const Mesh::Triangle &InTriangle, const Vector3 &InBarycentricCoordinate) const;
            inline void UpdateBuffer(const Vector2 &InPixel, const float depth);

        private:
            int mWindowWidth = 0;
            int mWindowHeight = 0;

            std::unique_ptr<std::unique_ptr<float[]>[]> mDepthBuffer = nullptr;
    };
}

HO::DepthBuffer::DepthBuffer(int InWindowWidth, int InWindowHeight): mWindowWidth(InWindowWidth), mWindowHeight(InWindowHeight){
    mDepthBuffer.reset(new std::unique_ptr<float[]>[mWindowHeight + 1]);
}

void HO::DepthBuffer::ResetBuffer(){
    for(int i = 0; i <= mWindowHeight; i++){
        mDepthBuffer[i].reset(new float[mWindowWidth + 1]);
        for(int j = 0; j <= mWindowWidth; j++){
            mDepthBuffer[i][j] = std::numeric_limits<float>::infinity();
        }
    }
}

//depth를 비교할때 오차값으로 인해 듬성듬성 빈틈 발생!! -> depth를 키워보자
bool HO::DepthBuffer::IsDeeper(const Vector2 &InPixel, const float depth) const{
    if (InPixel.X < 0 || InPixel.X > mWindowWidth) {
        return false;
    }
    else if (InPixel.Y < 0 || InPixel.Y > mWindowHeight) {
        return false;
    }
    else if(depth < 0){
        return false;
    }
    else if(mDepthBuffer[InPixel.Y][InPixel.X] < depth){
        return true;
    }
    else if(MathFunctions::IsAlmostEqual(mDepthBuffer[InPixel.Y][InPixel.X] , depth)){
        return true;
    }
    return false;
}

float HO::DepthBuffer::GetDepth(const std::vector<Vertex> &InVertexBuffer, const Mesh::Triangle &InTriangle, const Vector3 &InBarycentricCoordinate) const{
    const Vector3 &b = InBarycentricCoordinate;
    Vector3 p1 = InVertexBuffer[InTriangle.Index1].GetPoint().ToVector3();
    Vector3 p2 = InVertexBuffer[InTriangle.Index2].GetPoint().ToVector3();
    Vector3 p3 = InVertexBuffer[InTriangle.Index3].GetPoint().ToVector3();

    return b.X * p1.Z + b.Y * p2.Z + b.Z * p3.Z;
}

void HO::DepthBuffer::UpdateBuffer(const Vector2 &InPixel, const float depth){
    if (InPixel.X < 0 || InPixel.X > mWindowWidth) {
        return;
    }
    if (InPixel.Y < 0 || InPixel.Y > mWindowHeight) {
        return;
    }
    mDepthBuffer[InPixel.Y][InPixel.X] = depth;
}

