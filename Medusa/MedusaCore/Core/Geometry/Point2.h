// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Assertion/CommonAssert.h"
#include "Core/Math/Math.h"
#include "Core/Hash/HashUtility.h"
#include "Core/Siren/SirenDefines.h"

MEDUSA_BEGIN;

template<typename T>
class Point2
{
public:
	const static uint32 Size = 2;

	union
	{
		T Buffer[Size];
		struct
		{
			T X;
			T Y;
		};
	};

	const static Point2 Zero;
	const static Point2 One;
	const static Point2 UnitX;
	const static Point2 UnitY;
	const static Point2 HalfX;
	const static Point2 HalfY;
	const static Point2 Half;




	const static Point2 Min;
	const static Point2 Max;

public:
	Point2(void) {}
	Point2(T x, T y) :X(x), Y(y) {}
	Point2(const T* items) :X(*items), Y(*(items + 1)) {}

	template<typename T1>
	Point2(const Point2<T1>& point) : X((T)point.X), Y((T)point.Y) {}

	template<typename T1>
	Point2& operator=(const Point2<T1>& point) { X = (T)point.X; Y = (T)point.Y; return *this; }
	template<typename T1>
	Point2& operator=(T1 val) { X = (T)val; Y = (T)val; return *this; }

	Point2 operator-()const { return Point2(-X, -Y); }

	template<typename T1>
	bool operator==(const Point2<T1>& point)const { return Math::IsEqual(X, point.X) && Math::IsEqual(Y, point.Y); }
	template<typename T1>
	bool operator!=(const Point2<T1>& point)const { return !operator==(point); }
	template<typename T1>
	bool operator>(const Point2<T1>& point)const { return X > point.X&&Y > point.Y; }
	template<typename T1>
	bool operator<(const Point2<T1>& point)const { return X < point.X&&Y < point.Y; }
	template<typename T1>
	bool operator>=(const Point2<T1>& point)const { return X >= point.X&&Y >= point.Y; }
	template<typename T1>
	bool operator<=(const Point2<T1>& point)const { return X <= point.X&&Y <= point.Y; }

	template<typename T1>
	Point2 operator+(const Point2<T1>& point)const { return Point2(X + point.X, Y + point.Y); }
	template<typename T1>
	Point2 operator-(const Point2<T1>& point)const { return Point2(X - point.X, Y - point.Y); }
	template<typename T1>
	Point2& operator+=(const Point2<T1>& point) { X += point.X; Y += point.Y; return *this; }
	template<typename T1>
	Point2& operator-=(const Point2<T1>& point) { X -= point.X; Y -= point.Y; return *this; }
	template<typename T1>
	Point2 operator*(const Point2<T1>& point)const { return Point2(X*point.X, Y*point.Y); }
	template<typename T1>
	Point2& operator*=(const Point2<T1>& point) { X *= point.X; Y *= point.Y; return *this; }
	template<typename T1>
	Point2 operator/(const Point2<T1>& point)const { return Point2(X / point.X, Y / point.Y); }
	template<typename T1>
	Point2& operator/=(const Point2<T1>& point) { X /= point.X; Y /= point.Y; return *this; }


	template<typename T1>
	Point2 operator+(T1 delta)const { return Point2(X + delta, Y + delta); }
	template<typename T1>
	Point2 operator-(T1 delta)const { return Point2(X - delta, Y - delta); }
	template<typename T1>
	Point2& operator+=(T1 delta) { X += delta; Y += delta; return *this; }
	template<typename T1>
	Point2& operator-=(T1 delta) { X -= delta; Y -= delta; return *this; }
	template<typename T1>
	Point2 operator*(T1 delta)const { return Point2(X*delta, Y*delta); }
	template<typename T1>
	Point2 operator/(T1 delta)const { MEDUSA_ASSERT_NOT_ZERO(delta, ""); return Point2(X / delta, Y / delta); }
	template<typename T1>
	Point2& operator*=(T1 delta) { X *= delta; Y *= delta; return *this; }
	template<typename T1>
	Point2& operator/=(T1 delta) { MEDUSA_ASSERT_NOT_ZERO(delta, ""); X /= delta; Y /= delta; return *this; }

	Point2 operator<<(uint32 delta)const { return Point2(X << delta, Y << delta); }
	Point2 operator>>(uint32 delta)const { return Point2(X >> delta, Y >> delta); }
	Point2& operator<<=(uint32 delta) { X <<= delta; Y <<= delta; return *this; }
	Point2& operator>>=(uint32 delta) { X >>= delta; Y >>= delta; return *this; }

	Point2& operator++() { ++X; ++Y; return *this; }
	Point2& operator--() { --X; --Y; return *this; }

