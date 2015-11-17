// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Core/String/HeapString.h"
#include "Core/Geometry/Matrix.h"

#include "Core/Geometry/Matrix3.h"
#include "Core/Geometry/Matrix43.h"
#include "Core/Geometry/Matrix2.h"

#include "Core/Geometry/EulerAngle.h"
#include "Core/Geometry/Quaternion.h"
#include "Core/Geometry/Point2.h"

#include "Core/Geometry/Size3.h"
#include "Core/Geometry/Cube.h"
#include "Core/Geometry/Scale3.h"
#include "Core/Geometry/Rotation3.h"

#include "Core/Geometry/Rect2.h"
#include "Core/Geometry/Quad.h"
#include "Core/Math/Math.h"
#include "Core/Utility/Utility.h"
#include "Core/Assertion/CommonAssert.h"


MEDUSA_BEGIN;

const Matrix Matrix::Zero = Matrix(0.f, 0.f,
								   0.f, 0.f,
								   0.f, 0.f);

const Matrix Matrix::Identity = Matrix(1.f, 0.f,
									   0.f, 1.f,
									   0.f, 0.f);

Matrix::Matrix(float m11, float m12, float m13, float m14,
			   float m21, float m22, float m23, float m24,
			   float m31, float m32, float m33, float m34,
			   float m41, float m42, float m43, float m44,
			   MatrixFlags flags /*= MatrixFlags::None*/,
			   bool isTransposed /*= false*/, bool updateFlag /*= false*/)
			   :Flag(flags)
{
	if (isTransposed)
	{
		M11 = m11; M12 = m21; M13 = m31; M14 = m41;
		M21 = m12; M22 = m22; M23 = m32; M24 = m42;
		M31 = m13; M32 = m23; M33 = m33; M34 = m43;
		M41 = m14; M42 = m24; M43 = m34; M44 = m44;
	}
	else
	{
		M11 = m11; M12 = m12; M13 = m13; M14 = m14;
		M21 = m21; M22 = m22; M23 = m23; M24 = m24;
		M31 = m31; M32 = m32; M33 = m33; M34 = m34;
		M41 = m41; M42 = m42; M43 = m43; M44 = m44;
	}
	if (updateFlag)
	{
		UpdateFlag();
	}
}

Matrix::Matrix(float m11, float m12, float m13,
			   float m21, float m22, float m23,
			   float m31, float m32, float m33,
			   float m41, float m42, float m43, bool updateFlag /*= false*/)
			   :Flag(MatrixFlags::Affine)
{
	M11 = m11; M12 = m12; M13 = m13; M14 = 0.f;
	M21 = m21; M22 = m22; M23 = m23; M24 = 0.f;
	M31 = m31; M32 = m32; M33 = m33; M34 = 0.f;
	M41 = m41; M42 = m42; M43 = m43; M44 = 1.f;

	if (updateFlag)
	{
		UpdateFlag();
	}
}

Matrix::Matrix(float m11, float m12, float m13,
			   float m21, float m22, float m23,
			   float m31, float m32, float m33,
			   bool isTransposed /*= false*/, bool updateFlag /*= false*/)
			   : Flag(MatrixFlags::Is2D)
{
	if (isTransposed)
	{
		M11 = m11; M12 = m21; M13 = 0.f; M14 = m31;
		M21 = m12; M22 = m22; M23 = 0.f; M24 = m32;
		M31 = 0.f; M32 = 0.f; M33 = 1.f; M34 = 0.f;
		M41 = m13; M42 = m23; M43 = 0.f; M44 = m33;

	}
	else
	{
		M11 = m11; M12 = m12; M13 = 0.f; M14 = m13;
		M21 = m21; M22 = m22; M23 = 0.f; M24 = m23;
		M31 = 0.f; M32 = 0.f; M33 = 1.f; M34 = 0.f;
		M41 = m31; M42 = m32; M43 = 0.f; M44 = m33;
	}
	if (updateFlag)
	{
		UpdateFlag();
	}
}

Matrix::Matrix(float m11, float m12, float m21, float m22, float m31, float m32)
	: Flag(MatrixFlags::Is2D | MatrixFlags::Affine)
{

	M11 = m11; M12 = m12; M13 = 0.f; M14 = 0.f;
	M21 = m21; M22 = m22; M23 = 0.f; M24 = 0.f;
	M31 = 0.f; M32 = 0.f; M33 = 1.f; M34 = 0.f;
	M41 = m31; M42 = m32; M43 = 0.f; M44 = 1.f;
}



Matrix::Matrix(const Matrix43& m)
	:Flag(MatrixFlags::Affine)
{
	M11 = m.M11; M12 = m.M12; M13 = m.M13; M14 = 0.f;
	M21 = m.M21; M22 = m.M22; M23 = m.M23; M24 = 0.f;
	M31 = m.M31; M32 = m.M32; M33 = m.M33; M34 = 0.f;
	M41 = m.M41; M42 = m.M42; M43 = m.M43; M44 = 1.f;

}


Matrix& Matrix::operator=(const Matrix43& m)
{
	M11 = m.M11; M12 = m.M12; M13 = m.M13; M14 = 0.f;
	M21 = m.M21; M22 = m.M22; M23 = m.M23; M24 = 0.f;
	M31 = m.M31; M32 = m.M32; M33 = m.M33; M34 = 0.f;
	M41 = m.M41; M42 = m.M42; M43 = m.M43; M44 = 1.f;
	Flag = MatrixFlags::Affine;
	return *this;
}

Matrix::Matrix(const Matrix3& m, bool isTransposed/*=false*/)
	:Flag(MatrixFlags::Is2D)
{
	if (isTransposed)
	{
		M11 = m.M11; M12 = m.M21; M13 = 0.f; M14 = m.M31;
		M21 = m.M12; M22 = m.M22; M23 = 0.f; M24 = m.M32;
		M31 = 0.f; M32 = 0.f; M33 = 1.f; M34 = 0.f;
		M41 = m.M13; M42 = m.M23; M43 = 0.f; M44 = m.M33;

	}
	else
	{
		M11 = m.M11; M12 = m.M12; M13 = 0.f; M14 = m.M13;
		M21 = m.M21; M22 = m.M22; M23 = 0.f; M24 = m.M23;
		M31 = 0.f; M32 = 0.f; M33 = 1.f; M34 = 0.f;
		M41 = m.M31; M42 = m.M32; M43 = 0.f; M44 = m.M33;
	}

}


Matrix& Matrix::operator=(const Matrix3& m)
{
	M11 = m.M11; M12 = m.M12; M13 = 0.f; M14 = m.M13;
	M21 = m.M21; M22 = m.M22; M23 = 0.f; M24 = m.M23;
	M31 = 0.f; M32 = 0.f; M33 = 1.f; M34 = 0.f;
	M41 = m.M31; M42 = m.M32; M43 = 0.f; M44 = m.M33;

	Flag = MatrixFlags::Is2D;
	return *this;
}

Matrix::Matrix(const Matrix2& m)
	:Flag(MatrixFlags::Is2D | MatrixFlags::Affine)
{
	M11 = m.M11; M12 = m.M12; M13 = 0.f; M14 = 0.f;
	M21 = m.M21; M22 = m.M22; M23 = 0.f; M24 = 0.f;
	M31 = 0.f; M32 = 0.f; M33 = 1.f; M34 = 0.f;
	M41 = m.M31; M42 = m.M32; M43 = 0.f; M44 = 1.f;


}

Matrix::Matrix(const Matrix& m)
{
	M11 = m.M11; M12 = m.M12; M13 = m.M13; M14 = m.M14;
	M21 = m.M21; M22 = m.M22; M23 = m.M23; M24 = m.M24;
	M31 = m.M31; M32 = m.M32; M33 = m.M33; M34 = m.M34;
	M41 = m.M41; M42 = m.M42; M43 = m.M43; M44 = m.M44;
	Flag = m.Flag;
}



Matrix& Matrix::operator=(const Matrix2& m)
{
	M11 = m.M11; M12 = m.M12; M13 = 0.f; M14 = 0.f;
	M21 = m.M21; M22 = m.M22; M23 = 0.f; M24 = 0.f;
	M31 = 0.f; M32 = 0.f; M33 = 1.f; M34 = 0.f;
	M41 = m.M31; M42 = m.M32; M43 = 0.f; M44 = 1.f;

	Flag = MatrixFlags::Is2D | MatrixFlags::Affine;

	return *this;
}

Matrix& Matrix::operator=(const Matrix& m)
{
	M11 = m.M11; M12 = m.M12; M13 = m.M13; M14 = m.M14;
	M21 = m.M21; M22 = m.M22; M23 = m.M23; M24 = m.M24;
	M31 = m.M31; M32 = m.M32; M33 = m.M33; M34 = m.M34;
	M41 = m.M41; M42 = m.M42; M43 = m.M43; M44 = m.M44;
	Flag = m.Flag;
	return *this;
}


