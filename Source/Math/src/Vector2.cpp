#include "../../Main/include/Headers.h"

using namespace HO;

const Vector2 Vector2::UnitX = Vector2(1.f, 0.f);
const Vector2 Vector2::UnitY = Vector2(0.f, 1.f);
const Vector2 Vector2::ZERO = Vector2(0.f, 0.f); 

void Vector2::OutMinMaxVector2(const Vector2& InVector1, const Vector2& InVector2, const Vector2& InVector3, Vector2& OutMinVector, Vector2& OutMaxVector) {
	if (InVector1 < InVector2) {
		if (InVector2 < InVector3) {
			OutMaxVector = InVector3;
		}
		else {
			OutMaxVector = InVector2;
			if (InVector3 < InVector1) {
				OutMinVector = InVector3;
			}
			else {
				OutMinVector = InVector1;
			}
		}
	}
	else {
		if (InVector1 < InVector3) {
			OutMaxVector = InVector3;
		}
		else {
			OutMaxVector = InVector1;
			if (InVector3 < InVector2) {
				OutMinVector = InVector3;
			}
			else {
				OutMinVector = InVector2;
			}
		}
	}
}