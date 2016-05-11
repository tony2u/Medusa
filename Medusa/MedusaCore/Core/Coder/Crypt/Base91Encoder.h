// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Coder/ICoder.h"
MEDUSA_BEGIN;

/*                                                                      
http://base91.sourceforge.net/
https://github.com/r-lyeh/base91

Base91 is a lightweight binary-to-text data de/encoder (C++03).
Base91 is 19% to 10% smaller than Base64; additional Base64 de/encoder is also provided.
Base91 is JSON, XML and TSV friendly. Encoded data can be "quoted", splitted with tabs, spaces, linefeeds and carriages.
*/
class Base91Encoder:public ICoder
{
public:
	Base91Encoder() = default;
	Base91Encoder(const IEventArg& e);
	~Base91Encoder(){}
	using ICoder::Code;
	virtual CoderType Type()const override { return CoderType::Encoder_Base91; }
	virtual size_t GuessResultSize(const IStream& input)const override;
	virtual CoderFlags Flags()const override { return CoderFlags::Block; }

protected:
	virtual size_t OnCode(const MemoryData& input, MemoryData& output)const override;
private:
	const static char mEncodeChars[91];


};


MEDUSA_END;