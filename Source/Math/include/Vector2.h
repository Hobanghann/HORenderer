#pragma once

namespace HO {
	class Vector2 {
	public:
		Vector2() {};
		Vector2(float InX, float InY) :X(InX), Y(InY) {};

		//multiplication with scalar
		inline Vector2 operator*(const float InScalar) const;
		inline Vector2& operator*=(const float InScalar);
		//sumation
		inline Vector2 operator+(const Vector2& InVector) const;
		inline Vector2& operator+=(const Vector2& InVector);
		inline Vector2 operator-(const Vector2& InVector) const;
		inline Vector2& operator-=(const Vector2& InVector);
		//comparison
		inline bool operator==(const Vector2& InVector) const;
		inline bool operator!=(const Vector2& InVector) const;
		inline bool operator>(const Vector2& InVector) const;
		inline bool operator>=(const Vector2& InVector) const;
		inline bool operator<(const Vector2& InVector) const;
		inline bool operator<=(const Vector2& InVector) const;
		//dot product
		inline float Dot(const Vector2& InVector) const;
		//cross product
		//magnitude
		inline float GetMagnitude() const;
		inline float GetSqrdMagnitude() const;
		//normalization
		inline void Normalize();
		inline Vector2 GetNormalized() const;

	public:
		static void OutMinMaxVector2(const Vector2& InVector1, const Vector2& InVector2, const Vector2& InVector3, Vector2& OutMinVector, Vector2& OutMaxVector);

	public:
		float X = 0.f;
		float Y = 0.f;
		static const Vector2 UnitX;
		static const Vector2 UnitY;
		static const Vector2 ZERO;
	private:
	};
}


HO::Vector2 HO::Vector2::operator*(const float scalar) const {
	return Vector2(X * scalar, Y * scalar);
}
HO::Vector2& HO::Vector2::operator*=(const float scalar) {
	X *= scalar;
	Y *= scalar;
	return *this;
}

HO::Vector2 HO::Vector2::operator+(const Vector2& vector) const {
	return Vector2(X + vector.X, Y + vector.Y);
}
HO::Vector2& HO::Vector2::operator+=(const Vector2& vector) {
	X += vector.X;
	Y += vector.Y;
	return *this;
}

HO::Vector2 HO::Vector2::operator-(const Vector2& InVector) const {
	return Vector2(X - InVector.X, Y - InVector.Y);
}
HO::Vector2& HO::Vector2::operator-=(const Vector2& InVector) {
	X -= InVector.X;
	Y -= InVector.Y;
	return *this;
}


bool HO::Vector2::operator==(const Vector2& InVector) const {
	if (MathFunctions::IsAlmostEqual(X, InVector.X) && MathFunctions::IsAlmostEqual(Y, InVector.Y)) {
		return true;
	}
	return false;
}
bool HO::Vector2::operator!=(const Vector2& InVector) const {
	if (*this == InVector) {
		return false;
	}
	return true;
}

bool HO::Vector2::operator>(const Vector2& InVector) const {
	if (X > InVector.X) {
		return true;
	}
	else if (MathFunctions::IsAlmostEqual(X, InVector.X)) {
		if (Y > InVector.Y) {
			return true;
		}
	}
	return false;
}
bool HO::Vector2::operator>=(const Vector2& InVector) const {
	if ((*this > InVector) || *this == InVector) {
		return true;
	}
	return false;
}

bool HO::Vector2::operator<(const Vector2& InVector) const {
	if ((*this > InVector) || (*this == InVector)) {
		return false;
	}
	return true;
}
bool HO::Vector2::operator<=(const Vector2& InVector) const {
	if ((*this < InVector) || (*this == InVector)) {
		return true;
	}
	return false;
}


float HO::Vector2::Dot(const Vector2& vector) const {
	return X * vector.X + Y * vector.Y;
}

float HO::Vector2::GetMagnitude() const {
	return sqrtf(X * X + Y * Y);
}
float HO::Vector2::GetSqrdMagnitude() const {
	return X * X + Y * Y;
}

void HO::Vector2::Normalize() {
	float Magnitude = GetMagnitude();
	X /= Magnitude;
	Y /= Magnitude;
}
HO::Vector2 HO::Vector2::GetNormalized() const {
	float InvMag = 1.f / GetMagnitude();
	return *this * InvMag;
}


