#pragma once
//Put all needed defines and includes here
#define ScreenWidth 750
#define ScreenHeight 750
#define C2C(c) (((c&65280u)<<0x8u)|((c&4278190080u)>>0x18u)|((c&255u)<<0x18u)|((c&16711680u)>>0x08u))
const char* Name = "Spencer Frees";

#include <iostream>
#include "StoneHenge.h"
#include "StoneHenge_Texture.h"
#include "RasterSurface.h"
#include "Structs.h"
#include "Variables.h"
#include "ClearScreen.h"
#include "MathFunctions.h"
#include "Shaders.h"
#include "DrawPixel.h"
#include "DrawStar.h"
#include "DrawLine.h"
#include "Triangle.h"
#include "Utilities.h"
#include "XTime.h"