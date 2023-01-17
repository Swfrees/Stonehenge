#pragma once
#include "Define.h"

void PlotStar(Vertex point, unsigned int Color)
{
	if (VertexShader)
	{
		VertexShader(point);
	}

	if (point.XYZWUV[0] > 1 || point.XYZWUV[1] > 1 || point.XYZWUV[0] < -1 || point.XYZWUV[1] < -1 || point.XYZWUV[2] > 1 || point.XYZWUV[2] < -1)
	{
		return;
	}
	else 
	{
		CartesiantoPixel(point);

		PlotPixel(point, Color);
	}
}