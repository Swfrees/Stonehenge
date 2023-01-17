#pragma once
#include "Define.h"

void PlotPixel(Vertex point, unsigned int Color)
{
		unsigned int i = (int)point.XYZWUV[0] + ScreenWidth * (int)point.XYZWUV[1];
		if (i >= 0 && i <= Number)
		{
			if (point.XYZWUV[2] < zBuffer[i])
			{
				zBuffer[i] = point.XYZWUV[2];
				pixels[i] = Color;
			}
		}
}