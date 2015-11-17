// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Core/Math/Math.h"

MEDUSA_BEGIN;

namespace Math
{
	template<> const byte Values<byte>::Min = (byte)0x00;
	template<> const char Values<char>::Min = (char)-127;
	template<> const short Values<short>::Min = (short)0x8000u;
	template<> const ushort Values<ushort>::Min = (ushort)0x0000;
	template<> const int32 Values<int32>::Min = (int32)0x80000000;
	template<> const uint32 Values<uint32>::Min = (uint32)0x00000000;

	template<> const int64 Values<int64>::Min = (int64)0x8000000000000000;
	template<> const uint64 Values<uint64>::Min = (uint64)0x0000000000000000;

	template<> const float Values<float>::Min = FLT_MIN;
	template<> const double Values<double>::Min = DBL_MIN;

	template<> const byte Values<byte>::Max = (byte)0xFF;
	template<> const char Values<char>::Max = (char)0x7F;
	template<> const short Values<short>::Max = (short)0x7FFF;
	template<> const ushort Values<ushort>::Max = (ushort)0xFFFF;
	template<> const int32 Values<int32>::Max = (int32)0x7FFFFFFF;
	template<> const uint32 Values<uint32>::Max = (uint32)0xFFFFFFFF;

	template<> const int64 Values<int64>::Max = (int64)0x7FFFFFFFFFFFFFFF;
	template<> const uint64 Values<uint64>::Max = (uint64)0xFFFFFFFFFFFFFFFF;

#ifdef MEDUSA_IOS
#ifdef MEDUSA_X64
	template<> const long Values<long>::Min = (long)0x8000000000000000;
	template<> const ulong Values<ulong>::Min = (ulong)0x0000000000000000;
	template<> const long Values<long>::Max = (long)0x7FFFFFFFFFFFFFFF;
	template<> const ulong Values<ulong>::Max = (ulong)0xFFFFFFFFFFFFFFFF;
#else
	template<> const long Values<long>::Min = (long)0x80000000;
	template<> const ulong Values<ulong>::Min = (ulong)0x00000000;
	template<> const long Values<long>::Max = (long)0x7FFFFFFF;
	template<> const ulong Values<ulong>::Max = (ulong)0xFFFFFFFF;
#endif

#endif

	const int64 Int64MaxValue = (int64)0x7FFFFFFFFFFFFFFF;
	const int64 Int64MinValue = (int64)0x8000000000000000;
	const uint64 UInt64MaxValue = (uint64)0xFFFFFFFFFFFFFFFF;
	const uint64 UInt64MinValue = (uint64)0x0000000000000000;

	template<> const float Values<float>::Max = FLT_MAX;
	template<> const double Values<double>::Max = DBL_MAX;

	const size_t mPrimes[72] = {
		3, 7, 11, 0x11, 0x17, 0x1d, 0x25, 0x2f, 0x3b, 0x47, 0x59, 0x6b, 0x83, 0xa3, 0xc5, 0xef,
		0x125, 0x161, 0x1af, 0x209, 0x277, 0x2f9, 0x397, 0x44f, 0x52f, 0x63d, 0x78b, 0x91d, 0xaf1, 0xd2b, 0xfd1, 0x12fd,
		0x16cf, 0x1b65, 0x20e3, 0x2777, 0x2f6f, 0x38ff, 0x446f, 0x521f, 0x628d, 0x7655, 0x8e01, 0xaa6b, 0xcc89, 0xf583, 0x126a7, 0x1619b,
		0x1a857, 0x1fd3b, 0x26315, 0x2dd67, 0x3701b, 0x42023, 0x4f361, 0x5f0ed, 0x72125, 0x88e31, 0xa443b, 0xc51eb, 0xec8c1, 0x11bdbf, 0x154a3f, 0x198c4f,
		0x1ea867, 0x24ca19, 0x2c25c1, 0x34fa1b, 0x3f928f, 0x4c4987, 0x5b8b6f, 0x6dda89 };

#pragma region Trigonometric



	float Sin(float radian)
	{
#ifdef MEDUSA_MATH_NEON_ENABLED
		return sinf_neon(radian);
#else
		return sinf(radian);
#endif
	}

	float Sinh(float radian)
	{
#ifdef MEDUSA_MATH_NEON_ENABLED
		return sinhf_neon(radian);
#else
		return sinhf(radian);
#endif
	}