Matrix& Matrix::Multiply(const Matrix& m, MatrixOrder order)
{

	if (order == MatrixOrder::Prepend)
	{
		MatrixMultiplyOperation op = (MatrixMultiplyOperation)((m.Flag.ToUInt() << 8) + Flag.ToUInt());

#pragma region Prepend
		switch (op)
		{
			case MatrixMultiplyOperation::Matrix4_Matrix4:
			{
				//[BEGIN_MATRIX_AUTO_GENERATE_PREPEND_4_4]
				float a, b, c, d;
				a = m.M11 * M11 + m.M12 * M21 + m.M13 * M31 + m.M14 * M41;
				b = m.M11 * M12 + m.M12 * M22 + m.M13 * M32 + m.M14 * M42;
				c = m.M11 * M13 + m.M12 * M23 + m.M13 * M33 + m.M14 * M43;
				d = m.M11 * M14 + m.M12 * M24 + m.M13 * M34 + m.M14 * M44;
				M11 = a; M12 = b; M13 = c; M14 = d;
				a = m.M21 * M11 + m.M22 * M21 + m.M23 * M31 + m.M24 * M41;
				b = m.M21 * M12 + m.M22 * M22 + m.M23 * M32 + m.M24 * M42;
				c = m.M21 * M13 + m.M22 * M23 + m.M23 * M33 + m.M24 * M43;
				d = m.M21 * M14 + m.M22 * M24 + m.M23 * M34 + m.M24 * M44;
				M21 = a; M22 = b; M23 = c; M24 = d;
				a = m.M31 * M11 + m.M32 * M21 + m.M33 * M31 + m.M34 * M41;
				b = m.M31 * M12 + m.M32 * M22 + m.M33 * M32 + m.M34 * M42;
				c = m.M31 * M13 + m.M32 * M23 + m.M33 * M33 + m.M34 * M43;
				d = m.M31 * M14 + m.M32 * M24 + m.M33 * M34 + m.M34 * M44;
				M31 = a; M32 = b; M33 = c; M34 = d;
				a = m.M41 * M11 + m.M42 * M21 + m.M43 * M31 + m.M44 * M41;
				b = m.M41 * M12 + m.M42 * M22 + m.M43 * M32 + m.M44 * M42;
				c = m.M41 * M13 + m.M42 * M23 + m.M43 * M33 + m.M44 * M43;
				d = m.M41 * M14 + m.M42 * M24 + m.M43 * M34 + m.M44 * M44;
				M41 = a; M42 = b; M43 = c; M44 = d;
				//[END_MATRIX_AUTO_GENERATE_PREPEND_4_4]

			}
			break;
			case MatrixMultiplyOperation::Matrix4_Matrix43:
			{
				//[BEGIN_MATRIX_AUTO_GENERATE_PREPEND_4_43]
				float a, b, c, d;
				a = m.M11 * M11 + m.M12 * M21 + m.M13 * M31;
				b = m.M11 * M12 + m.M12 * M22 + m.M13 * M32;
				c = m.M11 * M13 + m.M12 * M23 + m.M13 * M33;
				d = m.M11 * M14 + m.M12 * M24 + m.M13 * M34;
				M11 = a; M12 = b; M13 = c; M14 = d;
				a = m.M21 * M11 + m.M22 * M21 + m.M23 * M31;
				b = m.M21 * M12 + m.M22 * M22 + m.M23 * M32;
				c = m.M21 * M13 + m.M22 * M23 + m.M23 * M33;
				d = m.M21 * M14 + m.M22 * M24 + m.M23 * M34;
				M21 = a; M22 = b; M23 = c; M24 = d;
				a = m.M31 * M11 + m.M32 * M21 + m.M33 * M31;
				b = m.M31 * M12 + m.M32 * M22 + m.M33 * M32;
				c = m.M31 * M13 + m.M32 * M23 + m.M33 * M33;
				d = m.M31 * M14 + m.M32 * M24 + m.M33 * M34;
				M31 = a; M32 = b; M33 = c; M34 = d;
				a = m.M41 * M11 + m.M42 * M21 + m.M43 * M31 + m.M44;
				b = m.M41 * M12 + m.M42 * M22 + m.M43 * M32 + m.M44;
				c = m.M41 * M13 + m.M42 * M23 + m.M43 * M33 + m.M44;
				d = m.M41 * M14 + m.M42 * M24 + m.M43 * M34 + m.M44;
				M41 = a; M42 = b; M43 = c; M44 = d;
				//[END_MATRIX_AUTO_GENERATE_PREPEND_4_43]

			}
			break;
			case MatrixMultiplyOperation::Matrix4_Matrix3:
			{
				//[BEGIN_MATRIX_AUTO_GENERATE_PREPEND_4_3]
				float a, b, c, d;
				a = m.M11 * M11 + m.M12 * M21 + m.M13 * M31;
				b = m.M11 * M12 + m.M12 * M22 + m.M13 * M32;
				c = m.M11 * M13 + m.M12 * M23 + m.M13 * M33;
				d = m.M11 * M14 + m.M12 * M24 + m.M13 * M34;
				M11 = a; M12 = b; M13 = c; M14 = d;
				a = m.M21 * M11 + m.M22 * M21 + m.M23 * M31;
				b = m.M21 * M12 + m.M22 * M22 + m.M23 * M32;
				c = m.M21 * M13 + m.M22 * M23 + m.M23 * M33;
				d = m.M21 * M14 + m.M22 * M24 + m.M23 * M34;
				M21 = a; M22 = b; M23 = c; M24 = d;
				M31 = m.M33; M32 = m.M33; M33 = m.M33; M34 = m.M33;
				a = m.M41 * M11 + m.M42 * M21 + m.M43 * M31 + m.M44;
				b = m.M41 * M12 + m.M42 * M22 + m.M43 * M32 + m.M44;
				c = m.M41 * M13 + m.M42 * M23 + m.M43 * M33 + m.M44;
				d = m.M41 * M14 + m.M42 * M24 + m.M43 * M34 + m.M44;
				M41 = a; M42 = b; M43 = c; M44 = d;
				//[END_MATRIX_AUTO_GENERATE_PREPEND_4_3]

			}
			break;
			case MatrixMultiplyOperation::Matrix4_Matrix2:
			{
				//[BEGIN_MATRIX_AUTO_GENERATE_PREPEND_4_2]
				float a, b, c, d;
				a = m.M11 * M11 + m.M12 * M21;
				b = m.M11 * M12 + m.M12 * M22;
				c = m.M11 * M13 + m.M12 * M23;
				d = m.M11 * M14 + m.M12 * M24;
				M11 = a; M12 = b; M13 = c; M14 = d;
				a = m.M21 * M11 + m.M22 * M21;
				b = m.M21 * M12 + m.M22 * M22;
				c = m.M21 * M13 + m.M22 * M23;
				d = m.M21 * M14 + m.M22 * M24;
				M21 = a; M22 = b; M23 = c; M24 = d;
				M31 = m.M33; M32 = m.M33; M33 = m.M33; M34 = m.M33;
				a = m.M41 * M11 + m.M42 * M21 + m.M44;
				b = m.M41 * M12 + m.M42 * M22 + m.M44;
				c = m.M41 * M13 + m.M42 * M23 + m.M44;
				d = m.M41 * M14 + m.M42 * M24 + m.M44;
				M41 = a; M42 = b; M43 = c; M44 = d;
				//[END_MATRIX_AUTO_GENERATE_PREPEND_4_2]

			}
			break;
			case MatrixMultiplyOperation::Matrix43_Matrix4:
			{
				Flag = MatrixFlags::None;
				//[BEGIN_MATRIX_AUTO_GENERATE_PREPEND_43_4]
				float a, b, c;
				a = m.M11 * M11 + m.M12 * M21 + m.M13 * M31 + m.M14 * M41;
				b = m.M11 * M12 + m.M12 * M22 + m.M13 * M32 + m.M14 * M42;
				c = m.M11 * M13 + m.M12 * M23 + m.M13 * M33 + m.M14 * M43;
				M11 = a; M12 = b; M13 = c; M14 = m.M14;
				a = m.M21 * M11 + m.M22 * M21 + m.M23 * M31 + m.M24 * M41;
				b = m.M21 * M12 + m.M22 * M22 + m.M23 * M32 + m.M24 * M42;
				c = m.M21 * M13 + m.M22 * M23 + m.M23 * M33 + m.M24 * M43;
				M21 = a; M22 = b; M23 = c; M24 = m.M24;
				a = m.M31 * M11 + m.M32 * M21 + m.M33 * M31 + m.M34 * M41;
				b = m.M31 * M12 + m.M32 * M22 + m.M33 * M32 + m.M34 * M42;
				c = m.M31 * M13 + m.M32 * M23 + m.M33 * M33 + m.M34 * M43;
				M31 = a; M32 = b; M33 = c; M34 = m.M34;
				a = m.M41 * M11 + m.M42 * M21 + m.M43 * M31 + m.M44 * M41;
				b = m.M41 * M12 + m.M42 * M22 + m.M43 * M32 + m.M44 * M42;
				c = m.M41 * M13 + m.M42 * M23 + m.M43 * M33 + m.M44 * M43;
				M41 = a; M42 = b; M43 = c; M44 = m.M44;
				//[END_MATRIX_AUTO_GENERATE_PREPEND_43_4]

			}
			break;
			case MatrixMultiplyOperation::Matrix43_Matrix43:
			{
				//[BEGIN_MATRIX_AUTO_GENERATE_PREPEND_43_43]
				float a, b, c;
				a = m.M11 * M11 + m.M12 * M21 + m.M13 * M31;
				b = m.M11 * M12 + m.M12 * M22 + m.M13 * M32;
				c = m.M11 * M13 + m.M12 * M23 + m.M13 * M33;
				M11 = a; M12 = b; M13 = c;
				a = m.M21 * M11 + m.M22 * M21 + m.M23 * M31;
				b = m.M21 * M12 + m.M22 * M22 + m.M23 * M32;
				c = m.M21 * M13 + m.M22 * M23 + m.M23 * M33;
				M21 = a; M22 = b; M23 = c;
				a = m.M31 * M11 + m.M32 * M21 + m.M33 * M31;
				b = m.M31 * M12 + m.M32 * M22 + m.M33 * M32;
				c = m.M31 * M13 + m.M32 * M23 + m.M33 * M33;
				M31 = a; M32 = b; M33 = c;
				a = m.M41 * M11 + m.M42 * M21 + m.M43 * M31 + m.M44;
				b = m.M41 * M12 + m.M42 * M22 + m.M43 * M32 + m.M44;
				c = m.M41 * M13 + m.M42 * M23 + m.M43 * M33 + m.M44;
				M41 = a; M42 = b; M43 = c;
				//[END_MATRIX_AUTO_GENERATE_PREPEND_43_43]

			}
			break;
			case MatrixMultiplyOperation::Matrix43_Matrix3:
			{
				//[BEGIN_MATRIX_AUTO_GENERATE_PREPEND_43_3]
				float a, b, c;
				a = m.M11 * M11 + m.M12 * M21 + m.M13 * M31;
				b = m.M11 * M12 + m.M12 * M22 + m.M13 * M32;
				c = m.M11 * M13 + m.M12 * M23 + m.M13 * M33;
				M11 = a; M12 = b; M13 = c;
				a = m.M21 * M11 + m.M22 * M21 + m.M23 * M31;
				b = m.M21 * M12 + m.M22 * M22 + m.M23 * M32;
				c = m.M21 * M13 + m.M22 * M23 + m.M23 * M33;
				M21 = a; M22 = b; M23 = c;
				M31 = m.M33; M32 = m.M33; M33 = m.M33;
				a = m.M41 * M11 + m.M42 * M21 + m.M43 * M31 + m.M44;
				b = m.M41 * M12 + m.M42 * M22 + m.M43 * M32 + m.M44;
				c = m.M41 * M13 + m.M42 * M23 + m.M43 * M33 + m.M44;
				M41 = a; M42 = b; M43 = c;
				//[END_MATRIX_AUTO_GENERATE_PREPEND_43_3]

			}
			break;
			case MatrixMultiplyOperation::Matrix43_Matrix2:
			{
				//[BEGIN_MATRIX_AUTO_GENERATE_PREPEND_43_2]
				float a, b, c;
				a = m.M11 * M11 + m.M12 * M21;
				b = m.M11 * M12 + m.M12 * M22;
				c = m.M11 * M13 + m.M12 * M23;
				M11 = a; M12 = b; M13 = c;
				a = m.M21 * M11 + m.M22 * M21;
				b = m.M21 * M12 + m.M22 * M22;
				c = m.M21 * M13 + m.M22 * M23;
				M21 = a; M22 = b; M23 = c;
				M31 = m.M33; M32 = m.M33; M33 = m.M33;
				a = m.M41 * M11 + m.M42 * M21 + m.M44;
				b = m.M41 * M12 + m.M42 * M22 + m.M44;
				c = m.M41 * M13 + m.M42 * M23 + m.M44;
				M41 = a; M42 = b; M43 = c;
				//[END_MATRIX_AUTO_GENERATE_PREPEND_43_2]

			}
			break;
			case MatrixMultiplyOperation::Matrix3_Matrix4:
			{
				Flag = MatrixFlags::None;
				//[BEGIN_MATRIX_AUTO_GENERATE_PREPEND_3_4]
				float a, b, c;
				a = m.M11 * M11 + m.M12 * M21 + m.M14 * M41;
				b = m.M11 * M12 + m.M12 * M22 + m.M14 * M42;
				c = m.M11 * M13 + m.M12 * M23 + m.M13 + m.M14 * M43;
				M11 = a; M12 = b; M13 = c; M14 = m.M14;
				a = m.M21 * M11 + m.M22 * M21 + m.M24 * M41;
				b = m.M21 * M12 + m.M22 * M22 + m.M24 * M42;
				c = m.M21 * M13 + m.M22 * M23 + m.M23 + m.M24 * M43;
				M21 = a; M22 = b; M23 = c; M24 = m.M24;
				a = m.M31 * M11 + m.M32 * M21 + m.M34 * M41;
				b = m.M31 * M12 + m.M32 * M22 + m.M34 * M42;
				c = m.M31 * M13 + m.M32 * M23 + m.M33 + m.M34 * M43;
				M31 = a; M32 = b; M33 = c; M34 = m.M34;
				a = m.M41 * M11 + m.M42 * M21 + m.M44 * M41;
				b = m.M41 * M12 + m.M42 * M22 + m.M44 * M42;
				c = m.M41 * M13 + m.M42 * M23 + m.M43 + m.M44 * M43;
				M41 = a; M42 = b; M43 = c; M44 = m.M44;
				//[END_MATRIX_AUTO_GENERATE_PREPEND_3_4]

			}
			break;
			case MatrixMultiplyOperation::Matrix3_Matrix43:
			{
				Flag = MatrixFlags::Affine;
				//[BEGIN_MATRIX_AUTO_GENERATE_PREPEND_3_43]
				float a, b, c;
				a = m.M11 * M11 + m.M12 * M21;
				b = m.M11 * M12 + m.M12 * M22;
				c = m.M11 * M13 + m.M12 * M23 + m.M13;
				M11 = a; M12 = b; M13 = c;
				a = m.M21 * M11 + m.M22 * M21;
				b = m.M21 * M12 + m.M22 * M22;
				c = m.M21 * M13 + m.M22 * M23 + m.M23;
				M21 = a; M22 = b; M23 = c;
				a = m.M31 * M11 + m.M32 * M21;
				b = m.M31 * M12 + m.M32 * M22;
				c = m.M31 * M13 + m.M32 * M23 + m.M33;
				M31 = a; M32 = b; M33 = c;
				a = m.M41 * M11 + m.M42 * M21 + m.M44;
				b = m.M41 * M12 + m.M42 * M22 + m.M44;
				c = m.M41 * M13 + m.M42 * M23 + m.M43 + m.M44;
				M41 = a; M42 = b; M43 = c;
				//[END_MATRIX_AUTO_GENERATE_PREPEND_3_43]

			}
			break;
			case MatrixMultiplyOperation::Matrix3_Matrix3:
			{
				//[BEGIN_MATRIX_AUTO_GENERATE_PREPEND_3_3]
				float a, b, c;
				a = m.M11 * M11 + m.M12 * M21;
				b = m.M11 * M12 + m.M12 * M22;
				c = m.M11 * M13 + m.M12 * M23 + m.M13;
				M11 = a; M12 = b; M13 = c;
				a = m.M21 * M11 + m.M22 * M21;
				b = m.M21 * M12 + m.M22 * M22;
				c = m.M21 * M13 + m.M22 * M23 + m.M23;
				M21 = a; M22 = b; M23 = c;

				a = m.M41 * M11 + m.M42 * M21 + m.M44;
				b = m.M41 * M12 + m.M42 * M22 + m.M44;
				c = m.M41 * M13 + m.M42 * M23 + m.M43 + m.M44;
				M41 = a; M42 = b; M43 = c;
				//[END_MATRIX_AUTO_GENERATE_PREPEND_3_3]

			}
			break;
			case MatrixMultiplyOperation::Matrix3_Matrix2:
			{
				//[BEGIN_MATRIX_AUTO_GENERATE_PREPEND_3_2]
				float a, b, c;
				a = m.M11 * M11 + m.M12 * M21;
				b = m.M11 * M12 + m.M12 * M22;
				c = m.M11 * M13 + m.M12 * M23;
				M11 = a; M12 = b; M13 = c;
				a = m.M21 * M11 + m.M22 * M21;
				b = m.M21 * M12 + m.M22 * M22;
				c = m.M21 * M13 + m.M22 * M23;
				M21 = a; M22 = b; M23 = c;

				a = m.M41 * M11 + m.M42 * M21 + m.M44;
				b = m.M41 * M12 + m.M42 * M22 + m.M44;
				c = m.M41 * M13 + m.M42 * M23 + m.M44;
				M41 = a; M42 = b; M43 = c;
				//[END_MATRIX_AUTO_GENERATE_PREPEND_3_2]

			}
			break;
			case MatrixMultiplyOperation::Matrix2_Matrix4:
			{
				Flag = MatrixFlags::None;
				//[BEGIN_MATRIX_AUTO_GENERATE_PREPEND_2_4]
				float a, b;
				a = m.M11 * M11 + m.M12 * M21 + m.M14 * M41;
				b = m.M11 * M12 + m.M12 * M22 + m.M14 * M42;
				M11 = a; M12 = b; M13 = m.M13; M14 = m.M14;
				a = m.M21 * M11 + m.M22 * M21 + m.M24 * M41;
				b = m.M21 * M12 + m.M22 * M22 + m.M24 * M42;
				M21 = a; M22 = b; M23 = m.M23; M24 = m.M24;
				a = m.M31 * M11 + m.M32 * M21 + m.M34 * M41;
				b = m.M31 * M12 + m.M32 * M22 + m.M34 * M42;
				M31 = a; M32 = b; M33 = m.M33; M34 = m.M34;
				a = m.M41 * M11 + m.M42 * M21 + m.M44 * M41;
				b = m.M41 * M12 + m.M42 * M22 + m.M44 * M42;
				M41 = a; M42 = b; M43 = m.M43; M44 = m.M44;
				//[END_MATRIX_AUTO_GENERATE_PREPEND_2_4]
			}
			break;
			case MatrixMultiplyOperation::Matrix2_Matrix43:
			{
				Flag = MatrixFlags::Affine;
				//[BEGIN_MATRIX_AUTO_GENERATE_PREPEND_2_43]
				float a, b;
				a = m.M11 * M11 + m.M12 * M21;
				b = m.M11 * M12 + m.M12 * M22;
				M11 = a; M12 = b; M13 = m.M13;
				a = m.M21 * M11 + m.M22 * M21;
				b = m.M21 * M12 + m.M22 * M22;
				M21 = a; M22 = b; M23 = m.M23;
				a = m.M31 * M11 + m.M32 * M21;
				b = m.M31 * M12 + m.M32 * M22;
				M31 = a; M32 = b; M33 = m.M33;
				a = m.M41 * M11 + m.M42 * M21 + m.M44;
				b = m.M41 * M12 + m.M42 * M22 + m.M44;
				M41 = a; M42 = b; M43 = m.M43;
				//[END_MATRIX_AUTO_GENERATE_PREPEND_2_43]

			}
			break;
			case MatrixMultiplyOperation::Matrix2_Matrix3:
			{
				Flag = MatrixFlags::Is2D;
				//[BEGIN_MATRIX_AUTO_GENERATE_PREPEND_2_3]
				float a, b;
				a = m.M11 * M11 + m.M12 * M21;
				b = m.M11 * M12 + m.M12 * M22;
				M11 = a; M12 = b; M13 = m.M13;
				a = m.M21 * M11 + m.M22 * M21;
				b = m.M21 * M12 + m.M22 * M22;
				M21 = a; M22 = b; M23 = m.M23;

				a = m.M41 * M11 + m.M42 * M21 + m.M44;
				b = m.M41 * M12 + m.M42 * M22 + m.M44;
				M41 = a; M42 = b; M43 = m.M43;
				//[END_MATRIX_AUTO_GENERATE_PREPEND_2_3]

			}
			break;
			case MatrixMultiplyOperation::Matrix2_Matrix2:
			{
				//[BEGIN_MATRIX_AUTO_GENERATE_PREPEND_2_2]
				float a, b;
				a = m.M11 * M11 + m.M12 * M21;
				b = m.M11 * M12 + m.M12 * M22;
				M11 = a; M12 = b;
				a = m.M21 * M11 + m.M22 * M21;
				b = m.M21 * M12 + m.M22 * M22;
				M21 = a; M22 = b;

				a = m.M41 * M11 + m.M42 * M21 + m.M44;
				b = m.M41 * M12 + m.M42 * M22 + m.M44;
				M41 = a; M42 = b;
				//[END_MATRIX_AUTO_GENERATE_PREPEND_2_2]
			}
			break;
			default:
				break;
		}

#pragma endregion Prepend

	}
	else
	{

#pragma region Append
		MatrixMultiplyOperation op = (MatrixMultiplyOperation)((Flag.ToUInt() << 8) + m.Flag.ToUInt());

		switch (op)
		{
			case MatrixMultiplyOperation::Matrix4_Matrix4:
			{
				//[BEGIN_MATRIX_AUTO_GENERATE_APPEND_4_4]
				float a, b, c, d;
				a = M11 * m.M11 + M12 * m.M21 + M13 * m.M31 + M14 * m.M41;
				b = M11 * m.M12 + M12 * m.M22 + M13 * m.M32 + M14 * m.M42;
				c = M11 * m.M13 + M12 * m.M23 + M13 * m.M33 + M14 * m.M43;
				d = M11 * m.M14 + M12 * m.M24 + M13 * m.M34 + M14 * m.M44;
				M11 = a; M12 = b; M13 = c; M14 = d;
				a = M21 * m.M11 + M22 * m.M21 + M23 * m.M31 + M24 * m.M41;
				b = M21 * m.M12 + M22 * m.M22 + M23 * m.M32 + M24 * m.M42;
				c = M21 * m.M13 + M22 * m.M23 + M23 * m.M33 + M24 * m.M43;
				d = M21 * m.M14 + M22 * m.M24 + M23 * m.M34 + M24 * m.M44;
				M21 = a; M22 = b; M23 = c; M24 = d;
				a = M31 * m.M11 + M32 * m.M21 + M33 * m.M31 + M34 * m.M41;
				b = M31 * m.M12 + M32 * m.M22 + M33 * m.M32 + M34 * m.M42;
				c = M31 * m.M13 + M32 * m.M23 + M33 * m.M33 + M34 * m.M43;
				d = M31 * m.M14 + M32 * m.M24 + M33 * m.M34 + M34 * m.M44;
				M31 = a; M32 = b; M33 = c; M34 = d;
				a = M41 * m.M11 + M42 * m.M21 + M43 * m.M31 + M44 * m.M41;
				b = M41 * m.M12 + M42 * m.M22 + M43 * m.M32 + M44 * m.M42;
				c = M41 * m.M13 + M42 * m.M23 + M43 * m.M33 + M44 * m.M43;
				d = M41 * m.M14 + M42 * m.M24 + M43 * m.M34 + M44 * m.M44;
				M41 = a; M42 = b; M43 = c; M44 = d;
				//[END_MATRIX_AUTO_GENERATE_APPEND_4_4]
			}
			break;
			case MatrixMultiplyOperation::Matrix4_Matrix43:
			{
				//[BEGIN_MATRIX_AUTO_GENERATE_APPEND_4_43]
				float a, b, c;
				a = M11 * m.M11 + M12 * m.M21 + M13 * m.M31 + M14 * m.M41;
				b = M11 * m.M12 + M12 * m.M22 + M13 * m.M32 + M14 * m.M42;
				c = M11 * m.M13 + M12 * m.M23 + M13 * m.M33 + M14 * m.M43;
				M11 = a; M12 = b; M13 = c;
				a = M21 * m.M11 + M22 * m.M21 + M23 * m.M31 + M24 * m.M41;
				b = M21 * m.M12 + M22 * m.M22 + M23 * m.M32 + M24 * m.M42;
				c = M21 * m.M13 + M22 * m.M23 + M23 * m.M33 + M24 * m.M43;
				M21 = a; M22 = b; M23 = c;
				a = M31 * m.M11 + M32 * m.M21 + M33 * m.M31 + M34 * m.M41;
				b = M31 * m.M12 + M32 * m.M22 + M33 * m.M32 + M34 * m.M42;
				c = M31 * m.M13 + M32 * m.M23 + M33 * m.M33 + M34 * m.M43;
				M31 = a; M32 = b; M33 = c;
				a = M41 * m.M11 + M42 * m.M21 + M43 * m.M31 + M44 * m.M41;
				b = M41 * m.M12 + M42 * m.M22 + M43 * m.M32 + M44 * m.M42;
				c = M41 * m.M13 + M42 * m.M23 + M43 * m.M33 + M44 * m.M43;
				M41 = a; M42 = b; M43 = c;
				//[END_MATRIX_AUTO_GENERATE_APPEND_4_43]

			}
			break;
			case MatrixMultiplyOperation::Matrix4_Matrix3:
			{
				//[BEGIN_MATRIX_AUTO_GENERATE_APPEND_4_3]
				float a, b, c;
				a = M11 * m.M11 + M12 * m.M21 + M14 * m.M41;
				b = M11 * m.M12 + M12 * m.M22 + M14 * m.M42;
				c = M11 * m.M13 + M12 * m.M23 + M13 + M14 * m.M43;
				M11 = a; M12 = b; M13 = c;
				a = M21 * m.M11 + M22 * m.M21 + M24 * m.M41;
				b = M21 * m.M12 + M22 * m.M22 + M24 * m.M42;
				c = M21 * m.M13 + M22 * m.M23 + M23 + M24 * m.M43;
				M21 = a; M22 = b; M23 = c;
				a = M31 * m.M11 + M32 * m.M21 + M34 * m.M41;
				b = M31 * m.M12 + M32 * m.M22 + M34 * m.M42;
				c = M31 * m.M13 + M32 * m.M23 + M33 + M34 * m.M43;
				M31 = a; M32 = b; M33 = c;
				a = M41 * m.M11 + M42 * m.M21 + M44 * m.M41;
				b = M41 * m.M12 + M42 * m.M22 + M44 * m.M42;
				c = M41 * m.M13 + M42 * m.M23 + M43 + M44 * m.M43;
				M41 = a; M42 = b; M43 = c;
				//[END_MATRIX_AUTO_GENERATE_APPEND_4_3]
			}
			break;
			case MatrixMultiplyOperation::Matrix4_Matrix2:
			{
				//[BEGIN_MATRIX_AUTO_GENERATE_APPEND_4_2]
				float a, b;
				a = M11 * m.M11 + M12 * m.M21 + M14 * m.M41;
				b = M11 * m.M12 + M12 * m.M22 + M14 * m.M42;
				M11 = a; M12 = b;
				a = M21 * m.M11 + M22 * m.M21 + M24 * m.M41;
				b = M21 * m.M12 + M22 * m.M22 + M24 * m.M42;
				M21 = a; M22 = b;
				a = M31 * m.M11 + M32 * m.M21 + M34 * m.M41;
				b = M31 * m.M12 + M32 * m.M22 + M34 * m.M42;
				M31 = a; M32 = b;
				a = M41 * m.M11 + M42 * m.M21 + M44 * m.M41;
				b = M41 * m.M12 + M42 * m.M22 + M44 * m.M42;
				M41 = a; M42 = b;
				//[END_MATRIX_AUTO_GENERATE_APPEND_4_2]
			}
			break;
			case MatrixMultiplyOperation::Matrix43_Matrix4:
			{
				Flag = MatrixFlags::None;
				//[BEGIN_MATRIX_AUTO_GENERATE_APPEND_43_4]
				float a, b, c, d;
				a = M11 * m.M11 + M12 * m.M21 + M13 * m.M31;
				b = M11 * m.M12 + M12 * m.M22 + M13 * m.M32;
				c = M11 * m.M13 + M12 * m.M23 + M13 * m.M33;
				d = M11 * m.M14 + M12 * m.M24 + M13 * m.M34;
				M11 = a; M12 = b; M13 = c; M14 = d;
				a = M21 * m.M11 + M22 * m.M21 + M23 * m.M31;
				b = M21 * m.M12 + M22 * m.M22 + M23 * m.M32;
				c = M21 * m.M13 + M22 * m.M23 + M23 * m.M33;
				d = M21 * m.M14 + M22 * m.M24 + M23 * m.M34;
				M21 = a; M22 = b; M23 = c; M24 = d;
				a = M31 * m.M11 + M32 * m.M21 + M33 * m.M31;
				b = M31 * m.M12 + M32 * m.M22 + M33 * m.M32;
				c = M31 * m.M13 + M32 * m.M23 + M33 * m.M33;
				d = M31 * m.M14 + M32 * m.M24 + M33 * m.M34;
				M31 = a; M32 = b; M33 = c; M34 = d;
				a = M41 * m.M11 + M42 * m.M21 + M43 * m.M31 + m.M41;
				b = M41 * m.M12 + M42 * m.M22 + M43 * m.M32 + m.M42;
				c = M41 * m.M13 + M42 * m.M23 + M43 * m.M33 + m.M43;
				d = M41 * m.M14 + M42 * m.M24 + M43 * m.M34 + m.M44;
				M41 = a; M42 = b; M43 = c; M44 = d;
				//[END_MATRIX_AUTO_GENERATE_APPEND_43_4]
			}
			break;
			case MatrixMultiplyOperation::Matrix43_Matrix43:
			{
				//[BEGIN_MATRIX_AUTO_GENERATE_APPEND_43_43]
				float a, b, c;
				a = M11 * m.M11 + M12 * m.M21 + M13 * m.M31;
				b = M11 * m.M12 + M12 * m.M22 + M13 * m.M32;
				c = M11 * m.M13 + M12 * m.M23 + M13 * m.M33;
				M11 = a; M12 = b; M13 = c;
				a = M21 * m.M11 + M22 * m.M21 + M23 * m.M31;
				b = M21 * m.M12 + M22 * m.M22 + M23 * m.M32;
				c = M21 * m.M13 + M22 * m.M23 + M23 * m.M33;
				M21 = a; M22 = b; M23 = c;
				a = M31 * m.M11 + M32 * m.M21 + M33 * m.M31;
				b = M31 * m.M12 + M32 * m.M22 + M33 * m.M32;
				c = M31 * m.M13 + M32 * m.M23 + M33 * m.M33;
				M31 = a; M32 = b; M33 = c;
				a = M41 * m.M11 + M42 * m.M21 + M43 * m.M31 + m.M41;
				b = M41 * m.M12 + M42 * m.M22 + M43 * m.M32 + m.M42;
				c = M41 * m.M13 + M42 * m.M23 + M43 * m.M33 + m.M43;
				M41 = a; M42 = b; M43 = c;
				//[END_MATRIX_AUTO_GENERATE_APPEND_43_43]
			}
			break;
			case MatrixMultiplyOperation::Matrix43_Matrix3:
			{
				//[BEGIN_MATRIX_AUTO_GENERATE_APPEND_43_3]
				float a, b, c;
				a = M11 * m.M11 + M12 * m.M21;
				b = M11 * m.M12 + M12 * m.M22;
				c = M11 * m.M13 + M12 * m.M23 + M13;
				M11 = a; M12 = b; M13 = c;
				a = M21 * m.M11 + M22 * m.M21;
				b = M21 * m.M12 + M22 * m.M22;
				c = M21 * m.M13 + M22 * m.M23 + M23;
				M21 = a; M22 = b; M23 = c;
				a = M31 * m.M11 + M32 * m.M21;
				b = M31 * m.M12 + M32 * m.M22;
				c = M31 * m.M13 + M32 * m.M23 + M33;
				M31 = a; M32 = b; M33 = c;
				a = M41 * m.M11 + M42 * m.M21 + m.M41;
				b = M41 * m.M12 + M42 * m.M22 + m.M42;
				c = M41 * m.M13 + M42 * m.M23 + M43 + m.M43;
				M41 = a; M42 = b; M43 = c;
				//[END_MATRIX_AUTO_GENERATE_APPEND_43_3]
			}
			break;
			case MatrixMultiplyOperation::Matrix43_Matrix2:
			{
				//[BEGIN_MATRIX_AUTO_GENERATE_APPEND_43_2]
				float a, b;
				a = M11 * m.M11 + M12 * m.M21;
				b = M11 * m.M12 + M12 * m.M22;
				M11 = a; M12 = b;
				a = M21 * m.M11 + M22 * m.M21;
				b = M21 * m.M12 + M22 * m.M22;
				M21 = a; M22 = b;
				a = M31 * m.M11 + M32 * m.M21;
				b = M31 * m.M12 + M32 * m.M22;
				M31 = a; M32 = b;
				a = M41 * m.M11 + M42 * m.M21 + m.M41;
				b = M41 * m.M12 + M42 * m.M22 + m.M42;
				M41 = a; M42 = b;
				//[END_MATRIX_AUTO_GENERATE_APPEND_43_2]
			}
			break;
			case MatrixMultiplyOperation::Matrix3_Matrix4:
			{
				Flag = MatrixFlags::None;
				//[BEGIN_MATRIX_AUTO_GENERATE_APPEND_3_4]
				float a, b, c, d;
				a = M11 * m.M11 + M12 * m.M21 + M13 * m.M31;
				b = M11 * m.M12 + M12 * m.M22 + M13 * m.M32;
				c = M11 * m.M13 + M12 * m.M23 + M13 * m.M33;
				d = M11 * m.M14 + M12 * m.M24 + M13 * m.M34;
				M11 = a; M12 = b; M13 = c; M14 = d;
				a = M21 * m.M11 + M22 * m.M21 + M23 * m.M31;
				b = M21 * m.M12 + M22 * m.M22 + M23 * m.M32;
				c = M21 * m.M13 + M22 * m.M23 + M23 * m.M33;
				d = M21 * m.M14 + M22 * m.M24 + M23 * m.M34;
				M21 = a; M22 = b; M23 = c; M24 = d;
				M31 = m.M31; M32 = m.M32; M33 = m.M33; M34 = m.M34;
				a = M41 * m.M11 + M42 * m.M21 + M43 * m.M31 + m.M41;
				b = M41 * m.M12 + M42 * m.M22 + M43 * m.M32 + m.M42;
				c = M41 * m.M13 + M42 * m.M23 + M43 * m.M33 + m.M43;
				d = M41 * m.M14 + M42 * m.M24 + M43 * m.M34 + m.M44;
				M41 = a; M42 = b; M43 = c; M44 = d;
				//[END_MATRIX_AUTO_GENERATE_APPEND_3_4]
			}
			break;
			case MatrixMultiplyOperation::Matrix3_Matrix43:
			{
				Flag = MatrixFlags::Affine;
				//[BEGIN_MATRIX_AUTO_GENERATE_APPEND_3_43]
				float a, b, c;
				a = M11 * m.M11 + M12 * m.M21 + M13 * m.M31;
				b = M11 * m.M12 + M12 * m.M22 + M13 * m.M32;
				c = M11 * m.M13 + M12 * m.M23 + M13 * m.M33;
				M11 = a; M12 = b; M13 = c;
				a = M21 * m.M11 + M22 * m.M21 + M23 * m.M31;
				b = M21 * m.M12 + M22 * m.M22 + M23 * m.M32;
				c = M21 * m.M13 + M22 * m.M23 + M23 * m.M33;
				M21 = a; M22 = b; M23 = c;
				M31 = m.M31; M32 = m.M32; M33 = m.M33;
				a = M41 * m.M11 + M42 * m.M21 + M43 * m.M31 + m.M41;
				b = M41 * m.M12 + M42 * m.M22 + M43 * m.M32 + m.M42;
				c = M41 * m.M13 + M42 * m.M23 + M43 * m.M33 + m.M43;
				M41 = a; M42 = b; M43 = c;
				//[END_MATRIX_AUTO_GENERATE_APPEND_3_43]
			}
			break;
			case MatrixMultiplyOperation::Matrix3_Matrix3:
			{
				//[BEGIN_MATRIX_AUTO_GENERATE_APPEND_3_3]
				float a, b, c;
				a = M11 * m.M11 + M12 * m.M21;
				b = M11 * m.M12 + M12 * m.M22;
				c = M11 * m.M13 + M12 * m.M23 + M13;
				M11 = a; M12 = b; M13 = c;
				a = M21 * m.M11 + M22 * m.M21;
				b = M21 * m.M12 + M22 * m.M22;
				c = M21 * m.M13 + M22 * m.M23 + M23;
				M21 = a; M22 = b; M23 = c;

				a = M41 * m.M11 + M42 * m.M21 + m.M41;
				b = M41 * m.M12 + M42 * m.M22 + m.M42;
				c = M41 * m.M13 + M42 * m.M23 + M43 + m.M43;
				M41 = a; M42 = b; M43 = c;
				//[END_MATRIX_AUTO_GENERATE_APPEND_3_3]
			}
			break;
			case MatrixMultiplyOperation::Matrix3_Matrix2:
			{
				//[BEGIN_MATRIX_AUTO_GENERATE_APPEND_3_2]
				float a, b;
				a = M11 * m.M11 + M12 * m.M21;
				b = M11 * m.M12 + M12 * m.M22;
				M11 = a; M12 = b;
				a = M21 * m.M11 + M22 * m.M21;
				b = M21 * m.M12 + M22 * m.M22;
				M21 = a; M22 = b;

				a = M41 * m.M11 + M42 * m.M21 + m.M41;
				b = M41 * m.M12 + M42 * m.M22 + m.M42;
				M41 = a; M42 = b;
				//[END_MATRIX_AUTO_GENERATE_APPEND_3_2]
			}
			break;
			case MatrixMultiplyOperation::Matrix2_Matrix4:
			{
				Flag = MatrixFlags::None;
				//[BEGIN_MATRIX_AUTO_GENERATE_APPEND_2_4]
				float a, b, c, d;
				a = M11 * m.M11 + M12 * m.M21;
				b = M11 * m.M12 + M12 * m.M22;
				c = M11 * m.M13 + M12 * m.M23;
				d = M11 * m.M14 + M12 * m.M24;
				M11 = a; M12 = b; M13 = c; M14 = d;
				a = M21 * m.M11 + M22 * m.M21;
				b = M21 * m.M12 + M22 * m.M22;
				c = M21 * m.M13 + M22 * m.M23;
				d = M21 * m.M14 + M22 * m.M24;
				M21 = a; M22 = b; M23 = c; M24 = d;
				M31 = m.M31; M32 = m.M32; M33 = m.M33; M34 = m.M34;
				a = M41 * m.M11 + M42 * m.M21 + m.M41;
				b = M41 * m.M12 + M42 * m.M22 + m.M42;
				c = M41 * m.M13 + M42 * m.M23 + m.M43;
				d = M41 * m.M14 + M42 * m.M24 + m.M44;
				M41 = a; M42 = b; M43 = c; M44 = d;
				//[END_MATRIX_AUTO_GENERATE_APPEND_2_4]
			}
			break;
			case MatrixMultiplyOperation::Matrix2_Matrix43:
			{
				Flag = MatrixFlags::Affine;
				//[BEGIN_MATRIX_AUTO_GENERATE_APPEND_2_43]
				float a, b, c;
				a = M11 * m.M11 + M12 * m.M21;
				b = M11 * m.M12 + M12 * m.M22;
				c = M11 * m.M13 + M12 * m.M23;
				M11 = a; M12 = b; M13 = c;
				a = M21 * m.M11 + M22 * m.M21;
				b = M21 * m.M12 + M22 * m.M22;
				c = M21 * m.M13 + M22 * m.M23;
				M21 = a; M22 = b; M23 = c;
				M31 = m.M31; M32 = m.M32; M33 = m.M33;
				a = M41 * m.M11 + M42 * m.M21 + m.M41;
				b = M41 * m.M12 + M42 * m.M22 + m.M42;
				c = M41 * m.M13 + M42 * m.M23 + m.M43;
				M41 = a; M42 = b; M43 = c;
				//[END_MATRIX_AUTO_GENERATE_APPEND_2_43]
			}
			break;
			case MatrixMultiplyOperation::Matrix2_Matrix3:
			{
				Flag = MatrixFlags::Is2D;
				//[BEGIN_MATRIX_AUTO_GENERATE_APPEND_2_3]
				float a, b, c;
				a = M11 * m.M11 + M12 * m.M21;
				b = M11 * m.M12 + M12 * m.M22;
				c = M11 * m.M13 + M12 * m.M23;
				M11 = a; M12 = b; M13 = c;
				a = M21 * m.M11 + M22 * m.M21;
				b = M21 * m.M12 + M22 * m.M22;
				c = M21 * m.M13 + M22 * m.M23;
				M21 = a; M22 = b; M23 = c;

				a = M41 * m.M11 + M42 * m.M21 + m.M41;
				b = M41 * m.M12 + M42 * m.M22 + m.M42;
				c = M41 * m.M13 + M42 * m.M23 + m.M43;
				M41 = a; M42 = b; M43 = c;
				//[END_MATRIX_AUTO_GENERATE_APPEND_2_3]
			}
			break;
			case MatrixMultiplyOperation::Matrix2_Matrix2:
			{
				//[BEGIN_MATRIX_AUTO_GENERATE_APPEND_2_2]
				float a, b;
				a = M11 * m.M11 + M12 * m.M21;
				b = M11 * m.M12 + M12 * m.M22;
				M11 = a; M12 = b;
				a = M21 * m.M11 + M22 * m.M21;
				b = M21 * m.M12 + M22 * m.M22;
				M21 = a; M22 = b;

				a = M41 * m.M11 + M42 * m.M21 + m.M41;
				b = M41 * m.M12 + M42 * m.M22 + m.M42;
				M41 = a; M42 = b;
				//[END_MATRIX_AUTO_GENERATE_APPEND_2_2]
			}
			break;
			default:
				break;
		}

#pragma endregion Append

	}


	return *this;
}

