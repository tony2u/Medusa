// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Core/Geometry/Matrix43.h"
#include "Core/Geometry/Matrix3.h"
#include "Core/Geometry/Matrix2.h"
#include "Core/Geometry/Matrix4.h"
#include "Core/Geometry/Matrix.h"



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

const Matrix43 Matrix43::Zero=Matrix43(0.f,0.f,0.f,
	0.f,0.f,0.f,
	0.f,0.f,0.f,
	0.f,0.f,0.f);
const Matrix43 Matrix43::Identity=Matrix43(1.f,0.f,0.f,
	0.f,1.f,0.f,
	0.f,0.f,1.f,
	0.f,0.f,0.f);


Matrix43::Matrix43( const Matrix4& m ,bool isTransposed)
{
	if (isTransposed)
	{
		M11=m.M11;M12=m.M21;M13=m.M31;
		M21=m.M12;M22=m.M22;M23=m.M32;
		M31=m.M13;M32=m.M23;M33=m.M33;
		M41=m.M14;M42=m.M24;M43=m.M34;
	}
	else
	{
		M11=m.M11;M12=m.M12;M13=m.M13;
		M21=m.M21;M22=m.M22;M23=m.M23;
		M31=m.M31;M32=m.M32;M33=m.M33;
		M41=m.M41;M42=m.M42;M43=m.M43;
	}

}

Matrix43& Matrix43::operator=( const Matrix4& m )
{
	M11=m.M11;M12=m.M12;M13=m.M13;
	M21=m.M21;M22=m.M22;M23=m.M23;
	M31=m.M31;M32=m.M32;M33=m.M33;
	M41=m.M41;M42=m.M42;M43=m.M43;
	return *this;
}

Matrix43::Matrix43( const Matrix3& m ,bool isTransposed)
{
	if (isTransposed)
	{
		M11=m.M11;M12=m.M21;M13=m.M31;
		M21=m.M12;M22=m.M22;M23=m.M31;
		M31=m.M13;M32=m.M23;M33=m.M33;
		M41=0.f;M42=0.f;M43=0.f;
	}
	else
	{
		M11=m.M11;M12=m.M12;M13=m.M13;
		M21=m.M21;M22=m.M22;M23=m.M23;
		M31=m.M31;M32=m.M32;M33=m.M33;
		M41=0.f;M42=0.f;M43=0.f;
	}
}

Matrix43::Matrix43(const Matrix& m, bool isTransposed /*= false*/)
{
	if (isTransposed)
	{
		M11 = m.M11; M12 = m.M21; M13 = m.M31;
		M21 = m.M12; M22 = m.M22; M23 = m.M32;
		M31 = m.M13; M32 = m.M23; M33 = m.M33;
		M41 = m.M14; M42 = m.M24; M43 = m.M34;
	}
	else
	{
		M11 = m.M11; M12 = m.M12; M13 = m.M13;
		M21 = m.M21; M22 = m.M22; M23 = m.M23;
		M31 = m.M31; M32 = m.M32; M33 = m.M33;
		M41 = m.M41; M42 = m.M42; M43 = m.M43;
	}
}

Matrix43::Matrix43(const float* items)
{
	Memory::Copy(M, items, Size);
}

Matrix43& Matrix43::operator=( const Matrix3& m )
{
	M11=m.M11;M12=m.M12;M13=m.M13;
	M21=m.M21;M22=m.M22;M23=m.M23;
	M31=m.M31;M32=m.M32;M33=m.M33;
	M41=0.f;M42=0.f;M43=0.f;
	return *this;
}

Matrix43& Matrix43::operator=(const Matrix& m)
{
	M11 = m.M11; M12 = m.M12; M13 = m.M13;
	M21 = m.M21; M22 = m.M22; M23 = m.M23;
	M31 = m.M31; M32 = m.M32; M33 = m.M33;
	M41 = m.M41; M42 = m.M42; M43 = m.M43;
	return *this;
}


