#include <stdint.h>
#include "digitslut.h"

//https ://github.com/miloyip/itoa-benchmark#
// Branching for different cases (forward)
// Use lookup table of two digits
template<typename T>
T* u32toa_branchlut(uint32_t value, T* buffer)
{
	const T* lut = GetDigitsLut<T>();
	if (value < 10000)
	{
		const uint32_t d1 = (value / 100) << 1;
		const uint32_t d2 = (value % 100) << 1;

		if (value >= 1000)
			*buffer++ = lut[d1];
		if (value >= 100)
			*buffer++ = lut[d1 + 1];
		if (value >= 10)

			*buffer++ = lut[d2];
		*buffer++ = lut[d2 + 1];
	}
	else if (value < 100000000)
	{
		// value = bbbbcccc
		const uint32_t b = value / 10000;
		const uint32_t c = value % 10000;

		const uint32_t d1 = (b / 100) << 1;
		const uint32_t d2 = (b % 100) << 1;

		const uint32_t d3 = (c / 100) << 1;
		const uint32_t d4 = (c % 100) << 1;

		if (value >= 10000000)
			*buffer++ = lut[d1];
		if (value >= 1000000)
			*buffer++ = lut[d1 + 1];
		if (value >= 100000)
			*buffer++ = lut[d2];
		*buffer++ = lut[d2 + 1];

		*buffer++ = lut[d3];
		*buffer++ = lut[d3 + 1];
		*buffer++ = lut[d4];
		*buffer++ = lut[d4 + 1];
	}
	else
	{
		// value = aabbbbcccc in decimal

		const uint32_t a = value / 100000000; // 1 to 42
		value %= 100000000;

		if (a >= 10)
		{
			const unsigned i = a << 1;
			*buffer++ = lut[i];
			*buffer++ = lut[i + 1];
		}
		else
			*buffer++ = '0' + static_cast<T>(a);

		const uint32_t b = value / 10000; // 0 to 9999
		const uint32_t c = value % 10000; // 0 to 9999

		const uint32_t d1 = (b / 100) << 1;
		const uint32_t d2 = (b % 100) << 1;

		const uint32_t d3 = (c / 100) << 1;
		const uint32_t d4 = (c % 100) << 1;

		*buffer++ = lut[d1];
		*buffer++ = lut[d1 + 1];
		*buffer++ = lut[d2];
		*buffer++ = lut[d2 + 1];
		*buffer++ = lut[d3];
		*buffer++ = lut[d3 + 1];
		*buffer++ = lut[d4];
		*buffer++ = lut[d4 + 1];
	}

	*buffer = '\0';
	return buffer;
}
template<typename T>
T* i32toa_branchlut(int32_t value, T* buffer)
{
	if (value < 0)
	{
		*buffer++ = '-';
		value = -value;
	}

	return u32toa_branchlut(static_cast<uint32_t>(value), buffer);
}

template<typename T>
T* i32toa_branchlut_without_sign(int32_t value, T* buffer,bool& outSign)
{
	if (value < 0)
	{
		outSign = false;
		value = -value;
	}
	outSign = true;
	return u32toa_branchlut(static_cast<uint32_t>(value), buffer);
}

