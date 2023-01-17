#pragma once
#include "Define.h"

void DrawALine(Vertex FirstPoint, Vertex SecondPoint)
{
	if (VertexShader)
	{
		VertexShader(FirstPoint);
		VertexShader(SecondPoint);
	}

	CartesiantoPixel(FirstPoint);
	CartesiantoPixel(SecondPoint);


	float XDelta = std::abs(SecondPoint.XYZWUV[0] - FirstPoint.XYZWUV[0]);
	float YDelta = std::abs(SecondPoint.XYZWUV[1] - FirstPoint.XYZWUV[1]);
	float Total = std::fmax(XDelta, YDelta);
	for (size_t i = 0; i < Total; i++)
	{
		float Ratio = ((float)i / Total);
		float screenX = (SecondPoint.XYZWUV[0] - FirstPoint.XYZWUV[0]) * Ratio + FirstPoint.XYZWUV[0];
		float screenY = (SecondPoint.XYZWUV[1] - FirstPoint.XYZWUV[1]) * Ratio + FirstPoint.XYZWUV[1];
		float screenZ = (SecondPoint.XYZWUV[2] - FirstPoint.XYZWUV[2])* Ratio + FirstPoint.XYZWUV[2];

		Vertex ScreenPoint;
		ScreenPoint.XYZWUV[0] = screenX;
		ScreenPoint.XYZWUV[1] = screenY;
		ScreenPoint.XYZWUV[2] = screenZ;


		PlotPixel(ScreenPoint, Color);
	}
}