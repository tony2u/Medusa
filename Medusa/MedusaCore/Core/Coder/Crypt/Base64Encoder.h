// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Coder/ICoder.h"

MEDUSA_BEGIN;

class Base64Encoder :public ICoder
{
public:
	Base64Encoder() = default;
	Base64Encoder(const IEventArg& e);
	~Base64Encoder() {}
	using ICoder::Code;
	virtual CoderType Type()const override { return CoderType::Encoder_Base64; }
	virtual size_t GuessResultSize(const IStream& input)const override;
	virtual CoderFlags Flags()const override { return CoderFlags::Block; }
protected:
	virtual size_t OnCode(const MemoryData& input, MemoryData& output)const override;
private:
	const static char mChars[64];
};


MEDUSA_END;