	Point2 operator++(int) { Point2 orign = *this; ++X; ++Y; return orign; }
	Point2 operator--(int) { Point2 orign = *this; --X; --Y; return orign; }

	template<typename T1>
	friend  Point2 operator*(T1 delta, const Point2<T>& point) { return Point2(delta*point.X, delta*point.Y); }

	float Length()const { return Math::Sqrt((float)(X*X + Y*Y)); }
	T LengthSquared()const { return X*X + Y*Y; }
	float Radian()const
	{
		return Math::Atan2(Y, X);
	}


	void Normalize()
	{
		float length = Length();
		if (length != 0.f)
		{
			X /= length; Y /= length;
		}
	}


	template<typename T1>
	float Cross(const Point2<T1>& point)const { return X*point.Y - Y*point.X; }

	template<typename T1>
	float Dot(const Point2<T1>& point)const { return X*point.X + Y*point.Y; }

	template<typename T1>
	float GetRadian(const Point2<T1>& point)const
	{
		Point2 a = *this;
		a.Normalize();
		Point2<T1> b = point;
		b.Normalize();
		return Math::Atan2(a.Cross(b), a.Dot(b));

		/*float cos=Dot(point)/(Length()*point.Length());
		return Math::Acos(cos);*/
	}

	template<typename T1>
	Point2 GetProjection(const Point2<T1>& point)const
	{
		float dot = Dot(point);
		return point*dot / point.LengthSquared();
	}

	template<typename T1>
	Point2 GetParallel(const Point2<T1>& point)const
	{
		return *this - GetProjection(point);
	}

	intp HashCode()const { return HashUtility::Hash(Buffer); }

	template<typename T1>
	void UpdateEachToMin(const Point2<T1>& point)
	{
		X = Math::Min(X, point.X);
		Y = Math::Min(Y, point.Y);
	}

	template<typename T1>
	void UpdateEachToMax(const Point2<T1>& point)
	{
		X = Math::Max(X, point.X);
		Y = Math::Max(Y, point.Y);
	}

	static Point2 MinAll(const Point2& v1, const Point2& v2)
	{
		return Point2(Math::Min(v1.X, v2.X), Math::Min(v1.Y, v2.Y));
	}

	static Point2 MaxAll(const Point2& v1, const Point2& v2)
	{
		return Point2(Math::Max(v1.X, v2.X), Math::Max(v1.Y, v2.Y));
	}

	static Point2 Clamp(const Point2& v1, const Point2& min, const Point2& max)
	{
		return Point2(Math::Clamp(v1.X, min.X, max.X), Math::Clamp(v1.Y, min.Y, max.Y));
	}

	static Point2 LinearInterpolate(const Point2& begin, const Point2& end, float blend)
	{
		return Point2(Math::LinearInterpolate(begin.X, end.X, blend), Math::LinearInterpolate(begin.Y, end.Y, blend));
	}


	static Point2 Barycentric(const Point2& v1, const Point2& v2, const Point2& v3, float amount1, float amount2)
	{
		return Point2(v1.X + amount1*(v2.X - v1.X) + amount2*(v3.X - v1.X), v1.Y + amount1*(v2.Y - v1.Y) + amount2*(v3.Y - v1.Y));
	}

	static Point2 SmoothStep(const Point2& v1, const Point2& v2, float blend)
	{
		blend = Math::Clamp(blend, 0.f, 1.f);
		blend = blend*blend*(3.f - 2.f*blend);
		return Point2(v1.X + blend*(v2.X - v1.X), v1.Y + blend*(v2.Y - v1.Y));
	}

	static Point2 CatmullRom(const Point2& v1, const Point2& v2, const Point2& v3, const Point2& v4, float amount)
	{
		float amount2 = amount*amount;
		float amount3 = amount2*amount;

		return Point2(0.5f * ((((2.f * v2.X) + ((-v1.X + v3.X) * amount)) + (((((2.f * v1.X) - (5.f * v2.X)) + (4.f * v3.X)) - v4.X) * amount2)) + ((((-v1.X + (3.f * v2.X)) - (3.f * v3.X)) + v4.X) * amount3)),
					  0.5f * ((((2.f * v2.Y) + ((-v1.Y + v3.Y) * amount)) + (((((2.f * v1.Y) - (5.f * v2.Y)) + (4.f * v3.Y)) - v4.Y) * amount2)) + ((((-v1.Y + (3.f * v2.Y)) - (3.f * v3.Y)) + v4.Y) * amount3)));
	}

