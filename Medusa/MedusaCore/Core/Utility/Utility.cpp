// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Core/Utility/Utility.h"
#include "Core/Math/Math.h"
#include "Endian.h"
#include "Core/Memory/Memory.h"

MEDUSA_BEGIN;



/*
	volatile float x=1.f;
	volatile float y=0.f;
	x=x/y;

	EM_ZERODIVIDE: /0.f error
	EM_OVERFLOW: overflow error
	EM_INVALID: exception
	*/
void Utility::EnableFloatPointException(bool isEnable)
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

uint32 Utility::SwapUInt(uint32 val)
{
	return ((val & 0x000000FF) << 24) + ((val & 0x0000FF00) << 8) + ((val & 0x00FF0000) >> 8) + ((val & 0xFF000000) >> 24);
}

uint64 Utility::SwapUInt64(uint64 val)
{
	unsigned char* bytes = (unsigned char*)&val;

	Math::Swap(bytes[0], bytes[7]);
	Math::Swap(bytes[1], bytes[6]);
	Math::Swap(bytes[2], bytes[5]);
	Math::Swap(bytes[3], bytes[4]);
	return val;
}

void Utility::SwapBytes(unsigned char* data, size_t size)
{
	size_t i = 0, j = size - 1;
	while (i < j)
	{
		Math::Swap(data[i++], data[j--]);
	}
}

int Utility::ToInt(const byte* data, size_t size /*= sizeof(int)*/)
{
	int result = 0;
	if (Endian::IsLittle())
	{
		for (int n = size - 1; n >= 0; n--)
			result = (result << 8) + data[n];
	}
	else
	{
		for (uint n = 0; n < size; n++)
			result = (result << 8) + data[n];
	}

	return result;
}

double Utility::ToDouble(const byte* data)
{
	double result;
	if (Endian::IsLittle())
	{
		Memory::SafeCopy((byte*)&result, sizeof(result), data, sizeof(result));
	}
	else
	{
		double temp;
		Memory::SafeCopy((byte*)&temp, sizeof(result), data, sizeof(result));
		SwapBytes((byte*)&temp, sizeof(result));
		Memory::SafeCopy((byte*)&result, sizeof(result), (const byte*)&temp, sizeof(result));
	}
	return result;
}

float Utility::ToFloat(const byte* data)
{
	float result;
	if (Endian::IsLittle())
	{
		Memory::SafeCopy((byte*)&result, sizeof(result), data, sizeof(result));
	}
	else
	{
		float temp;
		Memory::SafeCopy((byte*)&temp, sizeof(result), data, sizeof(result));
		SwapBytes((byte*)&temp, sizeof(result));
		Memory::SafeCopy((byte*)&result, sizeof(result), (const byte*)&temp, sizeof(result));
	}
	return result;
}

bool Utility::HasBit(size_t val, byte index)
{
	return (val&((intp)1 << index)) != 0;
}

int Utility::FromHexChar(char c)
{
	if (c >= 'a' && c <= 'f')
		return c - 'a' + 10;
	else if (c >= 'A' && c <= 'F')
		return c - 'A' + 10;
	else
		return c - '0';
}


char Utility::ToHexChar(int val)
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




MEDUSA_END;