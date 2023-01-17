#pragma once
#include "Define.h"

float implicitLineFunction(Vertex point, Vertex firstPoint, Vertex secondPoint)
{
	return (firstPoint.XYZWUV[1] - secondPoint.XYZWUV[1]) * point.XYZWUV[0] + (secondPoint.XYZWUV[0] - firstPoint.XYZWUV[0]) * point.XYZWUV[1] + firstPoint.XYZWUV[0] * secondPoint.XYZWUV[1] - secondPoint.XYZWUV[0] * firstPoint.XYZWUV[1];
}

Vector3 BarycentricCoordinates(Vertex point, Vertex firstPoint, Vertex secondPoint, Vertex thirdPoint)
{
	float Beta = implicitLineFunction(secondPoint, firstPoint, thirdPoint);
	float Gamma = implicitLineFunction(thirdPoint, secondPoint, firstPoint);
	float Alpha = implicitLineFunction(firstPoint, thirdPoint, secondPoint);
	float d = implicitLineFunction(point, firstPoint, thirdPoint);
	float e = implicitLineFunction(point, secondPoint, firstPoint);
	float f = implicitLineFunction(point, thirdPoint, secondPoint);

	Vector3 ReturnVector;

	ReturnVector.b = d / Beta;
	ReturnVector.y = e / Gamma;
	ReturnVector.a = f / Alpha;

	return ReturnVector;
}

float InterpolateBarycentricCoordinates(Vector3 BYA, float a, float b, float c)
{
	float interpolatedFloat = BYA.a * a + BYA.b * b + BYA.y * c; 
	return interpolatedFloat;
}
Vertex MatrixMultiplication(Vertex Point, Matrix4X4 ThreeXThree)
{
	Vertex tempVertex = Vertex();
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			tempVertex.XYZWUV[i] += Point.XYZWUV[j] * ThreeXThree.FourXFour[j][i];
		}
	}
	tempVertex.XYZWUV[4] = Point.XYZWUV[4];
	tempVertex.XYZWUV[5] = Point.XYZWUV[5];
	return tempVertex;
}

Matrix4X4 MatrixByMatrixMultiplication(Matrix4X4 a, Matrix4X4 b)
{
	Matrix4X4 tempMatrix = { 0 };
	for (size_t i = 0; i < 4; ++i)
	{
		for (size_t j = 0; j < 4; ++j)
		{
			for (size_t k = 0; k < 4; ++k)
			{
				tempMatrix.FourXFour[i][j] += a.FourXFour[i][k] * b.FourXFour[k][j];
			}
		}
	}
	return tempMatrix;
}

Matrix4X4 IdentityMatrix()
{
	Matrix4X4 TempMatrix;
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			TempMatrix.FourXFour[i][j] = 0;
		}
	}
	TempMatrix.FourXFour[0][0] = 1;
	TempMatrix.FourXFour[1][1] = 1;
	TempMatrix.FourXFour[2][2] = 1;
	TempMatrix.FourXFour[3][3] = 1;
	return TempMatrix;
}

Vertex IdentityVertex()
{
	Vertex TempVertex;
	for (size_t i = 0; i < 3; i++)
	{
		TempVertex.XYZWUV[i] = 0;
	}
	TempVertex.XYZWUV[3] = 1;
	return TempVertex;
}

Matrix4X4 TranslationMatrix(float X, float Y, float Z)
{
	Matrix4X4 TempMatrix = IdentityMatrix();
	TempMatrix.FourXFour[3][0] += X;
	TempMatrix.FourXFour[3][1] += Y;
	TempMatrix.FourXFour[3][2] += Z;
	return TempMatrix;
}

Matrix4X4 TransposeMatrix(Matrix4X4 aMatrix)
{
	Matrix4X4 tempMatrix = aMatrix;
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j) 
		{
			tempMatrix.FourXFour[j][i] = aMatrix.FourXFour[i][j];
		}
	}
	return tempMatrix;
}

Matrix4X4 OrthoginalAffineInverse(Matrix4X4 aMatrix)
{
	Matrix4X4 tempMatrix = aMatrix;
	Vertex tempVertex;

	tempMatrix = TransposeMatrix(tempMatrix);
	tempVertex.XYZWUV[0] = tempMatrix.FourXFour[3][0];
	tempVertex.XYZWUV[1] = tempMatrix.FourXFour[3][1];
	tempVertex.XYZWUV[2] = tempMatrix.FourXFour[3][2];
	tempMatrix.FourXFour[0][3] = 0;
	tempMatrix.FourXFour[3][0] = 0;
	tempMatrix.FourXFour[1][3] = 0;
	tempMatrix.FourXFour[3][1] = 0;
	tempMatrix.FourXFour[2][3] = 0;
	tempMatrix.FourXFour[3][2] = 0;
	tempVertex.XYZWUV[3] = 1;
	tempVertex = MatrixMultiplication(tempVertex, tempMatrix);
	tempMatrix.FourXFour[3][0] = -tempVertex.XYZWUV[0];
	tempMatrix.FourXFour[3][1] = -tempVertex.XYZWUV[1];
	tempMatrix.FourXFour[3][2] = -tempVertex.XYZWUV[2];
	tempMatrix.FourXFour[3][3] = tempVertex.XYZWUV[3];

	return tempMatrix;
}

float AspectRatio(int _ScreenWidth, int _ScreenHeight)
{
	float aspectRatio = (float)_ScreenWidth / _ScreenHeight;
	return aspectRatio;
}

