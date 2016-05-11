// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "MedusaPreDeclares.h"
#include "Core/Assertion/CommonAssert.h"

#include "Geometry/Point2.h"
#include "Geometry/Point3.h"
#include "Core/Math/Math.h"
#include "Core/Utility/Utility.h"

MEDUSA_BEGIN;

template<typename T>
class Point4
{
public:
	union
	{
		T Buffer[4];
		struct
		{
			T X;
			T Y;
			T Z;
			T W;
		};
	};

	const static Point4 Zero;
	const static Point4 One;
	const static Point4 UnitX;
	const static Point4 UnitY;
	const static Point4 UnitZ;
	const static Point4 UnitW;


	const static Point4 Min;
	const static Point4 Max;

public: 

public:
	Point4(void){}
	Point4(T x,T y,T z=0,T w=(T)1):X(x),Y(y),Z(z),W(w){}
	Point4(const T* items):X(*items),Y(*(items+1)),Z(*(items+2)),W(*(items+3)){}

	template<typename T1>
	Point4(const Point4<T1>& point):X((T)point.X),Y((T)point.Y),Z((T)point.Z),W((T)point.W){}

	template<typename T1>
	Point4(const Point2<T1>& point):X((T)point.X),Y((T)point.Y),Z((T)0),W((T)1){}

	template<typename T1>
	Point4(const Point3<T1>& point):X((T)point.X),Y((T)point.Y),Z((T)point.Z),W((T)1){}

	template<typename T1>
	Point4& operator=(const Point4<T1>& point){X=(T)point.X;Y=(T)point.Y;Z=(T)point.Z;W=(T)point.W;return *this;}

	template<typename T1>
	Point4& operator=(const Point2<T1>& point){X=(T)point.X;Y=(T)point.Y;Z=(T)0;W=(T)1;return *this;}

	template<typename T1>
	Point4& operator=(const Point3<T1>& point){X=(T)point.X;Y=(T)point.Y;Z=(T)point.Z;W=(T)1;return *this;}

	template<typename T1>
	Point4& operator=(T1 val){X=(T)val;Y=(T)val;Z=(T)val;W=(T)1;return *this;}

	Point4 operator-()const { return Point4(-X, -Y, -Z, -W); }


	template<typename T1>
	bool operator==(const Point4<T1>& point)const{return Math::IsEqual(X,point.X)&&Math::IsEqual(Y,point.Y)&&Math::IsEqual(Z,point.Z)&&Math::IsEqual(W,point.W);}
	template<typename T1>
	bool operator!=(const Point4<T1>& point)const{return !operator==(point);}
	template<typename T1>
	bool operator>(const Point4<T1>& point)const{return X>point.X&&Y>point.Y&&Z>point.Z&&W>point.W;}
	template<typename T1>
	bool operator<(const Point4<T1>& point)const{return X<point.X&&Y<point.Y&&Z<point.Z&&W<point.W;}
	template<typename T1>
	bool operator>=(const Point4<T1>& point)const{return X>=point.X&&Y>=point.Y&&Z>=point.Z&&W>=point.W;}
	template<typename T1>
	bool operator<=(const Point4<T1>& point)const{return X<=point.X&&Y<=point.Y&&Z<=point.Z&&W<=point.W;}

	template<typename T1>
	Point4 operator+(const Point4<T1>& point)const{return Point4(X+point.X,Y+point.Y,Z+point.Z,W+point.W);}
	template<typename T1>
	Point4 operator-(const Point4<T1>& point)const{return Point4(X-point.X,Y-point.Y,Z-point.Z,W-point.W);}
	template<typename T1>
	Point4& operator+=(const Point4<T1>& point){X+=point.X;Y+=point.Y;Z+=point.Z;W+=point.W;return *this;}
	template<typename T1>
	Point4& operator-=(const Point4<T1>& point){X-=point.X;Y-=point.Y;Z-=point.Z;W-=point.W;return *this;}

	template<typename T1>
	Point4 operator+(T1 delta)const { return Point4(X + delta, Y + delta, Z + delta, W + delta); }
	template<typename T1>
	Point4 operator-(T1 delta)const { return Point4(X - delta, Y - delta, Z - delta, W - delta); }
	template<typename T1>
	Point4& operator+=(T1 delta) { X += delta; Y += delta; Z += delta; W += delta; return *this; }
	template<typename T1>
	Point4& operator-=(T1 delta) { X -= delta; Y -= delta; Z -= delta; W -= delta; return *this; }
	template<typename T1>
	Point4 operator*(T1 delta)const{return Point4(X*delta,Y*delta,Z*delta,W*delta);}
	template<typename T1>
	Point4 operator/(T1 delta)const{MEDUSA_ASSERT_NOT_ZERO(delta,"");return Point4(X/delta,Y/delta,Z/delta,W/delta);}
	template<typename T1>
	Point4& operator*=(T1 delta){X*=delta;Y*=delta;Z*=delta;W*=delta;return *this;}
	template<typename T1>
	Point4& operator/=(T1 delta){MEDUSA_ASSERT_NOT_ZERO(delta,"");X/=delta;Y/=delta;Z/=delta;W/=delta;return *this;}