Matrix& Matrix::Append(const Matrix& m)
{
	return Multiply(m, MatrixOrder::Append);
}

Matrix& Matrix::Prepend(const Matrix& m)
{
	return Multiply(m, MatrixOrder::Prepend);
}


Vector3F Matrix::TransformVector(const Vector3F& point) const
{
	//point.W=0

	MatrixType type = (MatrixType)(Flag.ToUInt());
	switch (type)
	{
		case MatrixType::Matrix4:
			return Point3F(M11 * point.X + M21 * point.Y + M31 * point.Z,
						   M12 * point.X + M22 * point.Y + M32 * point.Z,
						   M13 * point.X + M23 * point.Y + M33 * point.Z);
		case MatrixType::Matrix43:
			return Point3F(M11 * point.X + M21 * point.Y + M31 * point.Z,
						   M12 * point.X + M22 * point.Y + M32 * point.Z,
						   M13 * point.X + M23 * point.Y + M33 * point.Z);
		case MatrixType::Matrix3:
			return Point3F(M11 * point.X + M21 * point.Y,
						   M12 * point.X + M22 * point.Y,
						   M13 * point.X + M23 * point.Y + point.Z);
		case MatrixType::Matrix2:
			return Point3F(M11 * point.X + M21 * point.Y,
						   M12 * point.X + M22 * point.Y,
						   point.Z);

	}

	return point;
}


