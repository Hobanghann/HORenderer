#pragma once

namespace HO {
	class RenderingPipeline {
	public:

		enum RenderingMode : int {
			eWireFrameMode = 0b0001,
			eBackfaceCullingMode = 0b0010,
			eDepthTestingMode = 0b100
		};

	public:
		RenderingPipeline(class GameEngine* InGameEngine) :mOwner(InGameEngine) {}

		inline Vertex VertexShader(const Vertex& InVertex, const Matrix4x4& InPVMMatrix);
		inline Vertex PerspectiveDivide(const Vertex& InVertex) const;		
		inline Vector2 DenormalizeNDC(const Vertex& InVertex, unsigned InWindowWidth, unsigned InWindowHeight) const;
		inline Vector2 Rasterize(const Vertex& InVertex, unsigned InWindowWidth, unsigned InWindowHeight) const;
		
		void DrawLine(const Vector2& InStartPoint, const Vector2& InEndPoint) const;
		void DrawTriangle(const std::vector<Vertex>& InVertexBuffer, Mesh::Triangle InTriangle, RenderingMode InMode) const;
		
		void FillTriangle(const std::vector<Vertex>& InVertexBuffer, const Mesh::Triangle& InTriangle) const;
		inline bool IsInTriangle(const std::vector<Vertex>& InVertexBuffer, const Mesh::Triangle& InTriangle, const Vector2& InPixel, float InDenominator) const;
		inline Vector3 GetBarycentricCoordinate(const std::vector<Vertex>& InVertexBuffer, const Mesh::Triangle& InTriangle, const Vector2& InPixel, float InDenominator) const;

		inline Vector3 GetBarycentricCoordinate(const std::vector<Vertex>& InVertexBuffer, const Mesh::Triangle& InTriangle, const Vector2& InPixel) const;		
		inline bool IsInTriangle(const std::vector<Vertex>& InVertexBuffer, const Mesh::Triangle& InTriangle, const Vector2& InPixel) const;		
		
		inline bool IsBackface(const std::vector<Vertex>& InVertexBuffer, const Mesh::Triangle& InTriangle, const Vector3 &InCameraForward) const;

		void SetRenderingColor(const std::string) const;
	private:
		class GameEngine* mOwner;
	};
}



HO::Vertex HO::RenderingPipeline::VertexShader(const Vertex& InVertex, const Matrix4x4& InPVMMatrix){
	return Vertex(InPVMMatrix * InVertex.GetPoint());
}


HO::Vertex HO::RenderingPipeline::PerspectiveDivide(const Vertex& InVertex) const {
	Vector4 InVector = InVertex.GetPoint();
	float InvW = 1.f / InVector.W;
	return Vertex(Vector4(InVector.X * InvW, InVector.Y * InvW, InVector.Z * InvW, InVector.W));
}


HO::Vector2 HO::RenderingPipeline::DenormalizeNDC(const Vertex& InVertex, unsigned InWindowWidth, unsigned InWindowHeight) const {
	return Vector2(InVertex.GetPoint().X * (InWindowWidth * 0.5f), InVertex.GetPoint().Y * (InWindowHeight * 0.5f));
}


HO::Vector2 HO::RenderingPipeline::Rasterize(const Vertex& InVertex, unsigned InWindowWidth, unsigned InWindowHeight) const {
	return Vector2(InVertex.GetPixel().X + (InWindowWidth * 0.5f), -InVertex.GetPixel().Y + (InWindowHeight * 0.5f));
}