float CotangentFunction(float a)
{
	return cos(a) / sin(a);
}

Matrix4X4 projectionMatrix(float NearPlane, float FarPlane, int VerticalFOV)
{
	float aspectRatio = AspectRatio(ScreenWidth, ScreenHeight);
	float TempFloat = VerticalFOV / 2;
	float Yscale = CotangentFunction(TempFloat);
	float Xscale = Yscale * aspectRatio;
	float thirdMatrixPoint = FarPlane / (FarPlane - NearPlane);
	float fourthMatrixPoint = -(FarPlane * NearPlane) / (FarPlane - NearPlane);
	Matrix4X4 tempMatrix = IdentityMatrix();
	tempMatrix.FourXFour[3][3] = 0;
	tempMatrix.FourXFour[2][3] = 1;
	tempMatrix.FourXFour[0][0] = Xscale;
	tempMatrix.FourXFour[1][1] = Yscale;
	tempMatrix.FourXFour[2][2] = thirdMatrixPoint;
	tempMatrix.FourXFour[3][2] = fourthMatrixPoint;

	return tempMatrix;
}

Matrix4X4 XRotation(float Theta)
{
	Matrix4X4 XRotMatrix = IdentityMatrix();
	Theta *= pi / 180;
	XRotMatrix.FourXFour[1][1] = cos(Theta);
	XRotMatrix.FourXFour[1][2] = -sin(Theta);
	XRotMatrix.FourXFour[2][1] = sin(Theta);
	XRotMatrix.FourXFour[2][2] = cos(Theta);
	return XRotMatrix;
}

Matrix4X4 YRotation(float Theta)
{
	Matrix4X4 YRotMatrix = IdentityMatrix();
	Theta *= pi / 180;
	YRotMatrix.FourXFour[0][0] = cos(Theta);   
	YRotMatrix.FourXFour[0][2] = sin(Theta); 
	YRotMatrix.FourXFour[2][0] = -sin(Theta);    
	YRotMatrix.FourXFour[2][2] = cos(Theta); 
	return YRotMatrix;
}

Matrix4X4 ZRotation(float Theta)
{
	Matrix4X4 ZRotMatrix = IdentityMatrix();
	Theta *= pi / 180;
	ZRotMatrix.FourXFour[0][0] = cos(Theta);
	ZRotMatrix.FourXFour[0][1] = -sin(Theta);
	ZRotMatrix.FourXFour[1][0] = sin(Theta);
	ZRotMatrix.FourXFour[1][1] = cos(Theta);
	return ZRotMatrix;
}

void CartesiantoPixel(Vertex &CopyPoint)
{
	CopyPoint.XYZWUV[0] = (CopyPoint.XYZWUV[0] + 1) * (ScreenWidth / 2) + 0.5;
	CopyPoint.XYZWUV[1] = (1 - CopyPoint.XYZWUV[1]) * (ScreenHeight / 2) + 0.5;
}

float DotProduct(Vertex firstPoint, Vertex secondPoint)
{
	//normalize before calling this function
	return (firstPoint.XYZWUV[0] * secondPoint.XYZWUV[0]) + (firstPoint.XYZWUV[1] * secondPoint.XYZWUV[1]) + (firstPoint.XYZWUV[2] * secondPoint.XYZWUV[2]);
}

Vertex CrossProduct(Vertex firstPoint, Vertex secondPoint)
{
	Vertex ReturnPoint;
	ReturnPoint.XYZWUV[0] = (firstPoint.XYZWUV[1] * secondPoint.XYZWUV[2]) - (firstPoint.XYZWUV[2] * secondPoint.XYZWUV[1]);
	ReturnPoint.XYZWUV[1] = (firstPoint.XYZWUV[2] * secondPoint.XYZWUV[0]) - (firstPoint.XYZWUV[0] * secondPoint.XYZWUV[2]);
	ReturnPoint.XYZWUV[2] = (firstPoint.XYZWUV[0] * secondPoint.XYZWUV[1]) - (firstPoint.XYZWUV[1] * secondPoint.XYZWUV[0]);
	return ReturnPoint;
}

float VertexLength(Vertex point)
{
	return sqrt((point.XYZWUV[0] * point.XYZWUV[0]) + (point.XYZWUV[1] * point.XYZWUV[1]) + (point.XYZWUV[2] * point.XYZWUV[2]));
}

Vertex VertexNormalize(Vertex point)
{
	Vertex ReturnVertex = point;
	ReturnVertex.XYZWUV[0] = point.XYZWUV[0] / VertexLength(point);
	ReturnVertex.XYZWUV[1] = point.XYZWUV[1] / VertexLength(point);
	ReturnVertex.XYZWUV[2] = point.XYZWUV[2] / VertexLength(point);
	return ReturnVertex;
}

unsigned int CombindColors(Vertex firstPoint, Vertex secondPoint)
{
	return firstPoint.color + secondPoint.color;
}

unsigned int ModulateColors(Vertex firstPoint, Vertex secondPoint)
{
	return firstPoint.color * secondPoint.color;
}

float Saturate(float value, int min = 0, int max = 1)
{
	return (value - min) / (max - min);
}

Matrix4X4 ScaleMatrix(float Scale)
{
	Matrix4X4 ScaledMatrix = IdentityMatrix();
	ScaledMatrix.FourXFour[0][0] = Scale;
	ScaledMatrix.FourXFour[1][1] = Scale;
	ScaledMatrix.FourXFour[2][2] = Scale;

	return ScaledMatrix;
}