Point4F Matrix::Transform(const Point4F& point) const
{
	MatrixType type = (MatrixType)(Flag.ToUInt());
	switch (type)
	{
		case MatrixType::Matrix4:
			return Point4F(M11 * point.X + M21 * point.Y + M31 * point.Z + M41*point.W,
						   M12 * point.X + M22 * point.Y + M32 * point.Z + M42*point.W,
						   M13 * point.X + M23 * point.Y + M33 * point.Z + M43*point.W,
						   M14 * point.X + M24 * point.Y + M34 * point.Z + M44*point.W
						   );
		case MatrixType::Matrix43:
			return Point4F(M11 * point.X + M21 * point.Y + M31 * point.Z + M41*point.W,
						   M12 * point.X + M22 * point.Y + M32 * point.Z + M42*point.W,
						   M13 * point.X + M23 * point.Y + M33 * point.Z + M43*point.W,
						   point.W
						   );
		case MatrixType::Matrix3:
			return Point4F(M11 * point.X + M21 * point.Y + M41*point.W,
						   M12 * point.X + M22 * point.Y + M42*point.W,
						   M13 * point.X + M23 * point.Y + point.Z + M43*point.W,
						   point.W
						   );

		case MatrixType::Matrix2:
			return Point4F(M11 * point.X + M21 * point.Y + M41*point.W,
						   M12 * point.X + M22 * point.Y + M42*point.W,
						   point.Z,
						   point.W
						   );
	}
	return point;
}

Point3F Matrix::Transform(const Point3F& point)const
{
	//point.W=1
	MatrixType type = (MatrixType)(Flag.ToUInt());
	switch (type)
	{
		case MatrixType::Matrix4:
		{
			float w = 1.f / (M14 * point.X + M24 * point.Y + M34 * point.Z + M44);
			return Point3F((M11 * point.X + M21 * point.Y + M31 * point.Z + M41)*w,
						   (M12 * point.X + M22 * point.Y + M32 * point.Z + M42)*w,
						   (M13 * point.X + M23 * point.Y + M33 * point.Z + M43)*w);
		}
		case MatrixType::Matrix43:
			return Point3F(M11 * point.X + M21 * point.Y + M31 * point.Z + M41,
						   M12 * point.X + M22 * point.Y + M32 * point.Z + M42,
						   M13 * point.X + M23 * point.Y + M33 * point.Z + M43);
			break;
		case MatrixType::Matrix3:
			return Point3F(M11 * point.X + M21 * point.Y + M41,
						   M12 * point.X + M22 * point.Y + M42,
						   M13 * point.X + M23 * point.Y + point.Z + M43
						   );
			break;
		case MatrixType::Matrix2:
			return Point3F(M11 * point.X + M21 * point.Y + M41,
						   M12 * point.X + M22 * point.Y + M42,
						   point.Z
						   );
			break;
	}
	return point;
}

Point2F Matrix::Transform(const Point2F& point) const
{
	//point.W=1,point.Z=0
	MatrixType type = (MatrixType)(Flag.ToUInt());
	switch (type)
	{
		case MatrixType::Matrix4:
		{
			float w = 1.f / (M14 * point.X + M24 * point.Y + M44);
			return Point2F((M11 * point.X + M21 * point.Y + M41)*w,
						   (M12 * point.X + M22 * point.Y + M42)*w);
		}
		case MatrixType::Matrix43:
		case MatrixType::Matrix3:
		case MatrixType::Matrix2:
			return Point2F(M11 * point.X + M21 * point.Y + M41,
						   M12 * point.X + M22 * point.Y + M42);
			break;
	}
	return point;
}




Rect2F Matrix::Transform(const Rect2F& rect) const
{
	Point2F p1 = Transform(rect.LeftBottom());
	Point2F p2 = Transform(rect.LeftTop());
	Point2F p3 = Transform(rect.RightBottom());
	Point2F p4 = Transform(rect.RightTop());

	float minX = Math::Min(p1.X, p2.X, p3.X, p4.X);
	float maxX = Math::Max(p1.X, p2.X, p3.X, p4.X);
	float minY = Math::Min(p1.Y, p2.Y, p3.Y, p4.Y);
	float maxY = Math::Max(p1.Y, p2.Y, p3.Y, p4.Y);

	return Rect2F(minX, minY, maxX - minX, maxY - minY);
}

CubeF Matrix::Transform(const CubeF& cube) const
{
	if (cube.IsZeroDepth())
	{
		Point3F p1 = Transform(cube.LeftBottomNear());
		Point3F p2 = Transform(cube.LeftTopNear());
		Point3F p3 = Transform(cube.RightBottomNear());
		Point3F p4 = Transform(cube.RightTopNear());

		float minX = Math::Min(p1.X, p2.X, p3.X, p4.X);
		float maxX = Math::Max(p1.X, p2.X, p3.X, p4.X);
		float minY = Math::Min(p1.Y, p2.Y, p3.Y, p4.Y);
		float maxY = Math::Max(p1.Y, p2.Y, p3.Y, p4.Y);

		return CubeF(minX, minY, cube.Origin.Z, maxX - minX, maxY - minY, 0.f);
	}
	else
	{
		Point3F p1 = Transform(cube.LeftBottomNear());
		Point3F p2 = Transform(cube.LeftTopNear());
		Point3F p3 = Transform(cube.RightBottomNear());
		Point3F p4 = Transform(cube.RightTopNear());

		Point3F p5 = Transform(cube.LeftBottomFar());
		Point3F p6 = Transform(cube.LeftTopFar());
		Point3F p7 = Transform(cube.RightBottomFar());
		Point3F p8 = Transform(cube.RightTopFar());

		float minX = Math::Min(p1.X, p2.X, p3.X, p4.X, p5.X, p6.X, p7.X, p8.X);
		float maxX = Math::Max(p1.X, p2.X, p3.X, p4.X, p5.X, p6.X, p7.X, p8.X);

		float minY = Math::Min(p1.Y, p2.Y, p3.Y, p4.Y, p5.Y, p6.Y, p7.Y, p8.Y);
		float maxY = Math::Max(p1.Y, p2.Y, p3.Y, p4.Y, p5.Y, p6.Y, p7.Y, p8.Y);

		float minZ = Math::Min(p1.Z, p2.Z, p3.Z, p4.Z, p5.Z, p6.Z, p7.Z, p8.Z);
		float maxZ = Math::Max(p1.Z, p2.Z, p3.Z, p4.Z, p5.Z, p6.Z, p7.Z, p8.Z);

		return CubeF(minX, minY, minZ, maxX - minX, maxY - minY, maxZ - minZ);
	}

}



void Matrix::SetRow(byte row, const Point4F& val)
{
	M[ColumnSize*row] = val.X;
	M[ColumnSize*row + 1] = val.Y;
	M[ColumnSize*row + 2] = val.Z;
	M[ColumnSize*row + 3] = val.W;
}

Point4F Matrix::Column(byte column)
{
	return Point4F(M[column], M[RowSize + column], M[2 * RowSize + column], M[3 * RowSize + column]);
}

void Matrix::SetColumn(byte column, const Point4F& val)
{
	M[column] = val.X;
	M[RowSize + column] = val.Y;
	M[2 * RowSize + column] = val.Z;
	M[3 * RowSize + column] = val.W;
}

