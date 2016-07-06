// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"

MEDUSA_BEGIN;


class BitConverter
{
#pragma region Convert
public:
	static int ToInt(const byte* data, size_t size = sizeof(int));
	static double ToDouble(const byte* data);
	static float ToFloat(const byte* data);

	static void GetBytes(int val, byte* outData);
#pragma endregion Convert
#pragma region Math
public:
	static void EnableFloatPointException(bool isEnable);
	static bool HasBit(size_t val, byte index);
	static uint32 SwapUInt(uint32 val);
	static uint64 SwapUInt64(uint64 val);
	static void SwapBytes(unsigned char* data, size_t size);
	
	static inline uint64 GetHighPart(uint64 val) { return val & 0xffffffff00000000ull; }

	// ZigZag encoding
	template<typename T>
	static inline typename std::make_unsigned<T>::type EncodeZigZag(T value)
	{
		return (value << 1) ^ (value >> (sizeof(T) * 8 - 1));
	}


	// ZigZag decoding
	template<typename T>
	static inline typename std::make_signed<T>::type DecodeZigZag(T value)
	{
		return (value >> 1) ^ (-(typename std::make_signed<T>::type)(value & 1));
	}


	static char ToHexChar(int val);
	static int FromHexChar(char c);
#pragma endregion Math


#pragma region Order

private:
#ifdef MEDUSA_WINDOWS

#ifndef htonll
	static uint64_t htonll(uint64_t v);
#endif

#ifndef ntohll
	static uint64_t ntohll(uint64_t v);
#endif

#endif
public:
	static inline bool IsLittle()
	{
		const int32_t x = 1;
		return *(char*)&x == 1;
	}

	static inline int ToLittle(int val)
	{
		if (!IsLittle())
		{
			val = ((val & 0x000000FF) << 24) + ((val & 0x0000FF00) << 8) + ((val & 0x00FF0000) >> 8) + ((val & 0xFF000000) >> 24);
		}
		return val;
	}
	static inline uint32 ToLittle(uint32 val)
	{
		if (!IsLittle())
		{
			val = ((val & 0x000000FF) << 24) + ((val & 0x0000FF00) << 8) + ((val & 0x00FF0000) >> 8) + ((val & 0xFF000000) >> 24);
		}
		return val;
	}


	static inline int64 ToLittle(int64 val)
	{
		if (!IsLittle())
		{
			byte* bytes = (byte*)&val;
			byte temp = bytes[0]; bytes[0] = bytes[7]; bytes[7] = temp;
			temp = bytes[1]; bytes[1] = bytes[6]; bytes[6] = temp;
			temp = bytes[2]; bytes[2] = bytes[5]; bytes[5] = temp;
			temp = bytes[3]; bytes[3] = bytes[4]; bytes[4] = temp;
			return val;
		}
		return val;
	}

	static inline uint64 ToLittle(uint64 val)
	{
		if (!IsLittle())
		{
			byte* bytes = (byte*)&val;
			byte temp = bytes[0]; bytes[0] = bytes[7]; bytes[7] = temp;
			temp = bytes[1]; bytes[1] = bytes[6]; bytes[6] = temp;
			temp = bytes[2]; bytes[2] = bytes[5]; bytes[5] = temp;
			temp = bytes[3]; bytes[3] = bytes[4]; bytes[4] = temp;
			return val;
		}
		return val;
	}
#ifdef MEDUSA_WINDOWS
	static inline uint64_t HostToNetwork(uint64_t host64)
	{
		return htonll(host64);
	}

	static uint32_t HostToNetwork(uint32_t host32);

	static uint16_t HostToNetwork(uint16_t host16);

	static inline uint64_t NetworkToHost(uint64_t net64)
	{
		return ntohll(net64);
	}

	static uint32_t NetworkToHost(uint32_t net32);

	static uint16_t NetworkToHost(uint16_t net16);
#else


	// the inline assembler code makes type blur,
	// so we disable warnings for a while.
#if defined(__clang__) || __GNUC_MINOR__ >= 6
#pragma GCC diagnostic push
#endif
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wold-style-cast"


	static inline uint64_t HostToNetwork(uint64_t host64)
	{
		return htobe64(host64);
	}

	static inline uint32_t HostToNetwork(uint32_t host32)
	{
		return htobe32(host32);
	}

	static inline uint16_t HostToNetwork(uint16_t host16)
	{
		return htobe16(host16);
	}

	static inline uint64_t NetworkToHost(uint64_t net64)
	{
		return be64toh(net64);
	}

	static inline uint32_t NetworkToHost(uint32_t net32)
	{
		return be32toh(net32);
	}

	static inline uint16_t NetworkToHost(uint16_t net16)
	{
		return be16toh(net16);
	}


#if defined(__clang__) || __GNUC_MINOR__ >= 6
#pragma GCC diagnostic pop
#else
#pragma GCC diagnostic warning "-Wconversion"
#pragma GCC diagnostic warning "-Wold-style-cast"
#endif

#endif

	static inline int64_t HostToNetwork(int64_t host64)
	{
		return (int64_t)HostToNetwork((uint64_t)host64);
	}

	static inline int32_t HostToNetwork(int32_t host32)
	{
		return (int32_t)HostToNetwork((uint32_t)host32);
	}

	static inline int16_t HostToNetwork(int16_t host16)
	{
		return (int16_t)HostToNetwork((uint16_t)host16);
	}

	static inline int64_t NetworkToHost(int64_t net64)
	{
		return (int64_t)NetworkToHost((uint64_t)net64);
	}

	static inline int32_t NetworkToHost(int32_t net32)
	{
		return (int32_t)NetworkToHost((uint32_t)net32);
	}

	static inline int16_t NetworkToHost(int16_t net16)
	{
		return (int16_t)NetworkToHost((uint16_t)net16);
	}
#pragma endregion Order

};

MEDUSA_END;
