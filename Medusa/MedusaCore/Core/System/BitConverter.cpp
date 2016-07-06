// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "BitConverter.h"
#include "Core/Math/Math.h"
#include "Core/Memory/Memory.h"

#ifdef MEDUSA_WINDOWS
#include <WinSock2.h>
#endif

MEDUSA_BEGIN;

#pragma region Convert

int BitConverter::ToInt(const byte* data, size_t size /*= sizeof(int)*/)
{
	//size maybe <= sizeof(int)
	int result = 0;
	if (BitConverter::IsLittle())
	{
		for (size_t n = size - 1; n >= 0; n--)
			result = (result << 8) + data[n];
	}
	else
	{
		for (size_t n = 0; n < size; n++)
			result = (result << 8) + data[n];
	}

	return result;
}

double BitConverter::ToDouble(const byte* data)
{
	if (BitConverter::IsLittle())
	{
		return *reinterpret_cast<const double*>(data);
	}
	else
	{
		double temp;
		temp= *reinterpret_cast<const double*>(data);
		SwapBytes((byte*)&temp, sizeof(double));
		return temp;
	}
}

float BitConverter::ToFloat(const byte* data)
{
	if (BitConverter::IsLittle())
	{
		return *reinterpret_cast<const float*>(data);
	}
	else
	{

		float temp;
		temp = *reinterpret_cast<const float*>(data);
		SwapBytes((byte*)&temp, sizeof(float));
		return temp;
	}
}

void BitConverter::GetBytes(int val, byte* outData)
{
	*(int*)outData = val;
}

#pragma endregion Convert
#pragma region Math


/*
	volatile float x=1.f;
	volatile float y=0.f;
	x=x/y;

	EM_ZERODIVIDE: /0.f error
	EM_OVERFLOW: overflow error
	EM_INVALID: exception
	*/
void BitConverter::EnableFloatPointException(bool isEnable)
{
#ifdef MEDUSA_WINDOWS
	uint32 currentState;
	uint32 newState;
	//get current state
	_controlfp_s(&currentState, 0, 0);
	newState = currentState;
	if (isEnable)
	{
		newState &= ~(EM_ZERODIVIDE | EM_OVERFLOW | EM_INVALID);
	}
	else
	{
		newState |= (EM_ZERODIVIDE | EM_OVERFLOW | EM_INVALID);
	}

	_controlfp_s(&currentState, newState, MCW_EM);
#else

#endif
}

uint32 BitConverter::SwapUInt(uint32 val)
{
	return ((val & 0x000000FF) << 24) + ((val & 0x0000FF00) << 8) + ((val & 0x00FF0000) >> 8) + ((val & 0xFF000000) >> 24);
}

uint64 BitConverter::SwapUInt64(uint64 val)
{
	unsigned char* bytes = (unsigned char*)&val;

	Math::Swap(bytes[0], bytes[7]);
	Math::Swap(bytes[1], bytes[6]);
	Math::Swap(bytes[2], bytes[5]);
	Math::Swap(bytes[3], bytes[4]);
	return val;
}

void BitConverter::SwapBytes(unsigned char* data, size_t size)
{
	size_t i = 0, j = size - 1;
	while (i < j)
	{
		Math::Swap(data[i++], data[j--]);
	}
}

bool BitConverter::HasBit(size_t val, byte index)
{
	return (val&((intp)1 << index)) != 0;
}

int BitConverter::FromHexChar(char c)
{
	if (c >= 'a' && c <= 'f')
		return c - 'a' + 10;
	else if (c >= 'A' && c <= 'F')
		return c - 'A' + 10;
	else
		return c - '0';
}

#ifndef ntohll
uint64_t BitConverter::ntohll(uint64_t v)
{
	union { uint32_t lv[2]; uint64_t llv; } u;
	u.llv = v;
	return ((uint64_t)ntohl(u.lv[0]) << 32) | (uint64_t)ntohl(u.lv[1]);
}


#endif

#ifndef htonll
uint64_t BitConverter::htonll(uint64_t v)
{
	union { uint32_t lv[2]; uint64_t llv; } u;
	u.lv[0] = htonl(v >> 32);
	u.lv[1] = htonl(v & 0xFFFFFFFFULL);
	return u.llv;
}
#endif

uint16_t BitConverter::NetworkToHost(uint16_t net16)
{
	return ntohs(net16);
}

uint32_t BitConverter::NetworkToHost(uint32_t net32)
{
	return ntohl(net32);
}

uint16_t BitConverter::HostToNetwork(uint16_t host16)
{
	return htons(host16);
}

uint32_t BitConverter::HostToNetwork(uint32_t host32)
{
	return htonl(host32);
}


char BitConverter::ToHexChar(int val)
{
	const static char hexChars[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };
	return hexChars[val & 0xf];
}

/*

					 int16, int32,          zig zag encoded to unsigned integer:
					 int64
											 0 -> 0
											-1 -> 1
											 1 -> 2
											-2 -> 3
											...

											and then encoded as unsigned integer

variable uint32
.---.---.   .---..---.---.   .---..---.---.   .---..---.---.   .---..---.---.---.---.   .---.
| 1 | v |...| v || 1 | v |...| v || 1 | v |...| v || 1 | v |...| v || 0 | 0 | 0 | v |...| v |
'---'---'   '---''---'---'   '---''---'---'   '---''---'---'   '---''---'---'---'---'   '---'
	  6       0        13      7        20      14       27      21               31      28

1 to 5 bytes, high bit of every byte indicates if there is another byte
*/


#pragma endregion Math



MEDUSA_END;