// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Memory/MemoryData.h"
#include "Core/Collection/List.h"
#include "Core/Coder/ICoder.h"
MEDUSA_BEGIN;

class Aes256Decoder :public ICoder
{
public:
	Aes256Decoder(const IEventArg& e);
	Aes256Decoder(const MemoryByteData& key);

public:
	using ICoder::Code;
	virtual CoderType Type()const override { return CoderType::Decoder_Aes256; }
	virtual size_t GuessResultSize(const IStream& input)const override;
	virtual CoderFlags Flags()const override { return CoderFlags::Block; }
	virtual bool Validate()const override { return mKey.IsValid(); }
protected:
	virtual size_t OnCode(const MemoryByteData& input, MemoryByteData& output)const override;
private:
	static void Decrypt(MemoryByteData& rkey, const MemoryByteData& key, const MemoryByteData& salt, unsigned char *buffer);

	static void expand_dec_key(byte* rkey, unsigned char *rc);

	static void sub_bytes_inv(unsigned char *buffer);
	static void shift_rows_inv(unsigned char *buffer);
	static void mix_columns_inv(unsigned char *buffer);
private:
	const static byte sboxinv[256];
private:
	MemoryByteData mKey;
};

MEDUSA_END;