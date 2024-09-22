#include "../../Main/include/Headers.h"

using namespace HO;

Mesh::Mesh(const Mesh& InMesh) :
	mName(InMesh.mName),
	mVertexBuffer(InMesh.mVertexBuffer),
	mIndexBuffer(InMesh.mIndexBuffer),
	mSphereBoundingVolume(new SphereBoundingVolume(this)) {}

Mesh::Mesh(const std::string InName, const std::vector<Vertex> InVertices, const std::list<Triangle> InIndices) :
	mName(InName),
	mVertexBuffer(InVertices),
	mIndexBuffer(InIndices),
	mSphereBoundingVolume(new SphereBoundingVolume(this))
{}


const Mesh Mesh::BOX(
	"BOX_MESH",
	std::vector<Vertex>{
	Vector3(1.f, 1.f, 1.f),
		Vector3(1.f, 1.f, -1.f),
		Vector3(-1.f, 1.f, -1.f),
		Vector3(-1.f, 1.f, 1.f),
		Vector3(1.f, -1.f, 1.f),
		Vector3(1.f, -1.f, -1.f),
		Vector3(-1.f, -1.f, -1.f),
		Vector3(-1.f, -1.f, 1.f)
},
std::list<Mesh::Triangle>{
	{0, 1, 2},
	{ 2, 3, 0},
	{ 0, 4, 5},
	{ 5, 1, 0},
	{ 1, 5, 6},
	{ 6, 2, 1},
	{ 2, 6, 7},
	{ 7, 3, 2},
	{ 3, 7, 4},
	{ 4, 0, 3},
	{ 4, 6, 5},
	{ 6, 4, 7}
}
);

const SphereBoundingVolume *Mesh::GetSphereBoundingVolume() const {
	return mSphereBoundingVolume;
}