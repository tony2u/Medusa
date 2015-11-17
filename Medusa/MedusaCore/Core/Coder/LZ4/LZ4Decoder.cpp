// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Core/Coder/LZ4/LZ4Decoder.h"
#include "Core/Coder/CoderFactory.h"
#include "CoreLib/Common/lz4/lz4.h"
#include "Core/IO/Stream/IStream.h"


MEDUSA_BEGIN;

LZ4Decoder::LZ4Decoder(const IEventArg& e):ICoder(e)
{
}

LZ4Decoder::~LZ4Decoder()
{

}

size_t LZ4Decoder::GuessResultSize(const IStream& input) const
{
	uintp pos = input.Position();
	uint size= input.Read<uint>();
	input.SetPosition(pos);
	return size;
}

size_t LZ4Decoder::OnCode(const MemoryByteData& input, MemoryByteData& output) const
{
	int size = LZ4_decompress_safe((const char*)input.Data()+sizeof(uint), (char*)output.MutableData(), (int)input.Size()- sizeof(uint), (int)output.Size());
	if (size>0)
	{
		output.ForceSetSize(size);
		return size;
	}
	else
	{
		return 0;
	}
	
}

MEDUSA_END;
