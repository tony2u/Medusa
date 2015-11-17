// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Base91Encoder.h"
#include "Core/String/HeapString.h"
#include "Core/IO/Stream/MemoryStream.h"

MEDUSA_BEGIN;

const char Base91Encoder::mEncodeChars[91] =
{
	/* // Henke's original
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', //00..12
	'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', //13..25
	'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', //26..38
	'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', //39..51
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '!', '#', '$', //52..64
	'%', '&', '(', ')', '*', '+', ',', '.', '/', ':', ';', '<', '=', //65..77
	'>', '?', '@', '[', ']', '^', '_', '`', '{', '|', '}', '~', '"'  //78..90 */
	// // rlyeh's modification
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', //00..12
	'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', //13..25
	'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', //26..38
	'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', //39..51
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '!', '#', '$', //52..64
	'%', '&', '(', ')', '*', '+', ',', '.', '/', ':', ';', '-', '=', //65..77
	'\\', '?', '@', '[', ']', '^', '_', '`', '{', '|', '}', '~', '\'' //78..90
};

Base91Encoder::Base91Encoder(const IEventArg& e)
{
	UN_USED(e);
}



size_t Base91Encoder::GuessResultSize(const IStream& input) const
{
	return input.LeftLength() * 4;	//make sure has enough space to store
}

size_t Base91Encoder::OnCode(const MemoryByteData& input, MemoryByteData& output) const
{
	RETURN_ZERO_IF_EMPTY(input);

	const unsigned char *ib = (unsigned char *)input.Data();
	byte* result = output.MutableData();
	byte* originalResult = result;

	unsigned long queue = 0;
	unsigned int nbits = 0;

	for (size_t len = input.Size(); len--;)
	{
		queue |= *ib++ << nbits;
		nbits += 8;
		if (nbits > 13)
		{   /* enough bits in queue */
			unsigned int val = queue & 8191;

			if (val > 88)
			{
				queue >>= 13;
				nbits -= 13;
			}
			else
			{    /* we can take 14 bits */
				val = queue & 16383;
				queue >>= 14;
				nbits -= 14;
			}
			*result++ = mEncodeChars[val % 91];
			*result++ = mEncodeChars[val / 91];
		}
	}

	/* process remaining bits from bit queue; write up to 2 bytes */
	if (nbits)
	{
		*result++ = mEncodeChars[queue % 91];
		if (nbits > 7 || queue > 90)
			*result++ = mEncodeChars[queue / 91];
	}
	return result - originalResult;
}


MEDUSA_END;

