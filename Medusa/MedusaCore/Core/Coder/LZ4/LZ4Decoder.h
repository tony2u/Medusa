// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#ifdef MEDUSA_LZ4
#include "Core/Coder/ICoder.h"

MEDUSA_BEGIN;

class LZ4Decoder:public ICoder
{
public:
	LZ4Decoder() = default;
	LZ4Decoder(const IEventArg& e);
	~LZ4Decoder();
	using ICoder::Code;
	virtual CoderType Type()const override { return CoderType::Decoder_LZ4; }
	virtual CoderFlags Flags()const override { return CoderFlags::Block; }
	virtual size_t GuessResultSize(const IStream& input)const override;
protected:
	virtual size_t OnCode(const MemoryData& input, MemoryData& output)const override;
};

MEDUSA_END;
#endif