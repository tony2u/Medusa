// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Core/Geometry/Matrix3.h"
#include "Core/Geometry/Matrix2.h"
#include "Core/Geometry/Matrix4.h"
#include "Core/Geometry/Matrix43.h"

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
#include "Core/Memory/Memory.h"

MEDUSA_BEGIN;

Point2F Matrix2::Transform(const Point2F& point) const
{
	return Point2F(A * point.X + C * point.Y + X, B * point.X + D * point.Y + Y);
}

QuadVertex2 Matrix2::Transform(const QuadVertex2& quad) const
{
	QuadVertex2 result;
	result.LeftBottom = Transform(quad.LeftBottom);
	result.LeftTop = Transform(quad.LeftTop);
	result.RightBottom = Transform(quad.RightBottom);
	result.RightTop = Transform(quad.RightTop);
	return result;
}

QuadVertex2 Matrix2::Transform(const Rect2F& rect) const
{
	QuadVertex2 quad(rect.LeftBottom(),  rect.RightBottom(), rect.RightTop(), rect.LeftTop());
	return Transform(quad);
}


Matrix2& Matrix2::Multiply(const Matrix2& m, MatrixOrder order)
{
	if (order == MatrixOrder::Append)
	{
		float old = A;
		A = A*m.A + B*m.C;
		B = old*m.B + B*m.D;

		old = C;
		C = C*m.A + D*m.C;
		D = old*m.B + D*m.D;

		old = X;
		X = X*m.A + Y*m.C + m.X;
		Y = old*m.B + Y*m.D + m.Y;
	}
	else
	{
		X = m.X*A + m.Y*C + X;
		Y = m.X*B + m.Y*D + Y;

		
		D = m.C*B + m.D*D;
		B = m.A*B + m.B*D;

		
		C = m.C*A + m.D*C;
		A = m.A*A + m.B*C;
	}

	return *this;
}


Matrix2& Matrix2::Append(const Matrix2& m)
{
	return Multiply(m, MatrixOrder::Append);
}

Matrix2& Matrix2::Prepend(const Matrix2& m)
{
	return Multiply(m, MatrixOrder::Prepend);
}


bool Matrix2::IsIdentity() const
{
	return Memory::Equals(M, Identity.M);
}


float Matrix2::Determinant() const
{
	return A * D - B * C;
}

bool Matrix2::IsInvertible() const
{
	return !Math::IsZero(Determinant());
}


Scale2F Matrix2::GetScale() const
{
	return Scale2F(Math::Hypot(A, B), Math::Hypot(C, D));
}

float Matrix2::GetRotation() const
{
	float scaleX = Math::Hypot(A, B);
	float scaleY = Math::Hypot(C, D);
	float sinz = B / scaleX;
	float cosz = A / scaleY;
	return Math::Atan2(sinz, cosz);
}

void Matrix2::Decompose(Scale2F& outScale, float outRotation, Point2F& outTranslation) const
{
	outTranslation = Translation();

	/*
	Sx*cosZ,Sx*sinz,0
	-Sy*sinZ,Sy*cosZ,0
	x,y,1
	*/

	outScale.X = Math::Hypot(A, B);
	outScale.Y = Math::Hypot(C, D);

	float sinz = B / outScale.X;
	float cosz = A / outScale.X;

	outTranslation = Math::Atan2(sinz, cosz);

}

#pragma region Transform

Matrix2& Matrix2::Inverse()
{
	float determinant = Determinant();
	if (Math::IsZero(determinant))
	{
		MEDUSA_ASSERT_FAILED("Matrix has no inverse: singular matrix");
	}

	determinant = 1.f / determinant;
	float a = determinant * D;
	float b = -determinant * B;
	float c = -determinant * C;
	float d = determinant * A;
	float x = determinant * (C * Y - D * X);
	float y = determinant * (B * X - A * Y);
	A = a;
	B = b;
	C = c;
	D = d;
	X = x;
	Y = y;

	return *this;
}


Matrix2& Matrix2::Transpose()
{
	Math::Swap(B, C);
	return *this;
}

Matrix2& Matrix2::Translate(const Point2F& point)
{
	X += point.X;
	Y += point.Y;

	return *this;
}

Matrix2& Matrix2::Scale(const Scale2F& scale)
{
	A *= scale.X;
	B *= scale.Y;
	C *= scale.X;
	D *= scale.Y;
	X *= scale.X;
	Y *= scale.Y;

	return *this;

}

Matrix2& Matrix2::Rotate(float radian)
{
	float cosZ = Math::Cos(radian);
	float sinZ = Math::Sin(radian);

	float old = A;
	A = A*cosZ - B*sinZ;
	B = old*sinZ + B*cosZ;

	old = C;
	C = C*cosZ - D*sinZ;
	D = old*sinZ + D*cosZ;

	old = X;
	X = X*cosZ - Y*sinZ;
	Y = old*sinZ + Y*cosZ;

	return *this;

}

Matrix2& Matrix2::FlipX()
{
	A = -A;
	C = -C;
	X = -X;

	return *this;

}

Matrix2& Matrix2::FlipY()
{
	B = -B;
	D = -D;
	Y = -Y;

	return *this;

}


Matrix2& Matrix2::ResetWorld(const Scale2F& scale, float radian, const Point2F& translation)
{
	*this = CreateWorld(scale, radian, translation);
	return *this;
}

