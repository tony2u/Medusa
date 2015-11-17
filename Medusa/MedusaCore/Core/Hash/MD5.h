// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/String/StringRef.h"
#include "Core/String/HeapString.h"
#include "IHasher.h"

MEDUSA_BEGIN;

class MD5 :public IHasher
{
public:
	MD5();
	MD5(const void* input, size_t length);
	MD5(const StringRef& str);

	constexpr static size_t  DigestSize = 16;
	constexpr static size_t  DigestAsIntSize = 4;
	constexpr static size_t  DigestAsInt64Size = 2;

	MD5(const MD5&) = delete;
	MD5& operator=(const MD5&) = delete;
	virtual HasherType Type()const override { return HasherType::MD5; }
public:
	const byte* Digest()const;
	const int* DigestAsInt()const;
	const int64* DigestAsInt64()const;
	const int128* DigestAsInt128()const;

	virtual void Process(const byte* input, size_t length)override;
	virtual void Final()override;
	virtual void Reset()override;
	virtual HeapString ToString()const override;

private:
	void UpdateHelper(const byte* input, size_t length);

	void Transform(const byte block[64]);
	void Encode(const uint32* input, byte* output, size_t length);
	void Decode(const byte* input, uint32* output, size_t length);

private:
	uint32 _state[4];	/* state (ABCD) */
	uint32 _count[2];	/* number of bits, modulo 2^64 (low-order word first) */
	byte _buffer[64];	/* input buffer */
	byte _digest[16];	/* message Digest */

	static const byte PADDING[64];	/* padding for calculate */
	static const char HEX[16];
	static const int mBufferSize = 1024;
};


MEDUSA_END;