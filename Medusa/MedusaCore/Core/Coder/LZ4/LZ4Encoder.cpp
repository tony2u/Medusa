// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Core/Coder/LZ4/LZ4Encoder.h"
#include "Core/Coder/CoderFactory.h"
#include "CoreLib/Common/lz4/lz4.h"
#include "Core/IO/Stream/IStream.h"
#include "Core/IO/Stream/MemoryStream.h"


MEDUSA_BEGIN;

LZ4Encoder::LZ4Encoder(const IEventArg& e) :ICoder(e)
{
}

LZ4Encoder::~LZ4Encoder()
{

}

size_t LZ4Encoder::GuessResultSize(const IStream& input) const
{
	size_t size = input.LeftLength();
	return (size_t)LZ4_compressBound((int)size) + sizeof(uint);	//to store length
}

size_t LZ4Encoder::OnCode(const MemoryByteData& input, MemoryByteData& output) const
{
	MemoryStream outputStream(output);
	outputStream.Write((uint)input.Size());
	int size = LZ4_compress_default((const char*)input.Data(), (char*)output.MutableData() + sizeof(uint), (int)input.Size(), (int)output.Size() - sizeof(uint));
	if (size>0)
	{
		size += sizeof(uint);
		output.ForceSetSize(size);
	}
	else
	{
		output.ForceSetSize(0);
	}
	return size;
}

MEDUSA_END;