Vector3F Matrix43::TransformVector( const Vector3F& point ) const
{
	return Point3F(M11 * point.X + M21 * point.Y + M31 * point.Z,
		M12 * point.X + M22 * point.Y + M32 * point.Z,
		M13 * point.X + M23 * point.Y + M33 * point.Z);
}


Point2F Matrix43::TransformPoint( const Point2F& point ) const
{
	return Point2F(M11 * point.X + M21 * point.Y +M41,
		M12 * point.X + M22 * point.Y +M42);
}

Point3F Matrix43::TransformPoint( const Point3F& point)const
{
	return Point3F(M11 * point.X + M21 * point.Y + M31 * point.Z+M41,
		M12 * point.X + M22 * point.Y + M32 * point.Z+M42,
		M13 * point.X + M23 * point.Y + M33 * point.Z+M43);
}

Point4F Matrix43::TransformPoint( const Point4F& point ) const
{
	return Point4F(M11 * point.X + M21 * point.Y + M31 * point.Z+M41*point.W,
		M12 * point.X + M22 * point.Y + M32 * point.Z+M42*point.W,
		M13 * point.X + M23 * point.Y + M33 * point.Z+M43*point.W,
		point.W
		);
}


Matrix43& Matrix43::Multiply( const Matrix43& m,MatrixOrder order )
{
	Matrix43 result;
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

		result.M41 = m.M41*M11 + m.M42*M21 + m.M43*M31 + M41;
		result.M42 = m.M41*M12 + m.M42*M22 + m.M43*M32 + M42;
		result.M43 = m.M41*M13 + m.M42*M23 + m.M43*M33 + M43;
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

		result.M41 = M41*m.M11 + M42*m.M21 + M43*m.M31 + m.M41;
		result.M42 = M41*m.M12 + M42*m.M22 + M43*m.M32 + m.M42;
		result.M43 = M41*m.M13 + M42*m.M23 + M43*m.M33 + m.M43;
		
	}


	*this=result;
	return *this;
}

Matrix43& Matrix43::Append( const Matrix43& m )
{
	return Multiply(m,MatrixOrder::Append);
}

Matrix43& Matrix43::Prepend( const Matrix43& m )
{
	return Multiply(m,MatrixOrder::Prepend);
}


void Matrix43::SetRow( byte row,const Point4F& val )
{
	M[ColumnSize*row]=val.X;
	M[ColumnSize*row+1]=val.Y;
	M[ColumnSize*row+2]=val.Z;
	M[ColumnSize*row+3]=val.W;
}

Point4F Matrix43::Column( byte column )
{
	return Point4F(M[column],M[RowSize+column],M[2*RowSize+column],M[3*RowSize+column]);
}

void Matrix43::SetColumn( byte column,const Point4F& val )
{
	M[column]=val.X;
	M[RowSize+column]=val.Y;
	M[2*RowSize+column]=val.Z;
	M[3*RowSize+column]=val.W;
}

HeapString Matrix43::ToString() const
{
	/*
	[11,12,13]	
	[21,22,23]	
	[31,32,33]	
	[41,42,43]	
	*/

	HeapString result;
	result.Format("[{},{},{}]\n[{},{},{}]\n[{},{},{}]\n[{},{},{}]",M11,M12,M13,M21,M22,M23,M31,M32,M33,M41,M42,M43);
	return result;
	
}

float Matrix43::Determinant() const
{
	//return A.Determinant
	return (M12*M23-M13*M22)*M31+(M13*M21-M11*M23)*M32+(M11*M22-M12*M21)*M33;

}

bool Matrix43::operator==( const Matrix43& matrix ) const
{
	return Memory::EqualsFloat(M, matrix.M);
}

bool Matrix43::operator!=( const Matrix43& matrix ) const
{
	return !Memory::EqualsFloat(M, matrix.M);
}

bool Matrix43::IsIdentity() const
{
	return Memory::EqualsFloat(M, Identity.M);
}

bool Matrix43::IsZero() const
{
	return Memory::EqualsFloat(M, Zero.M);
}

Point3F Matrix43::GetTranslation() const
{
	return Point3F(M41,M42,M43);
}

