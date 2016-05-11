// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "MedusaPreDeclares.h"
#include "Core/Assertion/CommonAssert.h"
#include "Core/Hash/HashUtility.h"
#include "Geometry/Point2.h"



MEDUSA_BEGIN;

template<typename T>
class Point3
{
public:
	const static uint32 Size=3;

	union
	{
		T Buffer[Size];
		struct
		{
			T X;
			T Y;
			T Z;
		};
	};

	const static Point3 Zero;
	const static Point3 One;
	const static Point3 UnitX;
	const static Point3 UnitY;
	const static Point3 UnitZ;
	const static Point3 Up;
	const static Point3 Down;
	const static Point3 Right;
	const static Point3 Left;
	const static Point3 ForWard;
	const static Point3 Backward;

	const static Point3 HalfX;
	const static Point3 HalfY;
	const static Point3 HalfZ;
	const static Point3 Half;


	const static Point3 Min;
	const static Point3 Max;

public:
	Point3(void){}
	Point3(T x,T y,T z=0):X(x),Y(y),Z(z){}
	Point3(const T* items):X(*items),Y(*(items+1)),Z(*(items+2)){}

	template<typename T1>
	Point3(const Point3<T1>& point):X((T)point.X),Y((T)point.Y),Z((T)point.Z){}

	template<typename T1>
	Point3(const Point2<T1>& point):X((T)point.X),Y((T)point.Y),Z(0){}

	template<typename T1>
	Point3& operator=(const Point3<T1>& point){X=(T)point.X;Y=(T)point.Y;Z=(T)point.Z;return *this;}

	template<typename T1>
	Point3& operator=(const Point2<T1>& point){X=(T)point.X;Y=(T)point.Y;Z=(T)0;return *this;}

	template<typename T1>
	Point3& operator=(T1 val){X=(T)val;Y=(T)val;Z=(T)val;return *this;}

	template<typename T1>
	bool operator==(const Point3<T1>& point)const{return Math::IsEqual(X,point.X)&&Math::IsEqual(Y,point.Y)&&Math::IsEqual(Z,point.Z);}
	template<typename T1>
	bool operator!=(const Point3<T1>& point)const{return !operator==(point);}
	template<typename T1>
	bool operator>(const Point3<T1>& point)const{return X>point.X&&Y>point.Y&&Z>point.Z;}
	template<typename T1>
	bool operator<(const Point3<T1>& point)const{return X<point.X&&Y<point.Y&&Z<point.Z;}
	template<typename T1>
	bool operator>=(const Point3<T1>& point)const{return X>=point.X&&Y>=point.Y&&Z>=point.Z;}
	template<typename T1>
	bool operator<=(const Point3<T1>& point)const{return X<=point.X&&Y<=point.Y&&Z<=point.Z;}

	Point3 operator-()const { return Point3(-X, -Y, -Z); }


	template<typename T1>
	Point3 operator+(const Point3<T1>& point)const{return Point3(X+point.X,Y+point.Y,Z+point.Z);}
	template<typename T1>
	Point3 operator-(const Point3<T1>& point)const{return Point3(X-point.X,Y-point.Y,Z-point.Z);}
	template<typename T1>
	Point3& operator+=(const Point3<T1>& point){X+=point.X;Y+=point.Y;Z+=point.Z;return *this;}
	template<typename T1>
	Point3& operator-=(const Point3<T1>& point){X-=point.X;Y-=point.Y;Z-=point.Z;return *this;}
	template<typename T1>
	Point3 operator*(const Point3<T1>& point)const { return Point3(X * point.X, Y * point.Y, Z * point.Z); }
	template<typename T1>
	Point3& operator*=(const Point3<T1>& point) { X *= point.X; Y *= point.Y; Z *= point.Z; return *this; }
	template<typename T1>
	Point3 operator/(const Point3<T1>& point)const { return Point3(X / point.X, Y / point.Y, Z / point.Z); }
	template<typename T1>
	Point3& operator/=(const Point3<T1>& point) { X /= point.X; Y /= point.Y; Z /= point.Z; return *this; }

	template<typename T1>
	Point3 operator+(Point2<T1> delta)const { return Point3(X + delta, Y + delta, Z + delta); }
	template<typename T1>
	Point3 operator-(T1 delta)const { return Point3(X - delta, Y - delta, Z - delta); }
	template<typename T1>
	Point3& operator+=(T1 delta) { X += delta; Y += delta; Z += delta; return *this; }
	template<typename T1>
	Point3& operator-=(T1 delta) { X -= delta; Y -= delta; Z -= delta; return *this; }
	template<typename T1>
	Point3 operator*(T1 delta)const{return Point3(X*delta,Y*delta,Z*delta);}
	template<typename T1>
	Point3 operator/(T1 delta)const{MEDUSA_ASSERT_NOT_ZERO(delta,"");return Point3(X/delta,Y/delta,Z/delta);}
	template<typename T1>
	Point3& operator*=(T1 delta){X*=delta;Y*=delta;Z*=delta;return *this;}
	template<typename T1>
	Point3& operator/=(T1 delta){MEDUSA_ASSERT_NOT_ZERO(delta,"");X/=delta;Y/=delta;Z/=delta;return *this;}

