// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Base64Decoder.h"
#include "Core/String/HeapString.h"
#include "Core/Memory/MemoryData.h"
#include "Core/IO/Stream/MemoryStream.h"

MEDUSA_BEGIN;

/* 'Private' declarations */

inline void a4_to_a3(unsigned char * a3, unsigned char * a4)
{
	a3[0] = (a4[0] << 2) + ((a4[1] & 0x30) >> 4);
	a3[1] = ((a4[1] & 0xf) << 4) + ((a4[2] & 0x3c) >> 2);
	a3[2] = ((a4[2] & 0x3) << 6) + a4[3];
}

inline unsigned char b64_lookup(char c)
{
	if (c >= 'A' && c <= 'Z') return c - 'A';
	if (c >= 'a' && c <= 'z') return c - 71;
	if (c >= '0' && c <= '9') return c + 4;
	if (c == '+') return 62;
	if (c == '/') return 63;
	return (byte)-1;
}
Base64Decoder::Base64Decoder(const IEventArg& e)
{
	UN_USED(e);
}
size_t Base64Decoder::GuessResultSize(const IStream& input) const
{
	//more exactly calculate result size
	uintp pos= input.Position();
	intp inputLen = input.LeftLength();
	intp numEq = 0;
	char c = '\0';
	do 
	{
		--numEq;
		input.Seek(numEq, SeekOrigin::End);
		c= (char)input.ReadChar();
	} while (c=='=');

	numEq = -numEq-1;	//-1 to erase first loop
	input.SetPosition(pos);

	return ((6 * inputLen) / 8) - numEq;
}

size_t Base64Decoder::OnCode(const MemoryData& input, MemoryData& output) const
{
	RETURN_ZERO_IF_EMPTY(input);
	char* originResult = (char*)output.MutableData();
	char* result = (char*)output.MutableData();

	int i = 0, j = 0;
	unsigned char a3[3];
	unsigned char a4[4];
	intp inputLen = input.Size();
	const char* data = (const char*)input.Data();

	while (inputLen--)
	{
		if (*data == '=')
		{
			break;
		}

		a4[i++] = *(data++);
		if (i == 4)
		{
			for (i = 0; i < 4; i++)
			{
				a4[i] = b64_lookup(a4[i]);
			}

			a4_to_a3(a3, a4);

			for (i = 0; i < 3; i++)
			{
				*result++ = a3[i];
			}
			i = 0;
		}
	}

	if (i)
	{
		for (j = i; j < 4; j++)
		{
			a4[j] = '\0';
		}

		for (j = 0; j < 4; j++)
		{
			a4[j] = b64_lookup(a4[j]);
		}

		a4_to_a3(a3, a4);

		for (j = 0; j < i - 1; j++)
		{
			*result++ = a3[j];
		}
	}

	return result - originResult;
}

MEDUSA_END;