	float Asin(float x)
	{
		if (x <= -1.f)
		{
			return -PIHalf;
		}
		else if (x >= 1.f)
		{
			return PIHalf;
		}
		else
		{
#ifdef MEDUSA_MATH_NEON_ENABLED
			return asinf_neon(x);
#else
			return asinf(x);
#endif
		}
	}

	float Cos(float radian)
	{
#ifdef MEDUSA_MATH_NEON_ENABLED
		return cosf_neon(radian);
#else
		return cosf(radian);
#endif
	}

	float Cosh(float radian)
	{
#ifdef MEDUSA_MATH_NEON_ENABLED
		return coshf_neon(radian);
#else
		return coshf(radian);
#endif
	}


	double Acosh(double radian)
	{
		return acosh(radian);
	}
	float Acosh(float radian)
	{
		return acoshf(radian);
	}

	double Asinh(double radian)
	{
		return asinh(radian);
	}
	float Asinh(float radian)
	{
		return asinhf(radian);
	}

	double Atanh(double radian)
	{
		return atanh(radian);
	}
	float Atanh(float radian)
	{
		return atanhf(radian);
	}


	float Acos(float x)
	{
		if (x <= -1.f)
		{
			return PI;
		}
		else if (x >= 1.f)
		{
			return 0.f;
		}
		else
		{
#ifdef MEDUSA_MATH_NEON_ENABLED
			return acosf_neon(x);
#else
			return acosf(x);
#endif
		}
	}

	float Tan(float radian)
	{
#ifdef MEDUSA_MATH_NEON_ENABLED
		return tanf_neon(radian);
#else
		return tanf(radian);
#endif
	}

	float Cot(float radian)
	{
		return Tan(PIHalf - radian);
	}

	float Tanh(float radian)
	{
#ifdef MEDUSA_MATH_NEON_ENABLED
		return tanhf_neon(radian);
#else
		return tanhf(radian);
#endif
	}

	float Atan(float x)
	{
#ifdef MEDUSA_MATH_NEON_ENABLED
		return atanf_neon(x);
#else
		return atanf(x);
#endif
	}

	float Atan2(float y, float x)
	{
		/*
			y=sin(a)
			x=cos(a)
			tan(a) = y / x,	And (x, y) is a point in Cartesian plane
			If (x, y) at 1 quadrant,then 0 < a < PI/2
			If (x, y) at 2 quadrant,then PI/2 < a<PI
			If (x, y) at 3 quadrant,then -PI < a < -PI/2
			If (x, y) at 4 quadrant,then -PI/2 < a < 0

			if point is at quadrant edge,then return:
			if y == 0 && x >0, then a = 0
			if y == 0 && x <0,then a=PI
			if y >0 && x==0,then a= PI/2
			if y <0 && x==0,then a= -PI/2
			if y == 0 && x == 0,then a = 0
			*/
#ifdef MEDUSA_MATH_NEON_ENABLED
		return atan2f_neon(y, x);
#else
		return atan2f(y, x);
#endif
	}


	float WrapToPI2(float a)
	{
		//limit a to 0 and 2??
		return a - PI2 * Floor(a *PI2Inverse);
	}

	float WrapToPI(float a)
	{
		//limit a to -PI and PI
		a += PI;
		a -= Floor(a*PI2Inverse)*PI2;
		a -= PI;
		return a;
	}


	float DiffAngle(float a, float b)
	{
		//limit a to -PI and PI
		float diff = Fmod(b - a + PI, PI2);
		if (diff < 0.f)
			diff += PI2;
		return diff - PI;
	}

	float BisectAngle(float a, float b)
	{
		return WrapToPI(a + DiffAngle(a, b)*0.5f);
	}

#pragma endregion Trigonometric

#pragma region Rounding and remainder functions

	float Exp(float x)
	{
#ifdef MEDUSA_MATH_NEON_ENABLED
		return expf_neon(x);
#else
		return expf(x);
#endif
	}


	
	float Exp2(float x)
	{
		return exp2(x);
	}
	double Exp2(double x)
	{
		return exp2(x);
	}

	float ExpM1(float x)
	{
		return expm1(x);
	}

	double ExpM1(double x)
	{
		return expm1(x);
	}

	//return log(|x| ) integer part,ilogb(10.000000) = 3
	int Ilogb(float x)
	{
		return ilogb(x);
	}
	int Ilogb(double x)
	{
		return ilogb(x);
	}

	//return log(|x| ) logb (1024.000000) = 10.000000
	float Logb(float x)
	{
		return logb(x);
	}
	double Logb(double x)
	{
		return logb(x);
	}

