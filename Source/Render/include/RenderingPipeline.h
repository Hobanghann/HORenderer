#pragma once

namespace HO {
	class RenderingPipeline {
	public:
		enum RenderingMode {
			eWireFrame,
			eFill
		};
	public:
		RenderingPipeline(class GameEngine* InGameEngine) :mOwner(InGameEngine) {}

		inline Vector4 VertexShader(const Vertex& InVertex, const Matrix4x4& InPVMMatrix);
		inline Vector3 PerspectiveDivide(const Vector4& InVector) const;		
		inline Vector2 DenormalizeNDC(const Vector3& InNDC, unsigned InWindowWidth, unsigned InWindowHeight) const;
		inline Vector3 Rasterize(const Vector3& InPoint, unsigned InWindowWidth, unsigned InWindowHeight) const;
		
		void DrawLine(const Vector2& InStartPoint, const Vector2& InEndPoint) const;
		void DrawTriangle(const std::vector<Vector2>& InPixelBuffer, Mesh::Triangle InTriangle, RenderingMode InMode) const;

		inline Vector3 GetBarycentricCoordinate(const std::vector<Vector2>& InPixelBuffer, const Mesh::Triangle& InTriangle, const Vector2& InPixel) const;
		inline Vector3 GetBarycentricCoordinate(const std::vector<Vector2>& InPixelBuffer, const Mesh::Triangle& InTriangle, const Vector2& InPixel, float InDenominator) const;
		inline bool IsInTriangle(const std::vector<Vector2>& InPixelBuffer, const Mesh::Triangle& InTriangle, const Vector2& InPixel) const;
		inline bool IsInTriangle(const std::vector<Vector2>& InPixelBuffer, const Mesh::Triangle& InTriangle, const Vector2& InPixel, float InDenominator) const;
		void FillTriangle(const std::vector<Vector2>& InPixelBuffer, const Mesh::Triangle& InTriangle) const;

		inline bool IsBackface(const std::vector<Vector3>& InNDCBuffer, const Mesh::Triangle& InTriangle, const Vector3 &InCameraForward) const;
	private:
		class GameEngine* mOwner;
	};
}



HO::Vector4 HO::RenderingPipeline::VertexShader(const Vertex& InVertex, const Matrix4x4& InPVMMatrix){
	return InPVMMatrix * InVertex.GetPoint();
}

HO::Vector2 HO::RenderingPipeline::DenormalizeNDC(const Vector3& InNDC, unsigned InWindowWidth, unsigned InWindowHeight) const {
	return Vector2(InNDC.X * (InWindowWidth * 0.5f), InNDC.Y * (InWindowHeight * 0.5f));
}

HO::Vector3 HO::RenderingPipeline::Rasterize(const Vector3& InPoint, unsigned InWindowWidth, unsigned InWindowHeight) const {
	return Vector3(InPoint.X + (InWindowWidth * 0.5f), -InPoint.Y + (InWindowHeight * 0.5f), InPoint.Z);
}

HO::Vector3 HO::RenderingPipeline::PerspectiveDivide(const Vector4& InVector) const {
	return InVector.ToVector3();
}



HO::Vector3 HO::RenderingPipeline::GetBarycentricCoordinate(const std::vector<Vector2>& InPixelBuffer, const Mesh::Triangle& InTriangle, const Vector2& InPixel) const {
	Vector2 toP1 = InPixelBuffer[InTriangle.Index1] - InPixelBuffer[InTriangle.Index3]; //Vector 'a'
	Vector2 toP2 = InPixelBuffer[InTriangle.Index2] - InPixelBuffer[InTriangle.Index3]; //Vector 'b'
	Vector2 toInP = InPixel - InPixelBuffer[InTriangle.Index3]; //Vector 'c'

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

HO::Vector3 HO::RenderingPipeline::GetBarycentricCoordinate(const std::vector<Vector2>& InPixelBuffer, const Mesh::Triangle& InTriangle, const Vector2& InPixel, float InDenominator) const {
	if (InDenominator == 0.f) {
		SDL_Log("Degenerate triangle\n");
		return Vector3::ZERO;
	}
	Vector2 toP1 = InPixelBuffer[InTriangle.Index1] - InPixelBuffer[InTriangle.Index3]; //Vector 'a'
	Vector2 toP2 = InPixelBuffer[InTriangle.Index2] - InPixelBuffer[InTriangle.Index3]; //Vector 'b'
	Vector2 toInP = InPixel - InPixelBuffer[InTriangle.Index3]; //Vector 'c'

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

bool HO::RenderingPipeline::IsInTriangle(const std::vector<Vector2>& InPixelBuffer, const Mesh::Triangle& InTriangle, const Vector2& InPixel) const {
	Vector3 barycentricCoordinate = GetBarycentricCoordinate(InPixelBuffer, InTriangle, InPixel);

	Vector3& b = barycentricCoordinate;
	if (b.GetSqrdMagnitude() == 0.f) {
		SDL_Log("Degenerate triangle\n");
		return false;
	}
	

	if ((b.X > 0.f && b.X < 1.f) && (b.Y > 0.f && b.Y < 1.f) && (b.Z > 0.f && b.Z < 1.f)) {
		return true;
	}
	return false;
}

bool HO::RenderingPipeline::IsInTriangle(const std::vector<Vector2>& InPixelBuffer, const Mesh::Triangle& InTriangle, const Vector2& InPixel, float InDenominator) const {
	if (InDenominator == 0.f) {
		return false;
	}
	Vector3 barycentricCoordinate = GetBarycentricCoordinate(InPixelBuffer, InTriangle, InPixel, InDenominator);

	Vector3& b = barycentricCoordinate;

	if ((b.X > 0.f && b.X < 1.f) && (b.Y > 0.f && b.Y < 1.f) && (b.Z > 0.f && b.Z < 1.f)) {
		return true;
	}
	return false;
}

bool HO::RenderingPipeline::IsBackface(const std::vector<Vector3>& InNDCBuffer, const Mesh::Triangle& InTriangle, const Vector3 &InCameraForward) const {
	Vector3 toP2 = InNDCBuffer[InTriangle.Index2] - InNDCBuffer[InTriangle.Index1]; //Vector 'a'
	Vector3 toP3 = InNDCBuffer[InTriangle.Index3] - InNDCBuffer[InTriangle.Index1]; //Vector 'b'

	Vector3& a = toP2;
	Vector3& b = toP3;

	Vector3 normalVector = (a.Cross(b)) * -1.f;

	if (normalVector.Dot(InCameraForward) > 0) {
		return true;
	}
	return false;
}