template<typename T>
T* u64toa_branchlut(uint64_t value, T* buffer)
{
	const T* lut = GetDigitsLut<T>();
	if (value < 100000000)
	{
		uint32_t v = static_cast<uint32_t>(value);
		if (v < 10000)
		{
			const uint32_t d1 = (v / 100) << 1;
			const uint32_t d2 = (v % 100) << 1;

			if (v >= 1000)
				*buffer++ = lut[d1];
			if (v >= 100)
				*buffer++ = lut[d1 + 1];
			if (v >= 10)
				*buffer++ = lut[d2];
			*buffer++ = lut[d2 + 1];
		}
		else
		{
			// value = bbbbcccc
			const uint32_t b = v / 10000;
			const uint32_t c = v % 10000;

			const uint32_t d1 = (b / 100) << 1;
			const uint32_t d2 = (b % 100) << 1;

			const uint32_t d3 = (c / 100) << 1;
			const uint32_t d4 = (c % 100) << 1;

			if (value >= 10000000)
				*buffer++ = lut[d1];
			if (value >= 1000000)
				*buffer++ = lut[d1 + 1];
			if (value >= 100000)
				*buffer++ = lut[d2];
			*buffer++ = lut[d2 + 1];

			*buffer++ = lut[d3];
			*buffer++ = lut[d3 + 1];
			*buffer++ = lut[d4];
			*buffer++ = lut[d4 + 1];
		}
	}
	else if (value < 10000000000000000)
	{
		const uint32_t v0 = static_cast<uint32_t>(value / 100000000);
		const uint32_t v1 = static_cast<uint32_t>(value % 100000000);

		const uint32_t b0 = v0 / 10000;
		const uint32_t c0 = v0 % 10000;

		const uint32_t d1 = (b0 / 100) << 1;
		const uint32_t d2 = (b0 % 100) << 1;

		const uint32_t d3 = (c0 / 100) << 1;
		const uint32_t d4 = (c0 % 100) << 1;

		const uint32_t b1 = v1 / 10000;
		const uint32_t c1 = v1 % 10000;

		const uint32_t d5 = (b1 / 100) << 1;
		const uint32_t d6 = (b1 % 100) << 1;

		const uint32_t d7 = (c1 / 100) << 1;
		const uint32_t d8 = (c1 % 100) << 1;

		if (value >= 1000000000000000)
			*buffer++ = lut[d1];
		if (value >= 100000000000000)
			*buffer++ = lut[d1 + 1];
		if (value >= 10000000000000)
			*buffer++ = lut[d2];
		if (value >= 1000000000000)
			*buffer++ = lut[d2 + 1];
		if (value >= 100000000000)
			*buffer++ = lut[d3];
		if (value >= 10000000000)
			*buffer++ = lut[d3 + 1];
		if (value >= 1000000000)
			*buffer++ = lut[d4];
		if (value >= 100000000)
			*buffer++ = lut[d4 + 1];

		*buffer++ = lut[d5];
		*buffer++ = lut[d5 + 1];
		*buffer++ = lut[d6];
		*buffer++ = lut[d6 + 1];
		*buffer++ = lut[d7];
		*buffer++ = lut[d7 + 1];
		*buffer++ = lut[d8];
		*buffer++ = lut[d8 + 1];
	}
	else
	{
		const uint32_t a = static_cast<uint32_t>(value / 10000000000000000); // 1 to 1844
		value %= 10000000000000000;

		if (a < 10)
			*buffer++ = '0' + static_cast<char>(a);
		else if (a < 100)
		{
			const uint32_t i = a << 1;
			*buffer++ = lut[i];
			*buffer++ = lut[i + 1];
		}
		else if (a < 1000)
		{
			*buffer++ = '0' + static_cast<char>(a / 100);

			const uint32_t i = (a % 100) << 1;
			*buffer++ = lut[i];
			*buffer++ = lut[i + 1];
		}
		else
		{
			const uint32_t i = (a / 100) << 1;
			const uint32_t j = (a % 100) << 1;
			*buffer++ = lut[i];
			*buffer++ = lut[i + 1];
			*buffer++ = lut[j];
			*buffer++ = lut[j + 1];
		}

		const uint32_t v0 = static_cast<uint32_t>(value / 100000000);
		const uint32_t v1 = static_cast<uint32_t>(value % 100000000);

		const uint32_t b0 = v0 / 10000;
		const uint32_t c0 = v0 % 10000;

		const uint32_t d1 = (b0 / 100) << 1;
		const uint32_t d2 = (b0 % 100) << 1;

		const uint32_t d3 = (c0 / 100) << 1;
		const uint32_t d4 = (c0 % 100) << 1;

		const uint32_t b1 = v1 / 10000;
		const uint32_t c1 = v1 % 10000;

		const uint32_t d5 = (b1 / 100) << 1;
		const uint32_t d6 = (b1 % 100) << 1;

		const uint32_t d7 = (c1 / 100) << 1;
		const uint32_t d8 = (c1 % 100) << 1;

		*buffer++ = lut[d1];
		*buffer++ = lut[d1 + 1];
		*buffer++ = lut[d2];
		*buffer++ = lut[d2 + 1];
		*buffer++ = lut[d3];
		*buffer++ = lut[d3 + 1];
		*buffer++ = lut[d4];
		*buffer++ = lut[d4 + 1];
		*buffer++ = lut[d5];
		*buffer++ = lut[d5 + 1];
		*buffer++ = lut[d6];
		*buffer++ = lut[d6 + 1];
		*buffer++ = lut[d7];
		*buffer++ = lut[d7 + 1];
		*buffer++ = lut[d8];
		*buffer++ = lut[d8 + 1];
	}

	*buffer = '\0';
	return buffer;
}

template<typename T>
T* i64toa_branchlut(int64_t value, T* buffer)
{
	if (value < 0)
	{
		*buffer++ = '-';
		value = -value;
	}

	return u64toa_branchlut(static_cast<uint64_t>(value), buffer);
}

template<typename T>
T* i64toa_branchlut_without_sign(int64_t value, T* buffer, bool& outSign)
{
	if (value < 0)
	{
		outSign = false;
		value = -value;
	}
	outSign = true;
	return u64toa_branchlut(static_cast<uint64_t>(value), buffer);
}