	//return log(|1+x| ) ,log1p (1.000000) = 0.693147
	float Log1p(float x)
	{
		return log1pf(x);
	}
	double Log1p(double x)
	{
		return log1p(x);
	}

	//log2x.
	float Log2(float x)
	{
		return log2f(x);
	}
	double Log2(double x)
	{
		return log2(x);
	}

	//Rounds x toward zero, returning the nearest integral value that is not larger in magnitude than x.
	float Truncate(float x)
	{
		return trunc(x);
	}
	double Truncate(double x)
	{
		return trunc(x);
	}

	//Returns the integral value that is nearest to x, with halfway cases rounded away from zero.
	float Round(float x)
	{
		return round(x);
	}
	double Round(double x)
	{
		return round(x);
	}

	//Returns the integer value that is nearest in value to x, with halfway cases rounded away from zero.
	//lround (2.3) = 2
	//	lround (3.8) = 4
	//	lround (-2.3) = -2
	//	lround (-3.8) = -4
	long int LRound(float x)
	{
		return lround(x);
	}
	long int LRound(double x)
	{
		return lround(x);
	}

	//Returns the integer value that is nearest in value to x, with halfway cases rounded away from zero.
	/*llround (2.3) = 2
	llround (3.8) = 4
	llround (-2.3) = -2
	llround (-3.8) = -4*/
	long long int LLRound(float x)
	{
		return llround(x);
	}
	long long int LLRound(double x)
	{
		return llround(x);
	}




	float Log(float x)
	{
#ifdef MEDUSA_MATH_NEON_ENABLED
		return logf_neon(x);
#else
		return logf(x);
#endif
	}

	double Log(double x)
	{
#ifdef MEDUSA_MATH_NEON_ENABLED
		return log_neon(x);
#else
		return log(x);
#endif
	}


	float Log10(float x)
	{
#ifdef MEDUSA_MATH_NEON_ENABLED
		return log10f_neon(x);
#else
		return log10f(x);
#endif
	}

	float Pow(float x, float y)
	{
#ifdef MEDUSA_MATH_NEON_ENABLED
		return powf_neon(x, y);
#else
		return powf(x, y);
#endif
	}

	float Fract(float x)
	{
#ifdef MEDUSA_MATH_NEON_ENABLED
		return x - floorf_neon(x);
#else
		return x - floorf(x);
#endif
	}

	float Floor(float x)
	{
#ifdef MEDUSA_MATH_NEON_ENABLED
		return floorf_neon(x);
#else
		return floorf(x);
#endif
	}

	float Ceil(float x)
	{
#ifdef MEDUSA_MATH_NEON_ENABLED
		return ceilf_neon(x);
#else
		return ceilf(x);
#endif
	}

	float Abs(float x)
	{
#ifdef MEDUSA_MATH_NEON_ENABLED
		return fabsf_neon(x);
#else
		return fabsf(x);
#endif
	}

#ifdef MEDUSA_WINDOWS
	div_t Div(int number, int denom)
	{
		return div(number, denom);
	}

	ldiv_t Div(long int number, long int denom)
	{
		return div(number, denom);
	}

	lldiv_t Div(long long int number, long long int denom)
	{
		return div(number, denom);
	}
#else
	div_t Div(int number, int denom)
	{
		return div(number, denom);
	}

#endif

	float Frexp(float x, int* y)
	{
#ifdef MEDUSA_MATH_NEON_ENABLED
		return medusa_frexpf(x, y);
#else
		return frexpf(x, y);
#endif
	}

	float Ldexp(float x, int y)
	{
#ifdef MEDUSA_MATH_NEON_ENABLED
		return ldexpf_neon(x, y);
#else
		return ldexpf(x, y);
#endif
	}

	double Mod(double x, double* y)
	{
#ifdef MEDUSA_MATH_NEON_ENABLED
		return modf_neon(x, y);
#else
		return modf(x, y);
#endif
	}

	float Fmod(float x, float y)
	{
#ifdef MEDUSA_MATH_NEON_ENABLED
		return fmodf_neon(x, y);
#else
		return fmodf(x, y);
#endif
	}

	float Sqrt(float x)
	{
#ifdef MEDUSA_MATH_NEON_ENABLED
		return sqrtf_neon(x);
#else
		return sqrtf(x);
#endif
	}

	double Sqrt(double x)
	{
#ifdef MEDUSA_MATH_NEON_ENABLED
		return sqrt_neon(x);
#else
		return sqrt(x);
#endif
	}