HO::Vector3 HO::RenderingPipeline::GetBarycentricCoordinate(const std::vector<Vertex>& InVertexBuffer, const Mesh::Triangle& InTriangle, const Vector2& InPixel) const {
	Vector2 toP1 = InVertexBuffer[InTriangle.Index1].GetPixel() - InVertexBuffer[InTriangle.Index3].GetPixel(); //Vector 'a'
	Vector2 toP2 = InVertexBuffer[InTriangle.Index2].GetPixel() - InVertexBuffer[InTriangle.Index3].GetPixel(); //Vector 'b'
	Vector2 toInP = InPixel - InVertexBuffer[InTriangle.Index3].GetPixel(); //Vector 'c'

	Vector2& a = toP1;
	Vector2& b = toP2;
	Vector2& c = toInP;
	
	float aDotb = a.Dot(b);
	float aDota = a.Dot(a);
	float bDotb = b.Dot(b);
	float cDotb = c.Dot(b);
	float cDota = c.Dot(a);

	float denominator = (aDotb * aDotb) - (aDota * bDotb);

	if (denominator == 0.f) {
		SDL_Log("Degenerate triangle\n");
		return Vector3::ZERO;
	}

	float InvDenominator = 1.f / denominator;
	
	float scalarOfP1 = ((cDotb * aDotb) - (cDota * bDotb)) * InvDenominator;
	float scalarOfP2 = ((cDota * aDotb) - (cDotb * aDota)) * InvDenominator;
	return Vector3(scalarOfP1, scalarOfP2, 1.f - scalarOfP1 - scalarOfP2);
}


HO::Vector3 HO::RenderingPipeline::GetBarycentricCoordinate(const std::vector<Vertex>& InVertexBuffer, const Mesh::Triangle& InTriangle, const Vector2& InPixel, float InDenominator) const {
	if (InDenominator == 0.f) {
		SDL_Log("Degenerate triangle\n");
		return Vector3::ZERO;
	}
	Vector2 toP1 = InVertexBuffer[InTriangle.Index1].GetPixel() - InVertexBuffer[InTriangle.Index3].GetPixel(); //Vector 'a'
	Vector2 toP2 = InVertexBuffer[InTriangle.Index2].GetPixel() - InVertexBuffer[InTriangle.Index3].GetPixel(); //Vector 'b'
	Vector2 toInP = InPixel - InVertexBuffer[InTriangle.Index3].GetPixel(); //Vector 'c'

	Vector2& a = toP1;
	Vector2& b = toP2;
	Vector2& c = toInP;

	float aDotb = a.Dot(b);
	float aDota = a.Dot(a);
	float bDotb = b.Dot(b);
	float cDotb = c.Dot(b);
	float cDota = c.Dot(a);

	float InvDenominator = 1.f / InDenominator;

	float scalarOfP1 = ((cDotb * aDotb) - (cDota * bDotb)) * InvDenominator;
	float scalarOfP2 = ((cDota * aDotb) - (cDotb * aDota)) * InvDenominator;
	return Vector3(scalarOfP1, scalarOfP2, 1.f - scalarOfP1 - scalarOfP2);
}

bool HO::RenderingPipeline::IsInTriangle(const std::vector<Vertex>& InVertexBuffer, const Mesh::Triangle& InTriangle, const Vector2& InPixel, float InDenominator) const {
	if (InDenominator == 0.f) {
		return false;
	}
	Vector3 barycentricCoordinate = GetBarycentricCoordinate(InVertexBuffer, InTriangle, InPixel, InDenominator);

	Vector3& b = barycentricCoordinate;

	if ((b.X > 0.f && b.X < 1.f) && (b.Y > 0.f && b.Y < 1.f) && (b.Z > 0.f && b.Z < 1.f)) {
		return true;
	}
	return false;
}

bool HO::RenderingPipeline::IsBackface(const std::vector<Vertex>& InVertexBuffer, const Mesh::Triangle& InTriangle, const Vector3 &InCameraForward) const {
	Vector3 toP2 = (InVertexBuffer[InTriangle.Index2].GetPoint() - InVertexBuffer[InTriangle.Index1].GetPoint()).ToVector3(); //Vector 'a'
	Vector3 toP3 = (InVertexBuffer[InTriangle.Index3].GetPoint() - InVertexBuffer[InTriangle.Index1].GetPoint()).ToVector3(); //Vector 'b'

	Vector3& a = toP2;
	Vector3& b = toP3;

	Vector3 normalVector = (a.Cross(b)) * -1.f;

	if (normalVector.Dot(InCameraForward) > 0) {
		return true;
	}
	return false;
}