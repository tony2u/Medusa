// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/String/StringRef.h"
#include "Core/Pattern/Singleton.h"
#include "IHasher.h"
#include "Core/Pattern/StaticConstructor.h"

MEDUSA_BEGIN;

class CRC32C:public IHasher
{
	MEDUSA_DECLARE_STATIC_CONSTRUCTOR();

	friend class Singleton<CRC32C>;
	typedef uint32 CalculateImpl(uint initialCRC, const void* input, size_t length, uint32(*crcTable)[256]);
public:
	CRC32C();
public:
	virtual HasherType Type()const override { return HasherType::CRC32C; }

	virtual void Process(const byte* input, size_t length)override;
	virtual void Final()override{}
	virtual void Reset()override { mCRC = 0; }
	virtual HeapString ToString()const override;
private:
	uint32 Calculate(uint initialCRC, const void* input, size_t length);

	static void InitCRCTable();
	static uint32 CalculateSoftware(uint initialCRC, const void* input, size_t length, uint32(*crcTable)[256]);
	static uint32 CalculateHardware(uint initialCRC, const void* input, size_t length, uint32(*crcTable)[256]);
private:
	static uint32(*mCRCTable)[256];
	static CalculateImpl* mImpl;
	uint mCRC=0;
};


MEDUSA_END;