	float InverseSqrt(float x)
	{
#ifdef MEDUSA_MATH_NEON_ENABLED
		return invsqrtf_neon(x);
#else
		return 1.f / sqrtf(x);
#endif
	}

	float Hypot(float x, float y)
	{
		return hypotf(x, y);
	}

#pragma endregion Rounding and remainder functions

	float CatmullRom(float value1, float value2, float value3, float value4, float amount)
	{
		float num = amount * amount;
		float num2 = amount * num;
		return (0.5f * ((((2.f * value2) + ((-value1 + value3) * amount)) + (((((2.f * value1) - (5.f * value2)) + (4.f * value3)) - value4) * num)) + ((((-value1 + (3.f * value2)) - (3.f * value3)) + value4) * num2)));
	}

	float Hermite(float value1, float tangent1, float value2, float tangent2, float amount)
	{
		float num3 = amount;
		float num = num3 * num3;
		float num2 = num3 * num;
		float num7 = ((2.f * num2) - (3.f * num)) + 1.f;
		float num6 = (-2.f * num2) + (3.f * num);
		float num5 = (num2 - (2.f * num)) + num3;
		float num4 = num2 - num;
		return ((((value1 * num7) + (value2 * num6)) + (tangent1 * num5)) + (tangent2 * num4));
	}



	size_t GetNewSizeSquare(size_t originalSize, size_t newSize)
	{
		if (originalSize == 0)
		{
			originalSize = 1;
		}

		while (originalSize < newSize)
		{
			originalSize <<= 1;
		}

		return originalSize;
	}


	size_t GetNewSizeOneAndHalf(size_t originalSize, size_t newSize)
	{
		if (originalSize == 0)
		{
			originalSize = 1;
		}

		while (originalSize < newSize)
		{
			originalSize += (originalSize + 1) / 2;
		}

		return originalSize;
	}

	size_t NextPOT(size_t x)
	{
		--x;
		x = x | (x >> 1);
		x = x | (x >> 2);
		x = x | (x >> 4);
		x = x | (x >> 8);
		x = x | (x >> 16);
		return ++x;
	}

	size_t GetPrime(size_t min)
	{
		for (size_t i = 0; i < 72; i++)
		{
			size_t num2 = mPrimes[i];
			if (num2 >= min)
			{
				return num2;
			}
		}

		for (size_t j = min | 1; j < 0x7fffffff; j += 2)
		{
			if (IsPrime(j))
			{
				return j;
			}
		}
		return min;
	}

	bool IsPrime(size_t candidate)
	{
		if ((candidate & 1) == 0)
		{
			return (candidate == 2);
		}

		int num = (int)Math::Sqrt((float)candidate);
		for (int i = 3; i <= num; i += 2)
		{
			if ((candidate % i) == 0)
			{
				return false;
			}
		}
		return true;
	}

	namespace Tween
	{

		float Linear(float time)
		{
			return time;
		}


		float QuadraticEaseIn(float time)
		{
			return time*time;
		}

		float QuadraticEaseOut(float time)
		{
			return -1 * time * (time - 2);
		}

		float QuadraticEaseInOut(float time)
		{
			time = time * 2;
			if (time < 1)
				return 0.5f * time * time;
			--time;
			return -0.5f * (time * (time - 2) - 1);
		}

		float CubicEaseIn(float time)
		{
			return time * time * time;
		}

		float CubicEaseOut(float time)
		{
			time -= 1;
			return (time * time * time + 1);
		}

		float CubicEaseInOut(float time)
		{
			time = time * 2;
			if (time < 1)
				return 0.5f * time * time * time;
			time -= 2;
			return 0.5f * (time * time * time + 2);
		}

		float QuarticEaseIn(float time)
		{
			return time * time * time * time;
		}

		float QuarticEaseOut(float time)
		{
			time -= 1;
			return -(time * time * time * time - 1);
		}

		float QuarticEaseInOut(float time)
		{
			time = time * 2;
			if (time < 1)
				return 0.5f * time * time * time * time;
			time -= 2;
			return -0.5f * (time * time * time * time - 2);
		}

		float QuinticEaseIn(float time)
		{
			return time * time * time * time * time;
		}

		float QuinticEaseOut(float time)
		{
			time -= 1;
			return (time * time * time * time * time + 1);
		}