	Point3 operator<<(uint32 delta)const { return Point3(X << delta, Y << delta, Z << delta); }
	Point3 operator>>(uint32 delta)const { return Point3(X >> delta, Y >> delta, Z >> delta); }
	Point3& operator<<=(uint32 delta){X<<=delta;Y<<=delta;Z<<=delta;return *this;}
	Point3& operator>>=(uint32 delta){X>>=delta;Y>>=delta;Z>>=delta;return *this;}


	Point3& operator++(){++X;++Y;++Z;return *this;}
	Point3& operator--(){--X;--Y;--Z;return *this;}

	Point3 operator++(int){Point3 orign=*this;++X;++Y;++Z;return orign;}
	Point3 operator--(int){Point3 orign=*this;--X;--Y;--Z;return orign;}

	friend Point3 operator*(T delta,const Point3& point){return Point3((T)delta*point.X,(T)delta*point.Y,(T)delta*point.Z);}


	Point2<T> To2D()const{return Point2<T>(X,Y);}

	template<typename T1>
	Point3 operator+(const Point2<T1>& point)const { return Point3(X + point.X, Y + point.Y, Z ); }
	template<typename T1>
	Point3 operator-(const Point2<T1>& point)const { return Point3(X - point.X, Y - point.Y, Z ); }
	template<typename T1>
	Point3& operator+=(const Point2<T1>& point) { X += point.X; Y += point.Y;  return *this; }
	template<typename T1>
	Point3& operator-=(const Point2<T1>& point) { X -= point.X; Y -= point.Y; return *this; }
	template<typename T1>
	Point3 operator*(const Point2<T1>& point)const { return Point3(X * point.X, Y * point.Y, Z); }
	template<typename T1>
	Point3& operator*=(const Point2<T1>& point) { X *= point.X; Y *= point.Y;  return *this; }
	template<typename T1>
	Point3 operator/(const Point2<T1>& point)const { return Point3(X / point.X, Y / point.Y, Z); }
	template<typename T1>
	Point3& operator/=(const Point2<T1>& point) { X /= point.X; Y /= point.Y;  return *this; }


	intp HashCode()const{return HashUtility::Hash(Buffer);}

	float Length()const{return Math::Sqrt((float)(X*X+Y*Y+Z*Z));}
	T LengthSquared()const{return X*X+Y*Y+Z*Z;}

	void Normalize()
	{
		float length=Length();
		if (length!=0.f)
		{
			X/=length;Y/=length;Z/=length;
		}
	}

	template<typename T1>
	float Dot(const Point3<T1>& point)const{return X*point.X+Y*point.Y+Z*point.Z;}

	template<typename T1>
	Point3 Cross(const Point3<T1>& point)const{return Point3(Y*point.Z-Z*point.Y,Z*point.X-X*point.Z,X*point.Y-Y*point.X);}

	template<typename T1>
	float GetRadian(const Point3<T1>& point)const
	{
		Point3 a=*this;
		a.Normalize();
		Point3<T1> b=point;
		b.Normalize();
		return Math::Atan2(a.Cross(b), a.Dot(b));

		/*float cos=Dot(point)/(Length()*point.Length());
		return Math::Acos(cos);*/
	}

	template<typename T1>
	Point3 GetProjection(const Point3<T1>& point)const
	{
		float dot=Dot(point);
		return point*dot/point.LengthSquared();
	}

	template<typename T1>
	Point3 GetParallel(const Point3<T1>& point)const
	{
		return *this-GetProjection(point);
	}

	template<typename T1>
	void UpdateEachToMin(const Point3<T1>& point)
	{
		X=Math::Min(X,point.X);
		Y=Math::Min(Y,point.Y);
		Z=Math::Min(Z,point.Z);
	}

	template<typename T1>
	void UpdateEachToMax(const Point3<T1>& point)
	{
		X=Math::Max(X,point.X);
		Y=Math::Max(Y,point.Y);
		Z=Math::Max(Z,point.Z);
	}

	static float TripleMultiply(const Point3& a,const Point3& b,const Point3& c)
	{
        Point3 t=a.Cross(b);
		return t.Dot(c);
	}

	static Point3 CalculateNormal(const Point3& p1,const Point3& p2,const Point3& p3)
	{
		Point3F v1=p2-p1;
		Point3F v2=p3-p1;
		return v1.Cross(v2);
	}