	static Point2 Hermite(const Point2& v1, const Point2& tangent1, const Point2& v2, const Point2& tangent2, float amount)
	{
		float amount2 = amount*amount;
		float amount3 = amount2*amount;

		float num6 = ((2.f * amount3) - (3.f * amount2)) + 1.f;
		float num5 = (-2.f * amount3) + (3.f * amount2);
		float num4 = (amount3 - (2.f * amount2)) + amount;
		float num3 = amount3 - amount2;
		return Point2(v1.X * num6 + v2.X * num5 + tangent1.X * num4 + tangent2.X * num3, v1.Y * num6 + v2.Y * num5 + tangent1.Y * num4 + tangent2.Y * num3);

	}

	template<typename T1>
	float GetDistance(const Point2<T1>& point)const
	{
		return Math::Hypot(X - point.X, Y - point.Y);
	}

	static float Distance(const Point2& begin, const Point2& end)
	{
		return (end - begin).Length();
	}

	static float DistanceSquared(const Point2& begin, const Point2& end)
	{
		return (end - begin).LengthSquared();
	}


	static Point2 Reflect(const Point2& inVec, const Point2& surfaceNormal)
	{
		return inVec - 2 * surfaceNormal*surfaceNormal.Dot(inVec);
	}

	static Point2 Refract(const Point2& inVec, const Point2& surfaceNormal, float refraction)
	{
		float n = surfaceNormal.Dot(inVec);
		float k = 1.f - refraction*refraction*(1.f - n*n);
		if (k < 0.f)
		{
			return 0.f;
		}
		return refraction*inVec - (refraction*n + Math::Sqrt(k))*surfaceNormal;
	}

	static Point2 Move(const Point2& from, const Point2& to, float distance)
	{
		float blend = distance / Distance(from, to);
		return LinearInterpolate(from, to, blend);
	}

};

template<typename T>
MEDUSA_WEAK_MULTIPLE_DEFINE const Point2<T> Point2<T>::Zero(0, 0);

template<typename T>
MEDUSA_WEAK_MULTIPLE_DEFINE const Point2<T> Point2<T>::One(1, 1);

template<typename T>
MEDUSA_WEAK_MULTIPLE_DEFINE const Point2<T> Point2<T>::UnitX(1, 0);

template<typename T>
MEDUSA_WEAK_MULTIPLE_DEFINE const Point2<T> Point2<T>::UnitY(0, 1);

template<typename T>
MEDUSA_WEAK_MULTIPLE_DEFINE const Point2<T> Point2<T>::Half(0.5, 0.5);

template<typename T>
MEDUSA_WEAK_MULTIPLE_DEFINE const Point2<T> Point2<T>::HalfX(0.5, 0);

template<typename T>
MEDUSA_WEAK_MULTIPLE_DEFINE const Point2<T> Point2<T>::HalfY(0, 0.5);
template<typename T>
MEDUSA_WEAK_MULTIPLE_DEFINE const Point2<T> Point2<T>::Min(Math::Values<T>::Min, Math::Values<T>::Min);

template<typename T>
MEDUSA_WEAK_MULTIPLE_DEFINE const Point2<T> Point2<T>::Max(Math::Values<T>::Max, Math::Values<T>::Max);



//[PRE_DECLARE_BEGIN]
typedef Point2<int> Point2I;
typedef Point2<uint> Point2U;

typedef Point2<float> Point2F;

typedef Point2I Vector2I;
typedef Point2F Vector2F;
//[PRE_DECLARE_END]


#define mppi(x,y) Point2I(x,y)
#define mpp(x,y) Point2F(x,y)


namespace Siren
{
	template <typename T>
	struct HasCustomSerialization<Point2<T>> : std::true_type{};	//[IGNORE_PRE_DECLARE]

	template <typename TWriter, typename T>
	void Serialize(TWriter& writer, const Point2<T>& obj)
	{
		writer.OnStructBegin();
		writer.template OnProperty<T, false>("X", 1, 0, obj.X);
		writer.template OnProperty<T, false>("Y", 1, 1, obj.Y);
		writer.OnStructEnd();
	}

	template <typename TReader, typename T>
	bool DeserializeTo(TReader& reader, Point2<T>& outObj)
	{
		reader.OnStructBegin();
		reader.template OnProperty<T, false>("X", 1, 0, outObj.X);
		reader.template OnProperty<T, false>("Y", 1, 1, outObj.Y);
		reader.OnStructEnd();

		return true;
	}
}

MEDUSA_END;

#ifdef MEDUSA_SCRIPT
MEDUSA_SCRIPT_BEGIN;
void RegisterPoint2F(asIScriptEngine* engine);
MEDUSA_SCRIPT_END;
#endif