#pragma once
#include "Define.h"
struct Vector2
{
	float X;
	float Y;
};

struct Vector3
{
	float b;
	float y;
	float a;
};

struct Vertex
{
	float XYZWUV[6]; 
	unsigned int color;
	float normal;
};

struct Matrix4X4
{
	float FourXFour[4][4];
};