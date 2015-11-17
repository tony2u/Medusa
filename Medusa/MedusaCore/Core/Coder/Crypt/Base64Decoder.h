// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Coder/ICoder.h"

MEDUSA_BEGIN;

class Base64Decoder :public ICoder
{
public:
	Base64Decoder() = default;
	Base64Decoder(const IEventArg& e);
	~Base64Decoder() {}
	using ICoder::Code;
	virtual CoderType Type()const override { return CoderType::Decoder_Base64; }
	virtual size_t GuessResultSize(const IStream& input)const override;
	virtual CoderFlags Flags()const override { return CoderFlags::Block; }
protected:
	virtual size_t OnCode(const MemoryByteData& input, MemoryByteData& output)const override;
};


MEDUSA_END;