// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Memory/MemoryData.h"
#include "Core/Collection/List.h"
#include "Core/Coder/ICoder.h"
MEDUSA_BEGIN;

class Aes256Encoder:public ICoder
{
	friend class Aes256Decoder;
public:
	using ICoder::Code;
	Aes256Encoder(const IEventArg& e);
	Aes256Encoder(const MemoryByteData& key,Random* random=nullptr);
public:
	virtual CoderType Type()const override { return CoderType::Encoder_Aes256; }
	virtual size_t GuessResultSize(const IStream& input)const override;
	virtual CoderFlags Flags()const override { return CoderFlags::Block; }
	virtual bool Validate()const override { return mKey.IsValid(); }
protected:
	virtual size_t OnCode(const MemoryByteData& input, MemoryByteData& output)const override;
private:
	static void Encrypt(MemoryByteData& rkey, const MemoryByteData& key,const MemoryByteData& salt,unsigned char *buffer);
	static void copy_key(MemoryByteData& rkey, const MemoryByteData& key, const MemoryByteData& salt);

	static void expand_enc_key(byte* rkey,unsigned char *rc);
	static void sub_bytes(unsigned char *buffer);
	static void add_round_key(const byte* rkey,unsigned char *buffer, const unsigned char round);
	static void shift_rows(unsigned char *buffer);
	static void mix_columns(unsigned char *buffer);
public:
	constexpr static uint KeyMaxSize = 32;
private:
	constexpr static uint BlockSize = 16;
	constexpr static uint RoundCount = 14;
	const static byte sbox[256];
private:
	Random* mRandom;
	MemoryByteData mKey;
};

MEDUSA_END;