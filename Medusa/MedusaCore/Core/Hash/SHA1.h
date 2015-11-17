// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/String/StringRef.h"
#include "Core/String/HeapString.h"
#include "IHasher.h"

MEDUSA_BEGIN;

class SHA1:public IHasher
{
public:
	SHA1();
	SHA1(const void* input, size_t length);
	SHA1(const StringRef& str);

	SHA1(const SHA1&) = delete;
	SHA1& operator=(const SHA1&) = delete;

	const static  size_t BLOCK_INTS = 16;  /* number of 32bit integers per SHA1 block */
	const static  size_t BLOCK_BYTES = BLOCK_INTS * 4;
public:
	virtual HasherType Type()const override { return HasherType::SHA1; }
	const byte* Digest()const { return (const byte*)digest; }

	virtual void Process(const byte* input, size_t length)override;
	virtual void Final()override;
	virtual void Reset()override;
	virtual  HeapString ToString()const override;

private:

	void UpdateHelper(const byte* input, size_t length);

	void Final(uint64_t transforms, const byte* leftInput, size_t leftLength);
private:
	uint32_t digest[5];

	uint32 mBlockBufferLength=0;
	byte mBlockBuffer[BLOCK_BYTES];
	uint64_t mTransforms=0;
};


MEDUSA_END;