#pragma once

namespace HO {
	class Matrix4x4 {
	public:
		Matrix4x4() = default;
		Matrix4x4(const Vector4& InCol1, const Vector4& InCol2, const Vector4& InCol3, const Vector4& InCol4) : mCol1(InCol1), mCol2(InCol2), mCol3(InCol3), mCol4(InCol4) {}
		Matrix4x4(const Matrix3x3& InMatrix) :
			mCol1(InMatrix.mCol1.X, InMatrix.mCol1.Y, InMatrix.mCol1.Z, 0.f),
			mCol2(InMatrix.mCol2.X, InMatrix.mCol2.Y, InMatrix.mCol3.Z, 0.f),
			mCol3(InMatrix.mCol3.X, InMatrix.mCol3.Y, InMatrix.mCol3.Z, 0.f),
			mCol4(0.f, 0.f, 0.f, 1.f) {}
		Matrix4x4(const Matrix3x3& InMatrix, const Vector4 &InVector) :
			mCol1(InMatrix.mCol1.X, InMatrix.mCol1.Y, InMatrix.mCol1.Z, 0.f),
			mCol2(InMatrix.mCol2.X, InMatrix.mCol2.Y, InMatrix.mCol3.Z, 0.f),
			mCol3(InMatrix.mCol3.X, InMatrix.mCol3.Y, InMatrix.mCol3.Z, 0.f),
			mCol4(InVector) {}
		//sumation
		inline Matrix4x4 operator+(const Matrix4x4& InMatrix) const;
		inline Matrix4x4& operator+=(const Matrix4x4& InMatrix);
		//Scalar multiplication
		inline Matrix4x4 operator*(const float InScalar) const;
		inline Matrix4x4& operator*=(const float InScalar);
		//matrix multiplication
		inline Matrix4x4 operator*(const Matrix4x4& InMatrix) const;
		inline Matrix4x4& operator*=(const Matrix4x4& InMatrix);
		inline Vector4 operator*(const Vector4& InVector) const;
		inline Matrix4x4 Transpose() const;

		inline Matrix3x3 ToMatrix3x3() const;


		inline Vector4 GetCol1() const;
		inline Vector4 GetCol2() const;
		inline Vector4 GetCol3() const;
		inline Vector4 GetCol4() const;

		inline Vector4 GetRow1() const;
		inline Vector4 GetRow2() const;
		inline Vector4 GetRow3() const;
		inline Vector4 GetRow4() const;

	private:
		Vector4 mCol1;
		Vector4 mCol2;
		Vector4 mCol3;
		Vector4 mCol4;
	};
}


