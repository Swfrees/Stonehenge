#pragma once
#include "Define.h"
#include <vector>

const int Number = ScreenWidth * ScreenHeight; //Size of scrren
unsigned int pixels[Number]; //put size of screen in brackets
float zBuffer[Number];
int Color;
const double pi = 3.14159265358979323846;
Matrix4X4 FourByFourMatrix;
Vertex StoneHengePoints[1457];