#pragma region Transform

Matrix43& Matrix43::Inverse()
{
	*this=CreateInverse();
	return *this;
}

Matrix43& Matrix43::Transpose()
{
	Math::Swap(M12,M21);
	Math::Swap(M13,M31);
	Math::Swap(M23,M32);
	M41=0.f;
	M42=0.f;
	M43=0.f;
	return *this;
}

Matrix43& Matrix43::Translate( const Point3F& point)
{
	M41+=point.X;
	M42+=point.Y;
	M43+=point.Z;
	return *this;
}

Matrix43& Matrix43::Scale( const Scale3F& scale)
{
	M11*=scale.X;
	M22*=scale.Y;
	M33*=scale.Z;

	M41+=M41*scale.X;
	M42+=M42*scale.Y;
	M43+=M43*scale.Z;
	return *this;
}

Matrix43& Matrix43::RotateXYZ( const Rotation3F& rotation)
{
	Matrix43 temp=CreateRotateXYZ(rotation);
	Append(temp);
	return *this;
}

Matrix43& Matrix43::RotateX( float radian)
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

	old=M42;
	M42+=M42*cosX+M43*-sinX;
	M43+=old*sinX+M43*cosX;
	return *this;
}

Matrix43& Matrix43::RotateY( float radian)
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

	old=M41;
	M41+=M41*cosY+M43*sinY;
	M43+=old*-sinY+M43*cosY;
	return *this;
}

Matrix43& Matrix43::RotateZ( float radian)
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

	old=M41;
	M41+=M41*cosZ+M42*-sinZ;
	M42+=old*sinZ+M42*cosZ;
	return *this;
}

Matrix43& Matrix43::RotateEuler( const EulerAngle& angle)
{
	Matrix43 temp=CreateFromEuler(angle);
	Append(temp);
	return *this;
}

Matrix43& Matrix43::FlipX()
{
	M11=-M11;
	M21=-M21;
	M31=-M31;
	M41=-M41;
	return *this;
}

Matrix43& Matrix43::FlipY()
{
	M12=-M12;
	M22=-M22;
	M32=-M32;
	M42=-M42;
	return *this;
}

Matrix43& Matrix43::FlipZ()
{
	M13=-M13;
	M23=-M23;
	M33=-M33;
	M43=-M43;
	return *this;
}

Matrix43 Matrix43::CreateInverse()
{
	//			Should be		[A 0]
	//							[B 1]

	float det=Determinant();
	if (Math::IsEqual(det,0.f))
	{
		MEDUSA_ASSERT_FAILED("Matrix has no inverse: singular matrix");
	}
	det=1.f/det;
	Matrix43 result;

	/*
	mat=A*B
	=> (A*B)-1=B-1*A-1=mat-1
	*/

	//inverse(A)=adj(A)/det;
	result.M11 =   ( M22 * M33 - M32 * M23 ) * det;
	result.M12 = - ( M12 * M33 - M32 * M13 ) * det;
	result.M13 =   ( M12 * M23 - M22 * M13 ) * det;
	result.M21 = - ( M21 * M33 - M31 * M23 ) * det;
	result.M22 =   ( M11 * M33 - M31 * M13 ) * det;
	result.M23 = - ( M11 * M23 - M21 * M13 ) * det;
	result.M31 =   ( M21 * M32 - M31 * M22 ) * det;
	result.M32 = - ( M11 * M32 - M31 * M12 ) * det;
	result.M33 =   ( M11 * M22 - M21 * M12 ) * det;
	//inverse(B)*inverse(A)
	//inverse(B)=-B
	//mat-1=-B*inverse(A)
	result.M41 = - ( M41 * result.M11 + M42 * result.M21 + M43 * result.M31 );
	result.M42 = - ( M41 * result.M12 + M42 * result.M22 + M43 * result.M32 );
	result.M43 = - ( M41 * result.M13 + M42 * result.M23 + M43 * result.M33 );

	return result;
}