HeapString Matrix::ToString() const
{
	/*
	[11,12,13,14]
	[21,22,23,24]
	[31,32,33,34]
	[41,42,43,44]
	*/

	HeapString result;

	MatrixType type = (MatrixType)(Flag.ToUInt());
	switch (type)
	{
		case MatrixType::Matrix4:
			result.Format("[{},{},{},{}]\n[{},{},{},{}]\n[{},{},{},{}]\n[{},{},{},{}]", M11, M12, M13, M14, M21, M22, M23, M24, M31, M32, M33, M34, M41, M42, M43, M44);
			break;
		case MatrixType::Matrix43:
			result.Format("[{},{},{}]\n[{},{},{}]\n[{},{},{}]\n[{},{},{}]", M11, M12, M13, M21, M22, M23, M31, M32, M33, M41, M42, M43);
			break;
		case MatrixType::Matrix3:
			result.Format("[{},{},{}]\n[{},{},{}]\n[{},{},{}]", M11, M12, M13, M21, M22, M23, M41, M42, M44);
			break;
		case MatrixType::Matrix2:
			result.Format("[{},{}]\n[{},{}]\n[{},{}]", M11, M12, M21, M22, M41, M42);
			break;
	}

	return result;

}

float Matrix::Determinant() const
{
	MatrixType type = (MatrixType)(Flag.ToUInt());
	switch (type)
	{
		case MatrixType::Matrix4:
			return M11*(M22*(M33*M44 - M34*M43) + M23*(M34*M42 - M32*M44) + M24*(M32*M43 - M33*M42))
				- M12*(M21*(M33*M44 - M34*M43) + M23*(M34*M41 - M31*M44) + M24*(M31*M43 - M33*M41))
				+ M13*(M21*(M32*M44 - M34*M42) + M22*(M34*M41 - M31*M44) + M24*(M31*M42 - M32*M41))
				- M14*(M21*(M32*M43 - M33*M42) + M22*(M33*M41 - M31*M43) + M23*(M31*M42 - M32*M41));
		case MatrixType::Matrix43:
			return (M12*M23 - M13*M22)*M31 + (M13*M21 - M11*M23)*M32 + (M11*M22 - M12*M21)*M33;
		case MatrixType::Matrix3:
			return M11*M22 - M12*M21;
			break;
		case MatrixType::Matrix2:
			return M11*M22 - M12*M21;
			break;
	}
	return 0.f;
}

bool Matrix::operator==(const Matrix& m) const
{
	MatrixFlags topFlags = Flag&m.Flag;
	MatrixType type = (MatrixType)(topFlags.ToUInt());
	switch (type)
	{
		case MatrixType::Matrix4:
			return Memory::EqualsFloat(M, m.M);
			break;
		case MatrixType::Matrix43:
			return Math::IsEqual(M11, m.M11) && Math::IsEqual(M12, m.M12) && Math::IsEqual(M13, m.M13) &&
				Math::IsEqual(M21, m.M21) && Math::IsEqual(M22, m.M22) && Math::IsEqual(M23, m.M23) &&
				Math::IsEqual(M31, m.M31) && Math::IsEqual(M32, m.M32) && Math::IsEqual(M33, m.M33) &&
				Math::IsEqual(M41, m.M41) && Math::IsEqual(M42, m.M42) && Math::IsEqual(M43, m.M43);
			break;
		case MatrixType::Matrix3:
			return Math::IsEqual(M11, m.M11) && Math::IsEqual(M12, m.M12) && Math::IsEqual(M14, m.M14) &&
				Math::IsEqual(M21, m.M21) && Math::IsEqual(M22, m.M22) && Math::IsEqual(M24, m.M24) &&
				Math::IsEqual(M41, m.M41) && Math::IsEqual(M42, m.M42) && Math::IsEqual(M44, m.M44);
			break;
		case MatrixType::Matrix2:
			return Math::IsEqual(M11, m.M11) && Math::IsEqual(M12, m.M12) &&
				Math::IsEqual(M21, m.M21) && Math::IsEqual(M22, m.M22) &&
				Math::IsEqual(M41, m.M41) && Math::IsEqual(M42, m.M42);
			break;
	}

	return false;

}

bool Matrix::operator!=(const Matrix& matrix) const
{
	return !operator==(matrix);
}

bool Matrix::IsIdentity() const
{
	return operator==(Identity);
}

bool Matrix::IsZero() const
{
	return operator==(Zero);
}

#pragma region Transform

Matrix& Matrix::Inverse()
{
	*this = CreateInverse();
	return *this;
}


Matrix& Matrix::Transpose()
{
	MatrixType type = (MatrixType)(Flag.ToUInt());
	switch (type)
	{
		case MatrixType::Matrix4:
		case MatrixType::Matrix43:
			Math::Swap(M12, M21);
			Math::Swap(M13, M31);
			Math::Swap(M14, M41);
			Math::Swap(M23, M32);
			Math::Swap(M24, M42);
			Math::Swap(M34, M43);
			break;
		case MatrixType::Matrix3:
			Math::Swap(M12, M21);
			Math::Swap(M14, M41);
			Math::Swap(M24, M42);

			break;
		case MatrixType::Matrix2:
			Math::Swap(M12, M21);
			break;
	}


	return *this;
}

Matrix& Matrix::Translate(const Point3F& point)
{
	//point.W=1
	MatrixType type = (MatrixType)(Flag.ToUInt());
	switch (type)
	{
		case MatrixType::Matrix4:
			M11 += M14*point.X;
			M12 += M14*point.Y;
			M13 += M14*point.Z;

			M21 += M24*point.X;
			M22 += M24*point.Y;
			M23 += M24*point.Z;

			M31 += M34*point.X;
			M32 += M34*point.Y;
			M33 += M34*point.Z;

			M41 += M44*point.X;
			M42 += M44*point.Y;
			M43 += M44*point.Z;
			break;
		case MatrixType::Matrix43:
			M41 += point.X;
			M42 += point.Y;
			M43 += point.Z;
			break;
		case MatrixType::Matrix3:
		case MatrixType::Matrix2:
			if (Math::IsZero(point.Z))
			{
				M41 += point.X;
				M41 += point.Y;
			}
			else
			{
				Flag = MatrixFlags::Affine;
				M41 += point.X;
				M42 += point.Y;
				M43 += point.Z;
			}
			break;
	}



	return *this;
}


Matrix& Matrix::Translate(const Point2F& point)
{
	MatrixType type = (MatrixType)(Flag.ToUInt());
	switch (type)
	{
		case MatrixType::Matrix4:
			M11 += M14*point.X;
			M12 += M14*point.Y;

			M21 += M24*point.X;
			M22 += M24*point.Y;

			M31 += M34*point.X;
			M32 += M34*point.Y;

			M41 += M44*point.X;
			M42 += M44*point.Y;
			break;
		case MatrixType::Matrix43:
			M41 += point.X;
			M42 += point.Y;
			break;
		case MatrixType::Matrix3:
		case MatrixType::Matrix2:
			M41 += point.X;
			M42 += point.Y;
			break;
	}



	return *this;
}

Matrix& Matrix::Scale(const Scale3F& scale)
{
	MatrixType type = (MatrixType)(Flag.ToUInt());
	switch (type)
	{
		case MatrixType::Matrix4:
		case MatrixType::Matrix43:
			M11 *= scale.X;
			M12 *= scale.Y;
			M13 *= scale.Z;

			M21 *= scale.X;
			M22 *= scale.Y;
			M23 *= scale.Z;

			M31 *= scale.X;
			M32 *= scale.Y;
			M33 *= scale.Z;

			M41 *= scale.X;
			M42 *= scale.Y;
			M43 *= scale.Z;
			break;
		case MatrixType::Matrix3:
		case MatrixType::Matrix2:
			if (Math::IsEqual(scale.Z, 1.f))
			{
				M11 *= scale.X;
				M12 *= scale.Y;

				M21 *= scale.X;
				M22 *= scale.Y;

				M41 *= scale.X;
				M42 *= scale.Y;
			}
			else
			{
				Flag = MatrixFlags::Affine;

				M11 *= scale.X;
				M12 *= scale.Y;

				M21 *= scale.X;
				M22 *= scale.Y;

				M33 *= scale.Z;

				M41 *= scale.X;
				M42 *= scale.Y;
			}


			break;
	}


	return *this;
}


Matrix& Matrix::Scale(const Scale2F& scale)
{
	MatrixType type = (MatrixType)(Flag.ToUInt());
	switch (type)
	{
		case MatrixType::Matrix4:
		case MatrixType::Matrix43:
			M11 *= scale.X;
			M12 *= scale.Y;

			M21 *= scale.X;
			M22 *= scale.Y;

			M31 *= scale.X;
			M32 *= scale.Y;

			M41 *= scale.X;
			M42 *= scale.Y;
			break;
		case MatrixType::Matrix3:
		case MatrixType::Matrix2:

			M11 *= scale.X;
			M12 *= scale.Y;

			M21 *= scale.X;
			M22 *= scale.Y;

			M41 *= scale.X;
			M42 *= scale.Y;
			break;
	}


	return *this;
}

Matrix& Matrix::RotateXYZ(const Rotation3F& rotation)
{
	Matrix temp = CreateRotateXYZ(rotation);
	Append(temp);
	return *this;
}

Matrix& Matrix::RotateXY(const Rotation2F& rotation)
{
	Matrix temp = CreateRotateXYZ(rotation);
	Append(temp);
	return *this;
}

Matrix& Matrix::RotateX(float radian)
{
	float cosX = Math::Cos(radian);
	float sinX = Math::Sin(radian);

	MatrixType type = (MatrixType)(Flag.ToUInt());
	switch (type)
	{
		case MatrixType::Matrix4:
		case MatrixType::Matrix43:
		{
			float old = M12;

			M12 = M12*cosX + M13*-sinX;
			M13 = old*sinX + M13*cosX;

			old = M22;
			M22 = M22*cosX + M23*-sinX;
			M23 = old*sinX + M23*cosX;

			old = M32;
			M32 = M32*cosX + M33*-sinX;
			M33 = old*sinX + M33*cosX;

			old = M42;
			M42 += M42*cosX + M43*-sinX;
			M43 += old*sinX + M43*cosX;
		}
		break;
		case MatrixType::Matrix3:
		case MatrixType::Matrix2:
		{
			Flag = MatrixFlags::Affine;
			float old = M12;

			M12 = M12*cosX + M13*-sinX;
			M13 = old*sinX + M13*cosX;

			old = M22;
			M22 = M22*cosX + M23*-sinX;
			M23 = old*sinX + M23*cosX;

			old = M32;
			M32 = M32*cosX + M33*-sinX;
			M33 = old*sinX + M33*cosX;

			old = M42;
			M42 += M42*cosX + M43*-sinX;
			M43 += old*sinX + M43*cosX;
		}
		break;
	}



	return *this;
}

Matrix& Matrix::RotateY(float radian)
{
	float cosY = Math::Cos(radian);
	float sinY = Math::Sin(radian);
	MatrixType type = (MatrixType)(Flag.ToUInt());
	switch (type)
	{
		case MatrixType::Matrix4:
		case MatrixType::Matrix43:
		{

			float old = M11;

			M11 = M11*cosY + M13*sinY;
			M13 = old*-sinY + M13*cosY;

			old = M21;
			M21 = M21*cosY + M23*sinY;
			M23 = old*-sinY + M23*cosY;

			old = M31;
			M31 = M31*cosY + M33*sinY;
			M33 = old*-sinY + M33*cosY;

			old = M41;
			M41 += M41*cosY + M43*sinY;
			M43 += old*-sinY + M43*cosY;
		}
		break;
		case MatrixType::Matrix3:
		case MatrixType::Matrix2:
		{
			Flag = MatrixFlags::Affine;

			float old = M11;

			M11 = M11*cosY + M13*sinY;
			M13 = old*-sinY + M13*cosY;

			old = M21;
			M21 = M21*cosY + M23*sinY;
			M23 = old*-sinY + M23*cosY;

			old = M31;
			M31 = M31*cosY + M33*sinY;
			M33 = old*-sinY + M33*cosY;

			old = M41;
			M41 += M41*cosY + M43*sinY;
			M43 += old*-sinY + M43*cosY;
		}
		break;
	}

	return *this;
}

Matrix& Matrix::RotateZ(float radian)
{
	float cosZ = Math::Cos(radian);
	float sinZ = Math::Sin(radian);

	MatrixType type = (MatrixType)(Flag.ToUInt());
	switch (type)
	{
		case MatrixType::Matrix4:
		case MatrixType::Matrix43:
		{
			float old = M11;

			M11 = M11*cosZ + M12*-sinZ;
			M12 = old*sinZ + M12*cosZ;

			old = M21;
			M21 = M21*cosZ + M22*-sinZ;
			M22 = old*sinZ + M22*cosZ;

			old = M31;
			M31 = M31*cosZ + M32*-sinZ;
			M32 = old*sinZ + M32*cosZ;

			old = M41;
			M41 += M41*cosZ + M42*-sinZ;
			M42 += old*sinZ + M42*cosZ;
		}
		break;
		case MatrixType::Matrix3:
		case MatrixType::Matrix2:
		{
			float old = M11;

			M11 = M11*cosZ + M12*-sinZ;
			M12 = old*sinZ + M12*cosZ;

			old = M21;
			M21 = M21*cosZ + M22*-sinZ;
			M22 = old*sinZ + M22*cosZ;

			old = M41;
			M41 += M41*cosZ + M42*-sinZ;
			M42 += old*sinZ + M42*cosZ;
		}
		break;
	}


	return *this;
}

Matrix& Matrix::RotateEuler(const EulerAngle& angle)
{
	Matrix temp = CreateFromEuler(angle);
	Append(temp);
	return *this;
}

Matrix& Matrix::FlipX()
{
	M11 = -M11;
	M21 = -M21;
	M31 = -M31;
	M41 = -M41;
	return *this;
}

Matrix& Matrix::FlipY()
{
	M12 = -M12;
	M22 = -M22;
	M32 = -M32;
	M42 = -M42;
	return *this;
}

Matrix& Matrix::FlipZ()
{
	M13 = -M13;
	M23 = -M23;
	M33 = -M33;
	M43 = -M43;

	if (Flag == MatrixFlags::All)
	{
		Flag = MatrixFlags::Is2D;
	}

	return *this;
}


Matrix& Matrix::ResetWorld(const Scale3F& scale, const Rotation3F& rotation, const Point3F& translation, FlipMask flip /*= FlipMask::None*/, Point3F flipPivot /*= Point3F::Zero*/, const Point3F& pivot/*=Point3F::Zero*/)
{
	*this = CreateWorld(scale, rotation, translation, flip, flipPivot, pivot);
	return *this;
}

Matrix& Matrix::ResetWorld(const Size3F& size, const Point3F& anchor, const Scale3F& scale, const Rotation3F& rotation, const Point3F& translation, FlipMask flip /*= FlipMask::None*/)
{
	*this = CreateWorld(size, anchor, scale, rotation, translation, flip);
	return *this;
}

Matrix& Matrix::ResetWorldWithoutAnchor(const Scale3F& scale, const Rotation3F& rotation, const Point3F& translation, FlipMask flip /*= FlipMask::None*/)
{
	*this = CreateWorldWithoutAnchor(scale, rotation, translation, flip);
	return *this;
}

Scale3F Matrix::GetScale() const
{
	return Scale3F(Math::Sqrt(M11*M11 + M12*M12 + M13*M13), Math::Sqrt(M21*M21 + M22*M22 + M23*M23), Math::Sqrt(M31*M31 + M32*M32 + M33*M33));
}

Rotation3F Matrix::GetRotationXYZ() const
{
	Rotation3F outRotation;
	Point3F outTranslation;
	Scale3F outScale;
	DecomposeXYZ(outScale, outRotation, outTranslation);
	return outRotation;
}



