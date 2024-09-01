#pragma once

namespace HO {
	class Mesh {

	public:
		struct Triangle {
			size_t Index1;
			size_t Index2;
			size_t Index3;
			bool IsBackface;
		};

	public:
		Mesh() = default;
		Mesh(const Mesh &InMesh): mName(InMesh.mName), mVertexBuffer(InMesh.mVertexBuffer), mIndexBuffer(InMesh.mIndexBuffer) {}
		Mesh(const std::string InName, const std::vector<Vertex> InVertices, const std::list<Triangle> InIndices) :mName(InName), mVertexBuffer(InVertices), mIndexBuffer(InIndices) {}

		inline std::string GetName() const;
		inline const std::vector<Vertex> &GetVertexBuffer() const;
		inline const std::list<Triangle> GetIndexBuffer() const;

	public:
		static const Mesh BOX;

	private:
		const std::string mName;
		const std::vector<Vertex> mVertexBuffer;
		const std::list<Triangle> mIndexBuffer;
	};
}


std::string HO::Mesh::GetName() const {
	return mName;
}
const std::vector<HO::Vertex> &HO::Mesh::GetVertexBuffer() const {
	return mVertexBuffer;
}
const std::list<HO::Mesh::Triangle> HO::Mesh::GetIndexBuffer() const {
	return mIndexBuffer;
}