#pragma once
#define PI 3.141592f

namespace HO {
	class MathFunctions {
	public:
		static inline bool IsAlmostEqual(const float InValue1, const float InValue2);

		static inline bool IsAlmostZero(const float InValue);
	};
}

bool HO::MathFunctions::IsAlmostEqual(const float InValue1, const float InValue2) {
	constexpr float epsilon = std::numeric_limits<float>::epsilon();
	return fabs(InValue1 - InValue2) < epsilon;
}

bool HO::MathFunctions::IsAlmostZero(const float InValue) {
	constexpr float epsilon = std::numeric_limits<float>::epsilon();
	return fabs(InValue) < epsilon;
}
