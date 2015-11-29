// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
MEDUSA_BEGIN;

namespace Math
{
	/*

	value   round   floor   ceil    trunc
	-----   -----   -----   ----    -----
	2.3     2.0     2.0     3.0     2.0
	3.8     4.0     3.0     4.0     3.0
	5.5     6.0     5.0     6.0     5.0
	-2.3    -2.0    -3.0    -2.0    -2.0
	-3.8    -4.0    -4.0    -3.0    -3.0
	-5.5    -6.0    -6.0    -5.0    -5.0

	*/

#pragma region Values

	template<typename T>
	struct Values	//[IGNORE_PRE_DECLARE]
	{
		const static T Min;
		const static T Max;
	};

	constexpr float PI= 3.14159265358979323846f;
	constexpr float PIHalf = 1.570796326794897f;
	constexpr float PI2 = 6.28318530717958647692f;
	constexpr float PIInverse = 0.3183098861837907f;
	constexpr float PI2Inverse = 0.1591549430918953f;
	constexpr float E = 2.7182818284590451f;
	constexpr float Sqrt2 = 1.414213562373095f;
	constexpr float FloatCompareEpsilon = 0.0001f;
	constexpr double DoubleCompareEpsilon = 0.0001f;
	constexpr float FloatMaxValue = FLT_MAX;
	constexpr float FloatMinValue = FLT_MIN;
	constexpr double DoubleMaxValue = DBL_MAX;
	constexpr double DoubleMinValue = DBL_MIN;

	constexpr byte ByteMaxValue = (byte)0xFF;
	constexpr byte ByteMinValue = (byte)0x00;
	constexpr char CharMaxValue = (char)0x7F;
	constexpr char CharMinValue = (char)-127;
	constexpr short ShortMaxValue = (short)0x7FFF;
	constexpr short ShortMinValue = (short)0x8000u;
	constexpr ushort UShortMaxValue = (ushort)0xFFFF;
	constexpr ushort UShortMinValue = (ushort)0x0000;
	constexpr int IntMaxValue = (int)0x7FFFFFFF;
	constexpr int IntMinValue = (int)0x80000000;
	constexpr uint UIntMaxValue = (uint)0xFFFFFFFF;
	constexpr uint UIntMinValue = (uint)0x00000000;

	const extern int64 Int64MaxValue;
	const extern int64 Int64MinValue;
	const extern uint64 UInt64MaxValue;
	const extern uint64 UInt64MinValue;

	const extern size_t mPrimes[72];

#pragma endregion Values
	template <typename T1,typename T2>
	MEDUSA_FORCE_INLINE bool HasBit(T1 val, T2 bitFlag)
	{
		return ((uintp)val&(uintp)bitFlag) == (uintp)bitFlag;
	}

	template <typename T>
	MEDUSA_FORCE_INLINE T Sign(T val)
	{
		if (val > (T)0)
		{
			return (T)1;
		}
		else if (val < (T)0)
		{
			return (T)(-1);
		}
		return (T)0;
	}

	template <typename T>
	MEDUSA_FORCE_INLINE T InverseSign(T val)
	{
		return -Sign(val);
	}

	template <typename T>
	MEDUSA_FORCE_INLINE bool IsPowerOfTwo(T val)
	{
		return (val&(val - 1)) == 0;
	}

	template <typename T1, typename T2>
	MEDUSA_FORCE_INLINE bool IsEqual(T1 left, T2 right)
	{
		return left == right;
	}

	template <typename T1, typename T2>
	MEDUSA_FORCE_INLINE bool IsSameSign(T1 left, T2 right)
	{
		return IsEqual<T1, T2>(Sign<T1>(left), Sign<T2>(right));
	}

	template <typename T>
	MEDUSA_FORCE_INLINE T Compare(T left, T right)
	{
		return left - right;
	}


	template <typename T1, typename T2, typename T3>
	MEDUSA_FORCE_INLINE bool IsEqualEpsilon(T1 left, T2 right, T3 epsilon)
	{
		T3 delta = left - right;
		if (delta < 0)
		{
			delta = -delta;
		}
		return delta < epsilon;
	}



	template <typename T>
	MEDUSA_FORCE_INLINE constexpr bool IsZero(T val)
	{
		return val == (T)0;
	}

	//explicit template specialization cannot have a storage class on GCC,so cannot replace inline with static
	template <>
	inline bool IsZero(float val)
	{
		return fabs(val) < Math::FloatCompareEpsilon;
	}

	template <>
	inline bool IsZero(double val)
	{
		return fabs(val) < DoubleCompareEpsilon;
	}

