#pragma once
#include "Define.h"

void BlankScreen()
{
	for (size_t i = 0; i < Number; i++)
	{
		pixels[i] = 0xFF003366;
		zBuffer[i] = 1;
	}
}