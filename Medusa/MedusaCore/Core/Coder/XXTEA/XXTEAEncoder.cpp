// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Core/Coder/XXTEA/XXTEAEncoder.h"
#include "Core/Command/EventArg/UserDataEventArg.h"
#include "Core/IO/Stream/MemoryStream.h"

MEDUSA_BEGIN;

XXTEAEncoder::XXTEAEncoder(const IEventArg& e)
{
	const UserDataEventArg<MemoryByteData>& e2 = (const UserDataEventArg<MemoryByteData>&)e;
	mKey = ToUIntArray(e2.Data(), false);
}

XXTEAEncoder::XXTEAEncoder(const MemoryByteData& key)
{
	mKey=ToUIntArray(key, false);
}

XXTEAEncoder::~XXTEAEncoder()
{
}


void XXTEAEncoder::EncryptHelper( MemoryUIntData& v)const
{
	RETURN_IF_FALSE(v.IsValid());
	uint32 n =static_cast<uint32>(v.Size()) - 1;
	if (n < 1|| mKey.Size() < 4)
	{
		return;
	}
	uint32 z = v[n];	//byte length

	uint32 sum = 0;
	uint32 q = 6 + 52 / (n + 1);
	while (q-- > 0)
	{
		sum+=mDelta;
		uint32 e = sum >> 2 & 3;
		uint32 y;
		uint32 p;
		for (p = 0; p < n; p++)
		{
			y = v[p + 1];
			z = v[p] += (z >> 5 ^ y << 2) + (y >> 3 ^ z << 4) ^ (sum ^ y) + (mKey[p & 3 ^ e] ^ z);
		}
		y = v[0];
		z = v[n] += (z >> 5 ^ y << 2) + (y >> 3 ^ z << 4) ^ (sum ^ y) + (mKey[p & 3 ^ e] ^ z);
	}
	return ;
}


MemoryUIntData XXTEAEncoder::ToUIntArray( const MemoryByteData& data, bool includeLength )
{
	size_t n = (((data.Size() & 3) == 0) ? (data.Size() >> 2) : ((data.Size() >> 2) + 1));
	MemoryUIntData result;

	if (includeLength)
	{
		result=MemoryUIntData::Alloc(n+1);
		result[n] = static_cast<uint32>(data.Size());
	}
	else
	{
		result=MemoryUIntData::Alloc(n);
	}

	n=data.Size();
	for (size_t i = 0; i < n; i++)
	{
		result[i /4] |= (size_t)data[i] << ((i %4) * 8);
	}
	return result;
}


size_t XXTEAEncoder::GuessResultSize(const IStream& input) const
{
	size_t size = input.LeftLength();
	size_t n = (((size & 3) == 0) ? (size >> 2) : ((size >> 2) + 1));
	return n * 4;	//align to int size
}

size_t XXTEAEncoder::OnCode(const MemoryByteData& input, MemoryByteData& output) const
{
	bool alignInt = input.Size() % 4 == 0;
	if (alignInt)
	{
		if (output.IsDataEqual(input))
		{
			MemoryUIntData dataBuffer = input.Cast<uint>();
			EncryptHelper(dataBuffer);
		}
		else
		{
			output.Copy(input);
			MemoryUIntData dataBuffer = output.Cast<uint>();
			EncryptHelper(dataBuffer);
		}
	}
	else
	{
		MemoryUIntData dataBuffer = ToUIntArray(input, alignInt);
		EncryptHelper(dataBuffer);

		byte* result = output.MutableData();
		for (size_t i = 0; i < input.Size(); i++)
		{
			result[i] = (byte)(dataBuffer[i >> 2] >> ((i & 3) << 3));
		}
	}
	return input.Size();

}

MEDUSA_END;

