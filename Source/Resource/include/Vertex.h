#pragma once

namespace HO {
	class Vertex {
	public:
		Vertex() = default;
		Vertex(const Vector3& InPoint) : mPoint(InPoint) {}
		Vertex(const Vector4& InPoint) :mPoint(InPoint) {}
		Vertex(const Vector4& InPoint, const Vector2& InUVCoordinate) :mPoint(InPoint), mUVCoordinate(InUVCoordinate) {}

		inline Vector4 GetPoint() const {
			return mPoint;
		}

		inline Vector2 GetUV() const {
			return mUVCoordinate;
		}

	private:
		const Vector4 mPoint;
		const Vector2 mUVCoordinate;
	};
}