Matrix43 Matrix43::CreateTranspose()
{
	return Matrix43(M11,M21,M31,
		M12,M22,M32,
		M13,M23,M33,
		0.f,0.f,0.f);
}

Matrix43 Matrix43::CreateTranslate( const Point3F& point )
{
	return Matrix43(1.f,0.f,0.f,
		0.f,1.f,0.f,
		0.f,0.f,1.f,
		point.X,point.Y,point.Z);
}

Matrix43 Matrix43::CreateScale( const Scale3F& scale )
{
	return Matrix43(scale.X,0.f,0.f,
		0.f,scale.Y,0.f,
		0.f,0.f,scale.Z,
		0.f,0.f,0.f);
}

Matrix43 Matrix43::CreateScaleAxis( const Point3F& axis,float scale )
{
	float xy=axis.X*axis.Y;
	float yz=axis.Y*axis.Z;
	float xz=axis.X*axis.Z;
	float xx=axis.X*axis.X;
	float yy=axis.Y*axis.Y;
	float zz=axis.Z*axis.Z;
	float scaleMinusOne=scale-1.f;

	return Matrix43(1+scaleMinusOne*xx,scaleMinusOne*xy,scaleMinusOne*xz,
		scaleMinusOne*xy,1+scaleMinusOne*yy,scaleMinusOne*yz,
		scaleMinusOne*xz,scaleMinusOne*yz,1+scaleMinusOne*zz,
		0.f,0.f,0.f);
}

Matrix43 Matrix43::CreateRotateXYZ( const Rotation3F& rotation )
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

	return Matrix43(cosY*cosZ,cosY*sinZ,-sinY,
		sinXsinY*cosZ-cosX*sinZ,sinXsinY*sinZ+cosX*cosZ,sinX*cosY,
		cosXsinY*cosZ+sinX*sinZ,cosXsinY*sinZ-sinX*cosZ,cosX*cosY,
		0.f,0.f,0.f);
}

Matrix43 Matrix43::CreateRotateX( float radian )
{
	float cosX=Math::Cos(radian);
	float sinX=Math::Sin(radian);

	return Matrix43(	1.f,0.f,0.f,
		0.f,cosX,sinX,
		0.f,-sinX,cosX,
		0.f,0.f,0.f);
}

Matrix43 Matrix43::CreateRotateY( float radian )
{
	float cosY=Math::Cos(radian);
	float sinY=Math::Sin(radian);

	return Matrix43(cosY,0.f,-sinY,
		0.f,1.f,0.f,
		sinY,0.f,cosY,
		0.f,0.f,0.f);
}

Matrix43 Matrix43::CreateRotateZ( float radian )
{
	float cosZ=Math::Cos(radian);
	float sinZ=Math::Sin(radian);

	return Matrix43(cosZ,sinZ,0.f,
		-sinZ,cosZ,0.f,
		0.f,0.f,1.f,
		0.f,0.f,0.f);
}

Matrix43 Matrix43::CreateRotateAxis( const Point3F& axis,float radian )
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


	return Matrix43(xx*oneMinusCosValue+cosValue,xy*oneMinusCosValue+zSin,xz*oneMinusCosValue-ySin,
		xy*oneMinusCosValue-zSin,yy*oneMinusCosValue+cosValue,yz*oneMinusCosValue+xSin,
		xz*oneMinusCosValue+ySin,yz*oneMinusCosValue-xSin,zz*oneMinusCosValue+cosValue,
		0.f,0.f,0.f);
}

Matrix43 Matrix43::CreateFromEuler( const EulerAngle& angle )
{
	float cosh=Math::Cos(angle.Heading);
	float cosp=Math::Cos(angle.Pitch);
	float cosb=Math::Cos(angle.Bank);

	float sinh=Math::Sin(angle.Heading);
	float sinp=Math::Sin(angle.Pitch);
	float sinb=Math::Sin(angle.Bank);

	return Matrix43(cosh*cosb+sinh*sinp*sinb,sinb*cosp,-sinh*cosb+cosh*sinp*sinb,
		-cosh*sinb+sinh*sinp*cosb,cosb*cosp,sinb*sinh+cosh*sinp*cosb,
		sinh*cosp,-sinp,cosh*cosp,
		0.f,0.f,0.f);
}

