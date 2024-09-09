#pragma once

namespace HO {
	class Vertex {
	public:
		enum VertexPosition{
			InLocalSpace,
			InWorldSpace,
			InViewSpace,
			InClipSpace,
			InScreenSpace
		};

	public:
		Vertex() = default;
		Vertex(const Vector3& InPoint) : mPoint(InPoint) {}
		Vertex(const Vector4& InPoint) :mPoint(InPoint) {}
		Vertex(const Vector4& InPoint, const Vector2& InUVCoordinate) :mPoint(InPoint), mUVCoordinate(InUVCoordinate) {}

		inline Vector2 GetUV() const {
			return mUVCoordinate;
		}
		
		
		inline void SetPoint(const Vector4 &InPoint);
		inline Vector4 GetPoint() const;		

		inline void SetPixel(const Vector2 &InPixel);
		inline Vector2 GetPixel() const;		
		
		inline VertexPosition SetVertexPosition(VertexPosition);
		
	private:
		Vector4 mPoint;
		Vector2 mPixel;
		Vector2 mUVCoordinate;
		VertexPosition mVertexPosition;
	};
}

void HO::Vertex::SetPoint(const Vector4 &InPoint){
	mPoint = InPoint;
}
HO::Vector4 HO::Vertex::GetPoint() const{
	return mPoint;
}

void HO::Vertex::SetPixel(const Vector2 &InPixel){
	mPixel = InPixel;
}
HO::Vector2 HO::Vertex::GetPixel() const{
	return mPixel;
}		

HO::Vertex::VertexPosition HO::Vertex::SetVertexPosition(VertexPosition InPosition){
			if(InPosition > InScreenSpace){
				SDL_Log("Wrong vertex position\n");
			}
			mVertexPosition = InPosition;
		}