//sumation
HO::Matrix4x4 HO::Matrix4x4::operator+(const Matrix4x4& InMatrix) const {
	return HO::Matrix4x4(mCol1 + InMatrix.mCol1, mCol2 + InMatrix.mCol2, mCol3 + InMatrix.mCol3, mCol4 + InMatrix.mCol4);
}
HO::Matrix4x4& HO::Matrix4x4::operator+=(const Matrix4x4& InMatrix) {
	mCol1 += InMatrix.mCol1;
	mCol2 += InMatrix.mCol2;
	mCol3 += InMatrix.mCol3;
	mCol4 += InMatrix.mCol4;
}
//Scalar multiplication
HO::Matrix4x4 HO::Matrix4x4::operator*(const float InScalar) const {
	return Matrix4x4(mCol1 * InScalar, mCol2 * InScalar, mCol3 * InScalar, mCol4 * InScalar);
}
HO::Matrix4x4& HO::Matrix4x4::operator*=(const float InScalar) {
	mCol1 *= InScalar;
	mCol2 *= InScalar;
	mCol3 *= InScalar;
	mCol4 *= InScalar;
	*this;
}
//matrix multiplication
HO::Matrix4x4 HO::Matrix4x4::operator*(const Matrix4x4& InMatrix) const {
	Vector4 NewCol1(
		mCol1.X * InMatrix.mCol1.X + mCol2.X * InMatrix.mCol1.Y + mCol3.X * InMatrix.mCol1.Z + mCol4.X * InMatrix.mCol1.W,
		mCol1.Y * InMatrix.mCol1.X + mCol2.Y * InMatrix.mCol1.Y + mCol3.Y * InMatrix.mCol1.Z + mCol4.Y * InMatrix.mCol1.W,
		mCol1.Z * InMatrix.mCol1.X + mCol2.Z * InMatrix.mCol1.Y + mCol3.Z * InMatrix.mCol1.Z + mCol4.Z * InMatrix.mCol1.W,
		mCol1.W * InMatrix.mCol1.X + mCol2.W * InMatrix.mCol1.Y + mCol3.W * InMatrix.mCol1.Z + mCol4.W * InMatrix.mCol1.W);
	Vector4 NewCol2(
		mCol1.X * InMatrix.mCol2.X + mCol2.X * InMatrix.mCol2.Y + mCol3.X * InMatrix.mCol2.Z + mCol4.X * InMatrix.mCol2.W,
		mCol1.Y * InMatrix.mCol2.X + mCol2.Y * InMatrix.mCol2.Y + mCol3.Y * InMatrix.mCol2.Z + mCol4.Y * InMatrix.mCol2.W,
		mCol1.Z * InMatrix.mCol2.X + mCol2.Z * InMatrix.mCol2.Y + mCol3.Z * InMatrix.mCol2.Z + mCol4.Z * InMatrix.mCol2.W,
		mCol1.W * InMatrix.mCol2.X + mCol2.W * InMatrix.mCol2.Y + mCol3.W * InMatrix.mCol2.Z + mCol4.W * InMatrix.mCol2.W);
	Vector4 NewCol3(
		mCol1.X * InMatrix.mCol3.X + mCol2.X * InMatrix.mCol3.Y + mCol3.X * InMatrix.mCol3.Z + mCol4.X * InMatrix.mCol3.W,
		mCol1.Y * InMatrix.mCol3.X + mCol2.Y * InMatrix.mCol3.Y + mCol3.Y * InMatrix.mCol3.Z + mCol4.Y * InMatrix.mCol3.W,
		mCol1.Z * InMatrix.mCol3.X + mCol2.Z * InMatrix.mCol3.Y + mCol3.Z * InMatrix.mCol3.Z + mCol4.Z * InMatrix.mCol3.W,
		mCol1.W * InMatrix.mCol3.X + mCol2.W * InMatrix.mCol3.Y + mCol3.W * InMatrix.mCol3.Z + mCol4.W * InMatrix.mCol3.W);
	Vector4 NewCol4(
		mCol1.X * InMatrix.mCol4.X + mCol2.X * InMatrix.mCol4.Y + mCol3.X * InMatrix.mCol4.Z + mCol4.X * InMatrix.mCol4.W,
		mCol1.Y * InMatrix.mCol4.X + mCol2.Y * InMatrix.mCol4.Y + mCol3.Y * InMatrix.mCol4.Z + mCol4.Y * InMatrix.mCol4.W,
		mCol1.Z * InMatrix.mCol4.X + mCol2.Z * InMatrix.mCol4.Y + mCol3.Z * InMatrix.mCol4.Z + mCol4.Z * InMatrix.mCol4.W,
		mCol1.W * InMatrix.mCol4.X + mCol2.W * InMatrix.mCol4.Y + mCol3.W * InMatrix.mCol4.Z + mCol4.W * InMatrix.mCol4.W);
	return Matrix4x4(NewCol1, NewCol2, NewCol3, NewCol4);
}
HO::Matrix4x4& HO::Matrix4x4::operator*=(const Matrix4x4& InMatrix) {
	mCol1.X = mCol1.X * InMatrix.mCol1.X + mCol2.X * InMatrix.mCol1.Y + mCol3.X * InMatrix.mCol1.Z + mCol4.X * InMatrix.mCol1.W;
	mCol1.Y = mCol1.Y * InMatrix.mCol1.X + mCol2.Y * InMatrix.mCol1.Y + mCol3.Y * InMatrix.mCol1.Z + mCol4.Y * InMatrix.mCol1.W;
	mCol1.Z = mCol1.Z * InMatrix.mCol1.X + mCol2.Z * InMatrix.mCol1.Y + mCol3.Z * InMatrix.mCol1.Z + mCol4.Z * InMatrix.mCol1.W;
	mCol1.W = mCol1.W * InMatrix.mCol1.X + mCol2.W * InMatrix.mCol1.Y + mCol3.W * InMatrix.mCol1.Z + mCol4.W * InMatrix.mCol1.W;
	mCol2.X = mCol1.X * InMatrix.mCol2.X + mCol2.X * InMatrix.mCol2.Y + mCol3.X * InMatrix.mCol2.Z + mCol4.X * InMatrix.mCol2.W;
	mCol2.Y = mCol1.Y * InMatrix.mCol2.X + mCol2.Y * InMatrix.mCol2.Y + mCol3.Y * InMatrix.mCol2.Z + mCol4.Y * InMatrix.mCol2.W;
	mCol2.Z = mCol1.Z * InMatrix.mCol2.X + mCol2.Z * InMatrix.mCol2.Y + mCol3.Z * InMatrix.mCol2.Z + mCol4.Z * InMatrix.mCol2.W;
	mCol2.W = mCol1.W * InMatrix.mCol2.X + mCol2.W * InMatrix.mCol2.Y + mCol3.W * InMatrix.mCol2.Z + mCol4.W * InMatrix.mCol2.W;
	mCol3.X = mCol1.X * InMatrix.mCol3.X + mCol2.X * InMatrix.mCol3.Y + mCol3.X * InMatrix.mCol3.Z + mCol4.X * InMatrix.mCol3.W;
	mCol3.Y = mCol1.Y * InMatrix.mCol3.X + mCol2.Y * InMatrix.mCol3.Y + mCol3.Y * InMatrix.mCol3.Z + mCol4.Y * InMatrix.mCol3.W;
	mCol3.Z = mCol1.Z * InMatrix.mCol3.X + mCol2.Z * InMatrix.mCol3.Y + mCol3.Z * InMatrix.mCol3.Z + mCol4.Z * InMatrix.mCol3.W;
	mCol3.W = mCol1.W * InMatrix.mCol3.X + mCol2.W * InMatrix.mCol3.Y + mCol3.W * InMatrix.mCol3.Z + mCol4.W * InMatrix.mCol3.W;
	mCol4.X = mCol1.X * InMatrix.mCol4.X + mCol2.X * InMatrix.mCol4.Y + mCol3.X * InMatrix.mCol4.Z + mCol4.X * InMatrix.mCol4.W;
	mCol4.Y = mCol1.Y * InMatrix.mCol4.X + mCol2.Y * InMatrix.mCol4.Y + mCol3.Y * InMatrix.mCol4.Z + mCol4.Y * InMatrix.mCol4.W;
	mCol4.Z = mCol1.Z * InMatrix.mCol4.X + mCol2.Z * InMatrix.mCol4.Y + mCol3.Z * InMatrix.mCol4.Z + mCol4.Z * InMatrix.mCol4.W;
	mCol4.W = mCol1.W * InMatrix.mCol4.X + mCol2.W * InMatrix.mCol4.Y + mCol3.W * InMatrix.mCol4.Z + mCol4.W * InMatrix.mCol4.W;
	return *this;
}

