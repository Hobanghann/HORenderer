#pragma once
namespace HO {
	class Matrix2x2 {
		friend class Matrix3x3;
	public:
		Matrix2x2() = default;
		Matrix2x2(const Vector2& InCol1, const Vector2& InCol2) : mCol1(InCol1), mCol2(InCol2) {}
		//sumation
		inline Matrix2x2 operator+(const Matrix2x2& InMatrix) const;
		inline Matrix2x2& operator+=(const Matrix2x2& InMatrix);
		//Scalar multiplication
		inline Matrix2x2 operator*(const float InScalar) const;
		inline Matrix2x2& operator*=(const float InScalar);
		//matrix multiplication
		inline Matrix2x2 operator*(const Matrix2x2& InMatrix) const;
		inline Matrix2x2& operator*=(const Matrix2x2& InMatrix);
		inline Vector2 operator*(const Vector2& InVector) const;
		//Transpose
		inline Matrix2x2 Transpose() const;
	private:
		Vector2 mCol1;
		Vector2 mCol2;
	};
}


HO::Matrix2x2 HO::Matrix2x2::operator+(const Matrix2x2& InMatrix) const {
	return Matrix2x2(mCol1 + InMatrix.mCol1, mCol2 + InMatrix.mCol2);
}

HO::Matrix2x2& HO::Matrix2x2::operator+=(const Matrix2x2& InMatrix) {
	mCol1 += InMatrix.mCol1;
	mCol2 += InMatrix.mCol2;
	return *this;
}

HO::Matrix2x2 HO::Matrix2x2::operator*(const float InScalar) const {
	return Matrix2x2(mCol1 * InScalar, mCol2 * InScalar);
}

HO::Matrix2x2& HO::Matrix2x2::operator*=(const float InScalar) {
	mCol1 *= InScalar;
	mCol2 *= InScalar;
	return *this;
}


HO::Matrix2x2 HO::Matrix2x2::operator*(const Matrix2x2& InMatrix) const {
	Vector2 NewCol1(mCol1.X * InMatrix.mCol1.X + mCol2.X * InMatrix.mCol1.Y,
		mCol1.Y * InMatrix.mCol1.Y + mCol2.Y * InMatrix.mCol2.Y);
	Vector2 NewCol2(mCol1.Y * InMatrix.mCol1.X + mCol2.Y * InMatrix.mCol1.Y,
		mCol1.X * InMatrix.mCol1.Y + mCol2.X * InMatrix.mCol2.Y);
	return Matrix2x2(NewCol1, NewCol2);
}

HO::Matrix2x2& HO::Matrix2x2::operator*=(const Matrix2x2& InMatrix) {
	mCol1.X = mCol1.X * InMatrix.mCol1.X + mCol2.X * InMatrix.mCol1.Y;
	mCol1.Y = mCol1.Y * InMatrix.mCol1.Y + mCol2.Y * InMatrix.mCol2.Y;
	mCol2.X = mCol1.Y * InMatrix.mCol1.X + mCol2.Y * InMatrix.mCol1.Y;
	mCol2.Y = mCol1.X * InMatrix.mCol1.Y + mCol2.X * InMatrix.mCol2.Y;
	return *this;
}

HO::Vector2 HO::Matrix2x2::operator*(const Vector2& InVector) const {
	Vector2 Result;
	Result.X = mCol1.X * InVector.X + mCol2.X * InVector.Y;
	Result.Y = mCol1.Y * InVector.X + mCol2.Y * InVector.Y;
	return Result;
}

HO::Matrix2x2 HO::Matrix2x2::Transpose() const {
	Vector2 NewCol1(mCol1.X, mCol2.X);
	Vector2 NewCol2(mCol1.Y, mCol2.Y);
	return Matrix2x2(NewCol1, NewCol2);
}
