// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Base64Encoder.h"
#include "Core/String/HeapString.h"
#include "Core/Memory/MemoryData.h"
#include "Core/IO/Stream/MemoryStream.h"

MEDUSA_BEGIN;

/* 'Private' declarations */
inline void a3_to_a4(unsigned char * a4, unsigned char * a3)
{
	a4[0] = (a3[0] & 0xfc) >> 2;
	a4[1] = ((a3[0] & 0x03) << 4) + ((a3[1] & 0xf0) >> 4);
	a4[2] = ((a3[1] & 0x0f) << 2) + ((a3[2] & 0xc0) >> 6);
	a4[3] = (a3[2] & 0x3f);
}

const char Base64Encoder::mChars[64] =
{
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', //00..12
	'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', //13..25
	'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', //26..38
	'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', //39..51
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'
};

Base64Encoder::Base64Encoder(const IEventArg& e)
{
	UN_USED(e);
}
size_t Base64Encoder::GuessResultSize(const IStream& input) const
{
	size_t length = input.LeftLength();
	return (length + 2 - ((length + 2) % 3)) / 3 * 4;
}

size_t Base64Encoder::OnCode(const MemoryByteData& input, MemoryByteData& output) const
{
	RETURN_ZERO_IF_EMPTY(input);

	char* result = (char*)output.MutableData();

	intp inputLen = input.Size();
	const byte* data = input.Data();

	int i = 0, j = 0;
	unsigned char a3[3];
	unsigned char a4[4];

	while (inputLen--)
	{
		a3[i++] = *(data++);
		if (i == 3)
		{
			a3_to_a4(a4, a3);

			for (i = 0; i < 4; i++)
			{
				*result++ = mChars[a4[i]];
			}

			i = 0;
		}
	}

	if (i)
	{
		for (j = i; j < 3; j++)
		{
			a3[j] = '\0';
		}

		a3_to_a4(a4, a3);

		for (j = 0; j < i + 1; j++)
		{
			*result++ = mChars[a4[j]];
		}

		while ((i++ < 3))
		{
			*result++ = '=';
		}
	}

	return output.Size();
}

MEDUSA_END;

