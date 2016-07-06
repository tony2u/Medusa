// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Geometry/Matrix3.h"
#include "Geometry/Matrix2.h"
#include "Geometry/Matrix4.h"
#include "Geometry/Matrix43.h"

#include "Geometry/EulerAngle.h"
#include "Geometry/Quaternion.h"
#include "Geometry/Point2.h"

#include "Geometry/Size3.h"
#include "Geometry/Cube.h"
#include "Geometry/Scale3.h"
#include "Geometry/Rotation3.h"

#include "Geometry/Rect2.h"
#include "Geometry/Quad.h"
#include "Core/Math/Math.h"
#include "Core/System/BitConverter.h"
#include "Core/Assertion/CommonAssert.h"


MEDUSA_BEGIN;

const Matrix3 Matrix3::Zero=Matrix3(0.f,0.f,0.f,
	0.f,0.f,0.f,
	0.f,0.f,0.f);
const Matrix3 Matrix3::Identity=Matrix3(1.f,0.f,0.f,
	0.f,1.f,0.f,
	0.f,0.f,1.f);


Matrix3::Matrix3( const Matrix4& m ,bool isTransposed)
{
	if (isTransposed)
	{
		M11=m.M11;M12=m.M21;M13=m.M31;
		M21=m.M12;M22=m.M22;M23=m.M32;
		M31=m.M13;M32=m.M23;M33=m.M33;
	}
	else
	{
		M11=m.M11;M12=m.M12;M13=m.M13;
		M21=m.M21;M22=m.M22;M23=m.M23;
		M31=m.M31;M32=m.M32;M33=m.M33;
	}
	
}

Matrix3& Matrix3::operator=( const Matrix4& m )
{
	M11=m.M11;M12=m.M12;M13=m.M13;
	M21=m.M21;M22=m.M22;M23=m.M23;
	M31=m.M31;M32=m.M32;M33=m.M33;
	return *this;
}

Matrix3::Matrix3( const Matrix43& m ,bool isTransposed)
{
	if (isTransposed)
	{
		M11=m.M11;M12=m.M21;M13=m.M31;
		M21=m.M12;M22=m.M22;M23=m.M32;
		M31=m.M13;M32=m.M23;M33=m.M33;
	}
	else
	{
		M11=m.M11;M12=m.M12;M13=m.M13;
		M21=m.M21;M22=m.M22;M23=m.M23;
		M31=m.M31;M32=m.M32;M33=m.M33;
	}
}

Matrix3::Matrix3(const float* items)
{
	Memory::Copy(M, items, Size);
}

Matrix3& Matrix3::operator=( const Matrix43& m )
{
	M11=m.M11;M12=m.M12;M13=m.M13;
	M21=m.M21;M22=m.M22;M23=m.M23;
	M31=m.M31;M32=m.M32;M33=m.M33;
	return *this;
}


Point3F Matrix3::Transform( const Point3F& point)const
{
	//prepend
	return Point3F(M11 * point.X + M21 * point.Y + M31 * point.Z,
		M12 * point.X + M22 * point.Y + M32 * point.Z,
		M13 * point.X + M23 * point.Y + M33 * point.Z);
}

Matrix3& Matrix3::Multiply( const Matrix3& m,MatrixOrder order )
{
	Matrix3 result;
	if (order==MatrixOrder::Prepend)
	{

		result.M11 = m.M11*M11 + m.M12*M21 + m.M13*M31;
		result.M12 = m.M11*M12 + m.M12*M22 + m.M13*M32;
		result.M13 = m.M11*M13 + m.M12*M23 + m.M13*M33;

		result.M21 = m.M21*M11 + m.M22*M21 + m.M23*M31;
		result.M22 = m.M21*M12 + m.M22*M22 + m.M23*M32;
		result.M23 = m.M21*M13 + m.M22*M23 + m.M23*M33;

		result.M31 = m.M31*M11 + m.M32*M21 + m.M33*M31;
		result.M32 = m.M31*M12 + m.M32*M22 + m.M33*M32;
		result.M33 = m.M31*M13 + m.M32*M23 + m.M33*M33;

	}
	else
	{
		result.M11 = M11*m.M11 + M12*m.M21 + M13*m.M31;
		result.M12 = M11*m.M12 + M12*m.M22 + M13*m.M32;
		result.M13 = M11*m.M13 + M12*m.M23 + M13*m.M33;

		result.M21 = M21*m.M11 + M22*m.M21 + M23*m.M31;
		result.M22 = M21*m.M12 + M22*m.M22 + M23*m.M32;
		result.M23 = M21*m.M13 + M22*m.M23 + M23*m.M33;

		result.M31 = M31*m.M11 + M32*m.M21 + M33*m.M31;
		result.M32 = M31*m.M12 + M32*m.M22 + M33*m.M32;
		result.M33 = M31*m.M13 + M32*m.M23 + M33*m.M33;
	}


	*this=result;
	return *this;
}

