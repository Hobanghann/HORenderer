#include "../../Main/include/Headers.h"

using namespace HO;

BoxBoundingVolume::BoxBoundingVolume(const Mesh *InMesh){
    Vector3 maxPoint = Vector3::ZERO;
    float infinity = std::numeric_limits<float>::infinity();
    Vector3 minPoint = Vector3(infinity, infinity, infinity);

    for(const Vertex vertex : InMesh->GetVertexBuffer()){
        Vector3 meshPoint = vertex.GetPoint().ToVector3();
        
        //update max
        if(maxPoint.X < meshPoint.X){
            maxPoint.X = meshPoint.X;
        }
        if(maxPoint.Y < meshPoint.Y){
            maxPoint.Y = meshPoint.Y;
        }
        if(maxPoint.Z < meshPoint.Z){
            maxPoint.Z = meshPoint.Z;
        }

        //update min
        if(minPoint.X > meshPoint.X){
            minPoint.X = meshPoint.X;
        }
        if(minPoint.Y > meshPoint.Y){
            minPoint.Y = meshPoint.Y;
        }
        if(minPoint.Z > meshPoint.Z){
            minPoint.Z = meshPoint.Z;
        }
    }

    mMaxPoint = maxPoint;
    mMinPoint = minPoint;
}