Matrix2& Matrix2::ResetWorldEx(const Scale2F& scale, float radian, const Point2F& translation, FlipMask flip /*= FlipMask::None*/, Point2F flipPivot /*= Point2F::Zero*/, const Point2F& pivot /*= Point2F::Zero*/)
{
	*this = CreateWorldEx(scale, radian, translation, flip, flipPivot, pivot);
	return *this;
}

Matrix2& Matrix2::ResetWorldEx(const Size2F& size, const Point2F& anchor, const Scale2F& scale, float radian, const Point2F& translation, FlipMask flip /*= FlipMask::None*/)
{
	*this = CreateWorldEx(size, anchor, scale, radian, translation, flip);
	return *this;
}

Matrix2 Matrix2::CreateInverse()
{
	float determinant = 1 / (A * D - B * C);
	float a = determinant * D;
	float b = -determinant * B;
	float c = -determinant * C;
	float d = determinant * A;
	float x = determinant * (C * Y - D * X);
	float y = determinant * (B * X - A * Y);

	return Matrix2(a, b, c, d, x, y);
}

Matrix2 Matrix2::CreateTranspose()
{
	return Matrix2(A, C,
				   B, D,
				   X, Y);
}

Matrix2 Matrix2::CreateTranslate(const Point2F& point)
{
	return Matrix2(1.f, 0.f,
				   0.f, 1.f,
				   point.X, point.Y);
}

Matrix2 Matrix2::CreateScale(const Scale2F& scale)
{
	return Matrix2(scale.X, 0.f,
				   0.f, scale.Y,
				   0.f, 0.f);
}

Matrix2 Matrix2::CreateRotate(float radian)
{
	float cosZ = Math::Cos(radian);
	float sinZ = Math::Sin(radian);

	return Matrix2(cosZ, sinZ,
				   -sinZ, cosZ,
				   0.f, 0.f);

}

Matrix2 Matrix2::CreateFlipX()
{
	return Matrix2(-1.f, 0.f,
				   0.f, 1.f,
				   0.f, 0.f);
}

Matrix2 Matrix2::CreateFlipY()
{
	return Matrix2(1.f, 0.f,
				   0.f, -1.f,
				   0.f, 0.f);
}

Matrix2 Matrix2::CreateFlip(FlipMask flip /*= FlipMask::None*/)
{
	float flipX = flip.Has(FlipMask::X) ? -1.f : 1.f;
	float flipY = flip.Has(FlipMask::Y) ? -1.f : 1.f;

	return Matrix2(flipX, 0.f,
				   0.f, flipY,
				   0.f, 0.f);
}

Matrix2 Matrix2::CreateWorld(const Scale2F& scale, float radian, const Point2F& translation)
{
	if (!Math::IsZero(radian))
	{
		float cosZ = Math::Cos(radian);
		float sinZ = Math::Sin(radian);

		return Matrix2(scale.X*cosZ, scale.X*sinZ,
					   -scale.Y*sinZ, scale.Y*cosZ,
					   translation.X, translation.Y);
	}
	else
	{
		return Matrix2(scale.X, 0.f,
					   0.f, scale.Y,
					   translation.X, translation.Y);
	}

}

Matrix2 Matrix2::CreateWorldEx(const Size2F& size, const Point2F& anchor, const Scale2F& scale, float radian, const Point2F& translation, FlipMask flip /*= FlipMask::None*/)
{
	Point2F pivot(anchor.X*size.Width, anchor.Y*size.Height);
	float flipX = flip.Has(FlipMask::X) ? 1.f : 0.f;
	float flipY = flip.Has(FlipMask::Y) ? 1.f : 0.f;

	Point2F flipPivot(0.5f*size.Width*flipX, 0.5f*size.Height*flipY);

	return CreateWorldEx(scale, radian, translation, flip, flipPivot, pivot);
}


Matrix2 Matrix2::CreateWorldEx(const Scale2F& scale, float radian, const Point2F& translation, FlipMask flip /*= FlipMask::None*/, Point2F flipPivot /*= Point2F::Zero*/, const Point2F& pivot /*= Point2F::Zero*/)
{
	//Matrix order: flipPivot*flip*pivot*scale*rotation*translation
	float flipX = flip.Has(FlipMask::X) ? 1.f : 0.f;
	float flipY = flip.Has(FlipMask::Y) ? 1.f : 0.f;

	if (!Math::IsZero(radian))
	{
		float cosZ = Math::Cos(radian);
		float sinZ = Math::Sin(radian);

		float m11 = scale.X*cosZ;
		float m12 = scale.X*sinZ;

		float m21 = -scale.Y* sinZ;
		float m22 = scale.Y* cosZ;

		float m41 = translation.X - pivot.X*m11 - pivot.Y*m21;
		float m42 = translation.Y - pivot.X*m12 - pivot.Y*m22;

		return Matrix2(m11*flipX, m12,
					   m21, m22*flipY,
					   -flipPivot.X*m11*flipX + m41, -flipPivot.Y*m22*flipY + m42);
	}
	else
	{
		return Matrix2(scale.X*flipX, 0.f,
					   0.f, scale.Y*flipY,
					   -flipPivot.X*scale.X*flipX + translation.X - scale.X*pivot.X, -flipPivot.Y*scale.Y*flipY + translation.Y - scale.Y*pivot.Y);
	}
}




#pragma endregion Transform

const Matrix2 Matrix2::Zero = Matrix2(0.f, 0.f, 0.f, 0.f,
									  0.f, 0.f);

const Matrix2 Matrix2::Identity = Matrix2(1.f, 0.f, 0.f, 1.f,
										  0.f, 0.f);


MEDUSA_END;