Matrix Matrix::CreateInverse()
{
	float det = Determinant();
	if (Math::IsZero(det))
	{
		MEDUSA_ASSERT_FAILED("Matrix has no inverse: singular matrix");
	}
	det = 1.f / det;

	MatrixType type = (MatrixType)(Flag.ToUInt());
	switch (type)
	{
		case MatrixType::Matrix4:
		{
			Matrix result = AdjointMatrix();
			FOR_EACH_SIZE(i, 16)
			{
				result.M[i] *= det;
			}

			return result;
		}
		break;
		case MatrixType::Matrix43:
		{
			Matrix result(Identity);
			result.Flag = MatrixFlags::Affine;
			result.M11 = (M22 * M33 - M32 * M23) * det;
			result.M12 = -(M12 * M33 - M32 * M13) * det;
			result.M13 = (M12 * M23 - M22 * M13) * det;
			result.M21 = -(M21 * M33 - M31 * M23) * det;
			result.M22 = (M11 * M33 - M31 * M13) * det;
			result.M23 = -(M11 * M23 - M21 * M13) * det;
			result.M31 = (M21 * M32 - M31 * M22) * det;
			result.M32 = -(M11 * M32 - M31 * M12) * det;
			result.M33 = (M11 * M22 - M21 * M12) * det;

			result.M41 = -(M41 * result.M11 + M42 * result.M21 + M43 * result.M31);
			result.M42 = -(M41 * result.M12 + M42 * result.M22 + M43 * result.M32);
			result.M43 = -(M41 * result.M13 + M42 * result.M23 + M43 * result.M33);

			return result;
		}
		break;
		case MatrixType::Matrix3:
		case MatrixType::Matrix2:
			return Matrix(M22*det, -M12*det, -M21*det, M11*det, (M21*M42 - M22*M41)*det, (M12*M41 - M11*M42)*det);
	}

	return Identity;
}


Matrix Matrix::CreateTranspose()
{
	return Matrix(M11, M21, M31, M41,
				  M12, M22, M32, M42,
				  M13, M23, M33, M43,
				  M14, M24, M34, M44, Flag);
}


Matrix Matrix::CreateTranslate(const Point3F& point)
{
	return Matrix(1.f, 0.f, 0.f,
				  0.f, 1.f, 0.f,
				  0.f, 0.f, 1.f,
				  point.X, point.Y, point.Z);
}

Matrix Matrix::CreateScale(const Scale3F& scale)
{
	return Matrix(scale.X, 0.f, 0.f,
				  0.f, scale.Y, 0.f,
				  0.f, 0.f, scale.Z);
}

Matrix Matrix::CreateScaleAxis(const Point3F& axis, float scale)
{
	float xy = axis.X*axis.Y;
	float yz = axis.Y*axis.Z;
	float xz = axis.X*axis.Z;
	float xx = axis.X*axis.X;
	float yy = axis.Y*axis.Y;
	float zz = axis.Z*axis.Z;
	float scaleMinusOne = scale - 1.f;

	return Matrix(1 + scaleMinusOne*xx, scaleMinusOne*xy, scaleMinusOne*xz,
				  scaleMinusOne*xy, 1 + scaleMinusOne*yy, scaleMinusOne*yz,
				  scaleMinusOne*xz, scaleMinusOne*yz, 1 + scaleMinusOne*zz);
}

Matrix Matrix::CreateRotateXYZ(const Rotation3F& rotation)
{
	//rotate order: x,y,z
	uint t = Math::IsZero(rotation.X) ? 0 : 1;
	t |= Math::IsZero(rotation.Y) ? 0 : 2;
	t |= Math::IsZero(rotation.Y) ? 0 : 4;

	RotationType type = (RotationType)t;
	switch (type)
	{
		case RotationType::None:
			return Identity;
			break;
		case RotationType::X:
		{
			float cosX = Math::Cos(rotation.X);
			float sinX = Math::Sin(rotation.X);

			return Matrix(1.f, 0.f, 0.f,
						  0.f, cosX, sinX,
						  0.f, -sinX, cosX);
		}
		case RotationType::Y:
		{
			float cosY = Math::Cos(rotation.Y);
			float sinY = Math::Sin(rotation.Y);

			return Matrix(cosY, 0.f, -sinY,
						  0.f, 1.f, 0.f,
						  sinY, 0.f, cosY);
		}
		case RotationType::Z:
		{
			float cosZ = Math::Cos(rotation.Z);
			float sinZ = Math::Sin(rotation.Z);

			return Matrix(cosZ, sinZ,
						  -sinZ, cosZ,
						  0.f, 0.f);
		}
		case RotationType::XY:
		{
			float cosY = Math::Cos(rotation.Y);
			float cosX = Math::Cos(rotation.X);

			float sinY = Math::Sin(rotation.Y);
			float sinX = Math::Sin(rotation.X);

			float sinXsinY = sinX*sinY;
			float cosXsinY = cosX*sinY;

			return Matrix(cosY, 0.f, -sinY,
						  sinXsinY, cosX, sinX*cosY,
						  cosXsinY, -sinX, cosX*cosY);
		}
		break;
		case RotationType::XZ:
		{
			float cosZ = Math::Cos(rotation.Z);
			float cosX = Math::Cos(rotation.X);

			float sinZ = Math::Sin(rotation.Z);
			float sinX = Math::Sin(rotation.X);

			return Matrix(cosZ, sinZ, 0.f,
						  -cosX*sinZ, cosX*cosZ, sinX,
						  sinX*sinZ, -sinX*cosZ, cosX);
		}
		case RotationType::YZ:
		{
			float cosY = Math::Cos(rotation.Y);
			float cosZ = Math::Cos(rotation.Z);

			float sinY = Math::Sin(rotation.Y);
			float sinZ = Math::Sin(rotation.Z);

			return Matrix(cosY*cosZ, cosY*sinZ, -sinY,
						  -sinZ, cosZ, 0.f,
						  sinY*cosZ, sinY*sinZ, cosY);
		}
		case RotationType::XYZ:
		{
			float cosY = Math::Cos(rotation.Y);
			float cosZ = Math::Cos(rotation.Z);
			float cosX = Math::Cos(rotation.X);

			float sinY = Math::Sin(rotation.Y);
			float sinZ = Math::Sin(rotation.Z);
			float sinX = Math::Sin(rotation.X);

			float sinXsinY = sinX*sinY;
			float cosXsinY = cosX*sinY;

			return Matrix(cosY*cosZ, cosY*sinZ, -sinY,
						  sinXsinY*cosZ - cosX*sinZ, sinXsinY*sinZ + cosX*cosZ, sinX*cosY,
						  cosXsinY*cosZ + sinX*sinZ, cosXsinY*sinZ - sinX*cosZ, cosX*cosY);
		}
	}

	return Identity;

}

Matrix Matrix::CreateRotateXY(const Rotation2F& rotation)
{
	//rotate order : x,y
	float cosY = Math::Cos(rotation.Y);
	float cosX = Math::Cos(rotation.X);

	float sinY = Math::Sin(rotation.Y);
	float sinX = Math::Sin(rotation.X);

	float sinXsinY = sinX*sinY;
	float cosXsinY = cosX*sinY;

	return Matrix(cosY, 0.f, -sinY,
				  sinXsinY, cosX, sinX*cosY,
				  cosXsinY, -sinX, cosX*cosY);
}

Matrix Matrix::CreateRotateX(float radian)
{
	float cosX = Math::Cos(radian);
	float sinX = Math::Sin(radian);

	return Matrix(1.f, 0.f, 0.f,
				  0.f, cosX, sinX,
				  0.f, -sinX, cosX);
}

Matrix Matrix::CreateRotateY(float radian)
{
	float cosY = Math::Cos(radian);
	float sinY = Math::Sin(radian);

	return Matrix(cosY, 0.f, -sinY,
				  0.f, 1.f, 0.f,
				  sinY, 0.f, cosY);
}

Matrix Matrix::CreateRotateZ(float radian)
{
	float cosZ = Math::Cos(radian);
	float sinZ = Math::Sin(radian);

	return Matrix(cosZ, sinZ,
				  -sinZ, cosZ,
				  0.f, 0.f);
}

Matrix Matrix::CreateRotateAxis(const Point3F& axis, float radian)
{
	float cosValue = Math::Cos(radian);
	float sinValue = Math::Sin(radian);
	float oneMinusCosValue = 1 - cosValue;

	float xy = axis.X*axis.Y;
	float yz = axis.Y*axis.Z;
	float xz = axis.X*axis.Z;
	float xx = axis.X*axis.X;
	float yy = axis.Y*axis.Y;
	float zz = axis.Z*axis.Z;

	float xSin = axis.X*sinValue;
	float ySin = axis.Y*sinValue;
	float zSin = axis.Z*sinValue;


	return Matrix(xx*oneMinusCosValue + cosValue, xy*oneMinusCosValue + zSin, xz*oneMinusCosValue - ySin,
				  xy*oneMinusCosValue - zSin, yy*oneMinusCosValue + cosValue, yz*oneMinusCosValue + xSin,
				  xz*oneMinusCosValue + ySin, yz*oneMinusCosValue - xSin, zz*oneMinusCosValue + cosValue);
}

Matrix Matrix::CreateFromEuler(const EulerAngle& angle)
{
	float cosh = Math::Cos(angle.Heading);
	float cosp = Math::Cos(angle.Pitch);
	float cosb = Math::Cos(angle.Bank);

	float sinh = Math::Sin(angle.Heading);
	float sinp = Math::Sin(angle.Pitch);
	float sinb = Math::Sin(angle.Bank);

	return Matrix(cosh*cosb + sinh*sinp*sinb, sinb*cosp, -sinh*cosb + cosh*sinp*sinb,
				  -cosh*sinb + sinh*sinp*cosb, cosb*cosp, sinb*sinh + cosh*sinp*cosb,
				  sinh*cosp, -sinp, cosh*cosp);
}

Matrix Matrix::CreateFromQuaternion(const Quaternion& q)
{

	/*
	Quaternion and matrix can be converted to each other
	often:

	[ ww+xx-yy-zz , 2xy-2wz , 2xz+2wy ]
	[ 2xy+2wz , ww-xx-yy-zz , 2yz-2wx ]
	[ 2xz-2wy , 2yz+2wx , ww-xx-yy-zz ]

	But with normalized Quaternion, Could be simplifed to :

	[ 1-2yy-2zz , 2xy-2wz , 2xz+2wy ]
	[ 2xy+2wz , 1-2xx-2zz , 2yz-2wx ]
	[ 2xz-2wy , 2yz+2wx , 1-2xx-2yy ]

	*/
	float xx = q.X*q.X;
	float yy = q.Y*q.Y;
	float zz = q.Z*q.Z;
	float xy = q.X*q.Y;
	float xz = q.X*q.Z;
	float yz = q.Y*q.Z;
	float wx = q.W*q.X;
	float wy = q.W*q.Y;
	float wz = q.W*q.Z;

	return Matrix(1.f - 2.f*(yy + zz), 2.f*(xy + wz), 2.f*(xz - wy),
				  2.f*(xy - wz), 1 - 2.f*(xx + zz), 2.f*(yz + wx),
				  2.f*(xz + wy), 2.f*(yz - wx), 1 - 2.f*(xx + yy));
}


Matrix Matrix::CreateWorld(const Size3F& size, const Point3F& anchor, const Scale3F& scale, const Rotation3F& rotation, const Point3F& translation, FlipMask flip /*= FlipMask::None*/)
{
	Point3F pivot(anchor.X*size.Width, anchor.Y*size.Height, anchor.Z*size.Depth);
	float flipX = flip.Has(FlipMask::X) ? 1.f : 0.f;
	float flipY = flip.Has(FlipMask::Y) ? 1.f : 0.f;
	float flipZ = flip.Has(FlipMask::Z) ? 1.f : 0.f;

	Point3F flipPivot(anchor.X*size.Width*flipX, anchor.Y*size.Height*flipY, anchor.Z*size.Depth*flipZ);

	return CreateWorld(scale, rotation, translation, flip, flipPivot, pivot);
}

Matrix Matrix::CreateWorldWithoutAnchor(const Scale3F& scale, const Rotation3F& rotation, const Point3F& translation, FlipMask flip /*= FlipMask::None*/)
{
	//matrix order: flip*scale*rotation*translation

	//rotate order: x,y,z
	float flipX = flip.Has(FlipMask::X) ? -1.f : 1.f;
	float flipY = flip.Has(FlipMask::Y) ? -1.f : 1.f;
	float flipZ = flip.Has(FlipMask::Z) ? -1.f : 1.f;

	if (rotation != Rotation3F::Zero)
	{
		float cosY = Math::Cos(rotation.Y);
		float cosZ = Math::Cos(rotation.Z);
		float cosX = Math::Cos(rotation.X);

		float sinY = Math::Sin(rotation.Y);
		float sinZ = Math::Sin(rotation.Z);
		float sinX = Math::Sin(rotation.X);

		float sinXsinY = sinX*sinY;
		float cosXsinY = cosX*sinY;

		float m11 = scale.X*cosY*cosZ;
		float m12 = scale.X*cosY*sinZ;
		float m13 = scale.X*(-sinY);

		float m21 = scale.Y*(sinXsinY*cosZ - cosX*sinZ);
		float m22 = scale.Y*(sinXsinY*sinZ + cosX*cosZ);
		float m23 = scale.Y*sinX*cosY;

		float m31 = scale.Z*(cosXsinY*cosZ + sinX*sinZ);
		float m32 = scale.Z*(cosXsinY*sinZ - sinX*cosZ);
		float m33 = scale.Z*cosX*cosY;

		return Matrix(m11*flipX, m12, m13,
					  m21, m22*flipY, m23,
					  m31, m32, m33*flipZ,
					  translation.X, translation.Y, translation.Z, true);
	}
	else
	{
		if (Math::IsEqual(scale.Z*flipZ, 1.f) && Math::IsZero(translation.Z))
		{
			return Matrix(scale.X*flipX, 0.f,
						  0.f, scale.Y*flipY,
						  translation.X, translation.Y);
		}
		else
		{
			return Matrix(scale.X*flipX, 0.f, 0.f,
						  0.f, scale.Y*flipY, 0.f,
						  0.f, 0.f, scale.Z*flipZ,
						  translation.X, translation.Y, translation.Z, true);
		}

	}
}