		float QuinticEaseInOut(float time)
		{
			time = time * 2;
			if (time < 1)
				return 0.5f * time * time * time * time * time;
			time -= 2;
			return 0.5f * (time * time * time * time * time + 2);
		}

		float SinusoidalEaseIn(float time)
		{
			return -1 * cosf(time * (float)PIHalf) + 1;
		}

		float SinusoidalEaseOut(float time)
		{
			return sinf(time * (float)PIHalf);
		}

		float SinusoidalEaseInOut(float time)
		{
			return -0.5f * (cosf((float)PI * time) - 1);
		}

		float ExponentialEaseIn(float time)
		{
			return time == 0 ? 0 : powf(2, 10 * (time / 1 - 1)) - 1 * 0.001f;
		}

		float ExponentialEaseOut(float time)
		{
			return time == 1 ? 1 : (-powf(2, -10 * time / 1) + 1);
		}

		float ExponentialEaseInOut(float time)
		{
			time /= 0.5f;
			if (time < 1)
			{
				time = 0.5f * powf(2, 10 * (time - 1));
			}
			else
			{
				time = 0.5f * (-powf(2, -10 * (time - 1)) + 2);
			}

			return time;
		}

		float CircularEaseIn(float time)
		{
			return -1 * (sqrt(1 - time * time) - 1);
		}

		float CircularEaseOut(float time)
		{
			time = time - 1;
			return sqrt(1 - time * time);
		}

		float CircularEaseInOut(float time)
		{
			time = time * 2;
			if (time < 1)
				return -0.5f * (sqrt(1 - time * time) - 1);
			time -= 2;
			return 0.5f * (sqrt(1 - time * time) + 1);
		}

		float ElasticEaseIn(float time, float period)
		{
			float newT = 0;
			if (time == 0 || time == 1)
			{
				newT = time;
			}
			else
			{
				float s = period / 4;
				time = time - 1;
				newT = -powf(2, 10 * time) * sinf((time - s) * PI2 / period);
			}

			return newT;
		}

		float ElasticEaseOut(float time, float period)
		{
			float newT = 0;
			if (time == 0 || time == 1)
			{
				newT = time;
			}
			else
			{
				float s = period / 4;
				newT = powf(2, -10 * time) * sinf((time - s) * PI2 / period) + 1;
			}

			return newT;
		}

		float ElasticEaseInOut(float time, float period)
		{
			float newT = 0;
			if (time == 0 || time == 1)
			{
				newT = time;
			}
			else
			{
				time = time * 2;
				if (!period)
				{
					period = 0.3f * 1.5f;
				}

				float s = period / 4;

				time = time - 1;
				if (time < 0)
				{
					newT = -0.5f * powf(2, 10 * time) * sinf((time - s) * PI2 / period);
				}
				else
				{
					newT = powf(2, -10 * time) * sinf((time - s) * PI2 / period) * 0.5f + 1;
				}
			}
			return newT;
		}

		float BackEaseIn(float time)
		{
			const float overshoot = 1.70158f;
			return time * time * ((overshoot + 1) * time - overshoot);
		}

		float BackEaseOut(float time)
		{
			const float overshoot = 1.70158f;
			time = time - 1;
			return time * time * ((overshoot + 1) * time + overshoot) + 1;
		}

		float BackEaseInOut(float time)
		{
			const float overshoot = 1.70158f * 1.525f;
			time = time * 2;
			if (time < 1)
			{
				return (time * time * ((overshoot + 1) * time - overshoot)) / 2;
			}
			else
			{
				time = time - 2;
				return (time * time * ((overshoot + 1) * time + overshoot)) / 2 + 1;
			}
		}

		float BounceTime(float time)
		{
			if (time < 1 / 2.75)
			{
				return 7.5625f * time * time;
			}
			else if (time < 2 / 2.75)
			{
				time -= 1.5f / 2.75f;
				return 7.5625f * time * time + 0.75f;
			}
			else if (time < 2.5 / 2.75)
			{
				time -= 2.25f / 2.75f;
				return 7.5625f * time * time + 0.9375f;
			}

			time -= 2.625f / 2.75f;
			return 7.5625f * time * time + 0.984375f;
		}

		float BounceEaseIn(float time)
		{
			return 1 - BounceTime(1 - time);
		}

		float BounceEaseOut(float time)
		{
			return BounceTime(time);
		}

		float BounceEaseInOut(float time)
		{
			float newT = 0;
			if (time < 0.5f)
			{
				time = time * 2;
				newT = (1 - BounceTime(1 - time)) * 0.5f;
			}
			else
			{
				newT = BounceTime(time * 2 - 1) * 0.5f + 0.5f;
			}

			return newT;
		}

