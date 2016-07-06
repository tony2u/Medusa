// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Core/Coder/XOR/XOREncoder.h"
#include "Core/Event/EventArg/UserDataEventArg.h"
#include "Core/Coder/CoderFactory.h"
#include "Core/IO/Stream/MemoryStream.h"
#include "Core/Log/Log.h"

MEDUSA_BEGIN;

XOREncoder::XOREncoder(const IEventArg& e) :ICoder(e)
{
	const UserDataEventArg<MemoryData>& e2 = (const UserDataEventArg<MemoryData>&)e;
	mKey = e2.Data();
}

XOREncoder::XOREncoder(const MemoryData& e)
{
	mKey = e;
}

XOREncoder::~XOREncoder()
{

}

size_t XOREncoder::GuessResultSize(const IStream& input) const
{
	return input.LeftLength();
}

size_t XOREncoder::OnCode(const MemoryData& input, MemoryData& output) const
{
	RETURN_ZERO_IF_EMPTY(input);
	if (output.Size() < input.Size())
	{
		Log::AssertFailedFormat("output size:{} < expected size{}", output.Size(), input.Size());
		return 0;
	}


	const byte* data = input.Data();
	byte* result = output.MutableData();

	size_t keyIndex = 0;
	size_t srcSize = input.Size();
	size_t keySize = mKey.Size();

	if (keySize != srcSize)
	{
		for (size_t i = 0; i < srcSize; ++i)
		{
			result[i] = data[i] ^ mKey[keyIndex];
			if (keyIndex < keySize - 1)
			{
				++keyIndex;
			}
			else
			{
				keyIndex = 0;
			}
		}
	}
	else
	{
		for (size_t i = 0; i < srcSize; ++i)
		{
			result[i] = (char)(data[i] ^ mKey[i]);
		}
	}

	return srcSize;
}




MEDUSA_END;