	template <>
	inline bool IsEqualEpsilon(float left, float right, float epsilon)
	{
		return fabs(left - right) < epsilon;
	}

	template <>
	inline bool IsEqualEpsilon(double left, double right, float epsilon)
	{
		return fabs(left - right) < epsilon;
	}

	template <>
	inline bool IsEqual(float left, float right)
	{
		return fabs(left - right) < FloatCompareEpsilon;
	}

	template <>
	inline bool IsEqual(double left, double right)
	{
		return fabs(left - right) < DoubleCompareEpsilon;
	}

	template <>
	inline float Compare(float left, float right)
	{
		float delta = left - right;
		return fabs(delta) < FloatCompareEpsilon ? 0.f : delta;
	}

	template <>
	inline double Compare(double left, double right)
	{
		double delta = left - right;
		return fabs(delta) < DoubleCompareEpsilon ? 0.0 : delta;
	}

	template <typename T> 
	MEDUSA_FORCE_INLINE T Max(T first,T second) { return first < second ? second : first; }

	template <typename T1, typename... T>
	MEDUSA_FORCE_INLINE T1 Max(T1 first, T1 second, T... args) { return Max(Max(first, second), args...); }

	template <typename T>
	MEDUSA_FORCE_INLINE T Min(T first, T second) { return first < second ? first : second; }

	template <typename T1, typename... T>
	MEDUSA_FORCE_INLINE T1 Min(T1 first, T1 second, T... args) { return Min(Min(first, second), args...); }


	template <typename T>
	MEDUSA_FORCE_INLINE  void Swap(T& a, T& b)
	{
		T temp = a;
		a = b;
		b = temp;
	}
#pragma region Trigonometric
	/*
	cosx=1-(x^2)/(2!)+(x^4)/(4!)-(x^6)/(6!)+...    x belong (-infinityinfinity
	sinx=x-(x^3)/(3!)+(x^5)/(5!)-(x^7)/(7!)+...     x belong (-infinityinfinity

	sin(x)=x*term(n)
	term(n)=1-x^2/(2n+2)/(2n+3)*term(n+1)

	cos(x)=term(n)
	term(n)=1-x^2/(2n+1)/(2n+2)*term(n+1)

	TODO: it has the same performce as system sin() even in VS release mode. it's strange that we have to profile it in IOS system again.
	*/

	constexpr float ToDegree(float radian)
	{
		return radian*57.29577951f;
	}

	constexpr float ToRadian(float degree)
	{
		return degree*0.01745329252f;
	}
	float Sin(float radian);
	float Sinh(float radian);

	//-PI/2 <=a<=PI/2
	float Asin(float x);
	float Cos(float radian);
	float Cosh(float radian);

	double Acosh(double radian);
	float Acosh(float radian);
	double Asinh(double radian);
	float Asinh(float radian);
	double Atanh(double radian);
	float Atanh(float radian);

	//0<=a<=PI
	float Acos(float x);
	float Tan(float radian);
	float Cot(float radian);
	float Tanh(float radian);
	//-PI/2<=a<=PI/2
	float Atan(float x);
	//-PI<=a<=PI
	float Atan2(float y, float x);
	float WrapToPI(float a);
	float WrapToPI2(float a);

	//diff on the "smaller" side
	float DiffAngle(float a, float b);	//-PI<=a<=PI
	//bisect an angle on the "smaller" side
	float BisectAngle(float a, float b);	//-PI<=a<=PI


#pragma endregion Trigonometric
#pragma region Rounding and remainder functions
	
	float Exp(float x);

	
	float Exp2(float x);
	double Exp2(double x);

	
	float ExpM1(float x);
	double ExpM1(double x);

	//return log(|x| ) integer part,ilogb(10.000000) = 3
	int Ilogb(float x);
	int Ilogb(double x);

	//return log(|x| ) logb (1024.000000) = 10.000000
	float Logb(float x);
	double Logb(double x);

	//return log(|1+x| ) ,log1p (1.000000) = 0.693147
	float Log1p(float x);
	double Log1p(double x);

	//log2x.
	float Log2(float x);
	double Log2(double x);

	//Rounds x toward zero, returning the nearest integral value that is not larger in magnitude than x.
	float Truncate(float x);
	double Truncate(double x);

	//Returns the integral value that is nearest to x, with halfway cases rounded away from zero.
	float Round(float x);
	double Round(double x);

	//Returns the integer value that is nearest in value to x, with halfway cases rounded away from zero.
	//lround (2.3) = 2
	//	lround (3.8) = 4
	//	lround (-2.3) = -2
	//	lround (-3.8) = -4
	long int LRound(float x);
	long int LRound(double x);