Matrix Matrix::CreateWorld(const Scale3F& scale, const Rotation3F& rotation, const Point3F& translation, FlipMask flip /*= FlipMask::None*/, Point3F flipPivot /*= Point3F::Zero*/, const Point3F& pivot/*=Point3F::Zero*/)
{
	//matrix order: -flipPivot*flip*(flipPivot)*(-pivot)*scale*rotation*translation

	//rotate order: x,y,z
	float flipX = flip.Has(FlipMask::X) ? -1.f : 1.f;
	float flipY = flip.Has(FlipMask::Y) ? -1.f : 1.f;
	float flipZ = flip.Has(FlipMask::Z) ? -1.f : 1.f;


	if (rotation != Rotation3F::Zero)
	{
		float cosY = Math::Cos(rotation.Y);
		float cosZ = Math::Cos(rotation.Z);
		float cosX = Math::Cos(rotation.X);

		float sinY = Math::Sin(rotation.Y);
		float sinZ = Math::Sin(rotation.Z);
		float sinX = Math::Sin(rotation.X);

		float sinXsinY = sinX*sinY;
		float cosXsinY = cosX*sinY;

		float m11 = scale.X*cosY*cosZ;
		float m12 = scale.X*cosY*sinZ;
		float m13 = scale.X*(-sinY);

		float m21 = scale.Y*(sinXsinY*cosZ - cosX*sinZ);
		float m22 = scale.Y*(sinXsinY*sinZ + cosX*cosZ);
		float m23 = scale.Y*sinX*cosY;

		float m31 = scale.Z*(cosXsinY*cosZ + sinX*sinZ);
		float m32 = scale.Z*(cosXsinY*sinZ - sinX*cosZ);
		float m33 = scale.Z*cosX*cosY;

		float m41 = translation.X - pivot.X*m11 - pivot.Y*m21 - pivot.Z*m31;
		float m42 = translation.Y - pivot.X*m12 - pivot.Y*m22 - pivot.Z*m32;
		float m43 = translation.Z - pivot.X*m13 - pivot.Y*m23 - pivot.Z*m33;

		return Matrix(m11*flipX, m12, m13,
					  m21, m22*flipY, m23,
					  m31, m32, m33*flipZ,
					  flipPivot.X*(1.f - flipX)*m11 + m41, flipPivot.Y*(1.f - flipY)*m22 + m42, flipPivot.Z*(1.f - flipZ)*m33 + m43, true);
	}
	else
	{
		return Matrix(scale.X*flipX, 0.f, 0.f,
					  0.f, scale.Y*flipY, 0.f,
					  0.f, 0.f, scale.Z*flipZ,
					  flipPivot.X*(1.f - flipX)*scale.X + translation.X - scale.X*pivot.X, flipPivot.Y*(1.f - flipY)*scale.Y + translation.Y - scale.Y*pivot.Y, flipPivot.Z*(1.f-flipZ)*scale.Z + translation.Z - scale.Z*pivot.Z, true);
	}

}


Matrix Matrix::CreateProjectToXY()
{
	return Matrix(1.f, 0.f, 0.f,
				  0.f, 1.f, 0.f,
				  0.f, 0.f, 0.f);
}

Matrix Matrix::CreateProjectToXZ()
{
	return Matrix(1.f, 0.f,
				  0.f, 0.f,
				  0.f, 0.f);
}

Matrix Matrix::CreateProjectToYZ()
{
	return Matrix(0.f, 0.f,
				  0.f, 1.f,
				  0.f, 0.f);
}

Matrix Matrix::CreateProjectToPlane(const Point3F& normal)
{
	float xy = normal.X*normal.Y;
	float yz = normal.Y*normal.Z;
	float xz = normal.X*normal.Z;
	float xx = normal.X*normal.X;
	float yy = normal.Y*normal.Y;
	float zz = normal.Z*normal.Z;

	return Matrix(1 - xx, -xy, -xz,
				  -xy, 1 - yy, -yz,
				  -xz, -yz, 1 - zz);
}

Matrix Matrix::CreateFlipX()
{
	return Matrix(-1.f, 0.f,
				  0.f, 1.f,
				  0.f, 0.f);
}

Matrix Matrix::CreateFlipY()
{
	return Matrix(1.f, 0.f,
				  0.f, -1.f,
				  0.f, 0.f);
}

Matrix Matrix::CreateFlipZ()
{
	return Matrix(1.f, 0.f, 0.f,
				  0.f, 1.f, 0.f,
				  0.f, 0.f, -1.f);
}

Matrix Matrix::CreateFlipByPlane(const Point3F& normal)
{
	float xy2 = normal.X*normal.Y*2.f;
	float yz2 = normal.Y*normal.Z*2.f;
	float xz2 = normal.X*normal.Z*2.f;
	float xx2 = normal.X*normal.X*2.f;
	float yy2 = normal.Y*normal.Y*2.f;
	float zz2 = normal.Z*normal.Z*2.f;

	return Matrix(1 - xx2, -xy2, -xz2,
				  -xy2, 1 - yy2, -yz2,
				  -xz2, -yz2, 1 - zz2);
}


Matrix Matrix::CreateFlip(FlipMask flip /*= FlipMask::None*/, Point3F flipPivot /*= Point3F::Zero*/)
{
	float flipX = flip.Has(FlipMask::X) ? -1.f : 1.f;
	float flipY = flip.Has(FlipMask::Y) ? -1.f : 1.f;
	float flipZ = flip.Has(FlipMask::Z) ? -1.f : 1.f;

	return Matrix(flipX, 0.f, 0.f,
				  0.f, flipY, 0.f,
				  0.f, 0.f, flipZ,
				  -flipPivot.X, -flipPivot.Y, -flipPivot.Z);
}


Matrix Matrix::CreateShear(float xy, float xz, float yx, float yz, float zx, float zy)
{
	return Matrix(1.f, yx, zx,
				  xy, 1.f, zy,
				  xz, yz, 1.f,
				  0.f, 0.f, 0.f);
}


Matrix Matrix::CreateNormal()
{
	return Matrix(0.5f, 0.f, 0.f,
				  0.0f, 0.5f, 0.f,
				  0.0f, 0.f, 0.5f,
				  0.5f, 0.5f, 0.5f);
}



Matrix Matrix::AdjointMatrix()
{
	Matrix result;

	// We'll use i to incrementally compute -1 ^ (r+c)
	int k = 1;
	for (byte i = 0; i < 4; ++i)
	{
		for (byte j = 0; j < 4; ++j)
		{
			result[i * 4 + j] = SubDeterminant(i, j)*k;
			k = -k;
		}
		k = -k;
	}

	result.Transpose();
	return result;
}

float Matrix::SubDeterminant(byte row, byte column)
{
	byte myRow[3];
	byte myColumn[3];
	for (byte i = 0; i < 3; ++i)
	{
		myRow[i] = i;
		myColumn[i] = i;
		if (i >= row)
		{
			++myRow[i];
		}
		if (i >= column)
		{
			++myColumn[i];
		}
	}

	Matrix& m = *this;
	Point3F row1(m(myRow[0], myColumn[0]), m(myRow[0], myColumn[1]), m(myRow[0], myColumn[2]));
	Point3F row2(m(myRow[1], myColumn[0]), m(myRow[1], myColumn[1]), m(myRow[1], myColumn[2]));
	Point3F row3(m(myRow[2], myColumn[0]), m(myRow[2], myColumn[1]), m(myRow[2], myColumn[2]));
	return Point3F::TripleMultiply(row1, row2, row3);
}

Matrix Matrix::LookAtLH(const Vector3F& eyes, const Vector3F& target, const Vector3F& up)
{
	return LookAt(eyes, target, up, false);
}

Matrix Matrix::LookAtRH(const Vector3F& eyes, const Vector3F& target, const Vector3F& up)
{
	return LookAt(eyes, target, up, true);
}

Matrix Matrix::LookAt(const Vector3F& eyes, const Vector3F& target, const Vector3F& up, bool isRightHand/*=MEDUSA_IS_RIGHT_HAND*/)
{
	//sdk=GraphicsSDK::DirectX;
	if (isRightHand)
	{

		// f-> look/z   
		// u-> up/y   
		// s-> right/x   
		/*Vector3F f = target - eyes;
		f.Normalize();
		Vector3F s = f.CrossMultiply(up);
		s.Normalize();
		Vector3F u = s.CrossMultiply(f);
		float sdote = s.DotMultiply(eyes);
		float fdote = f.DotMultiply(eyes);
		float udote = u.DotMultiply(eyes);

		return Matrix(s.X,u.X,-f.X,0.f,
		s.Y,u.Y,-f.Y,0.f,
		s.Z,u.Z,-f.Z,0.f,
		-sdote,-udote,fdote,1.f);
		*/

		//right hand
		Vector3F zaxis = eyes - target;
		zaxis.Normalize();
		Vector3F xaxis = up.Cross(zaxis);
		xaxis.Normalize();
		Vector3F yaxis = zaxis.Cross(xaxis);	//because zaxis and xaxis have been normalized so no need for yaxis

		float x = xaxis.Dot(eyes);
		float y = yaxis.Dot(eyes);
		float z = zaxis.Dot(eyes);


		return Matrix(xaxis.X, yaxis.X, zaxis.X,
					  xaxis.Y, yaxis.Y, zaxis.Y,
					  xaxis.Z, yaxis.Z, zaxis.Z,
					  -x, -y, -z);


	}
	else
	{
		//left hand

		Vector3F zaxis = target - eyes;
		zaxis.Normalize();
		Vector3F xaxis = up.Cross(zaxis);
		xaxis.Normalize();
		Vector3F yaxis = zaxis.Cross(xaxis);	//because zaxis and xaxis have been normalized so no need for yaxis

		float x = xaxis.Dot(eyes);
		float y = yaxis.Dot(eyes);
		float z = zaxis.Dot(eyes);


		return Matrix(xaxis.X, yaxis.X, zaxis.X,
					  xaxis.Y, yaxis.Y, zaxis.Y,
					  xaxis.Z, yaxis.Z, zaxis.Z,
					  -x, -y, -z);
	}
}

Matrix Matrix::OrthoRH(float width, float height, float nearPlane, float farPlane, GraphicsSDK sdk/*=MEDUSA_DEFAULT_GRAPHICS_SDK*/)
{
	return Ortho(width, height, nearPlane, farPlane, true, sdk);
}

Matrix Matrix::OrthoLH(float width, float height, float nearPlane, float farPlane, GraphicsSDK sdk/*=MEDUSA_DEFAULT_GRAPHICS_SDK*/)
{
	return Ortho(width, height, nearPlane, farPlane, false, sdk);
}

Matrix Matrix::Ortho(float width, float height, float nearPlane, float farPlane, bool isRightHand/*=MEDUSA_IS_RIGHT_HAND*/, GraphicsSDK sdk/*=MEDUSA_DEFAULT_GRAPHICS_SDK*/)
{
	float halfWidth = width*0.5f;;
	float halfHeight = height*0.5f;
	return OrthoOffCenter(-halfWidth, halfWidth, -halfHeight, halfHeight, nearPlane, farPlane, isRightHand, sdk);
}


Matrix Matrix::OrthoOffCenterRH(float left, float right, float bottom, float top, float nearPlane, float farPlane, GraphicsSDK sdk/*=MEDUSA_DEFAULT_GRAPHICS_SDK*/)
{
	return OrthoOffCenter(left, right, bottom, top, nearPlane, farPlane, true, sdk);
}

Matrix Matrix::OrthoOffCenterLH(float left, float right, float bottom, float top, float nearPlane, float farPlane, GraphicsSDK sdk/*=MEDUSA_DEFAULT_GRAPHICS_SDK*/)
{
	return OrthoOffCenter(left, right, bottom, top, nearPlane, farPlane, false, sdk);
}


Matrix Matrix::OrthoOffCenter(float left, float right, float bottom, float top, float nearPlane, float farPlane, bool isRightHand/*=MEDUSA_IS_RIGHT_HAND*/, GraphicsSDK sdk/*=MEDUSA_DEFAULT_GRAPHICS_SDK*/)
{
	/*
	OpenGL
	[2/(r-l),0,0,-(r+l)/(r-l)]	[x]
	[0,2/(t-b),0,-(t+b)/(t-b)]	[y]
	[0,0,2/(n-f),(n+f)/(n-f)]	[z]
	[0,0,0,1]					[1]
	DirectX
	[x,y,z,1]	[2/(r-l),0,0,0]
	[0,2/(t-b),0,0]
	[0,0,1/(f-n),0]
	[-(r+l)/(r-l),-(t+b)/(t-b),-n/(f-n),1]
	*/

	float widthRcp = 1.f / (right - left);
	float heightRcp = 1.f / (top - bottom);
	float depthRcp = 1.f / (farPlane - nearPlane);

	if (sdk == GraphicsSDK::OpenGL)
	{
		if (isRightHand)
		{
			/*
			OpenGL
			[2/(r-l),0,0,-(r+l)/(r-l)]	[x]
			[0,2/(t-b),0,-(t+b)/(t-b)]	[y]
			[0,0,-2/(f-n),-(n+f)/(f-n)]	[z]
			[0,0,0,1]					[1]
			*/
			return Matrix(2.f*widthRcp, 0.f, 0.f, -(right + left)*widthRcp,
						  0.f, 2 * heightRcp, 0.f, -(top + bottom)*widthRcp,
						  0.f, 0.f, -2.f*depthRcp, -(nearPlane + farPlane)*depthRcp,
						  0.f, 0.f, 0.f, 1.f, MatrixFlags::Affine, true);
		}
		else
		{
			/*
			OpenGL
			[2/(r-l),0,0,-(r+l)/(r-l)]	[x]
			[0,2/(t-b),0,-(t+b)/(t-b)]	[y]
			[0,0,2/(f-n),-(n+f)/(f-n)]	[z]
			[0,0,0,1]					[1]
			*/
			return Matrix(2.f*widthRcp, 0.f, 0.f, -(right + left)*widthRcp,
						  0.f, 2 * heightRcp, 0.f, -(top + bottom)*widthRcp,
						  0.f, 0.f, 2.f*depthRcp, -(nearPlane + farPlane)*depthRcp,
						  0.f, 0.f, 0.f, 1.f, MatrixFlags::Affine, true);
		}
	}
	else
	{
		if (isRightHand)
		{
			/*
			DirectX
			[x,y,z,1]	[2/(r-l),0,0,0]
			[0,2/(t-b),0,0]
			[0,0,-1/(f-n),0]
			[-(r+l)/(r-l),-(t+b)/(t-b),-n/(f-n),1]
			*/

			return Matrix(2.f*widthRcp, 0.f, 0.f,
						  0.f, 2 * heightRcp, 0.f,
						  0.f, 0.f, -depthRcp,
						  -(right + left)*widthRcp, -(top + bottom)*widthRcp, -nearPlane*depthRcp);
		}
		else
		{
			/*
			DirectX
			[x,y,z,1]	[2/(r-l),0,0,0]
			[0,2/(t-b),0,0]
			[0,0,1/(f-n),0]
			[-(r+l)/(r-l),-(t+b)/(t-b),-n/(f-n),1]
			*/

			return Matrix(2.f*widthRcp, 0.f, 0.f,
						  0.f, 2 * heightRcp, 0.f,
						  0.f, 0.f, depthRcp,
						  -(right + left)*widthRcp, -(top + bottom)*widthRcp, -nearPlane*depthRcp);
		}

	}
}

Matrix Matrix::PerspectiveOffCenterLH(float left, float right, float bottom, float top, float nearPlane, float farPlane, GraphicsSDK sdk/*=MEDUSA_DEFAULT_GRAPHICS_SDK*/)
{
	return PerspectiveOffCenter(left, right, bottom, top, nearPlane, farPlane, false, sdk);
}

Matrix Matrix::PerspectiveOffCenterRH(float left, float right, float bottom, float top, float nearPlane, float farPlane, GraphicsSDK sdk/*=MEDUSA_DEFAULT_GRAPHICS_SDK*/)
{
	return PerspectiveOffCenter(left, right, bottom, top, nearPlane, farPlane, true, sdk);
}

