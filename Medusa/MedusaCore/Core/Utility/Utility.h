// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once

#include "MedusaCorePreDeclares.h"
#include "Core/Compile/TypeTraits.h"

MEDUSA_BEGIN;



namespace Utility
{
	void EnableFloatPointException(bool isEnable);
	bool HasBit(size_t val, byte index);
	uint32 SwapUInt(uint32 val);
	uint64 SwapUInt64(uint64 val);

	void SwapBytes(unsigned char* data, size_t size);
	int ToInt(const byte* data, size_t size = sizeof(int));
	double ToDouble(const byte* data);
	float ToFloat(const byte* data);



	inline uint64 GetHighPart(uint64 val) { return val & 0xffffffff00000000ull; }

	// ZigZag encoding
	template<typename T>
	inline typename std::make_unsigned<T>::type EncodeZigZag(T value)
	{
		return (value << 1) ^ (value >> (sizeof(T) * 8 - 1));
	}


	// ZigZag decoding
	template<typename T>
	inline typename std::make_signed<T>::type DecodeZigZag(T value)
	{
		return (value >> 1) ^ (-(typename std::make_signed<T>::type)(value & 1));
	}


	char ToHexChar(int val);
	int FromHexChar(char c);
}

MEDUSA_END;