		float RateEaseIn(float time, float rate)
		{
			return powf(time, rate);
		}

		float RateEaseOut(float time, float rate)
		{
			return powf(time, 1 / rate);
		}

		float RateEaseInOut(float time, float rate)
		{
			time *= 2;
			if (time < 1)
			{
				return 0.5f * powf(time, rate);
			}
			else
			{
				return (1.0f - 0.5f * powf(2 - time, rate));
			}
		}

		float Bezier2(float time, float a, float b, float c)
		{
			return (powf(1 - time, 2) * a + 2 * time*(1 - time)*b + powf(time, 2)*c);
		}

		float Bezier3(float time, float a, float b, float c, float d)
		{
			return (powf(1 - time, 3) * a + 3 * time*(powf(1 - time, 2))*b + 3 * powf(time, 2)*(1 - time)*c + powf(time, 3)*d);
		}

		float BezierCurve3(float time, float fromX, float fromY, float cx1, float cy1, float cx2, float cy2, float toX, float toY, int steps)
		{
			/*
			The way of curve is actually conducted by the aforementioned Bezier3 step approximation of (formula derivation of Bezier3)
			First on the x axis Bezier3 than time until I find a nearby points, then the work out after Bezier3 y points at the same time
			*/
			time = Math::Clamp(time, fromX, toX);
			if (Math::IsEqual(time, fromX))
			{
				return fromY;
			}
			if (Math::IsEqual(time, toX))
			{
				return toY;
			}

			float subdiv_step = 1.f / steps;
			float subdiv_step2 = subdiv_step*subdiv_step;
			float subdiv_step3 = subdiv_step2*subdiv_step;

			float pre1 = 3.f * subdiv_step;
			float pre2 = 3.f * subdiv_step2;
			float pre4 = 6.f * subdiv_step2;
			float pre5 = 6.f * subdiv_step3;

			float tmp1x = fromX - cx1 * 2.f + cx2;
			float tmp1y = fromY - cy1 * 2.f + cy2;

			float tmp2x = (cx1 - cx2)*3.f - fromX + toX;
			float tmp2y = (cy1 - cy2)*3.f - fromY + toY;

			float x = fromX;
			float y = fromY;

			float dfx = (cx1 - fromX)*pre1 + tmp1x*pre2 + tmp2x*subdiv_step3;
			float dfy = (cy1 - fromY)*pre1 + tmp1y*pre2 + tmp2y*subdiv_step3;

			float ddfx = tmp1x*pre4 + tmp2x*pre5;
			float ddfy = tmp1y*pre4 + tmp2y*pre5;

			float dddfx = tmp2x*pre5;
			float dddfy = tmp2y*pre5;

			float prevX = x;
			float prevY = y;

			//start step
			do
			{
				if (x >= time)
				{
					//do linear slerp between current value and prev value
					return Math::LinearInterpolate(time, prevX, x, prevY, y);
				}

				prevX = x;
				prevY = y;

				x += dfx;
				y += dfy;
				dfx += ddfx;
				dfy += ddfy;
				ddfx += dddfx;
				ddfy += dddfy;
			} while (steps--);

			//still not reach target, use last point to linear slerp
			return Math::LinearInterpolate(time, x, toX, y, toY);
		}

		float BezierCurve3ZeroToOneWithStep10(float time, float cx1, float cy1, float cx2, float cy2)
		{
			time = Math::Clamp(time, 0.f, 1.f);
			if (Math::IsEqual(time, 0.f))
			{
				return 0.f;
			}
			if (Math::IsEqual(time, 1.f))
			{
				return 1.f;
			}

			float tmp1x = -cx1 * 2.f + cx2;
			float tmp1y = -cy1 * 2.f + cy2;

			float tmp2x = (cx1 - cx2)*3.f + 1.f;
			float tmp2y = (cy1 - cy2)*3.f + 1.f;

			float x = 0.f;
			float y = 0.f;

			float dfx = (cx1)*0.3f + tmp1x*0.03f + tmp2x*0.001f;
			float dfy = (cy1)*0.3f + tmp1y*0.03f + tmp2y*0.001f;

			float ddfx = tmp1x*0.06f + tmp2x*0.006f;
			float ddfy = tmp1y*0.06f + tmp2y*0.006f;

			float dddfx = tmp2x*0.006f;
			float dddfy = tmp2y*0.006f;

			float prevX = x;
			float prevY = y;

			//start step
			int steps = 10;
			do
			{
				if (x >= time)
				{
					//do linear slerp between current value and prev value
					return Math::LinearInterpolate(time, prevX, x, prevY, y);
				}

				prevX = x;
				prevY = y;

				x += dfx;
				y += dfy;
				dfx += ddfx;
				dfy += ddfy;
				ddfx += dddfx;
				ddfy += dddfy;
			} while (steps--);

			//still not reach target, use last point to linear slerp
			return Math::LinearInterpolate(time, x, 1.f, y, 1.f);
		}

