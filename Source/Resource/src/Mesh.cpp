#include "../../Main/include/Headers.h"

using namespace HO;

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
	{0, 1, 2, false},
	{ 2, 3, 0, false },
	{ 0, 4, 5, false },
	{ 5, 1, 0, false },
	{ 1, 5, 6, false },
	{ 6, 2, 1, false },
	{ 2, 6, 7, false },
	{ 7, 3, 2, false },
	{ 3, 7, 4, false },
	{ 4, 0, 3, false },
	{ 4, 6, 5, false },
	{ 6, 4, 7, false }
}
);