#pragma once
#include "Define.h"

float RandomFloat(float min, float max)
{
	float r = rand() / (float)RAND_MAX;
	float returnFloat = (max - min) * r + min;
	return returnFloat;
}

int main()
{
	RS_Initialize(Name, ScreenWidth, ScreenHeight);

	float X = 1.0f;

	Vertex VertexArray[3000];
		for (size_t i = 0; i < 3000; i++)
		{
			VertexArray[i].XYZWUV[0] = RandomFloat(-1, 1);
			VertexArray[i].XYZWUV[0] *= 50;
			VertexArray[i].XYZWUV[1] = RandomFloat(-1, 1);
			VertexArray[i].XYZWUV[1] *= 50;
			VertexArray[i].XYZWUV[2] = RandomFloat(-1, 1);
			VertexArray[i].XYZWUV[2] *= 50;
			VertexArray[i].XYZWUV[3] = 1;
		}

		for (size_t i = 0; i < 1457; i++)
		{
			StoneHengePoints[i].XYZWUV[0] = StoneHenge_data[i].pos[0];
			StoneHengePoints[i].XYZWUV[1] = StoneHenge_data[i].pos[1];
			StoneHengePoints[i].XYZWUV[2] = StoneHenge_data[i].pos[2];
			StoneHengePoints[i].XYZWUV[3] = 1.0f;
			StoneHengePoints[i].XYZWUV[4] = StoneHenge_data[i].uvw[0];
			StoneHengePoints[i].XYZWUV[5] = StoneHenge_data[i].uvw[1];
			StoneHengePoints[i].normal = StoneHenge_data[i].nrm[0];

			MatrixMultiplication(StoneHengePoints[i], ScaleMatrix(0.1f));
		}

	while (RS_Update(pixels, Number))
	{
		BlankScreen();
		if (GetKeyState(VK_LEFT))
		{
			X += .1;
		}
		else if (GetKeyState(VK_RIGHT))
		{
			X -= .1;
		}
		SV_WorldMatrix = YRotation(X);
		Matrix4X4 XRotationMatrix = XRotation(-15);
		Matrix4X4 TempTranslationMatrix = TranslationMatrix(0, 0, -34);
		SV_ViewMatrix = MatrixByMatrixMultiplication(TempTranslationMatrix, XRotationMatrix);
		SV_ViewMatrix = OrthoginalAffineInverse(SV_ViewMatrix);
		SV_ProjectionMatrix = projectionMatrix(0.1, 100.0, 90);
		VertexShader = VS_RotateMe;
		for (size_t i = 0; i < 3000; i++)
		{
			PlotStar(VertexArray[i], 0xFFFFFF);
		}

		PixelShader = PS_TriangleTexture;
		
		for (size_t i = 0; i < 2532; i+=3)
		{
			DrawTriangle(StoneHengePoints[StoneHenge_indicies[i]], StoneHengePoints[StoneHenge_indicies[i + 1]], StoneHengePoints[StoneHenge_indicies[i + 2]], 0xFF0000);
		}
	}
	RS_Shutdown();
}