	static Point3 LinearInterpolate(const Point3& begin,const Point3& end,float blend)
	{
		return Point3(Math::LinearInterpolate(begin.X,end.X,blend),Math::LinearInterpolate(begin.Y,end.Y,blend),Math::LinearInterpolate(begin.Z,end.Z,blend));
	}

	template<typename T1>
	float GetDistance(const Point3<T1>& point)const
	{
		float x=(float)(X-point.X);
		float y=(float)(Y-point.Y);
		float z=(float)(Z-point.Z);

		return Math::Sqrt(x*x+y*y+z*z);
	}

	static float Distance(const Point3& begin,const Point3& end)
	{
		return (end-begin).Length();
	}
	static float DistanceSquared(const Point3& begin,const Point3& end)
	{
		return (end-begin).LengthSquared();
	}

	static Point3 Reflect(const Point3& inVec,const Point3& surfaceNormal)
	{
		return inVec-2*surfaceNormal*surfaceNormal.Dot(inVec);
	}

	static Point3 Refract(const Point3& inVec,const Point3& surfaceNormal,float refraction)
	{
		float n=surfaceNormal.Dot(inVec);
		float k=1.f-refraction*refraction*(1.f-n*n);
		if (k<0.f)
		{
			return 0.f;
		}
		return refraction*inVec-(refraction*n+Math::Sqrt(k))*surfaceNormal;
	}


	static Point3 MinAll(const Point3& v1,const Point3& v2)
	{
		return Point3(Math::Min(v1.X,v2.X),Math::Min(v1.Y,v2.Y),Math::Min(v1.Z,v2.Z));
	}

	static Point3 MaxAll(const Point3& v1,const Point3& v2)
	{
		return Point3(Math::Max(v1.X,v2.X),Math::Max(v1.Y,v2.Y),Math::Max(v1.Z,v2.Z));
	}

	static Point3 Clamp(const Point3& v1,const Point3& min,const Point3& max)
	{
		return Point3(Math::Clamp(v1.X,min.X,max.X),Math::Clamp(v1.Y,min.Y,max.Y),Math::Clamp(v1.Z,min.Z,max.Z));
	}

	static Point3 Barycentric(const Point3& v1,const Point3& v2,const Point3& v3,float amount1,float amount2)
	{
		return Point3(v1.X+amount1*(v2.X-v1.X)+amount2*(v3.X-v1.X),v1.Y+amount1*(v2.Y-v1.Y)+amount2*(v3.Y-v1.Y),v1.Z+amount1*(v2.Z-v1.Z)+amount2*(v3.Z-v1.Z));
	}

	static Point3 SmoothStep(const Point3& v1,const Point3& v2,float blend)
	{
		blend=Math::Clamp(blend,0.f,1.f);
		blend=blend*blend*(3.f-2.f*blend);
		return Point3(v1.X+blend*(v2.X-v1.X),v1.Y+blend*(v2.Y-v1.Y),v1.Z+blend*(v2.Z-v1.Z));
	}

	static Point3 CatmullRom(const Point3& v1,const Point3& v2,const Point3& v3,const Point3& v4,float amount)
	{
		float amount2=amount*amount;
		float amount3=amount2*amount;

		return Point3(0.5f * ((((2.f * v2.X) + ((-v1.X + v3.X) * amount)) + (((((2.f * v1.X) - (5.f * v2.X)) + (4.f * v3.X)) - v4.X) * amount2)) + ((((-v1.X + (3.f * v2.X)) - (3.f * v3.X)) + v4.X) * amount3)),
			0.5f * ((((2.f * v2.Y) + ((-v1.Y + v3.Y) * amount)) + (((((2.f * v1.Y) - (5.f * v2.Y)) + (4.f * v3.Y)) - v4.Y) * amount2)) + ((((-v1.Y + (3.f * v2.Y)) - (3.f * v3.Y)) + v4.Y) * amount3)),
			0.5f * ((((2.f * v2.Z) + ((-v1.Z + v3.Z) * amount)) + (((((2.f * v1.Z) - (5.f * v2.Z)) + (4.f * v3.Z)) - v4.Z) * amount2)) + ((((-v1.Z + (3.f * v2.Z)) - (3.f * v3.Z)) + v4.Z) * amount3)) );
	}

	static Point3 Hermite(const Point3& v1,const Point3& tangent1,const Point3& v2,const Point3& tangent2,float amount)
	{
		float amount2=amount*amount;
		float amount3=amount2*amount;

		float num6 = ((2.f * amount3) - (3.f * amount2)) + 1.f;
		float num5 = (-2.f * amount3) + (3.f * amount2);
		float num4 = (amount3 - (2.f * amount2)) + amount;
		float num3 = amount3 - amount2;
		return Point3(v1.X * num6 + v2.X * num5 + tangent1.X * num4 + tangent2.X * num3,
			v1.Y * num6 + v2.Y * num5 +tangent1.Y * num4 + tangent2.Y * num3,
			v1.Z * num6 + v2.Z * num5 +tangent1.Z * num4 + tangent2.Z * num3);

	}

