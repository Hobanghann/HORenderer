#include "../../Main/include/Headers.h"

using namespace HO;

const Matrix4x4 Transform::Pitch180Rotation(
	Vector4(1.f, 0.f, 0.f, 0.f),
	Vector4(0.f, -1.f, 0.f, 0.f),
	Vector4(0.f, 0.f, -1.f, 0.f),
	Vector4::UnitW
);

const Matrix4x4 Transform::Yaw180Rotation(
	Vector4(-1.f, 0.f, 0.f, 0.f),
	Vector4(0.f, 1.f, 0.f, 0.f),
	Vector4(0.f, 0.f, -1.f, 0.f),
	Vector4::UnitW
);

const Matrix4x4 Transform::Roll180Rotation(
	Vector4(-1.f, 0.f, 0.f, 0.f),
	Vector4(0.f, -1.f, 0.f, 0.f),
	Vector4(0.f, 0.f, 1.f, 0.f),
	Vector4::UnitW
);

//class가 imcomplete type member를 가진 경우 해당 member는 pointer type을 가지도록 정의, 해당 member는 class 외부 소스에서 접근
//class 선언을 하지 않으니 GameObject class를 인식하지 못함.
