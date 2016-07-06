// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Core/Coder/XXTEA/XXTEADecoder.h"
#include "Core/Event/EventArg/UserDataEventArg.h"
#include "Core/IO/Stream/MemoryStream.h"
#include "XXTEAEncoder.h"

MEDUSA_BEGIN;

XXTEADecoder::XXTEADecoder(const IEventArg& e)
{
	const UserDataEventArg<MemoryData>& e2 = (const UserDataEventArg<MemoryData>&)e;
	mKey = XXTEAEncoder::ToUIntArray(e2.Data(), false);
}

XXTEADecoder::XXTEADecoder(const MemoryData& key)
{
	mKey= XXTEAEncoder::ToUIntArray(key, false);
}

XXTEADecoder::~XXTEADecoder()
{
}


void XXTEADecoder::DecryptHelper( MemoryUIntData& v)const
{
	RETURN_IF_FALSE(v.IsValid());

	uint32 n =static_cast<uint32>( v.Size()) - 1;
	if (n < 1||mKey.Size() < 4)
	{
		return;
	}
	uint32 y = v[0];

	uint32 q = 6 + 52 / (n + 1);
	uint32 sum = (uint32)(q * mDelta);
	while (sum != 0)
	{
		uint32 e = sum >> 2 & 3;
		uint32 z;
		uint32 p;
		for (p = n; p > 0; p--)
		{
			z = v[p - 1];
			y = v[p] -= (z >> 5 ^ y << 2) + (y >> 3 ^ z << 4) ^ (sum ^ y) + (mKey[p & 3 ^ e] ^ z);
		}
		z = v[n];
		y = v[0] -= (z >> 5 ^ y << 2) + (y >> 3 ^ z << 4) ^ (sum ^ y) + (mKey[p & 3 ^ e] ^ z);
		sum -= mDelta;
	}
	return;
}


size_t XXTEADecoder::GuessResultSize(const IStream& input) const
{
	size_t size = input.LeftLength();
	size_t n = (((size & 3) == 0) ? (size >> 2) : ((size >> 2) + 1));
	return n * 4;	//align to int size
}

size_t XXTEADecoder::OnCode(const MemoryData& input, MemoryData& output) const
{
	bool alignInt = input.Size() % 4 == 0;
	if (alignInt)
	{
		if (output.IsDataEqual(input))
		{
			MemoryUIntData dataBuffer = input.Cast<uint>();
			DecryptHelper(dataBuffer);
		}
		else
		{
			output.Copy(input);
			MemoryUIntData dataBuffer = output.Cast<uint>();
			DecryptHelper(dataBuffer);
		}
	}
	else
	{
		MemoryUIntData dataBuffer = XXTEAEncoder::ToUIntArray(input, alignInt);
		DecryptHelper(dataBuffer);

		byte* result = output.MutableData();
		for (size_t i = 0; i < input.Size(); i++)
		{
			result[i] = (byte)(dataBuffer[i >> 2] >> ((i & 3) << 3));
		}
	}
	return input.Size();
}


MEDUSA_END;