	static Point3 Move(const Point3& from,const Point3& to,float distance)
	{
		float blend=distance/Distance(from,to);
		return LinearInterpolate(from,to,blend);
	}
};

template<typename T>
MEDUSA_WEAK_MULTIPLE_DEFINE const Point3<T> Point3<T>::Zero(0,0,0);

template<typename T>
MEDUSA_WEAK_MULTIPLE_DEFINE const Point3<T> Point3<T>::One(1,1,1);

template<typename T> MEDUSA_WEAK_MULTIPLE_DEFINE const Point3<T> Point3<T>::UnitX(1,0,0);
template<typename T> MEDUSA_WEAK_MULTIPLE_DEFINE const Point3<T> Point3<T>::UnitY(0,1,0);
template<typename T> MEDUSA_WEAK_MULTIPLE_DEFINE const Point3<T> Point3<T>::UnitZ(0,0,1);
template<typename T> MEDUSA_WEAK_MULTIPLE_DEFINE const Point3<T> Point3<T>::Up(0,1,0);
template<typename T> MEDUSA_WEAK_MULTIPLE_DEFINE const Point3<T> Point3<T>::Down(0,-1,0);
template<typename T> MEDUSA_WEAK_MULTIPLE_DEFINE const Point3<T> Point3<T>::Right(1,0,0);
template<typename T> MEDUSA_WEAK_MULTIPLE_DEFINE const Point3<T> Point3<T>::Left(-1,0,0);
template<typename T> MEDUSA_WEAK_MULTIPLE_DEFINE const Point3<T> Point3<T>::ForWard(0,0,-1);
template<typename T> MEDUSA_WEAK_MULTIPLE_DEFINE const Point3<T> Point3<T>::Backward(0,0,1);

template<typename T> MEDUSA_WEAK_MULTIPLE_DEFINE const Point3<T> Point3<T>::Half(0.5,0.5,0.5);
template<typename T> MEDUSA_WEAK_MULTIPLE_DEFINE const Point3<T> Point3<T>::HalfX(0.5,0,0);
template<typename T> MEDUSA_WEAK_MULTIPLE_DEFINE const Point3<T> Point3<T>::HalfY(0,0.5,0);
template<typename T> MEDUSA_WEAK_MULTIPLE_DEFINE const Point3<T> Point3<T>::HalfZ(0,0,0.5);



template<typename T>
MEDUSA_WEAK_MULTIPLE_DEFINE const Point3<T> Point3<T>::Min(Math::Values<T>::Min,Math::Values<T>::Min,Math::Values<T>::Min);

template<typename T>
MEDUSA_WEAK_MULTIPLE_DEFINE const Point3<T> Point3<T>::Max(Math::Values<T>::Max,Math::Values<T>::Max,Math::Values<T>::Max);

//[PRE_DECLARE_BEGIN]
typedef Point3<int> Point3I;
typedef Point3<float> Point3F;

typedef Point3I Vector3I;
typedef Point3F Vector3F;
//[PRE_DECLARE_END]

#define mpppi(x,y,z) Point3I(x,y,z)
#define mppp(x,y,z) Point3F(x,y,z)

MEDUSA_END;


#ifdef MEDUSA_LUA
#include "Core/Lua/LuaState.h"
MEDUSA_BEGIN;

template <typename T>
struct LuaTypeMapping <Point3<T>>//[IGNORE_PRE_DECLARE]
{
	static void Push(lua_State* L, const Point3<T>& val)
	{
		LuaStack s(L);
		s.NewTable(0, 3);
		s.Rawset("X", val.X);
		s.Rawset("Y", val.Y);
		s.Rawset("Z", val.Z);
	}

	static Point3<T> Get(lua_State* L, int index)
	{
		Point3<T> result;
		LuaStack s(L);
		result.X = s.Get<T>("X",index);
		result.Y = s.Get<T>("Y",index);
		result.Z = s.Get("Z",(T)0,index);
		return result;
	}

	static Point3<T> Optional(lua_State* L, int index, const Point3<T>& def)
	{
		return lua_isnoneornil(L, index) ? Point3<T>::Zero : Get(L, index);
	}

	static bool TryGet(lua_State* L, int index, Point3<T>& outValue)
	{
		RETURN_FALSE_IF(lua_isnoneornil(L, index));
		outValue = Get(L, index);
		return true;
	}
};
MEDUSA_END;

#endif