	//Returns the integer value that is nearest in value to x, with halfway cases rounded away from zero.
	/*llround (2.3) = 2
	llround (3.8) = 4
	llround (-2.3) = -2
	llround (-3.8) = -4*/
	long long int LLRound(float x);
	long long int LLRound(double x);

	float Log(float x);
	double Log(double x);

	float Log10(float x);
	float Pow(float x, float y);
	float Fract(float x);
	//int <=x
	float Floor(float x);
	//int >=x
	float Ceil(float x);
	constexpr int Abs(int x)
	{
		return x < 0 ? -x : x;
	}
	constexpr short Abs(short x)
	{
		return x < 0 ? -x : x;
	}
	float Abs(float x);

#ifdef MEDUSA_WINDOWS
	div_t Div(int number, int denom);
	ldiv_t Div(long int number, long int denom);
	lldiv_t Div(long long int number, long long int denom);
#else
	div_t Div(int number, int denom);
#endif

	//Split float x to mantissa and exponent
	//x=m*2^y,return m, and store exponent to y
	float Frexp(float x, int* y);

	//load float
	//return x*2^y
	float Ldexp(float x, int y);

	//split float x to integer part and float part
	//return float part and store integer to y
	double Mod(double x, double* y);

	//x%y
	float Fmod(float x, float y);
	extern float Sqrt(float x);
	extern double Sqrt(double x);

	float InverseSqrt(float x);
	
	float Hypot(float x, float y);

	uint32_t CountLeadingZero(uint32_t val);
	uint32_t CountLeadingZero(uint64_t val);
	uint32_t CountTrailingZero(uint32_t val);
	uint32_t CountTrailingZero(uint64_t val);

#pragma endregion Rounding and remainder functions

	template<typename T>
	MEDUSA_FORCE_INLINE  T Clamp(T x, T min, T max)
	{
		return x<min ? min : (x>max ? max : x);
	}

	template<typename T>
	MEDUSA_FORCE_INLINE  T ClampAboveZero(T x)
	{
		return x < 0 ? 0 : x;
	}

	template<typename T>
	MEDUSA_FORCE_INLINE  T Mix(float f, T min, T max)
	{
		return (T)(min*(1.f - f) + max*f);
	}

	//blend [0-1]
	template<typename T>
	MEDUSA_FORCE_INLINE  T LinearInterpolate(T begin, T end, float blend)
	{
		return begin + (T)((end - begin)*blend);
	}


	template<typename T>
	MEDUSA_FORCE_INLINE  T LinearInterpolate(T val, T srcMin, T srcMax, T destMin, T destMax)
	{
		return destMin + (destMax - destMin)*(val - srcMin) / (srcMax - srcMin);
	}

	template<typename T>
	MEDUSA_FORCE_INLINE  float LinearBlend(T val, T begin, T end)
	{
		return Clamp((val - begin) / (end - begin), 0.f, 1.f);
	}

	template<typename T>
	MEDUSA_FORCE_INLINE  float SmoothBlend(T val, T begin, T end)
	{
		float f = Clamp((val - begin) / (end - begin), 0.f, 1.f);
		return f*f*(3.f - 2.f*f);
	}

	template<typename T>
	MEDUSA_FORCE_INLINE  T Barycentric(T value1, T value2, T value3, T amount1, T amount2)
	{
		return ((value1 + (amount1 * (value2 - value1))) + (amount2 * (value3 - value1)));
	}

	float CatmullRom(float value1, float value2, float value3, float value4, float amount);
	float Hermite(float value1, float tangent1, float value2, float tangent2, float amount);
	size_t GetNewSizeSquare(size_t originalSize, size_t newSize);
	size_t GetNewSizeOneAndHalf(size_t originalSize, size_t newSize);

	size_t NextPOT(size_t x);

	size_t GetPrime(size_t min);

	bool IsPrime(size_t candidate);

	enum class TweenType
	{
		None = -1,
		//Linear:
		Linear,

		//Quadratic:(t^2)
		QuadraticEaseIn,
		QuadraticEaseOut,
		QuadraticEaseInOut,

		//Cubic:(t^3)
		CubicEaseIn,
		CubicEaseOut,
		CubicEaseInOut,

		//Quartic:(t^4)
		QuarticEaseIn,
		QuarticEaseOut,
		QuarticEaseInOut,

		//Quintic:(t^5)
		QuinticEaseIn,
		QuinticEaseOut,
		QuinticEaseInOut,

		//Sinusoidal:(sin(t))
		SinusoidalEaseIn,
		SinusoidalEaseOut,
		SinusoidalEaseInOut,

