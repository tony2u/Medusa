// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Coder/ICoder.h"

MEDUSA_BEGIN;

class XOREncoder:public ICoder
{
public:
	XOREncoder() = default;
	XOREncoder(const IEventArg& e);
	XOREncoder(const MemoryData& e);

	~XOREncoder();
	void SetKey(const MemoryData& e){mKey=e;}
	virtual CoderFlags Flags()const override { return CoderFlags::InPlace; }
	using ICoder::Code;
	virtual CoderType Type()const override { return CoderType::Encoder_XOR; }
	virtual size_t GuessResultSize(const IStream& input)const override;
protected:
	virtual size_t OnCode(const MemoryData& input, MemoryData& output)const override;

private:
	MemoryData mKey;
};

MEDUSA_END;