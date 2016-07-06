// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"

#ifdef MEDUSA_LZMA
#include "Core/Coder/ICoder.h"

MEDUSA_BEGIN;

class LZMADecoder:public ICoder
{
public:
	LZMADecoder() = default;
	LZMADecoder(const IEventArg& e);
	~LZMADecoder();
	using ICoder::Code;
	virtual CoderType Type()const override { return CoderType::Decoder_LZMA; }
	virtual CoderFlags Flags()const override { return CoderFlags::Block; }

	virtual size_t GuessResultSize(const IStream& input)const override;
protected:
	virtual size_t OnCode(const MemoryData& input, MemoryData& output)const override;
private:
};

MEDUSA_END;
#endif
