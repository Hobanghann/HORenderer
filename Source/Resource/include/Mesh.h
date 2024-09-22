#pragma once

namespace HO {
	class Mesh {

	public:
		struct Triangle {
			size_t Index1;
			size_t Index2;
			size_t Index3;
		};

	public:
		Mesh() = default;
		Mesh(const Mesh& InMesh);
		Mesh(const std::string InName, const std::vector<Vertex> InVertices, const std::list<Triangle> InIndices);

		inline std::string GetName() const;
		inline std::vector<Vertex> GetVertexBuffer() const;
		inline const std::list<Triangle> GetIndexBuffer() const;
		const SphereBoundingVolume *GetSphereBoundingVolume() const;
		const BoxBoundingVolume *GetBoxBoundingVolume() const;
	public:
		static const Mesh BOX;

	private:
		const std::string mName;
		std::vector<Vertex> mVertexBuffer;
		const std::list<Triangle> mIndexBuffer;

		const SphereBoundingVolume *mSphereBoundingVolume;
		const BoxBoundingVolume *mBoxBoundingVolume;
	};
}


std::string HO::Mesh::GetName() const {
	return mName;
}
std::vector<HO::Vertex> HO::Mesh::GetVertexBuffer() const {
	return mVertexBuffer;
}
const std::list<HO::Mesh::Triangle> HO::Mesh::GetIndexBuffer() const {
	return mIndexBuffer;
}