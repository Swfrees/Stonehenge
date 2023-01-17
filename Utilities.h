#pragma once
#include "Define.h"

void InitializeScreen(int _ScreenWidth, int _ScreenHeight)
{
	RS_Initialize(Name, _ScreenWidth, _ScreenHeight);
}

void EndProgram()
{
	int f = 0;
	std::cin >> f;
	RS_Shutdown();
}