Matrix3& Matrix3::Append( const Matrix3& m )
{
	return Multiply(m,MatrixOrder::Append);
}

Matrix3& Matrix3::Prepend( const Matrix3& m )
{
	return Multiply(m,MatrixOrder::Prepend);
}
void Matrix3::SetRow( byte row,const Point3F& val )
{
	M[ColumnSize*row]=val.X;
	M[ColumnSize*row+1]=val.Y;
	M[ColumnSize*row+2]=val.Z;
}

Point3F Matrix3::Column( byte column )
{
	return Point3F(M[column],M[RowSize+column],M[2*RowSize+column]);
}

void Matrix3::SetColumn( byte column,const Point3F& val )
{
	M[column]=val.X;
	M[RowSize+column]=val.Y;
	M[2*RowSize+column]=val.Z;
}

HeapString Matrix3::ToString() const
{
	/*
	[11,12,13]	
	[21,22,23]	
	[31,32,33]	
	*/

	HeapString result;
	result.Format("[{},{},{}]\n[{},{},{}]\n[{},{},{}]",M11,M12,M13,M21,M22,M23,M31,M32,M33);
	return result;
}


float Matrix3::Determinant() const
{
	return (M12*M23-M13*M22)*M31+(M13*M21-M11*M23)*M32+(M11*M22-M12*M21)*M33;
}

bool Matrix3::IsIdentity() const
{
	return Memory::EqualsFloat(M, Identity.M);
}

bool Matrix3::IsZero() const
{
	return Memory::EqualsFloat(M, Zero.M);
}

bool Matrix3::operator==( const Matrix3& matrix ) const
{
	return Memory::EqualsFloat(M, matrix.M);
}

bool Matrix3::operator!=( const Matrix3& matrix ) const
{
	return !Memory::EqualsFloat(M, matrix.M);
}

#pragma region Transform

Matrix3& Matrix3::Inverse()
{
	*this=CreateInverse();
	return *this;
}

Matrix3& Matrix3::Transpose()
{
	Math::Swap(M12,M21);
	Math::Swap(M13,M31);
	Math::Swap(M23,M32);
	return *this;
}

Matrix3& Matrix3::Scale( const Scale3F& scale )
{
	M11*=scale.X;
	M22*=scale.Y;
	M33*=scale.Z;
	return *this;
}

Matrix3& Matrix3::RotateXYZ( const Rotation3F& rotation )
{
	Matrix3 temp=CreateRotateXYZ(rotation);
	Append(temp);
	return *this;
}

Matrix3& Matrix3::RotateX( float radian)
{
	float cosX=Math::Cos(radian);
	float sinX=Math::Sin(radian);
	float old=M12;

	M12 = M12*cosX + M13*-sinX;
	M13 = old*sinX + M13*cosX;

	old=M22;
	M22 = M22*cosX + M23*-sinX;
	M23 = old*sinX + M23*cosX;

	old=M32;
	M32 = M32*cosX + M33*-sinX;
	M33 = old*sinX + M33*cosX;
	return *this;
}

Matrix3& Matrix3::RotateY( float radian )
{
	float cosY=Math::Cos(radian);
	float sinY=Math::Sin(radian);

	float old=M11;

	M11 = M11*cosY + M13*sinY;
	M13 = old*-sinY + M13*cosY;

	old=M21;
	M21 = M21*cosY + M23*sinY;
	M23 = old*-sinY + M23*cosY;

	old=M31;
	M31 = M31*cosY + M33*sinY;
	M33 = old*-sinY + M33*cosY;
	return *this;
}

Matrix3& Matrix3::RotateZ( float radian )
{
	float cosZ=Math::Cos(radian);
	float sinZ=Math::Sin(radian);
	float old=M11;

	M11 = M11*cosZ + M12*-sinZ;
	M12 = old*sinZ + M12*cosZ;

	old=M21;
	M21 = M21*cosZ + M22*-sinZ; 
	M22 = old*sinZ + M22*cosZ;

	old=M31;
	M31 = M31*cosZ + M32*-sinZ; 
	M32 = old*sinZ + M32*cosZ;
	return *this;
}

Matrix3& Matrix3::RotateEuler( const EulerAngle& angle )
{
	Matrix3 temp=CreateFromEuler(angle);
	Append(temp);
	return *this;
}