		float BezierCurve3ZeroToOne(float time, float cx1, float cy1, float cx2, float cy2, int steps)
		{
			time = Math::Clamp(time, 0.f, 1.f);
			if (Math::IsEqual(time, 0.f))
			{
				return 0.f;
			}
			if (Math::IsEqual(time, 1.f))
			{
				return 1.f;
			}

			float subdiv_step = 1.f / steps;
			float subdiv_step2 = subdiv_step*subdiv_step;
			float subdiv_step3 = subdiv_step2*subdiv_step;

			float pre1 = 3.f * subdiv_step;
			float pre2 = 3.f * subdiv_step2;
			float pre4 = 6.f * subdiv_step2;
			float pre5 = 6.f * subdiv_step3;

			float tmp1x = -cx1 * 2.f + cx2;
			float tmp1y = -cy1 * 2.f + cy2;

			float tmp2x = (cx1 - cx2)*3.f + 1.f;
			float tmp2y = (cy1 - cy2)*3.f + 1.f;

			float x = 0.f;
			float y = 0.f;

			float dfx = (cx1)*pre1 + tmp1x*pre2 + tmp2x*subdiv_step3;
			float dfy = (cy1)*pre1 + tmp1y*pre2 + tmp2y*subdiv_step3;

			float ddfx = tmp1x*pre4 + tmp2x*pre5;
			float ddfy = tmp1y*pre4 + tmp2y*pre5;

			float dddfx = tmp2x*pre5;
			float dddfy = tmp2y*pre5;

			float prevX = x;
			float prevY = y;

			//start step
			do
			{
				if (x >= time)
				{
					//do linear slerp between current value and prev value
					return Math::LinearInterpolate(time, prevX, x, prevY, y);
				}
				prevX = x;
				prevY = y;
				x += dfx;
				y += dfy;
				dfx += ddfx;
				dfy += ddfy;
				ddfx += dddfx;
				ddfy += dddfy;
			} while (steps--);

			//still not reach target, use last point to linear slerp
			return Math::LinearInterpolate(time, x, 1.f, y, 1.f);
		}


		void PreCalculateBezierCurve3ZeroToOne(float cx1, float cy1, float cx2, float cy2, int steps, float* outArgs)
		{
			float subdiv_step = 1.f / steps;
			float subdiv_step2 = subdiv_step*subdiv_step;
			float subdiv_step3 = subdiv_step2*subdiv_step;

			float pre1 = 3.f * subdiv_step;
			float pre2 = 3.f * subdiv_step2;
			float pre4 = 6.f * subdiv_step2;
			float pre5 = 6.f * subdiv_step3;

			float tmp1x = -cx1 * 2.f + cx2;
			float tmp1y = -cy1 * 2.f + cy2;

			float tmp2x = (cx1 - cx2)*3.f + 1.f;
			float tmp2y = (cy1 - cy2)*3.f + 1.f;

			outArgs[0] = (cx1)*pre1 + tmp1x*pre2 + tmp2x*subdiv_step3;
			outArgs[1] = (cy1)*pre1 + tmp1y*pre2 + tmp2y*subdiv_step3;

			outArgs[2] = tmp1x*pre4 + tmp2x*pre5;
			outArgs[3] = tmp1y*pre4 + tmp2y*pre5;

			outArgs[4] = tmp2x*pre5;
			outArgs[5] = tmp2y*pre5;

			outArgs[6] = (float)steps;
		}


