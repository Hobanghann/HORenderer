#include "../../Main/include/Headers.h"

using namespace HO;

HO::SphereBoundingVolume::SphereBoundingVolume(Mesh *InMesh){
    std::vector<Vertex> vertexBuffer = InMesh->GetVertexBuffer();

    float numVertex = 0.f;
    Vector3 sumVector = Vector3::ZERO;

    for(auto vertex : vertexBuffer){
        sumVector += vertex.GetPoint().ToVector3();
        numVertex++;
    }

    float invNumVertex = 1.f / numVertex;
    mCenter = Vector3(sumVector.X * invNumVertex, sumVector.Y * invNumVertex, sumVector.Z * invNumVertex);

    float maxLength = 0.f;
    for(auto vertex : vertexBuffer){
        float sqrdLength = (vertex.GetPoint().ToVector3() - mCenter).GetSqrdMagnitude();
        if(maxLength < sqrdLength){
            maxLength = sqrdLength;
        }
    }
    mRadious = std::sqrtf(maxLength);
}