#pragma once

namespace HO {
	class Vector4 {
	public:
		Vector4() {};
		Vector4(float InX, float InY, float InZ, float InW) :X(InX), Y(InY), Z(InZ), W(InW) {}
		Vector4(const Vector3 &InVector): X(InVector.X), Y(InVector.Y), Z(InVector.Z), W(1.f) {}
		//multiplication with scalar
		inline Vector4 operator*(const float InScalar) const;
		inline Vector4& operator*=(const float InScalar);
		//sumation
		inline Vector4 operator+(const Vector4& InVector) const;
		inline Vector4& operator+=(const Vector4& InVector);
		inline Vector4 operator-(const Vector4& InVector) const;
		inline Vector4& operator-=(const Vector4& InVector);
		//dot product
		inline float Dot(const Vector4& InVector) const;
		//magnitude
		inline float GetMagnitude() const;
		inline float GetSqrdMagnitude() const;
		//normalization
		inline void Normalize();
		inline Vector4 GetNormalized() const;
		inline Vector3 ToVector3() const;

	public:
		float X = 0.f;
		float Y = 0.f;
		float Z = 0.f;
		float W = 0.f;
		static const Vector4 UnitX;
		static const Vector4 UnitY;
		static const Vector4 UnitZ;
		static const Vector4 UnitW;
		static const Vector4 ZERO;
	private:
	};
}


//multiplication with scalar
HO::Vector4 HO::Vector4::operator*(const float InScalar) const {
	return Vector4(InScalar * X, InScalar * Y, InScalar * Z, InScalar * W);
}
HO::Vector4& HO::Vector4::operator*=(const float InScalar) {
	X *= InScalar;
	Y *= InScalar;
	Z *= InScalar;
	W *= InScalar;
	return *this;
}
//sumation
HO::Vector4 HO::Vector4::operator+(const Vector4& InVector) const {
	return Vector4(X + InVector.X, Y + InVector.Y, Z + InVector.Z, W + InVector.W);
}
HO::Vector4& HO::Vector4::operator+=(const Vector4& InVector) {
	X += InVector.X;
	Y += InVector.Y;
	Z += InVector.Z;
	W += InVector.W;
}

HO::Vector4 HO::Vector4::operator-(const Vector4& InVector) const {
	return Vector4(X - InVector.X, Y - InVector.Y, Z - InVector.Z, W - InVector.W);
}
HO::Vector4& HO::Vector4::operator-=(const Vector4& InVector) {
	X -= InVector.X;
	Y -= InVector.Y;
	Z -= InVector.Z;
	W -= InVector.W;
	return *this;
}
//dot product
float HO::Vector4::Dot(const Vector4& InVector) const {
	return X * InVector.X + Y * InVector.Y + Z * InVector.Z + W * InVector.W;
}
//magnitude
float HO::Vector4::GetMagnitude() const {
	return sqrtf(X * X + Y * Y + Z * Z + W * W);
}
float HO::Vector4::GetSqrdMagnitude() const {
	return X * X + Y * Y + Z * Z + W * W;
}
//normalization
void HO::Vector4::Normalize() {
	float Magnitude = this->GetMagnitude();
	X /= Magnitude;
	Y /= Magnitude;
	Y /= Magnitude;
	W /= Magnitude;
}
HO::Vector4 HO::Vector4::GetNormalized() const {
	float InvMag = 1.f / this->GetMagnitude();
	return *this * InvMag;
}

HO::Vector3 HO::Vector4::ToVector3() const {
	return Vector3(X / W, Y / W, Z / W);
}