HO::Vector4 HO::Matrix4x4::operator*(const Vector4& InVector) const {
	Vector4 Result;
	Result.X = mCol1.X * InVector.X + mCol2.X * InVector.Y + mCol3.X * InVector.Z + mCol4.X * InVector.W;
	Result.Y = mCol1.Y * InVector.X + mCol2.Y * InVector.Y + mCol3.Y * InVector.Z + mCol4.Y * InVector.W;
	Result.Z = mCol1.Z * InVector.X + mCol2.Z * InVector.Y + mCol3.Z * InVector.Z + mCol4.Z * InVector.W;
	Result.W = mCol1.W * InVector.X + mCol2.W * InVector.Y + mCol3.W * InVector.Z + mCol4.W * InVector.W;
	return Result;
}

HO::Matrix4x4 HO::Matrix4x4::Transpose() const {
	Vector4 NewCol1(mCol1.X, mCol2.X, mCol3.X, mCol4.X);
	Vector4 NewCol2(mCol1.Y, mCol2.Y, mCol3.Y, mCol4.Y);
	Vector4 NewCol3(mCol1.Z, mCol2.Z, mCol3.Z, mCol4.Z);
	Vector4 NewCol4(mCol1.W, mCol2.W, mCol3.W, mCol4.W);
	return Matrix4x4(NewCol1, NewCol2, NewCol3, NewCol4);
}

HO::Matrix3x3 HO::Matrix4x4::ToMatrix3x3() const {
	return Matrix3x3(
		Vector3(mCol1.X, mCol1.Y, mCol1.Z),
		Vector3(mCol2.X, mCol2.Y, mCol2.Z),
		Vector3(mCol3.X, mCol3.Y, mCol3.Z)
	);
}

HO::Vector4 HO::Matrix4x4::GetCol1() const {
	return mCol1;
}
HO::Vector4 HO::Matrix4x4::GetCol2() const {
	return mCol2;
}
HO::Vector4 HO::Matrix4x4::GetCol3() const {
	return mCol3;
}
HO::Vector4 HO::Matrix4x4::GetCol4() const {
	return mCol4;
}

HO::Vector4 HO::Matrix4x4::GetRow1() const {
	return Vector4(mCol1.X, mCol2.X, mCol3.X, mCol4.X);
}
HO::Vector4 HO::Matrix4x4::GetRow2() const {
	return Vector4(mCol1.Y, mCol2.Y, mCol3.Y, mCol4.Y);
}
HO::Vector4 HO::Matrix4x4::GetRow3() const {
	return Vector4(mCol1.Z, mCol2.Z, mCol3.Z, mCol4.Z);
}
HO::Vector4 HO::Matrix4x4::GetRow4() const {
	return Vector4(mCol1.W, mCol2.W, mCol3.W, mCol4.W);
}