// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "MedusaCorePreDeclares.h"
#include "Core/Pattern/LazyValue.h"
#include "Core/Geometry/Point3.h"
#include "FlipMask.h"
#include "GeometryDefines.h"

MEDUSA_BEGIN;


class Matrix2
{
public:
	const static Matrix2 Zero;
	const static Matrix2 Identity;
	const static byte Size=6;
public:
	inline Matrix2(void){}
	inline Matrix2(const float* items)
	{
		Memory::Copy(M,items,Size);
	}
	//No need this because C++ will produce default copy-assignment for us
	
	inline Matrix2(const Matrix2& matrix){Memory::Copy(M,matrix.M,Size);}
	inline Matrix2& operator=(const Matrix2& matrix){Memory::Copy(M,matrix.M,Size); return *this;}

	//in row-major
	inline Matrix2(float a,float b,float c,float d,float x,float y,bool isTransposed=false)
		:A(a),B(b),C(c),D(d),X(x),Y(y)
	{
		if (isTransposed)
		{
			A = a; B = c;
			C = b; D = d;
			X = x; Y = y;
		}
		else
		{
			A = a; B = b;
			C = c; D = d;
			X = x; Y = y;
		}
	}

	float* Items(){return M;}
	const float* const Items()const{return M;}

	//inline operator float*(){return M;}
	//inline operator const float*()const{return M;}

	inline float& operator[](uint32 index){return M[index];}
	inline const float& operator[](uint32 index)const{return M[index];}


	inline bool operator==(const Matrix2& matrix)const{return memcmp(M,matrix.Items(),sizeof(Matrix2))==0;}
	inline bool operator!=(const Matrix2& matrix)const{return memcmp(M,matrix.Items(),sizeof(Matrix2))!=0;}

public:

	inline Matrix2 operator*(const Matrix2& matrix)const
	{
		Matrix2 ret=*this;
		ret.Multiply(matrix,MatrixOrder::Append);
		return ret;
	}
	inline Matrix2& operator*=(const Matrix2& matrix)
	{
		Multiply(matrix, MatrixOrder::Append);
		return *this;
	}
public:
	Point2F Transform(const Point2F& point)const;
	QuadVertex2 Transform(const QuadVertex2& quad)const;
	QuadVertex2 Transform(const Rect2F& rect)const;


	
	Matrix2& Multiply(const Matrix2& other, MatrixOrder order);
	Matrix2& Append(const Matrix2& m);
	Matrix2& Prepend(const Matrix2& m);

	void LoadIdentity(){*this=Identity;}
	void LoadZero(){*this=Zero;}

	bool IsIdentity()const;
	bool IsInvertible()const;

	intp HashCode()const{return HashUtility::Hash(M);}
	float Determinant()const;

	Point2F Translation()const { return Point2F(X, Y); }
	void SetTranslation(const Point2F& val) { X = val.X; Y = val.Y; }

	Scale2F GetScale()const;
	float GetRotation()const;

	void Decompose(Scale2F& outScale, float outRotation, Point2F& outTranslation)const;

#pragma region Transform
public:
	Matrix2& Inverse();
	Matrix2& Transpose();
	Matrix2& Translate(const Point2F& point);
	Matrix2& Scale(const Scale2F& scale);
	Matrix2& Rotate(float radian);
	Matrix2& FlipX();
	Matrix2& FlipY();

	Matrix2 CreateInverse();
	Matrix2 CreateTranspose();
	Matrix2& ResetWorld(const Scale2F& scale, float radian, const Point2F& translation);

	Matrix2& ResetWorldEx(const Scale2F& scale, float radian, const Point2F& translation, FlipMask flip = FlipMask::None, Point2F flipPivot = Point2F::Zero, const Point2F& pivot = Point2F::Zero);
	Matrix2& ResetWorldEx(const Size2F& size, const Point2F& anchor, const Scale2F& scale, float radian, const Point2F& translation, FlipMask flip = FlipMask::None);

	static Matrix2 CreateTranslate(const Point2F& point);
	static Matrix2 CreateScale(const Scale2F& scale);
	static Matrix2 CreateRotate(float radian);
	static Matrix2 CreateFlipX();
	static Matrix2 CreateFlipY();
	static Matrix2 CreateFlip(FlipMask flip = FlipMask::None);

	static Matrix2 CreateWorld(const Scale2F& scale, float radian, const Point2F& translation);

	static Matrix2 CreateWorldEx(const Scale2F& scale, float radian, const Point2F& translation, FlipMask flip = FlipMask::None, Point2F flipPivot = Point2F::Zero, const Point2F& pivot = Point2F::Zero);
	static Matrix2 CreateWorldEx(const Size2F& size, const Point2F& anchor, const Scale2F& scale, float radian, const Point2F& translation, FlipMask flip = FlipMask::None);


#pragma endregion Transform


public:

	union
	{
		float M[Size];
		/*
		a b 0
		c d 0
		x y 1
		*/
		struct
		{
			float A;float B;	
			float C;float D;	
			float X;float Y;
		};

		struct
		{
			float M11; float M12;
			float M21; float M22;
			float M31; float M32;
		};
	};
};



MEDUSA_END;
