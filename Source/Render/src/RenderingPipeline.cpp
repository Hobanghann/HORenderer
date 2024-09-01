#include "../../Main/include/Headers.h"

using namespace HO;

void RenderingPipeline::DrawLine(const Vector2& InStartPoint, const Vector2& InEndPoint) const {
	SDL_RenderDrawLine(mOwner->mRenderer, static_cast<int>(InStartPoint.X), static_cast<int>(InStartPoint.Y), static_cast<int>(InEndPoint.X), static_cast<int>(InEndPoint.Y));
}

void RenderingPipeline::DrawTriangle(const std::vector<Vector2>& InPixelBuffer, Mesh::Triangle InTriangle, RenderingMode InMode) const {
	Vector2 p1 = InPixelBuffer[InTriangle.Index1];
	Vector2 p2 = InPixelBuffer[InTriangle.Index2];
	Vector2 p3 = InPixelBuffer[InTriangle.Index3];
	DrawLine(p1, p2);
	DrawLine(p2, p3);
	DrawLine(p3, p1);
	if (InMode == eFill) {
		FillTriangle(InPixelBuffer, InTriangle);
	}
}

void RenderingPipeline::FillTriangle(const std::vector<Vector2>& InPixelBuffer, const Mesh::Triangle& InTriangle) const {
	Vector2 p1 = InPixelBuffer[InTriangle.Index1];
	Vector2 p2 = InPixelBuffer[InTriangle.Index2];
	Vector2 p3 = InPixelBuffer[InTriangle.Index3];

	Vector2 min, max;
	min.X = std::min({ p1.X, p2.X, p3.X });
	min.Y = std::min({ p1.Y, p2.Y, p3.Y });
	max.X = std::max({ p1.X, p2.X, p3.X });
	max.Y = std::max({ p1.Y, p2.Y, p3.Y });

	Vector2 p3Top1 = p1 - p3;
	Vector2 p3Top2 = p2 - p3;

	Vector2& a = p3Top1;
	Vector2& b = p3Top2;

	float aDotb = a.Dot(b);
	float aDota = a.Dot(a);
	float bDotb = b.Dot(b);

	float denominator = aDotb * aDotb - aDota * bDotb;

	if (denominator == 0.f) {
		SDL_Log("Degenerate triangle\n");
		return;
	}

	for (int i = static_cast<int>(min.X); i < static_cast<int>(max.X); i++) {
		for (int j = static_cast<int>(min.Y); j < static_cast<int>(max.Y); j++) {
			if (IsInTriangle(InPixelBuffer, InTriangle, Vector2(static_cast<float>(i), static_cast<float>(j)), denominator)) {
				SDL_RenderDrawPoint(mOwner->mRenderer, i, j);
			}
		}
	}
}