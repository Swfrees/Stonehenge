#pragma once
#include "Define.h"

void DrawTriangle(Vertex FirstPoint, Vertex SecondPoint, Vertex ThirdPoint, unsigned int color)
{
	Color = color;
	if (VertexShader)
	{
		VertexShader(FirstPoint);
		VertexShader(SecondPoint);
		VertexShader(ThirdPoint);
	}

	if (FirstPoint.XYZWUV[0] > 1 || FirstPoint.XYZWUV[1] > 1 || FirstPoint.XYZWUV[0] < -1 || FirstPoint.XYZWUV[1] < -1 || FirstPoint.XYZWUV[2] > 1 || FirstPoint.XYZWUV[2] < -1 || SecondPoint.XYZWUV[0] > 1 || SecondPoint.XYZWUV[1] > 1 || SecondPoint.XYZWUV[0] < -1 || SecondPoint.XYZWUV[1] < -1 || SecondPoint.XYZWUV[2] > 1 || SecondPoint.XYZWUV[2] < -1 || ThirdPoint.XYZWUV[0] > 1 || ThirdPoint.XYZWUV[1] > 1 || ThirdPoint.XYZWUV[0] < -1 || ThirdPoint.XYZWUV[1] < -1 || ThirdPoint.XYZWUV[2] > 1 || ThirdPoint.XYZWUV[2] < -1)
	{
		return;
	}
	else
	{
		CartesiantoPixel(FirstPoint);
		CartesiantoPixel(SecondPoint);
		CartesiantoPixel(ThirdPoint);

		Vertex a;
		Vertex b;
		Vertex c;

		a = FirstPoint;
		b = SecondPoint;
		c = ThirdPoint;

		float StartX = std::fmin(a.XYZWUV[0], b.XYZWUV[0]);
		StartX = std::fmin(StartX, c.XYZWUV[0]);
		float StartY = std::fmin(a.XYZWUV[1], b.XYZWUV[1]);
		StartY = std::fmin(StartY, c.XYZWUV[1]);
		float EndX = std::fmax(a.XYZWUV[0], b.XYZWUV[0]);
		EndX = std::fmax(EndX, c.XYZWUV[0]);
		float EndY = std::fmax(a.XYZWUV[1], b.XYZWUV[1]);
		EndY = std::fmax(EndY, c.XYZWUV[1]);

		for (float i = StartY; i <= EndY; i++)
		{
			for (float j = StartX; j <= EndX; j++)
			{
				float CurrX = j;
				float CurrY = i;

				Vertex currPoint;
				currPoint.XYZWUV[0] = CurrX;
				currPoint.XYZWUV[1] = CurrY;
				currPoint.XYZWUV[3] = 1;

				Vector3 bya = BarycentricCoordinates(currPoint, a, b, c);

				if (bya.b >= 0 && bya.b <= 1 && bya.y >= 0 && bya.y <= 1 && bya.a >= 0 && bya.a <= 1)
				{
					float zPoint = InterpolateBarycentricCoordinates(bya, a.XYZWUV[2], b.XYZWUV[2], c.XYZWUV[2]);
					float uPoint = InterpolateBarycentricCoordinates(bya, a.XYZWUV[4], b.XYZWUV[4], c.XYZWUV[4]);
					float vPoint = InterpolateBarycentricCoordinates(bya, a.XYZWUV[5], b.XYZWUV[5], c.XYZWUV[5]);

					currPoint.XYZWUV[2] = zPoint;
					U = uPoint;
					V = vPoint;

					if (PixelShader)
					{
						PixelShader(currPoint.color);
					}

					PlotPixel(currPoint, Color);
				}
			}
		}
	}
	}