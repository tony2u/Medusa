// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Core/Geometry/Matrix3.h"
#include "Core/Geometry/Matrix43.h"
#include "Core/Geometry/Matrix4.h"
#include "Core/Geometry/EulerAngle.h"
#include "Core/Geometry/Quaternion.h"


MEDUSA_BEGIN;

Quaternion::Quaternion( const Point3F& normalVector,float angle )
{
	angle*=0.5f;
	float sinV=Math::Sin(angle);
	X=normalVector.X*sinV;
	Y=normalVector.Y*sinV;
	Z=normalVector.Z*sinV;
	W=Math::Cos(angle);
}

Quaternion Quaternion::operator*(const Quaternion& q)const
{
	//Note that this is different from standard multiply
	return Quaternion(W*q.X+X*q.W+Z*q.Y-Y*q.Z,
		W*q.Y+Y*q.W+X*q.Z-Z*q.X,
		W*q.Z+Z*q.W+Y*q.X-X*q.Y,
		W*q.W-X*q.X-Y*q.Y-Z*q.Z);
}

Quaternion& Quaternion::operator*=(const Quaternion& q)
{
	//Note that this is different from standard multiply

	float x=W*q.X+X*q.W+Z*q.Y-Y*q.Z;
	float y=W*q.Y+Y*q.W+X*q.Z-Z*q.X;
	float z=W*q.Z+Z*q.W+Y*q.X-X*q.Y;
	float w=W*q.W-X*q.X-Y*q.Y-Z*q.Z;

	X=x;Y=y;Z=z;W=w;
	return *this;
}

Point3F Quaternion::Tranform( const Point3F& point ) const
{
	//p'=q'pq
	Quaternion q2=Inverse();
	q2*=Quaternion(point);
	q2*=*this;
	return q2.ToPoint();

}

Quaternion Quaternion::Sub( const Quaternion& q ) const
{
	return Inverse()*q;
}

Quaternion Quaternion::CreateFromEuler( const EulerAngle& angle )
{
	float h=angle.Heading*0.5f;
	float p=angle.Pitch*0.5f;
	float b=angle.Bank*0.5f;

	float sinh=Math::Sin(h);
	float sinp=Math::Sin(p);
	float sinb=Math::Sin(b);

	float cosh=Math::Cos(h);
	float cosp=Math::Cos(p);
	float cosb=Math::Cos(b);

	Quaternion q;
	q.W=cosh*cosp*cosb+sinh*sinp*sinb;
	q.X=cosh*sinp*cosb+sinh*cosp*sinb;
	q.Y=sinh*cosp*cosb-cosh*sinp*sinb;
	q.Z=cosh*cosp*sinb-sinh*sinp*cosb;

	return q;
}

Quaternion Quaternion::CreateFromMatrix( const Matrix3& m )
{
	Quaternion q;
	float wwMinus1=m.M11+m.M22+m.M33;
	float xxMinus1=m.M11-m.M22-m.M33;
	float yyMinus1=m.M22-m.M11-m.M33;
	float zzMinus1=m.M33-m.M11-m.M22;
	//find max one
	uint32 biggestIndex=0;
	float biggestValue=wwMinus1;
	if (xxMinus1>biggestValue)
	{
		biggestIndex=1;
		biggestValue=xxMinus1;
	}

	if (yyMinus1>biggestValue)
	{
		biggestIndex=2;
		biggestValue=yyMinus1;
	}

	if (zzMinus1>biggestValue)
	{
		biggestIndex=3;
		biggestValue=zzMinus1;
	}

	float mult=0.25f/Math::Sqrt(biggestValue+1.f)*0.5f;
	switch(biggestIndex)
	{
	case 0:
		q.W=biggestValue;
		q.X=(m.M23-m.M32)*mult;
		q.Y=(m.M31-m.M13)*mult;
		q.Z=(m.M12-m.M21)*mult;
		break;
	case 1:
		q.X=biggestValue;
		q.Y=(m.M12+m.M21)*mult;
		q.Z=(m.M31+m.M13)*mult;
		q.W=(m.M23-m.M32)*mult;
		break;
	case 2:
		q.Y=biggestValue;
		q.X=(m.M12+m.M21)*mult;
		q.Z=(m.M23+m.M32)*mult;
		q.W=(m.M31-m.M13)*mult;
		break;
	case 3:
		q.Z=biggestValue;
		q.X=(m.M12-m.M21)*mult;
		q.Y=(m.M31+m.M13)*mult;
		q.W=(m.M23+m.M32)*mult;
		break;
	}

	return q;
}

Quaternion Quaternion::Slerp( const Quaternion& begin,const Quaternion& end,float t )
{
	Quaternion tempEnd=end;
	
	float cosa=begin.DotMultiply(tempEnd);

	if (cosa<0.f)
	{
		//If dot multiply is negative, then flip a Quaternion to get shorted 4D "arc"
		tempEnd=-tempEnd;
		cosa=-cosa;
	}

	//check if too close to avoid divide by 0
	float k0,k1;
	if (cosa>0.9999f)
	{
		//too close, use linear slerp
		k0=1.f-t;
		k1=t;
	}
	else
	{
		//Usd sin^2+cos^2=1 to calculate sin value
		float sina=Math::Sqrt(1.f-cosa*cosa);
		//use sin and cos value to calcualte angle
		float a=Math::Atan2(sina,cosa);
		float invSina=1.f/sina;
		k0=Math::Sin((1.f-t)*a)*invSina;
		k1=Math::Sin(t*a)*invSina;
	}
	Quaternion result=begin*k0+tempEnd*k1;
	result.Normalize();
	return result;
}

void Quaternion::ConvertToAxisAngle( Point3F& outNormalVector,float& outAngle )
{
	outAngle=Math::Acos(W);
	float sinV=1.f/Math::Sin(outAngle);
	outAngle*=2.f;

	outNormalVector.X=X*sinV;
	outNormalVector.Y=Y*sinV;
	outNormalVector.Z=Z*sinV;
}

void Quaternion::Normalize()
{
	float t=Math::Sqrt(X*X+Y*Y+Z*Z+W*W);
	if (!Math::IsZero(t))
	{
		t=1.f/t;
		X*=t;
		Y*=t;
		Z*=t;
		W*=t;
	}
}

const Quaternion Quaternion::Zero(0,0,0,0);
const Quaternion Quaternion::Identity(0,0,0,1);


MEDUSA_END;