Matrix43 Matrix43::CreateFromQuaternion( const Quaternion& q )
{
	/*
	????????????????.
	??????????????:

	[ ww+xx-yy-zz , 2xy-2wz , 2xz+2wy ]
	[ 2xy+2wz , ww-xx-yy-zz , 2yz-2wx ]
	[ 2xz-2wy , 2yz+2wx , ww-xx-yy-zz ]

	???????????, ???????????:

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

	return Matrix43(1.f-2.f*(yy+zz),2.f*(xy+wz),2.f*(xz-wy),
		2.f*(xy-wz),1-2.f*(xx+zz),2.f*(yz+wx),
		2.f*(xz+wy),2.f*(yz-wx),1-2.f*(xx+yy),
		0.f,0.f,0.f);
}

Matrix43 Matrix43::CreateProjectToXY()
{
	return Matrix43(1.f,0.f,0.f,
		0.f,1.f,0.f,
		0.f,0.f,0.f,
		0.f,0.f,0.f);
}

Matrix43 Matrix43::CreateProjectToXZ()
{
	return Matrix43(1.f,0.f,0.f,
		0.f,0.f,0.f,
		0.f,0.f,1.f,
		0.f,0.f,0.f);
}

Matrix43 Matrix43::CreateProjectToYZ()
{
	return Matrix43(0.f,0.f,0.f,
		0.f,1.f,0.f,
		0.f,0.f,1.f,
		0.f,0.f,0.f);
}

Matrix43 Matrix43::CreateProjectToPlane( const Point3F& normal )
{
	float xy=normal.X*normal.Y;
	float yz=normal.Y*normal.Z;
	float xz=normal.X*normal.Z;
	float xx=normal.X*normal.X;
	float yy=normal.Y*normal.Y;
	float zz=normal.Z*normal.Z;

	return Matrix43(1-xx,-xy,-xz,
		-xy,1-yy,-yz,
		-xz,-yz,1-zz,
		0.f,0.f,0.f);
}

Matrix43 Matrix43::CreateFlipX()
{
	return Matrix43(-1.f,0.f,0.f,
		0.f,1.f,0.f,
		0.f,0.f,1.f,
		0.f,0.f,0.f);
}

Matrix43 Matrix43::CreateFlipY()
{
	return Matrix43(1.f,0.f,0.f,
		0.f,-1.f,0.f,
		0.f,0.f,1.f,
		0.f,0.f,0.f);
}

Matrix43 Matrix43::CreateFlipZ()
{
	return Matrix43(1.f,0.f,0.f,
		0.f,1.f,0.f,
		0.f,0.f,-1.f,
		0.f,0.f,0.f);
}

Matrix43 Matrix43::CreateFlipByPlane( const Point3F& normal )
{
	float xy2=normal.X*normal.Y*2.f;
	float yz2=normal.Y*normal.Z*2.f;
	float xz2=normal.X*normal.Z*2.f;
	float xx2=normal.X*normal.X*2.f;
	float yy2=normal.Y*normal.Y*2.f;
	float zz2=normal.Z*normal.Z*2.f;

	return Matrix43(1-xx2,-xy2,-xz2,
		-xy2,1-yy2,-yz2,
		-xz2,-yz2,1-zz2,
		0.f,0.f,0.f);
}

Matrix43 Matrix43::CreateShear( float xy,float xz,float yx,float yz,float zx,float zy )
{
	return Matrix43(1.f,yx,zx,
		xy,1.f,zy,
		xz,yz,1.f,
		0.f,0.f,0.f);
}

Matrix43 Matrix43::CreateNormal()
{
	return Matrix43(0.5f,0.f,0.f,
		0.0f,0.5f,0.f,
		0.0f,0.f,0.5f,
		0.5f,0.5f,0.5f);
}

#pragma endregion Transform

MEDUSA_END;