Matrix3& Matrix3::FlipX()
{
	M11=-M11;
	M21=-M21;
	M31=-M31;
	return *this;
}

Matrix3& Matrix3::FlipY()
{
	M12=-M12;
	M22=-M22;
	M32=-M32;
	return *this;
}

Matrix3& Matrix3::FlipZ()
{
	M13=-M13;
	M23=-M23;
	M33=-M33;
	return *this;
}

Matrix3 Matrix3::CreateInverse()
{
	float det=Determinant();
	if (Math::IsEqual(det,0.f))
	{
		MEDUSA_ASSERT_FAILED("Matrix has no inverse: singular matrix");
	}
	det=1.f/det;

	return Matrix3(( M22 * M33 - M32 * M23 ) * det,- ( M12 * M33 - M32 * M13 ) * det, ( M12 * M23 - M22 * M13 ) * det,
		- ( M21 * M33 - M31 * M23 ) * det,( M11 * M33 - M31 * M13 ) * det,- ( M11 * M23 - M21 * M13 ) * det,
		 ( M21 * M32 - M31 * M22 ) * det,- ( M11 * M32 - M31 * M12 ) * det,( M11 * M22 - M21 * M12 ) * det);
}

Matrix3 Matrix3::CreateTranspose()
{
	return Matrix3(M11,M21,M31,
					M12,M22,M32,
					M13,M23,M33);
}


Matrix3 Matrix3::CreateScale( const Scale3F& scale )
{
	return Matrix3(scale.X,0.f,0.f,
		0.f,scale.Y,0.f,
		0.f,0.f,scale.Z);
}

Matrix3 Matrix3::CreateScaleAxis( const Point3F& axis,float scale )
{
	float xy=axis.X*axis.Y;
	float yz=axis.Y*axis.Z;
	float xz=axis.X*axis.Z;
	float xx=axis.X*axis.X;
	float yy=axis.Y*axis.Y;
	float zz=axis.Z*axis.Z;
	float scaleMinusOne=scale-1.f;

	return Matrix3(1+scaleMinusOne*xx,scaleMinusOne*xy,scaleMinusOne*xz,
		scaleMinusOne*xy,1+scaleMinusOne*yy,scaleMinusOne*yz,
		scaleMinusOne*xz,scaleMinusOne*yz,1+scaleMinusOne*zz);
}

Matrix3 Matrix3::CreateRotateXYZ( const Rotation3F& rotation )
{
	//rotate order: x,y,z
	float cosY=Math::Cos(rotation.Y);
	float cosZ=Math::Cos(rotation.Z);
	float cosX=Math::Cos(rotation.X);

	float sinY=Math::Sin(rotation.Y);
	float sinZ=Math::Sin(rotation.Z);
	float sinX=Math::Sin(rotation.X);

	float sinXsinY=sinX*sinY;
	float cosXsinY=cosX*sinY;

	return Matrix3(cosY*cosZ,cosY*sinZ,-sinY,
		sinXsinY*cosZ-cosX*sinZ,sinXsinY*sinZ+cosX*cosZ,sinX*cosY,
		cosXsinY*cosZ+sinX*sinZ,cosXsinY*sinZ,cosX*cosY);
}

Matrix3 Matrix3::CreateRotateX( float radian )
{
	float cosX=Math::Cos(radian);
	float sinX=Math::Sin(radian);

	return Matrix3(	1.f,0.f,0.f,
		0.f,cosX,sinX,
		0.f,-sinX,cosX);
}

Matrix3 Matrix3::CreateRotateY( float radian )
{
	float cosY=Math::Cos(radian);
	float sinY=Math::Sin(radian);

	return Matrix3(cosY,0.f,-sinY,
		0.f,1.f,0.f,
		sinY,0.f,cosY);
}

Matrix3 Matrix3::CreateRotateZ( float radian )
{
	float cosZ=Math::Cos(radian);
	float sinZ=Math::Sin(radian);

	return Matrix3(cosZ,sinZ,0.f,
		-sinZ,cosZ,0.f,
		0.f,0.f,1.f);
}