		float BezierCurve3ZeroToOneWithPreCalculateArgs(float time, float dfx, float dfy, float ddfx, float ddfy, float dddfx, float dddfy, int steps)
		{
			time = Math::Clamp(time, 0.f, 1.f);
			if (Math::IsEqual(time, 0.f))
			{
				return 0.f;
			}
			if (Math::IsEqual(time, 1.f))
			{
				return 1.f;
			}

			float x = 0.f;
			float y = 0.f;

			float prevX = x;
			float prevY = y;

			//start step
			do
			{
				if (x >= time)
				{
					//do linear slerp between current value and prev value
					return Math::LinearInterpolate(time, prevX, x, prevY, y);
				}

				prevX = x;
				prevY = y;
				x += dfx;
				y += dfy;
				dfx += ddfx;
				dfy += ddfy;
				ddfx += dddfx;
				ddfy += dddfy;
			} while (steps--);

			//still not reach target, use last point to linear slerp
			return Math::LinearInterpolate(time, x, 1.f, y, 1.f);
		}


		float TweenTo(float time, TweenType type, const float* args)
		{
			switch (type)
			{
			case TweenType::None:return time >= 1.f ? 1.f : 0.f;
			case TweenType::Linear:return Linear(time);
			case TweenType::QuadraticEaseIn:return QuadraticEaseIn(time);
			case TweenType::QuadraticEaseOut:return QuadraticEaseOut(time);
			case TweenType::QuadraticEaseInOut:return QuadraticEaseInOut(time);
			case TweenType::CubicEaseIn:return CubicEaseIn(time);
			case TweenType::CubicEaseOut:return CubicEaseOut(time);
			case TweenType::CubicEaseInOut:return CubicEaseInOut(time);
			case TweenType::QuarticEaseIn:return QuarticEaseIn(time);
			case TweenType::QuarticEaseOut:return QuarticEaseOut(time);
			case TweenType::QuarticEaseInOut:return QuarticEaseInOut(time);
			case TweenType::QuinticEaseIn:return QuinticEaseIn(time);
			case TweenType::QuinticEaseOut:return QuinticEaseOut(time);
			case TweenType::QuinticEaseInOut:return QuinticEaseInOut(time);
			case TweenType::SinusoidalEaseIn:return SinusoidalEaseIn(time);
			case TweenType::SinusoidalEaseOut:return SinusoidalEaseOut(time);
			case TweenType::SinusoidalEaseInOut:return SinusoidalEaseInOut(time);
			case TweenType::ExponentialEaseIn:return ExponentialEaseIn(time);
			case TweenType::ExponentialEaseOut:return ExponentialEaseOut(time);
			case TweenType::ExponentialEaseInOut:return ExponentialEaseInOut(time);
			case TweenType::CircularEaseIn:return CircularEaseIn(time);
			case TweenType::CircularEaseOut:return CircularEaseOut(time);
			case TweenType::CircularEaseInOut:return CircularEaseInOut(time);
			case TweenType::ElasticEaseIn:return ElasticEaseIn(time, args[0]);
			case TweenType::ElasticEaseOut:return ElasticEaseOut(time, args[0]);
			case TweenType::ElasticEaseInOut:return ElasticEaseInOut(time, args[0]);
			case TweenType::BackEaseIn:return BackEaseIn(time);
			case TweenType::BackEaseOut:return BackEaseOut(time);
			case TweenType::BackEaseInOut:return BackEaseInOut(time);
			case TweenType::BounceEaseIn:return BounceEaseIn(time);
			case TweenType::BounceEaseOut:return BounceEaseOut(time);
			case TweenType::BounceEaseInOut:return BounceEaseInOut(time);
			case TweenType::RateEaseIn:return RateEaseIn(time, args[0]);
			case TweenType::RateEaseOut:return RateEaseOut(time, args[0]);
			case TweenType::RateEaseInOut:return RateEaseInOut(time, args[0]);
			case TweenType::Bezier2:return Bezier2(time, args[0], args[1], args[2]);
			case TweenType::Bezier3:return Bezier3(time, args[0], args[1], args[2], args[3]);
			case TweenType::BezierCurve3:return BezierCurve3(time, args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7], (int)args[8]);
			case TweenType::BezierCurve3ZeroToOneWithStep10:return BezierCurve3ZeroToOneWithStep10(time, args[0], args[1], args[2], args[3]);
			case TweenType::BezierCurve3ZeroToOne:return BezierCurve3ZeroToOne(time, args[0], args[1], args[2], args[3], (int)args[4]);
			case TweenType::BezierCurve3ZeroToOneWithPreCalculateArgs:return BezierCurve3ZeroToOneWithPreCalculateArgs(time, args[0], args[1], args[2], args[3], args[4], args[5], (int)args[6]);
			default:
				break;
			}
			return time;
		}

	}






}


MEDUSA_END;
