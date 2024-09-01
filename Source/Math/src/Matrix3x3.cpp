#include "../../Main/include/Headers.h"

using namespace HO;

Matrix4x4 Matrix3x3::MakeAffineMatrix(const Vector4& InPosition) const {
	return Matrix4x4(
		Vector4(mCol1.X, mCol1.Y, mCol1.Z, 0.f),
		Vector4(mCol2.X, mCol2.Y, mCol2.Z, 0.f),
		Vector4(mCol3.X, mCol3.Y, mCol3.Z, 0.f),
		InPosition
	);
}