Matrix3 Matrix3::CreateRotateAxis( const Point3F& axis,float radian )
{
	float cosValue=Math::Cos(radian);
	float sinValue=Math::Sin(radian);
	float oneMinusCosValue=1-cosValue;

	float xy=axis.X*axis.Y;
	float yz=axis.Y*axis.Z;
	float xz=axis.X*axis.Z;
	float xx=axis.X*axis.X;
	float yy=axis.Y*axis.Y;
	float zz=axis.Z*axis.Z;

	float xSin=axis.X*sinValue;
	float ySin=axis.Y*sinValue;
	float zSin=axis.Z*sinValue;


	return Matrix3(xx*oneMinusCosValue+cosValue,xy*oneMinusCosValue+zSin,xz*oneMinusCosValue-ySin,
		xy*oneMinusCosValue-zSin,yy*oneMinusCosValue+cosValue,yz*oneMinusCosValue+xSin,
		xz*oneMinusCosValue+ySin,yz*oneMinusCosValue-xSin,zz*oneMinusCosValue+cosValue);
}

Matrix3 Matrix3::CreateFromEuler( const EulerAngle& angle )
{
	float cosh=Math::Cos(angle.Heading);
	float cosp=Math::Cos(angle.Pitch);
	float cosb=Math::Cos(angle.Bank);

	float sinh=Math::Sin(angle.Heading);
	float sinp=Math::Sin(angle.Pitch);
	float sinb=Math::Sin(angle.Bank);

	return Matrix3(cosh*cosb+sinh*sinp*sinb,sinb*cosp,-sinh*cosb+cosh*sinp*sinb,
		-cosh*sinb+sinh*sinp*cosb,cosb*cosp,sinb*sinh+cosh*sinp*cosb,
		sinh*cosp,-sinp,cosh*cosp);
}

Matrix3 Matrix3::CreateFromQuaternion( const Quaternion& q )
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
	float xx=q.X*q.X;
	float yy=q.Y*q.Y;
	float zz=q.Z*q.Z;
	float xy=q.X*q.Y;
	float xz=q.X*q.Z;
	float yz=q.Y*q.Z;
	float wx=q.W*q.X;
	float wy=q.W*q.Y;
	float wz=q.W*q.Z;

	return Matrix3(1.f - 2.f*(yy + zz), 2.f*(xy - wz), 2.f*(xz + wy),
		2.f*(xy + wz), 1 - 2.f*(xx + zz), 2.f*(yz - wx),
		2.f*(xz - wy), 2.f*(yz + wx), 1 - 2.f*(xx + yy));
}

Matrix3 Matrix3::CreateProjectToXY()
{
	return Matrix3(1.f,0.f,0.f,
		0.f,1.f,0.f,
		0.f,0.f,0.f);
}

Matrix3 Matrix3::CreateProjectToXZ()
{
	return Matrix3(1.f,0.f,0.f,
		0.f,0.f,0.f,
		0.f,0.f,1.f);
}

Matrix3 Matrix3::CreateProjectToYZ()
{
	return Matrix3(0.f,0.f,0.f,
		0.f,1.f,0.f,
		0.f,0.f,1.f);
}

Matrix3 Matrix3::CreateProjectToPlane( const Point3F& normal )
{
	float xy=normal.X*normal.Y;
	float yz=normal.Y*normal.Z;
	float xz=normal.X*normal.Z;
	float xx=normal.X*normal.X;
	float yy=normal.Y*normal.Y;
	float zz=normal.Z*normal.Z;

	return Matrix3(1-xx,-xy,-xz,
		-xy,1-yy,-yz,
		-xz,-yz,1-zz);
}

Matrix3 Matrix3::CreateFlipX()
{
	return Matrix3(-1.f,0.f,0.f,
		0.f,1.f,0.f,
		0.f,0.f,1.f);
}

Matrix3 Matrix3::CreateFlipY()
{
	return Matrix3(1.f,0.f,0.f,
		0.f,-1.f,0.f,
		0.f,0.f,1.f);
}

Matrix3 Matrix3::CreateFlipZ()
{
	return Matrix3(1.f,0.f,0.f,
		0.f,1.f,0.f,
		0.f,0.f,-1.f);
}

Matrix3 Matrix3::CreateFlipByPlane( const Point3F& normal )
{
	float xy2=normal.X*normal.Y*2.f;
	float yz2=normal.Y*normal.Z*2.f;
	float xz2=normal.X*normal.Z*2.f;
	float xx2=normal.X*normal.X*2.f;
	float yy2=normal.Y*normal.Y*2.f;
	float zz2=normal.Z*normal.Z*2.f;

	return Matrix3(1-xx2,-xy2,-xz2,
		-xy2,1-yy2,-yz2,
		-xz2,-yz2,1-zz2);
}

Matrix3 Matrix3::CreateShear( float xy,float xz,float yx,float yz,float zx,float zy )
{
	return Matrix3(1.f,yx,zx,
		xy,1.f,zy,
		xz,yz,1.f);
}







#pragma endregion Transform

MEDUSA_END;
