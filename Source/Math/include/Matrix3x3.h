#pragma once

namespace HO {
	
	class Matrix3x3 {
		friend class Matrix4x4;
	public:
		Matrix3x3() = default;
		Matrix3x3(const Vector3& InCol1, const Vector3& InCol2, const Vector3& InCol3) : mCol1(InCol1), mCol2(InCol2), mCol3(InCol3) {}
		Matrix3x3(const Matrix2x2& InMatrix) :
			mCol1(InMatrix.mCol1.X, InMatrix.mCol1.Y, 0.f),
			mCol2(InMatrix.mCol2.X, InMatrix.mCol2.Y, 0.f),
			mCol3(0.f, 0.f, 1.f) {}
		Matrix3x3(const Matrix2x2& InMatrix, const Vector3 &InVector) :
			mCol1(InMatrix.mCol1.X, InMatrix.mCol1.Y, 0.f),
			mCol2(InMatrix.mCol2.X, InMatrix.mCol2.Y, 0.f),
			mCol3(InVector) {}
		//sumation
		inline Matrix3x3 operator+(const Matrix3x3& InMatrix) const;
		inline Matrix3x3& operator+=(const Matrix3x3& InMatrix);
		//Scalar multiplication
		inline Matrix3x3 operator*(const float InScalar) const;
		inline Matrix3x3& operator*=(const float InScalar);
		//matrix multiplication
		inline Matrix3x3 operator*(const Matrix3x3& InMatrix) const;
		inline Matrix3x3& operator*=(const Matrix3x3& InMatrix);
		inline Vector3 operator*(const Vector3& InVector) const;
		inline Matrix3x3 Transpose() const;

		class Matrix4x4 MakeAffineMatrix(const Vector4& InPosition) const;
	private:
		Vector3 mCol1;
		Vector3 mCol2;
		Vector3 mCol3;
	};
}


HO::Matrix3x3 HO::Matrix3x3::operator+(const Matrix3x3& InMatrix) const {
	return Matrix3x3(mCol1 + InMatrix.mCol1, mCol2 + InMatrix.mCol2, mCol3 + InMatrix.mCol3);
}

HO::Matrix3x3& HO::Matrix3x3::operator+=(const Matrix3x3& InMatrix) {
	mCol1 += InMatrix.mCol1;
	mCol2 += InMatrix.mCol2;
	mCol3 += InMatrix.mCol3;
	return *this;
}

//Scalar multiplication
HO::Matrix3x3 HO::Matrix3x3::operator*(const float InScalar) const {
	return Matrix3x3(mCol1 * InScalar, mCol2 * InScalar, mCol3 * InScalar);
}
HO::Matrix3x3& HO::Matrix3x3::operator*=(const float InScalar) {
	mCol1 *= InScalar;
	mCol2 *= InScalar;
	mCol3 *= InScalar;
	return *this;
}
//matrix multiplication
HO::Matrix3x3 HO::Matrix3x3::operator*(const Matrix3x3& InMatrix) const {
	Vector3 NewCol1(
		mCol1.X * InMatrix.mCol1.X + mCol2.X * InMatrix.mCol1.Y + mCol3.X * InMatrix.mCol1.Z,
		mCol1.Y * InMatrix.mCol1.X + mCol2.Y * InMatrix.mCol1.Y + mCol3.Y * InMatrix.mCol1.Z,
		mCol1.Z * InMatrix.mCol1.X + mCol2.Z * InMatrix.mCol1.Y + mCol3.Z * InMatrix.mCol1.Z);
	Vector3 NewCol2(
		mCol1.X * InMatrix.mCol2.X + mCol2.X * InMatrix.mCol2.Y + mCol3.X * InMatrix.mCol2.Z,
		mCol1.Y * InMatrix.mCol2.X + mCol2.Y * InMatrix.mCol2.Y + mCol3.Y * InMatrix.mCol2.Z,
		mCol1.Z * InMatrix.mCol2.X + mCol2.Z * InMatrix.mCol2.Y + mCol2.Z * InMatrix.mCol2.Z);
	Vector3 NewCol3(
		mCol1.X * InMatrix.mCol3.X + mCol2.X * InMatrix.mCol3.Y + mCol3.X * InMatrix.mCol3.Z,
		mCol1.Y * InMatrix.mCol3.X + mCol2.Y * InMatrix.mCol3.Y + mCol3.Y * InMatrix.mCol3.Z,
		mCol1.Z * InMatrix.mCol3.X + mCol2.Z * InMatrix.mCol3.Y + mCol3.Z * InMatrix.mCol3.Z);
	return Matrix3x3(NewCol1, NewCol2, NewCol3);
}
HO::Matrix3x3& HO::Matrix3x3::operator*=(const Matrix3x3& InMatrix) {
	mCol1.X = mCol1.X * InMatrix.mCol1.X + mCol2.X * InMatrix.mCol1.Y + mCol3.X * InMatrix.mCol1.Z;
	mCol1.Y = mCol1.Y * InMatrix.mCol1.X + mCol2.Y * InMatrix.mCol1.Y + mCol3.Y * InMatrix.mCol1.Z;
	mCol1.Z = mCol1.Z * InMatrix.mCol1.X + mCol2.Z * InMatrix.mCol1.Y + mCol3.Z * InMatrix.mCol1.Z;
	mCol2.X = mCol1.X * InMatrix.mCol2.X + mCol2.X * InMatrix.mCol2.Y + mCol3.X * InMatrix.mCol2.Z;
	mCol2.Y = mCol1.Y * InMatrix.mCol2.X + mCol2.Y * InMatrix.mCol2.Y + mCol3.Y * InMatrix.mCol2.Z;
	mCol2.Z = mCol1.Z * InMatrix.mCol2.X + mCol2.Z * InMatrix.mCol2.Y + mCol2.Z * InMatrix.mCol2.Z;
	mCol3.X = mCol1.X * InMatrix.mCol3.X + mCol2.X * InMatrix.mCol3.Y + mCol3.X * InMatrix.mCol3.Z;
	mCol3.Y = mCol1.Y * InMatrix.mCol3.X + mCol2.Y * InMatrix.mCol3.Y + mCol3.Y * InMatrix.mCol3.Z;
	mCol3.Z = mCol1.Z * InMatrix.mCol3.X + mCol2.Z * InMatrix.mCol3.Y + mCol3.Z * InMatrix.mCol3.Z;
	return *this;
}

HO::Vector3 HO::Matrix3x3::operator*(const Vector3& InVector) const {
	Vector3 Result;
	Result.X = mCol1.X * InVector.X + mCol2.X * InVector.Y + mCol3.X * InVector.Z;
	Result.Y = mCol1.Y * InVector.X + mCol2.Y * InVector.Y + mCol3.Y * InVector.Z;
	Result.Z = mCol1.Z * InVector.X + mCol2.Z * InVector.Y + mCol3.Z * InVector.Z;
	return Result;
}

HO::Matrix3x3 HO::Matrix3x3::Transpose() const {
	Vector3 NewCol1(mCol1.X, mCol2.X, mCol3.X);
	Vector3 NewCol2(mCol1.Y, mCol2.Y, mCol3.Y);
	Vector3 NewCol3(mCol1.Z, mCol2.Y, mCol3.Z);
	return Matrix3x3(NewCol1, NewCol2, NewCol3);
}


