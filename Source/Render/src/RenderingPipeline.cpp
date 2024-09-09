#include "../../Main/include/Headers.h"

using namespace HO;

void RenderingPipeline::DrawLine(const Vector2& InStartPoint, const Vector2& InEndPoint) const {
	SDL_RenderDrawLine(mOwner->mRenderer, static_cast<int>(InStartPoint.X), static_cast<int>(InStartPoint.Y), static_cast<int>(InEndPoint.X), static_cast<int>(InEndPoint.Y));
}

void RenderingPipeline::DrawTriangle(const std::vector<Vertex>& InVertexBuffer, Mesh::Triangle InTriangle, RenderingMode InMode) const {
	Vector2 p1 = InVertexBuffer[InTriangle.Index1].GetPixel();
	Vector2 p2 = InVertexBuffer[InTriangle.Index2].GetPixel();
	Vector2 p3 = InVertexBuffer[InTriangle.Index3].GetPixel();
	DrawLine(p1, p2);
	DrawLine(p2, p3);
	DrawLine(p3, p1);
	if ((InMode & eWireFrameMode) == 0) {
		FillTriangle(InVertexBuffer, InTriangle);
	}
}

void RenderingPipeline::FillTriangle(const std::vector<Vertex>& InVertexBuffer, const Mesh::Triangle& InTriangle) const {
	Vector2 p1 = InVertexBuffer[InTriangle.Index1].GetPixel();
	Vector2 p2 = InVertexBuffer[InTriangle.Index2].GetPixel();
	Vector2 p3 = InVertexBuffer[InTriangle.Index3].GetPixel();

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
			if (IsInTriangle(InVertexBuffer, InTriangle, Vector2(static_cast<float>(i), static_cast<float>(j)), denominator)) {
				SDL_RenderDrawPoint(mOwner->mRenderer, i, j);
			}
		}
	}
}

void HO::RenderingPipeline::SetRenderingColor(const std::string InColor) const{
	if(InColor == "BLACK"){
		SDL_SetRenderDrawColor(mOwner->mRenderer, 0, 0, 0, 255);
	}
	else if(InColor == "WHITE"){
		SDL_SetRenderDrawColor(mOwner->mRenderer, 255, 255, 255, 255);
	}
	else if(InColor == "RED"){
		SDL_SetRenderDrawColor(mOwner->mRenderer, 255, 0, 0, 255);
	}
	else if(InColor == "BLUE"){
		SDL_SetRenderDrawColor(mOwner->mRenderer, 0, 255, 0, 255);
	}
	else if(InColor == "GREEN"){
		SDL_SetRenderDrawColor(mOwner->mRenderer, 0, 0, 255, 255);
	}
	else if(InColor == "YELLOW"){
		SDL_SetRenderDrawColor(mOwner->mRenderer, 255, 255, 0, 255);
	}
	else if(InColor == "PURPLE"){
		SDL_SetRenderDrawColor(mOwner->mRenderer, 153, 051, 204, 255);
	}
}