	Point4 operator<<(uint32 delta)const { return Point4(X << delta, Y << delta, Z << delta, W << delta); }
	Point4 operator>>(uint32 delta)const { return Point4(X >> delta, Y >> delta, Z >> delta, W >> delta); }
	Point4& operator<<=(uint32 delta){X<<=delta;Y<<=delta;Z<<=delta;W<<=delta;return *this;}
	Point4& operator>>=(uint32 delta){X>>=delta;Y>>=delta;Z>>=delta;W>>=delta;return *this;}

	Point4& operator++(){++X;++Y;++Z;++W;return *this;}
	Point4& operator--(){--X;--Y;--Z;--W;return *this;}

	Point4 operator++(int){Point4 orign=*this;++X;++Y;++Z;++W;return orign;}
	Point4 operator--(int){Point4 orign=*this;--X;--Y;--Z;--W;return orign;}

	template<typename T1>
	friend  Point4 operator*(T1 delta,const Point4<T>& point){return Point4(delta*point.X,delta*point.Y,delta*point.Z,delta*point.W);}

	Point2<T> To2D()const{return Point2<T>(X*W,Y*W);}
	Point3<T> To3D()const{return Point3<T>(X*W,Y*W,Z*W);}
	Point3<T> TruncateTo3D()const{return Point3<T>(X,Y,Z);}
	Point2<T> TruncateTo2D()const{return Point2<T>(X,Y);}


	intp HashCode()const{return HashUtility::Hash(Buffer);}


	float Length()const{return Math::Sqrt((float)(X*X+Y*Y+Z*Z+W*W));}
	T LengthSquared()const{return X*X+Y*Y+Z*Z+W*W;}

	void Normalize()
	{
		float length=Length();
		if (length!=0.f)
		{
			X/=length;Y/=length;Z/=length;W/=length;
		}
	}

	template<typename T1>
	float Dot(const Point4<T1>& point)const{return X*point.X+Y*point.Y+Z*point.Z+W*point.W;}

	template<typename T1>
	void UpdateEachToMin(const Point4<T1>& point)
	{
		X=Math::Min(X,point.X);
		Y=Math::Min(Y,point.Y);
		Z=Math::Min(Z,point.Z);
		W=Math::Min(W,point.W);
	}

	template<typename T1>
	void UpdateEachToMax(const Point4<T1>& point)
	{
		X=Math::Max(X,point.X);
		Y=Math::Max(Y,point.Y);
		Z=Math::Max(Z,point.Z);
		W=Math::Max(W,point.W);
	}

	static Point4 LinearInterpolate(const Point4& begin,const Point4& end,float blend)
	{
		return Scale3<T>(Math::LinearInterpolate(begin.X,end.X,blend),
			Math::LinearInterpolate(begin.Y,end.Y,blend),
			Math::LinearInterpolate(begin.Z,end.Z,blend),
			Math::LinearInterpolate(begin.W,end.W,blend)
			);
	}

	template<typename T1>
	float GetDistance(const Point4<T1>& point)const
	{
		float x=(float)(X-point.X);
		float y=(float)(Y-point.Y);
		float z=(float)(Z-point.Z);
		float w=(float)(W-point.W);


		return Math::Sqrt(x*x+y*y+z*z+w*w);
	}

	static float Distance(const Point4& begin,const Point4& end)
	{
		return (end-begin).Length();
	}

	static float DistanceSquared(const Point4& begin,const Point4& end)
	{
		return (end-begin).LengthSquared();
	}

	static Point4 MinAll(const Point4& v1,const Point4& v2)
	{
		return Point4(Math::Min(v1.X,v2.X),Math::Min(v1.Y,v2.Y),Math::Min(v1.Z,v2.Z),Math::Min(v1.W,v2.W));
	}

	static Point4 MaxAll(const Point4& v1,const Point4& v2)
	{
		return Point4(Math::Max(v1.X,v2.X),Math::Max(v1.Y,v2.Y),Math::Max(v1.Z,v2.Z),Math::Max(v1.W,v2.W));
	}

	static Point4 Clamp(const Point4& v1,const Point4& min,const Point4& max)
	{
		return Point4(Math::Clamp(v1.X,min.X,max.X),Math::Clamp(v1.Y,min.Y,max.Y),Math::Clamp(v1.Z,min.Z,max.Z),Math::Clamp(v1.W,min.W,max.W));
	}

	static Point4 Barycentric(const Point4& v1,const Point4& v2,const Point4& v3,float amount1,float amount2)
	{
		return Point4(v1.X+amount1*(v2.X-v1.X)+amount2*(v3.X-v1.X),
			v1.Y+amount1*(v2.Y-v1.Y)+amount2*(v3.Y-v1.Y),
			v1.Z+amount1*(v2.Z-v1.Z)+amount2*(v3.Z-v1.Z),
			v1.W+amount1*(v2.W-v1.W)+amount2*(v3.W-v1.W)
			);
	}

