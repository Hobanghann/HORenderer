#pragma once

namespace HO {
	class Vector3 {
	public:
		Vector3() {};
		Vector3(float InX, float InY, float InZ) :X(InX), Y(InY), Z(InZ) {};
		Vector3(const Vector2 &InVector) : X(InVector.X), Y(InVector.Y), Z(1.f) {}
		//multiplication with scalar
		inline Vector3 operator*(const float InScalar) const;
		inline Vector3& operator*=(const float InScalar);
		//sumation
		inline Vector3 operator+(const Vector3& InVector) const;
		inline Vector3& operator+=(const Vector3& InVector);
		inline Vector3 operator-(const Vector3& InVector) const;
		inline Vector3& operator-=(const Vector3& InVector);
		//dot product
		inline float Dot(const Vector3& InVector) const;
		//cross product
		inline Vector3 Cross(const Vector3& InVector) const;
		//magnitude
		inline float GetMagnitude() const;
		inline float GetSqrdMagnitude() const;
		//normalization
		inline void Normalize();
		inline Vector3 GetNormalized() const;
		inline Vector2 ToVector2() const;

	public:
		float X = 0.f;
		float Y = 0.f;
		float Z = 0.f;
		static const Vector3 UnitX;
		static const Vector3 UnitY;
		static const Vector3 UnitZ;
		static const Vector3 ZERO;
	};
}


//multiplication with scalar
HO::Vector3 HO::Vector3::operator*(const float InScalar) const {
	return Vector3(InScalar * X, InScalar * Y, InScalar * Z);
}
HO::Vector3& HO::Vector3::operator*=(const float InScalar) {
	X *= InScalar;
	Y *= InScalar;
	Z *= InScalar;
	return *this;
}
//sumation
HO::Vector3 HO::Vector3::operator+(const Vector3& InVector) const {
	return Vector3(X + InVector.X, Y + InVector.Y, Z + InVector.Z);
}
HO::Vector3& HO::Vector3::operator+=(const Vector3& InVector) {
	X += InVector.X;
	Y += InVector.Y;
	Z += InVector.Z;
	return *this;
}

HO::Vector3 HO::Vector3::operator-(const Vector3& InVector) const {
	return Vector3(X - InVector.X, Y - InVector.Y, Z - InVector.Z);
}
HO::Vector3& HO::Vector3::operator-=(const Vector3& InVector) {
	X -= InVector.X;
	Y -= InVector.Y;
	Z -= InVector.Z;
	return *this;
}
//dot product
float HO::Vector3::Dot(const Vector3& InVector) const {
	return X * InVector.X + Y * InVector.Y + Z * InVector.Z;
}
//cross product
HO::Vector3 HO::Vector3::Cross(const Vector3& InVector) const {
	return Vector3(
		Y * InVector.Z - Z * InVector.Y,
		Z * InVector.X - X * InVector.Z,
		X * InVector.Y - Y * InVector.X);
}
//magnitude
float HO::Vector3::GetMagnitude() const {
	return sqrtf(X * X + Y * Y + Z * Z);
}
float HO::Vector3::GetSqrdMagnitude() const {
	return X * X + Y * Y + Z * Z;
}
//normalization
void HO::Vector3::Normalize() {
	float Magnitude = GetMagnitude();
	X /= Magnitude;
	Y /= Magnitude;
	Z /= Magnitude;
}
HO::Vector3 HO::Vector3::GetNormalized() const {
	float InvMag = 1.f / GetMagnitude();
	return *this * InvMag;
}

inline HO::Vector2 HO::Vector3::ToVector2() const {
	return Vector2(X, Y);
}
