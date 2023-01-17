#pragma once
#include "MathFunctions.h"
#include "Define.h"

void (*VertexShader)(Vertex&) = nullptr;
void (*PixelShader)(unsigned int&) = nullptr;
Matrix4X4 SV_WorldMatrix;
Matrix4X4 SV_ViewMatrix;
Matrix4X4 SV_ProjectionMatrix;
float U;
float V;

void VS_MoveRight(Vertex& ChangeMe)
{
	ChangeMe.XYZWUV[0] += .5f;
}

void VS_RotateMe(Vertex& ChangeMe)
{
	ChangeMe.XYZWUV[1] += .25;
	ChangeMe = MatrixMultiplication(ChangeMe, SV_WorldMatrix);
	ChangeMe = MatrixMultiplication(ChangeMe, SV_ViewMatrix);
	ChangeMe = MatrixMultiplication(ChangeMe, SV_ProjectionMatrix);
	ChangeMe.XYZWUV[0] = ChangeMe.XYZWUV[0] / ChangeMe.XYZWUV[3];
	ChangeMe.XYZWUV[1] = ChangeMe.XYZWUV[1] / ChangeMe.XYZWUV[3];
	ChangeMe.XYZWUV[2] = ChangeMe.XYZWUV[2] / ChangeMe.XYZWUV[3];
}

void VS_ViewMatrix(Vertex& ChangeMe)
{
	ChangeMe = MatrixMultiplication(ChangeMe, SV_ViewMatrix);
}

void VS_ProjectionMatrix(Vertex& ChangeMe)
{
	ChangeMe = MatrixMultiplication(ChangeMe, SV_ViewMatrix);
	ChangeMe = MatrixMultiplication(ChangeMe, SV_ProjectionMatrix);
	ChangeMe.XYZWUV[0] = ChangeMe.XYZWUV[0] / ChangeMe.XYZWUV[3];
	ChangeMe.XYZWUV[1] = ChangeMe.XYZWUV[1] / ChangeMe.XYZWUV[3];
	ChangeMe.XYZWUV[2] = ChangeMe.XYZWUV[2] / ChangeMe.XYZWUV[3];
}

void PS_TriangleTexture(unsigned int& ChangeColor)
{
	float NewX = U * StoneHenge_width;
	float NewY = V * StoneHenge_height;
	unsigned int numberToImage = (int)NewX + StoneHenge_width * (int)NewY;

	ChangeColor = C2C(StoneHenge_pixels[numberToImage]);

	float colorAlpha = ((ChangeColor >> 24)) / (float)255;
	unsigned int colorRed = (ChangeColor << 8) >> 24;
	unsigned int colorGreen = (ChangeColor << 16) >> 24;
	unsigned int colorBlue = (ChangeColor << 24) >> 24;
	unsigned int redPixel = (Color << 8) >> 24;
	unsigned int greenPixel = (Color << 16) >> 24;
	unsigned int bluePixel = (Color << 24) >> 24;

	colorRed = colorRed * colorAlpha + redPixel * (1 - colorAlpha);
	colorGreen = colorGreen * colorAlpha + greenPixel * (1 - colorAlpha);
	colorBlue = colorBlue * colorAlpha + bluePixel * (1 - colorAlpha);

	Color = (colorRed << 16) ^ (colorGreen << 8) ^ colorBlue;
}