	static Point4 SmoothStep(const Point4& v1,const Point4& v2,float blend)
	{
		blend=Math::Clamp(blend,0.f,1.f);
		blend=blend*blend*(3.f-2.f*blend);
		return Point4(v1.X+blend*(v2.X-v1.X),v1.Y+blend*(v2.Y-v1.Y),v1.Z+blend*(v2.Z-v1.Z),v1.W+blend*(v2.W-v1.W));
	}

	static Point4 CatmullRom(const Point4& v1,const Point4& v2,const Point4& v3,const Point4& v4,float amount)
	{
		float amount2=amount*amount;
		float amount3=amount2*amount;

		return Point4(0.5f * ((((2.f * v2.X) + ((-v1.X + v3.X) * amount)) + (((((2.f * v1.X) - (5.f * v2.X)) + (4.f * v3.X)) - v4.X) * amount2)) + ((((-v1.X + (3.f * v2.X)) - (3.f * v3.X)) + v4.X) * amount3)),
			0.5f * ((((2.f * v2.Y) + ((-v1.Y + v3.Y) * amount)) + (((((2.f * v1.Y) - (5.f * v2.Y)) + (4.f * v3.Y)) - v4.Y) * amount2)) + ((((-v1.Y + (3.f * v2.Y)) - (3.f * v3.Y)) + v4.Y) * amount3)),
			0.5f * ((((2.f * v2.Z) + ((-v1.Z + v3.Z) * amount)) + (((((2.f * v1.Z) - (5.f * v2.Z)) + (4.f * v3.Z)) - v4.Z) * amount2)) + ((((-v1.Z + (3.f * v2.Z)) - (3.f * v3.Z)) + v4.Z) * amount3)),
			0.5f * ((((2.f * v2.W) + ((-v1.W + v3.W) * amount)) + (((((2.f * v1.W) - (5.f * v2.W)) + (4.f * v3.W)) - v4.W) * amount2)) + ((((-v1.W + (3.f * v2.W)) - (3.f * v3.W)) + v4.W) * amount3)));
	}

	static Point4 Hermite(const Point4& v1,const Point4& tangent1,const Point4& v2,const Point4& tangent2,float amount)
	{
		float amount2=amount*amount;
		float amount3=amount2*amount;

		float num6 = ((2.f * amount3) - (3.f * amount2)) + 1.f;
		float num5 = (-2.f * amount3) + (3.f * amount2);
		float num4 = (amount3 - (2.f * amount2)) + amount;
		float num3 = amount3 - amount2;
		return Point4(v1.X * num6 + v2.X * num5 + tangent1.X * num4 + tangent2.X * num3,
			v1.Y * num6 + v2.Y * num5 +tangent1.Y * num4 + tangent2.Y * num3,
			v1.Z * num6 + v2.Z * num5 +tangent1.Z * num4 + tangent2.Z * num3,
			v1.W * num6 + v2.W * num5 +tangent1.W * num4 + tangent2.W * num3);

	}

	static Point4 Move(const Point4& from,const Point4& to,float distance)
	{
		float blend=distance/Distance(from,to);
		return LinearInterpolate(from,to,blend);
	}
};

template<typename T> MEDUSA_WEAK_MULTIPLE_DEFINE const Point4<T> Point4<T>::Zero(0,0,0,0);
template<typename T> MEDUSA_WEAK_MULTIPLE_DEFINE const Point4<T> Point4<T>::One(1,1,1,1);
template<typename T> MEDUSA_WEAK_MULTIPLE_DEFINE const Point4<T> Point4<T>::UnitX(1,0,0,0);
template<typename T> MEDUSA_WEAK_MULTIPLE_DEFINE const Point4<T> Point4<T>::UnitY(0,1,0,0);
template<typename T> MEDUSA_WEAK_MULTIPLE_DEFINE const Point4<T> Point4<T>::UnitZ(0,0,1,0);
template<typename T> MEDUSA_WEAK_MULTIPLE_DEFINE const Point4<T> Point4<T>::UnitW(0,0,0,1);



template<typename T>
MEDUSA_WEAK_MULTIPLE_DEFINE const Point4<T> Point4<T>::Min(Math::Values<T>::Min,Math::Values<T>::Min,Math::Values<T>::Min);

template<typename T>
MEDUSA_WEAK_MULTIPLE_DEFINE const Point4<T> Point4<T>::Max(Math::Values<T>::Max,Math::Values<T>::Max,Math::Values<T>::Max);

//[PRE_DECLARE_BEGIN]
typedef Point4<int> Point4I;
typedef Point4<uint> Point4U;
typedef Point4<float> Point4F;

typedef Point4I Vector4I;
typedef Point4U Vector4U;
typedef Point4F Vector4F;
//[PRE_DECLARE_END]

#define mppppi(x,y,z,w) Point4I(x,y,z,w)
#define mppppu(x,y,z,w) Point4U(x,y,z,w)
#define mpppp(x,y,z,w) Point4F(x,y,z,w)

MEDUSA_END;