		//Exponential:(2^t)
		ExponentialEaseIn,
		ExponentialEaseOut,
		ExponentialEaseInOut,

		//Circular:(sqrt(1-t^2))
		CircularEaseIn,
		CircularEaseOut,
		CircularEaseInOut,

		//Elastic:
		ElasticEaseIn,
		ElasticEaseOut,
		ElasticEaseInOut,

		//Back:((s+1)*t^3 - s*t^2)
		BackEaseIn,
		BackEaseOut,
		BackEaseInOut,

		//Bounce:
		BounceEaseIn,
		BounceEaseOut,
		BounceEaseInOut,

		//Rate:
		RateEaseIn,
		RateEaseOut,
		RateEaseInOut,

		Bezier2,
		Bezier3,
		BezierCurve3,
		BezierCurve3ZeroToOneWithStep10,
		BezierCurve3ZeroToOne,
		BezierCurve3ZeroToOneWithPreCalculateArgs,



		Count,
	};


	namespace Tween
	{
		


		float Linear(float time);

		float QuadraticEaseIn(float time);
		float QuadraticEaseOut(float time);
		float QuadraticEaseInOut(float time);

		float CubicEaseIn(float time);
		float CubicEaseOut(float time);
		float CubicEaseInOut(float time);

		float QuarticEaseIn(float time);
		float QuarticEaseOut(float time);
		float QuarticEaseInOut(float time);

		float QuinticEaseIn(float time);
		float QuinticEaseOut(float time);
		float QuinticEaseInOut(float time);


		float SinusoidalEaseIn(float time);
		float SinusoidalEaseOut(float time);
		float SinusoidalEaseInOut(float time);

		float ExponentialEaseIn(float time);
		float ExponentialEaseOut(float time);
		float ExponentialEaseInOut(float time);

		float CircularEaseIn(float time);
		float CircularEaseOut(float time);
		float CircularEaseInOut(float time);

		float ElasticEaseIn(float time, float period);
		float ElasticEaseOut(float time, float period);
		float ElasticEaseInOut(float time, float period);

		float BackEaseIn(float time);
		float BackEaseOut(float time);
		float BackEaseInOut(float time);

		float BounceTime(float time);
		float BounceEaseIn(float time);
		float BounceEaseOut(float time);
		float BounceEaseInOut(float time);

		float RateEaseIn(float time, float rate);
		float RateEaseOut(float time, float rate);
		float RateEaseInOut(float time, float rate);

		float Bezier2(float time, float a, float b, float c);
		float Bezier3(float time, float a, float b, float c, float d);

		/*
		Bezier curve
		x axis means time changes
		target changes from "from" to "to", time to get y
		c1,c2 indicates 2 control points,
		need steps to simulate
		*/
		float BezierCurve3(float time, float fromX, float fromY, float cx1, float cy1, float cx2, float cy2, float toX, float toY, int steps);
		/*
		simple version
		from=(0,0)
		to=(1,1)
		steps=10
		*/
		float BezierCurve3ZeroToOneWithStep10(float time, float cx1, float cy1, float cx2, float cy2);
		float BezierCurve3ZeroToOne(float time, float cx1, float cy1, float cx2, float cy2, int steps);

		void PreCalculateBezierCurve3ZeroToOne(float cx1, float cy1, float cx2, float cy2, int steps, float* outArgs);
		float BezierCurve3ZeroToOneWithPreCalculateArgs(float time, float dfx, float dfy, float ddfx, float ddfy, float dddfx, float dddfy, int steps);




		//custom
		float TweenTo(float time, TweenType type, const float* args);


	}

	




};



//template<> byte MinValue(){return ByteMinValue;}
//template<> char MinValue(){return CharMinValue;}
//template<> short MinValue(){return ShortMinValue;}
//template<> ushort MinValue(){return UShortMinValue;}
//template<> int MinValue(){return IntMinValue;}
//template<> uint MinValue(){return UIntMinValue;}
//template<> float MinValue(){return FloatMinValue;}
//template<> double MinValue(){return DoubleMinValue;}
//
//template<> byte MaxValue(){return ByteMaxValue;}
//template<> char MaxValue(){return CharMaxValue;}
//template<> short MaxValue(){return ShortMaxValue;}
//template<> ushort MaxValue(){return UShortMaxValue;}
//template<> int MaxValue(){return IntMaxValue;}
//template<> uint MaxValue(){return UIntMaxValue;}
//template<> float MaxValue(){return FloatMaxValue;}
//template<> double MaxValue(){return DoubleMaxValue;}


MEDUSA_END;