Matrix Matrix::PerspectiveOffCenter(float left, float right, float bottom, float top, float nearPlane, float farPlane, bool isRightHand/*=MEDUSA_IS_RIGHT_HAND*/, GraphicsSDK sdk/*=MEDUSA_DEFAULT_GRAPHICS_SDK*/)
{
	//the difference between left hand with right hand corrdinate  is whether flip z. For opengl, is to flip 3rd colum,for directX, flip 3rd row
	float widthRcp = 1.f / (right - left);
	float heightRcp = 1.f / (top - bottom);
	float depthRcp = 1.f / (farPlane - nearPlane);

	if (sdk == GraphicsSDK::OpenGL)
	{
		if (isRightHand)
		{
			/*
			OpenGL
			[2n/(r-l),0,(r+l)/(r-l),0]	[x]
			[0,2n/(t-b),(t+b)/(t-b),0]	[y]
			[0,0,-(n+f)/(f-n),-2nf/(f-n)]	[z]
			[0,0,-1,0]					[1]
			*/
			return Matrix(2.f*nearPlane*widthRcp, 0.f, (right + left)*widthRcp, 0.f,
						  0.f, 2.f*nearPlane*heightRcp, (top + bottom)*widthRcp, 0.f,
						  0.f, 0.f, -(nearPlane + farPlane)*depthRcp, -2.f*nearPlane*farPlane*depthRcp,
						  0.f, 0.f, -1.f, 0.f, MatrixFlags::None, true);
		}
		else
		{
			/*
			OpenGL
			[2n/(r-l),0,-(r+l)/(r-l),0]	[x]
			[0,2n/(t-b),-(t+b)/(t-b),0]	[y]
			[0,0,(n+f)/(f-n),2nf/(f-n)]	[z]
			[0,0,1,0]					[1]
			*/
			return Matrix(2.f*nearPlane*widthRcp, 0.f, -(right + left)*widthRcp, 0.f,
						  0.f, 2.f*nearPlane*heightRcp, -(top + bottom)*widthRcp, 0.f,
						  0.f, 0.f, -(nearPlane + farPlane)*depthRcp, 2.f*nearPlane*farPlane*depthRcp,
						  0.f, 0.f, 1.f, 0.f, MatrixFlags::None, true);
		}
	}
	else
	{
		if (isRightHand)
		{
			/*
			DirectX
			[x,y,z,1]	[2n/(r-l),0,0,0]
			[0,2n/(t-b),0,0]
			[(r+l)/(r-l),(t+b)/(t-b),-f/(f-n),-1]
			[0,0,-nf/(f-n),0]
			*/
			return Matrix(2.f*nearPlane*widthRcp, 0.f, 0.f, 0.f,
						  0.f, 2 * nearPlane*heightRcp, 0.f, 0.f,
						  (right + left)*widthRcp, (top + bottom)*widthRcp, -farPlane*depthRcp, -1.f,
						  0.f, 0.f, -nearPlane*farPlane*depthRcp, 0.f);
		}
		else
		{
			/*
			DirectX
			[x,y,z,1]	[2n/(r-l),0,0,0]
			[0,2n/(t-b),0,0]
			[-(r+l)/(r-l),-(t+b)/(t-b),f/(f-n),1]
			[0,0,-nf/(f-n),0]
			*/

			return Matrix(2.f*nearPlane*widthRcp, 0.f, 0.f, 0.f,
						  0.f, 2 * nearPlane*heightRcp, 0.f, 0.f,
						  -(right + left)*widthRcp, -(top + bottom)*widthRcp, farPlane*depthRcp, 1.f,
						  0.f, 0.f, -nearPlane*farPlane*depthRcp, 0.f);
		}

	}
}

Matrix Matrix::PerspectiveLH(float width, float height, float nearPlane, float farPlane, GraphicsSDK sdk/*=MEDUSA_DEFAULT_GRAPHICS_SDK*/)
{
	return Perspective(width, height, nearPlane, farPlane, false, sdk);
}

Matrix Matrix::PerspectiveRH(float width, float height, float nearPlane, float farPlane, GraphicsSDK sdk/*=MEDUSA_DEFAULT_GRAPHICS_SDK*/)
{
	return Perspective(width, height, nearPlane, farPlane, true, sdk);
}

Matrix Matrix::Perspective(float width, float height, float nearPlane, float farPlane, bool isRightHand/*=MEDUSA_IS_RIGHT_HAND*/, GraphicsSDK sdk/*=MEDUSA_DEFAULT_GRAPHICS_SDK*/)
{
	float halfWidth = width*0.5f;;
	float halfHeight = height*0.5f;
	return PerspectiveOffCenter(-halfWidth, halfWidth, -halfHeight, halfHeight, nearPlane, farPlane, isRightHand, sdk);
}

Matrix Matrix::PerspectiveFOVLH(float fovY, float aspect, float nearPlane, float farPlane, GraphicsSDK sdk/*=MEDUSA_DEFAULT_GRAPHICS_SDK*/)
{
	return PerspectiveFOV(fovY, aspect, nearPlane, farPlane, false, sdk);
}

Matrix Matrix::PerspectiveFOVRH(float fovY, float aspect, float nearPlane, float farPlane, GraphicsSDK sdk/*=MEDUSA_DEFAULT_GRAPHICS_SDK*/)
{
	return PerspectiveFOV(fovY, aspect, nearPlane, farPlane, true, sdk);
}

Matrix Matrix::PerspectiveFOV(float fovY, float aspect, float nearPlane, float farPlane, bool isRightHand/*=MEDUSA_IS_RIGHT_HAND*/, GraphicsSDK sdk/*=MEDUSA_DEFAULT_GRAPHICS_SDK*/)
{
	float height = 2.f*nearPlane*Math::Tan(fovY*0.5f);
	float width = height*aspect;
	return Perspective(width, height, nearPlane, farPlane, isRightHand, sdk);
}

Matrix Matrix::CreateBillboard(const Vector3F& objectPosition, const Vector3F& cameraPosition, const Vector3F& cameraUp, const Vector3F& cameraForward/*=Vector3F::ForWard*/,
							   bool isRightHand/*=MEDUSA_IS_RIGHT_HAND*/, GraphicsSDK sdk/*=MEDUSA_DEFAULT_GRAPHICS_SDK*/)
{
	//TODO: test
	Vector3F cameraLook = objectPosition - cameraPosition;
	if (Math::IsZero(cameraLook.LengthSquared()))
	{
		cameraLook = cameraForward;
	}
	else
	{
		cameraLook.Normalize();
	}

	Vector3F cameraRight = cameraUp.Cross(cameraLook);
	cameraRight.Normalize();
	Vector3F newCameraUp = cameraLook.Cross(cameraRight);

	if (sdk == GraphicsSDK::OpenGL)
	{
		return Matrix(cameraRight.X, cameraRight.Y, cameraRight.Z,
					  newCameraUp.X, newCameraUp.Y, newCameraUp.Z,
					  cameraLook.X, cameraLook.Y, cameraLook.Z,
					  objectPosition.X, objectPosition.Y, objectPosition.Z, true);

	}
	else
	{
		return Matrix(cameraRight.X, cameraRight.Y, cameraRight.Z,
					  newCameraUp.X, newCameraUp.Y, newCameraUp.Z,
					  cameraLook.X, cameraLook.Y, cameraLook.Z,
					  objectPosition.X, objectPosition.Y, objectPosition.Z);

	}
}

Matrix Matrix::CreateConstrainedBillboard(const Vector3F& objectPosition, const Vector3F& cameraPosition, const Vector3F& rotateAxis, const Vector3F& cameraForward/*=Vector3F::ForWard*/, const Vector3F& objectForward/*=Vector3F::ForWard*/, bool isRightHand/*=MEDUSA_IS_RIGHT_HAND*/, GraphicsSDK sdk/*=MEDUSA_DEFAULT_GRAPHICS_SDK*/)
{
	//TODO: test
	const static float dotValue = 0.9982547f;
	Vector3F cameraLook = objectPosition - cameraPosition;
	if (Math::IsZero(cameraLook.LengthSquared()))
	{
		cameraLook = cameraForward;
	}
	else
	{
		cameraLook.Normalize();
	}

	Vector3F cameraRight;
	Vector3F newCameraUp;

	float num = rotateAxis.Dot(cameraLook);
	if (Math::Abs(num) > dotValue)	//Don't know why,copy from XNA.Matrix
	{
		if (objectForward != Vector3F::ForWard)
		{
			newCameraUp = objectForward;
			num = rotateAxis.Dot(newCameraUp);
			if (Math::Abs(num) > dotValue)
			{
				num = rotateAxis.Dot(Vector3F::ForWard);
				newCameraUp = Math::Abs(dotValue) > dotValue ? Vector3F::Right : Vector3F::ForWard;
			}
		}
		else
		{
			num = rotateAxis.Dot(Vector3F::ForWard);
			newCameraUp = Math::Abs(dotValue) > dotValue ? Vector3F::Right : Vector3F::ForWard;
		}

		cameraRight = rotateAxis.Cross(newCameraUp);
		cameraRight.Normalize();
		newCameraUp = cameraRight.Cross(rotateAxis);
		newCameraUp.Normalize();
	}
	else
	{
		cameraRight = rotateAxis.Cross(cameraLook);
		cameraRight.Normalize();
		newCameraUp = cameraRight.Cross(rotateAxis);
		newCameraUp.Normalize();
	}


	if (sdk == GraphicsSDK::OpenGL)
	{
		return Matrix(cameraRight.X, cameraRight.Y, cameraRight.Z,
					  newCameraUp.X, newCameraUp.Y, newCameraUp.Z,
					  cameraLook.X, cameraLook.Y, cameraLook.Z,
					  objectPosition.X, objectPosition.Y, objectPosition.Z, true);

	}
	else
	{
		return Matrix(cameraRight.X, cameraRight.Y, cameraRight.Z,
					  newCameraUp.X, newCameraUp.Y, newCameraUp.Z,
					  cameraLook.X, cameraLook.Y, cameraLook.Z,
					  objectPosition.X, objectPosition.Y, objectPosition.Z);

	}


}

void Matrix::DecomposeXYZ(Scale3F& outScale, Rotation3F& outRotation, Point3F& outTranslation)const
{
	//limit euler angle, limit y to +/-90, limit x,y to +/- 180

	/*
	Matrix(scale.X*cosY*cosZ,scale.X*cosY*sinZ,scale.X*(-sinY),0.f,
	scale.Y*(sinXsinY*cosZ-cosX*sinZ),scale.Y*(sinXsinY*sinZ+cosX*cosZ),scale.Y*sinX*cosY,0.f,
	scale.Z*(cosXsinY*cosZ+sinX*sinZ),scale.Z*(cosXsinY*sinZ-sinX*cosZ),scale.Z*cosX*cosY,0.f,
	translation.X,translation.Y,translation.Z,1.f);

	*/

	outTranslation = Translation();
	outScale.X = Math::Sqrt(M11*M11 + M12*M12 + M13*M13);
	outScale.Y = Math::Sqrt(M21*M21 + M22*M22 + M23*M23);
	outScale.Z = Math::Sqrt(M31*M31 + M32*M32 + M33*M33);

	outRotation.Y = Math::Asin(-M13 / outScale.X);
	float cosy = Math::Cos(outRotation.Y);

	float cosz = M11 / (outScale.X*cosy);
	float sinz = M12 / (outScale.X*cosy);
	outRotation.Z = Math::Atan2(sinz, cosz);

	if (Math::IsEqual(outRotation.Y, Math::PIHalf))
	{
		outRotation.X = 0.f;
	}
	else
	{
		float sinx = M23 / (outScale.Y*cosy);
		float cosx = M33 / (outScale.Z*cosy);
		outRotation.X = Math::Atan2(sinx, cosx);
	}
}

Point3F Matrix::Translation() const
{
	return Point3F(M41, M42, M43);
}

void Matrix::SetTranslation(const Point3F& val)
{
	M41 = val.X; M42 = val.Y; M43 = val.Z;
}

Point3F Matrix::Backward() const
{
	if (Flag.Has(MatrixFlags::Is2D))
	{
		return Point3F::Zero;
	}
	else
	{
		return Point3F(M31, M32, M33);
	}

}

void Matrix::SetBackward(const Point3F& val)
{
	M31 = val.X; M32 = val.Y; M33 = val.Z;
	Flag.Remove(MatrixFlags::Is2D);
}

Point3F Matrix::Forward() const
{
	if (Flag.Has(MatrixFlags::Is2D))
	{
		return Point3F::Zero;
	}
	else
	{
		return Point3F(-M31, -M32, -M33);
	}


}

void Matrix::SetForward(const Point3F& val)
{
	M31 = -val.X; M32 = -val.Y; M33 = -val.Z;
	Flag.Remove(MatrixFlags::Is2D);

}

intp Matrix::HashCode() const
{
	MatrixType type = (MatrixType)(Flag.ToUInt());
	switch (type)
	{
		case MatrixType::Matrix4:
			return HashUtility::Hash(M);
		case MatrixType::Matrix43:
			return HashUtility::Hash(M11) ^ HashUtility::Hash(M12) ^ HashUtility::Hash(M13) ^
				HashUtility::Hash(M21) ^ HashUtility::Hash(M22) ^ HashUtility::Hash(M23) ^
				HashUtility::Hash(M31) ^ HashUtility::Hash(M32) ^ HashUtility::Hash(M33) ^
				HashUtility::Hash(M41) ^ HashUtility::Hash(M42) ^ HashUtility::Hash(M43);
		case MatrixType::Matrix3:
			return HashUtility::Hash(M11) ^ HashUtility::Hash(M12) ^ HashUtility::Hash(M14) ^
				HashUtility::Hash(M21) ^ HashUtility::Hash(M22) ^ HashUtility::Hash(M24) ^
				HashUtility::Hash(M41) ^ HashUtility::Hash(M42) ^ HashUtility::Hash(M44);
			break;
		case MatrixType::Matrix2:
			return HashUtility::Hash(M11) ^ HashUtility::Hash(M12) ^
				HashUtility::Hash(M21) ^ HashUtility::Hash(M22) ^
				HashUtility::Hash(M41) ^ HashUtility::Hash(M42);

			break;
	}

	return 0;

}
void Matrix::UpdateFlag()
{
	/*
	44:
	[11,12,13,14]
	[21,22,23,24]
	[31,32,33,34]
	[41,42,43,44]

	43:
	[11,12,13,0]
	[21,22,23,0]
	[31,32,33,0]
	[41,42,43,1]

	3:
	[11,12,13,0]
	[21,22,23,0]
	[0,0,1,0]
	[41,42,43,1]

	2:
	[11,12,0,0]
	[21,22,0,0]
	[0,0,1,0]
	[41,42,0,1]

	*/

	if (Math::IsZero(M14) && Math::IsZero(M24) && Math::IsZero(M34) && Math::IsEqual(M44, 1.f))
	{
		if (Math::IsZero(M31) && Math::IsZero(M31) && Math::IsEqual(M33, 1.f))
		{
			if (Math::IsZero(M13) && Math::IsZero(M23) && Math::IsZero(M43))
			{
				Flag = MatrixFlags::Is2D | MatrixFlags::Affine;	//2
				return;
			}
			Flag = MatrixFlags::Is2D;	//33
			return;
		}

		Flag = MatrixFlags::Affine;	//43
		return;
	}
	Flag = MatrixFlags::None;	//4

}






#pragma endregion Transform

MEDUSA_END;
