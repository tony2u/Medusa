// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "MedusaCorePreDeclares.h"
#include "Core/Pattern/LazyValue.h"
#include "Core/Geometry/Point3.h"
#include "Core/Geometry/Point4.h"
#include "FlipMask.h"
#include "GeometryDefines.h"

MEDUSA_BEGIN;

/*
Affine

[m11,m12,m13,0]
[m21,m22,m23,0]
[m31,m32,m33,0]
[m41,m42,m43,1]

v'=v*S*R*T	Append
transform prepend
*/
class EulerAngle;
class Quaternion;
class Matrix4;
class Matrix3;


class Matrix43
{
public:
	inline Matrix43(void) {}
	Matrix43(const float* items);
	//No need this because C++ will produce default copy-assignment for us
	//inline Matrix43(const Matrix43& matrix);
	//inline Matrix43& operator=(const Matrix43& matrix);

	//in row-major
	inline Matrix43(float m11, float m12, float m13,
					float m21, float m22, float m23,
					float m31, float m32, float m33,
					float m41, float m42, float m43)
	{
		M11 = m11; M12 = m12; M13 = m13;
		M21 = m21; M22 = m22; M23 = m23;
		M31 = m31; M32 = m32; M33 = m33;
		M41 = m41; M42 = m42; M43 = m43;

	}


	explicit Matrix43(const Matrix4& m, bool isTransposed = false);
	Matrix43& operator=(const Matrix4& m);

	explicit Matrix43(const Matrix3& m, bool isTransposed = false);
	Matrix43& operator=(const Matrix3& m);

	float* Items() { return M; }
	const float* const Items()const { return M; }

	float& operator[](byte index) { return M[index]; }
	const float& operator[](byte index)const { return M[index]; }

	inline float& operator()(byte row, byte column) { return M[row*ColumnSize + column]; }
	inline const float& operator()(byte row, byte column)const { return M[row*ColumnSize + column]; }

	Point4F Row(byte row)const { return Point4F(M + ColumnSize*row); }
	void SetRow(byte row, const Point4F& val);

	Point4F Column(byte column);
	void SetColumn(byte column, const Point4F& val);


	bool operator==(const Matrix43& matrix)const;
	bool operator!=(const Matrix43& matrix)const;
	bool IsIdentity()const;
	bool IsZero()const;
public:
	inline Matrix43 operator*(const Matrix43& matrix)const
	{
		Matrix43 ret = *this;
		ret.Append(matrix);
		return ret;
	}
	inline Matrix43& operator*=(const Matrix43& matrix)
	{
		Append(matrix);
		return *this;
	}

	intp HashCode()const
	{
		return HashUtility::Hash(M);
	}

public:
	Matrix43& Multiply(const Matrix43& m, MatrixOrder order);
	Matrix43& Append(const Matrix43& m);
	Matrix43& Prepend(const Matrix43& m);
	float Determinant()const;

	inline void LoadIdentity() { *this = Identity; }
	inline void LoadZero() { *this = Zero; }

	Vector3F TransformVector(const Vector3F& point)const;

	Point2F TransformPoint(const Point2F& point)const;
	Point3F TransformPoint(const Point3F& point)const;
	Point4F TransformPoint(const Point4F& point)const;


	Point3F GetTranslation()const;
	HeapString ToString()const;


#pragma region Transform
public:
	Matrix43& Inverse();
	Matrix43& Transpose();
	Matrix43& Translate(const Point3F& point);
	Matrix43& Scale(const Scale3F& scale);
	Matrix43& RotateXYZ(const Rotation3F& rotation);
	Matrix43& RotateX(float radian);
	Matrix43& RotateY(float radian);
	Matrix43& RotateZ(float radian);
	Matrix43& RotateEuler(const EulerAngle& angle);
	Matrix43& FlipX();
	Matrix43& FlipY();
	Matrix43& FlipZ();
	Matrix43 CreateInverse();
	Matrix43 CreateTranspose();

	static Matrix43 CreateTranslate(const Point3F& point);
	static Matrix43 CreateScale(const Scale3F& scale);
	static Matrix43 CreateScaleAxis(const Point3F& axis, float scale);
	static Matrix43 CreateRotateXYZ(const Rotation3F& rotation);
	static Matrix43 CreateRotateX(float radian);
	static Matrix43 CreateRotateY(float radian);
	static Matrix43 CreateRotateZ(float radian);
	static Matrix43 CreateRotateAxis(const Point3F& axis, float radian);
	static Matrix43 CreateFromEuler(const EulerAngle& angle);
	static Matrix43 CreateFromQuaternion(const Quaternion& q);
	static Matrix43 CreateProjectToXY();
	static Matrix43 CreateProjectToXZ();
	static Matrix43 CreateProjectToYZ();
	static Matrix43 CreateProjectToPlane(const Point3F& normal);
	static Matrix43 CreateFlipX();
	static Matrix43 CreateFlipY();
	static Matrix43 CreateFlipZ();
	static Matrix43 CreateFlipByPlane(const Point3F& normal);
	static Matrix43 CreateShear(float xy, float xz, float yx, float yz, float zx, float zy);
	static Matrix43 CreateNormal();

#pragma endregion Transform

public:
	const static Matrix43 Zero;
	const static Matrix43 Identity;
	const static byte Size = 12;
	const static byte RowSize = 4;
	const static byte ColumnSize = 3;

	union
	{
		float M[Size];

		struct
		{
			union { float M11; float A; }; union { float M12; float B; }; float M13; 
			union { float M21; float C; }; union { float M22; float D; }; float M23; 
			float M31; float M32; float M33;
			union { float M41; float X; }; union { float M42; float Y; }; union { float M43; float Z; }; 
		};

	};

};

//[PRE_DECLARE_BEGIN]
typedef LazyValue<Matrix43> LazyMatrix43;
//[PRE_DECLARE_END]
MEDUSA_END;
