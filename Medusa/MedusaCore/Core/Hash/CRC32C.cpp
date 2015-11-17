// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "CRC32C.h"

MEDUSA_BEGIN;

void cpuid(uint32_t op, uint32_t reg[4])
{
#if defined(__x86_64__)
	__asm__ volatile(
		"pushq %%rbx       \n\t"
		"cpuid             \n\t"
		"movl  %%ebx, %1   \n\t"
		"popq  %%rbx       \n\t"
		: "=a"(reg[0]), "=r"(reg[1]), "=c"(reg[2]), "=d"(reg[3])
		: "a"(op)
		: "cc");
#elif defined(_WIN64) || defined(_WIN32)
#include <intrin.h>
	__cpuid((int *)reg, 1);
#else
	__asm__ volatile(
		"pushl %%ebx       \n\t"
		"cpuid             \n\t"
		"movl  %%ebx, %1   \n\t"
		"popl  %%ebx       \n\t"
		: "=a"(reg[0]), "=r"(reg[1]), "=c"(reg[2]), "=d"(reg[3])
		: "a"(op)
		: "cc");
#endif
}

bool IsSSE42Available()
{
#ifdef MEDUSA_IOS
    return false;
#else
    
	uint32_t reg[4];

	cpuid(1, reg);
	return ((reg[2] >> 20) & 1) == 1;
#endif
}


void InitCrcTable(uint32_t(&crc32cTable)[8][256])
{
	// The CRC-32C polynomial in reversed bit order
	constexpr uint32 polynomial = 0x82f63b78;

	uint32_t i, j, crc;

	for (i = 0; i < 256; i++)
	{
		crc = i;
		crc = crc & 1 ? (crc >> 1) ^ polynomial : crc >> 1;
		crc = crc & 1 ? (crc >> 1) ^ polynomial : crc >> 1;
		crc = crc & 1 ? (crc >> 1) ^ polynomial : crc >> 1;
		crc = crc & 1 ? (crc >> 1) ^ polynomial : crc >> 1;
		crc = crc & 1 ? (crc >> 1) ^ polynomial : crc >> 1;
		crc = crc & 1 ? (crc >> 1) ^ polynomial : crc >> 1;
		crc = crc & 1 ? (crc >> 1) ^ polynomial : crc >> 1;
		crc = crc & 1 ? (crc >> 1) ^ polynomial : crc >> 1;
		crc32cTable[0][i] = crc;
	}

	for (i = 0; i < 256; i++)
	{
		crc = crc32cTable[0][i];
		for (j = 1; j < 8; j++)
		{
			crc = crc32cTable[0][crc & 0xff] ^ (crc >> 8);
			crc32cTable[j][i] = crc;
		}
	}
}


CRC32C::CRC32C()
{
	
}

uint32 CRC32C::Calculate(uint initialCRC, const void* input, size_t length)
{
	return mImpl(initialCRC, input, length, mCRCTable);
}


void CRC32C::Process(const byte* input, size_t length)
{
	mCRC = Calculate(mCRC, input, length);
}

HeapString CRC32C::ToString() const
{
	return StringParser::ToString(mCRC);
}

void CRC32C::InitCRCTable()
{
	const static bool isSSE42Available = IsSSE42Available();
	if (!isSSE42Available)
	{
		static uint32_t crc32cTable[8][256];// Stores the CRC-32 lookup table for the software-fallback implementation
		InitCrcTable(crc32cTable);
		mCRCTable = crc32cTable;
		mImpl = CalculateSoftware;
	}
	else
	{
		mCRCTable = nullptr;
		mImpl = CalculateHardware;
	}
}

uint32 CRC32C::CalculateSoftware(uint initialCRC, const void* input, size_t length, uint32(*crcTable)[256])
{
	const char *next = (const char*)input;
	uint64_t crc = initialCRC;


	// If the string is empty, return 0
	if (length == 0) return (uint32_t)crc;

	// XOR the initial CRC with INT_MAX
	crc ^= 0xFFFFFFFF;

	// Process byte-by-byte until aligned to 8-byte boundary
	while (length && ((uintptr_t)next & 7) != 0)
	{
		crc = crcTable[0][(crc ^ *next++) & 0xff] ^ (crc >> 8);
		length--;
	}

	// Process 8 bytes at a time
	while (length >= 8)
	{
		crc ^= *(uint64_t *)next;
		crc = crcTable[7][(crc >> 0) & 0xff] ^ crcTable[6][(crc >> 8) & 0xff]
			^ crcTable[5][(crc >> 16) & 0xff] ^ crcTable[4][(crc >> 24) & 0xff]
			^ crcTable[3][(crc >> 32) & 0xff] ^ crcTable[2][(crc >> 40) & 0xff]
			^ crcTable[1][(crc >> 48) & 0xff] ^ crcTable[0][(crc >> 56)];
		next += 8;
		length -= 8;
	}

	// Process any remaining bytes
	while (length)
	{
		crc = crcTable[0][(crc ^ *next++) & 0xff] ^ (crc >> 8);
		length--;
	}

	// XOR again with INT_MAX
	return (uint32_t)(crc ^= 0xFFFFFFFF);

}

// Performs H/W CRC operations
#define CALC_CRC(op, crc, type, buf, len) for (; (len) >= sizeof(type); (len) -= sizeof(type), buf += sizeof(type)) {(crc) = (uint32_t)op((crc), *(type *) (buf));}                                                                                                    


uint32 CRC32C::CalculateHardware(uint initialCRC, const void* input, size_t length, uint32(*crcTable)[256])
{
	UN_USED(crcTable);
#ifndef MEDUSA_IOS
	// Byte-boundary alignment issues
	constexpr uint32 alginSize = 0x08UL;	// Align at an 8-byte boundary
	constexpr uint32 alginMask = alginSize - 1;	// Bitmask for 8-byte bound addresses

	const char *buf = (const char*)input;

	uint32_t crc = initialCRC;

	// If the string is empty, return the initial crc
	if (length == 0) return crc;

	// XOR the initial CRC with INT_MAX
	crc ^= 0xFFFFFFFF;


	// Align the input to the word boundary
	for (; (length > 0) && ((size_t)buf & alginMask); length--, buf++)
	{
		crc = _mm_crc32_u8(crc, *buf);
	}

	// Blast off the CRC32 calculation on hardware
#if defined(__x86_64__) || defined(_M_X64)
	CALC_CRC(_mm_crc32_u64, crc, uint64_t, buf, length);
#endif
	CALC_CRC(_mm_crc32_u32, crc, uint32_t, buf, length);
	CALC_CRC(_mm_crc32_u16, crc, uint16_t, buf, length);
	CALC_CRC(_mm_crc32_u8, crc, uint8_t, buf, length);
    // XOR again with INT_MAX
    return (crc ^= 0xFFFFFFFF);
#else
	assert(false);	//disable
    return 0;
#endif

	
}

#undef CALC_CRC

uint32(*CRC32C::mCRCTable)[256];
CRC32C::CalculateImpl* CRC32C::mImpl=nullptr;
MEDUSA_IMPLEMENT_STATIC_CONSTRUCTOR(CRC32C, InitCRCTable);
MEDUSA_END;

