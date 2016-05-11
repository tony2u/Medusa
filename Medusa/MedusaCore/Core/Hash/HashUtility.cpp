// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "HashUtility.h"
#include "Core/Math/Math.h"
#include "Core/Utility/Endian.h"

MEDUSA_BEGIN;

/************************************************************************/
/*
Refer to :
http://burtleburtle.net/bob/c/lookup3.c
*/

/************************************************************************/
#define MEDUSA_HASH_SIZE(n) ((uint32)1<<(n))
#define MEDUSA_HASH_MASK(n) (MEDUSA_HASH_SIZE(n)-1)
#define MEDUSA_ROT(x,k) (((x)<<(k)) | ((x)>>(32-(k))))

#define MEDUSA_MIX(a,b,c) \
{ \
	a -= c;  a ^= MEDUSA_ROT(c, 4);  c += b; \
	b -= a;  b ^= MEDUSA_ROT(a, 6);  a += c; \
	c -= b;  c ^= MEDUSA_ROT(b, 8);  b += a; \
	a -= c;  a ^= MEDUSA_ROT(c,16);  c += b; \
	b -= a;  b ^= MEDUSA_ROT(a,19);  a += c; \
	c -= b;  c ^= MEDUSA_ROT(b, 4);  b += a; \
}

#define MEDUSA_FINAL(a,b,c) \
{ \
	c ^= b; c -= MEDUSA_ROT(b,14); \
	a ^= c; a -= MEDUSA_ROT(c,11); \
	b ^= a; b -= MEDUSA_ROT(a,25); \
	c ^= b; c -= MEDUSA_ROT(b,16); \
	a ^= c; a -= MEDUSA_ROT(c,4);  \
	b ^= a; b -= MEDUSA_ROT(a,14); \
	c ^= b; c -= MEDUSA_ROT(b,24); \
}


//constexpr size_t HashUtility::HashString(const char* str, size_t seed /*= 0*/)
//{
//	return  '\0' == *str ? seed : HashString(str + 1, seed ^ (*str + 0x9e3779b9 + (seed << 6) + (seed >> 2)));
//}
//
//constexpr size_t HashUtility::HashString(const wchar_t* str, size_t seed /*= 0*/)
//{
//	return  '\0' == *str ? seed : HashString(str + 1, seed ^ (*str + 0x9e3779b9 + (seed << 6) + (seed >> 2)));
//}

/*

int32 HashUtility::HashString(const char* str)
{
	if (str == nullptr)
	{
		return 0;
	}
	//BKDRHash
	const static int32 seed = 131; // 31 131 1313 13131 131313 etc..
	int32 hash = 0;
	while (*str)
	{
		hash = hash * seed + (*str++);
	}

	return (hash & 0x7FFFFFFF);
}

int32 HashUtility::HashString(const wchar_t* str)
{
	if (str == nullptr)
	{
		return 0;
	}
	//BKDRHash
	const static int32 seed = 131; // 31 131 1313 13131 131313 etc..
	int32 hash = 0;
	while (*str)
	{
		hash = hash * seed + (*str++);
	}

	return (hash & 0x7FFFFFFF);
}


int32 HashUtility::HashString(const char* str, size_t length)
{
	if (length==Math::UIntMaxValue)
	{
		return HashString(str);
	}
	if (str == nullptr)
	{
		return 0;
	}
	//BKDRHash
	const static int32 seed = 131; // 31 131 1313 13131 131313 etc..
	int32 hash = 0;
	while (length>0)
	{
		hash = hash * seed + (*str++);
		--length;
	}

	return (hash & 0x7FFFFFFF);
}

int32 HashUtility::HashString(const wchar_t* str, size_t length)
{
	if (length == Math::UIntMaxValue)
	{
		return HashString(str);
	}

	if (str == nullptr)
	{
		return 0;
	}
	//BKDRHash
	const static int32 seed = 131; // 31 131 1313 13131 131313 etc..
	int32 hash = 0;
	while (length>0)
	{
		hash = hash * seed + (*str++);
		--length;
	}

	return (hash & 0x7FFFFFFF);
}
*/
int32 HashUtility::HashIntArray(const int* buffer, size_t size, int32 initialValue/*=0*/)
{
	int32 a, b, c;

	/* Set up the internal state */
	a = b = c = 0xdeadbeef + (((int32)size) << 2) + initialValue;

	/*------------------------------------------------- handle most of the key */
	while (size > 3)
	{
		a += buffer[0];
		b += buffer[1];
		c += buffer[2];
		MEDUSA_MIX(a, b, c);
		size -= 3;
		buffer += 3;
	}

	/*------------------------------------------- handle the last 3 int32's */
	switch (size)                     /* all the case statements fall through */
	{
		case 3: c += buffer[2];
		case 2: b += buffer[1];
		case 1: a += buffer[0];
			MEDUSA_FINAL(a, b, c);
		case 0:     /* case 0: nothing left to add */
			break;
	}

	return c;
}


int64 HashUtility::HashIntArray64(const int* buffer, size_t size, int64 initialValue/*=0*/)
{
	int32 a, b, c;

	/* Set up the internal state */
	a = b = c = 0xdeadbeef + ((int32)(size << 2)) + MEDUSA_HIGH_INT(initialValue);
	c += MEDUSA_LOW_INT(initialValue);

	/*------------------------------------------------- handle most of the key */
	while (size > 3)
	{
		a += buffer[0];
		b += buffer[1];
		c += buffer[2];
		MEDUSA_MIX(a, b, c);
		size -= 3;
		buffer += 3;
	}

	/*------------------------------------------- handle the last 3 int32's */
	switch (size)                     /* all the case statements fall through */
	{
		case 3: c += buffer[2];
		case 2: b += buffer[1];
		case 1: a += buffer[0];
			MEDUSA_FINAL(a, b, c);
		case 0:     /* case 0: nothing left to add */
			break;
	}
	return ((int64)b) << 32 | c;
}

int32 HashUtility::HashStringJenkins(const char* buffer, size_t length, int32 initialValue/*=0*/)
{
	const bool isLittleEndian = Endian::IsLittle();
	int32 a, b, c;                                          /* internal state */
	union { const void *ptr; size_t i; } u;     /* needed for Mac Powerbook G4 */

	/* Set up the internal state */
	a = b = c = 0xdeadbeef + ((int32)length) + initialValue;

	u.ptr = buffer;
	if (isLittleEndian && ((u.i & 0x3) == 0))
	{
		const int32 *k = (const int32 *)buffer;         /* read 32-bit chunks */


		/*------ all but last block: aligned reads and affect 32 bits of (a,b,c) */
		while (length > 12)
		{
			a += k[0];
			b += k[1];
			c += k[2];
			MEDUSA_MIX(a, b, c);
			length -= 12;
			k += 3;
		}

		/*----------------------------- handle the last (probably partial) block */
		/*
		* "k[2]&0xffffff" actually reads beyond the end of the string, but
		* then masks off the part it's not allowed to read.  Because the
		* string is aligned, the masked-off tail is in the same word as the
		* rest of the string.  Every machine with memory protection I've seen
		* does it on word boundaries, so is OK with this.  But VALGRIND will
		* still catch it and complain.  The masking trick does make the hash
		* noticably faster for short strings (like English words).
		*/
#ifndef VALGRIND

		switch (length)
		{
			case 12: c += k[2]; b += k[1]; a += k[0]; break;
			case 11: c += k[2] & 0xffffff; b += k[1]; a += k[0]; break;
			case 10: c += k[2] & 0xffff; b += k[1]; a += k[0]; break;
			case 9: c += k[2] & 0xff; b += k[1]; a += k[0]; break;
			case 8: b += k[1]; a += k[0]; break;
			case 7: b += k[1] & 0xffffff; a += k[0]; break;
			case 6: b += k[1] & 0xffff; a += k[0]; break;
			case 5: b += k[1] & 0xff; a += k[0]; break;
			case 4: a += k[0]; break;
			case 3: a += k[0] & 0xffffff; break;
			case 2: a += k[0] & 0xffff; break;
			case 1: a += k[0] & 0xff; break;
			case 0: return c;              /* zero length strings require no mixing */
		}

#else /* make valgrind happy */

		const byte* k8 = (const byte *)k;
		switch (length)
		{
			case 12: c += k[2]; b += k[1]; a += k[0]; break;
			case 11: c += ((int32)k8[10]) << 16;  /* fall through */
			case 10: c += ((int32)k8[9]) << 8;    /* fall through */
			case 9: c += k8[8];                   /* fall through */
			case 8: b += k[1]; a += k[0]; break;
			case 7: b += ((int32)k8[6]) << 16;   /* fall through */
			case 6: b += ((int32)k8[5]) << 8;    /* fall through */
			case 5: b += k8[4];                   /* fall through */
			case 4: a += k[0]; break;
			case 3: a += ((int32)k8[2]) << 16;   /* fall through */
			case 2: a += ((int32)k8[1]) << 8;    /* fall through */
			case 1: a += k8[0]; break;
			case 0: return c;
		}

#endif /* !valgrind */

	}
	else if (isLittleEndian && ((u.i & 0x1) == 0))
	{
		const int16 *k = (const int16 *)buffer;         /* read 16-bit chunks */
		const byte  *k8;

		/*--------------- all but last block: aligned reads and different mixing */
		while (length > 12)
		{
			a += k[0] + (((int32)k[1]) << 16);
			b += k[2] + (((int32)k[3]) << 16);
			c += k[4] + (((int32)k[5]) << 16);
			MEDUSA_MIX(a, b, c);
			length -= 12;
			k += 6;
		}

		/*----------------------------- handle the last (probably partial) block */
		k8 = (const byte *)k;
		switch (length)
		{
			case 12: c += k[4] + (((int32)k[5]) << 16);
				b += k[2] + (((int32)k[3]) << 16);
				a += k[0] + (((int32)k[1]) << 16);
				break;
			case 11: c += ((int32)k8[10]) << 16;     /* fall through */
			case 10: c += k[4];
				b += k[2] + (((int32)k[3]) << 16);
				a += k[0] + (((int32)k[1]) << 16);
				break;
			case 9: c += k8[8];                      /* fall through */
			case 8: b += k[2] + (((int32)k[3]) << 16);
				a += k[0] + (((int32)k[1]) << 16);
				break;
			case 7: b += ((int32)k8[6]) << 16;      /* fall through */
			case 6: b += k[2];
				a += k[0] + (((int32)k[1]) << 16);
				break;
			case 5: b += k8[4];                      /* fall through */
			case 4: a += k[0] + (((int32)k[1]) << 16);
				break;
			case 3: a += ((int32)k8[2]) << 16;      /* fall through */
			case 2: a += k[0];
				break;
			case 1: a += k8[0];
				break;
			case 0: return c;                     /* zero length requires no mixing */
		}

	}
	else
	{                        /* need to read the key one byte at a time */
		const byte *k = (const byte *)buffer;

		/*--------------- all but the last block: affect some 32 bits of (a,b,c) */
		while (length > 12)
		{
			a += k[0];
			a += ((int32)k[1]) << 8;
			a += ((int32)k[2]) << 16;
			a += ((int32)k[3]) << 24;
			b += k[4];
			b += ((int32)k[5]) << 8;
			b += ((int32)k[6]) << 16;
			b += ((int32)k[7]) << 24;
			c += k[8];
			c += ((int32)k[9]) << 8;
			c += ((int32)k[10]) << 16;
			c += ((int32)k[11]) << 24;
			MEDUSA_MIX(a, b, c);
			length -= 12;
			k += 12;
		}

		/*-------------------------------- last block: affect all 32 bits of (c) */
		switch (length)                   /* all the case statements fall through */
		{
			case 12: c += ((int32)k[11]) << 24;
			case 11: c += ((int32)k[10]) << 16;
			case 10: c += ((int32)k[9]) << 8;
			case 9: c += k[8];
			case 8: b += ((int32)k[7]) << 24;
			case 7: b += ((int32)k[6]) << 16;
			case 6: b += ((int32)k[5]) << 8;
			case 5: b += k[4];
			case 4: a += ((int32)k[3]) << 24;
			case 3: a += ((int32)k[2]) << 16;
			case 2: a += ((int32)k[1]) << 8;
			case 1: a += k[0];
				break;
			case 0: return c;
		}
	}

	MEDUSA_FINAL(a, b, c);
	return c;
}

int64 HashUtility::HashStringJenkins64(const char* buffer, size_t length, int64 initialValue/*=0*/)
{
	const bool isLittleEndian = Endian::IsLittle();

	int32 a, b, c;                                          /* internal state */
	union { const void *ptr; size_t i; } u;     /* needed for Mac Powerbook G4 */

	/* Set up the internal state */
	a = b = c = 0xdeadbeef + ((int32)length) + MEDUSA_HIGH_INT(initialValue);
	c += MEDUSA_LOW_INT(initialValue);

	u.ptr = buffer;
	if (isLittleEndian && ((u.i & 0x3) == 0))
	{
		const int32 *k = (const int32 *)buffer;         /* read 32-bit chunks */


		/*------ all but last block: aligned reads and affect 32 bits of (a,b,c) */
		while (length > 12)
		{
			a += k[0];
			b += k[1];
			c += k[2];
			MEDUSA_MIX(a, b, c);
			length -= 12;
			k += 3;
		}

		/*----------------------------- handle the last (probably partial) block */
		/*
		* "k[2]&0xffffff" actually reads beyond the end of the string, but
		* then masks off the part it's not allowed to read.  Because the
		* string is aligned, the masked-off tail is in the same word as the
		* rest of the string.  Every machine with memory protection I've seen
		* does it on word boundaries, so is OK with this.  But VALGRIND will
		* still catch it and complain.  The masking trick does make the hash
		* noticably faster for short strings (like English words).
		*/
#ifndef VALGRIND

		switch (length)
		{
			case 12: c += k[2]; b += k[1]; a += k[0]; break;
			case 11: c += k[2] & 0xffffff; b += k[1]; a += k[0]; break;
			case 10: c += k[2] & 0xffff; b += k[1]; a += k[0]; break;
			case 9: c += k[2] & 0xff; b += k[1]; a += k[0]; break;
			case 8: b += k[1]; a += k[0]; break;
			case 7: b += k[1] & 0xffffff; a += k[0]; break;
			case 6: b += k[1] & 0xffff; a += k[0]; break;
			case 5: b += k[1] & 0xff; a += k[0]; break;
			case 4: a += k[0]; break;
			case 3: a += k[0] & 0xffffff; break;
			case 2: a += k[0] & 0xffff; break;
			case 1: a += k[0] & 0xff; break;
			case 0: return ((int64)b) << 32 | c;  /* zero length strings require no mixing */
		}

#else /* make valgrind happy */

		const byte  *k8; = (const byte *)k;
		switch (length)
		{
			case 12: c += k[2]; b += k[1]; a += k[0]; break;
			case 11: c += ((int32)k8[10]) << 16;  /* fall through */
			case 10: c += ((int32)k8[9]) << 8;    /* fall through */
			case 9: c += k8[8];                   /* fall through */
			case 8: b += k[1]; a += k[0]; break;
			case 7: b += ((int32)k8[6]) << 16;   /* fall through */
			case 6: b += ((int32)k8[5]) << 8;    /* fall through */
			case 5: b += k8[4];                   /* fall through */
			case 4: a += k[0]; break;
			case 3: a += ((int32)k8[2]) << 16;   /* fall through */
			case 2: a += ((int32)k8[1]) << 8;    /* fall through */
			case 1: a += k8[0]; break;
			case 0: return ((int64)b) << 32 | c; /* zero length strings require no mixing */
		}

#endif /* !valgrind */

	}
	else if (isLittleEndian && ((u.i & 0x1) == 0))
	{
		const uint16_t *k = (const uint16_t *)buffer;         /* read 16-bit chunks */
		const byte  *k8;

		/*--------------- all but last block: aligned reads and different mixing */
		while (length > 12)
		{
			a += k[0] + (((int32)k[1]) << 16);
			b += k[2] + (((int32)k[3]) << 16);
			c += k[4] + (((int32)k[5]) << 16);
			MEDUSA_MIX(a, b, c);
			length -= 12;
			k += 6;
		}

		/*----------------------------- handle the last (probably partial) block */
		k8 = (const byte *)k;
		switch (length)
		{
			case 12: c += k[4] + (((int32)k[5]) << 16);
				b += k[2] + (((int32)k[3]) << 16);
				a += k[0] + (((int32)k[1]) << 16);
				break;
			case 11: c += ((int32)k8[10]) << 16;     /* fall through */
			case 10: c += k[4];
				b += k[2] + (((int32)k[3]) << 16);
				a += k[0] + (((int32)k[1]) << 16);
				break;
			case 9: c += k8[8];                      /* fall through */
			case 8: b += k[2] + (((int32)k[3]) << 16);
				a += k[0] + (((int32)k[1]) << 16);
				break;
			case 7: b += ((int32)k8[6]) << 16;      /* fall through */
			case 6: b += k[2];
				a += k[0] + (((int32)k[1]) << 16);
				break;
			case 5: b += k8[4];                      /* fall through */
			case 4: a += k[0] + (((int32)k[1]) << 16);
				break;
			case 3: a += ((int32)k8[2]) << 16;      /* fall through */
			case 2: a += k[0];
				break;
			case 1: a += k8[0];
				break;
			case 0: return ((int64)b) << 32 | c;   /* zero length strings require no mixing */
		}

	}
	else
	{                        /* need to read the key one byte at a time */
		const byte *k = (const byte *)buffer;

		/*--------------- all but the last block: affect some 32 bits of (a,b,c) */
		while (length > 12)
		{
			a += k[0];
			a += ((int32)k[1]) << 8;
			a += ((int32)k[2]) << 16;
			a += ((int32)k[3]) << 24;
			b += k[4];
			b += ((int32)k[5]) << 8;
			b += ((int32)k[6]) << 16;
			b += ((int32)k[7]) << 24;
			c += k[8];
			c += ((int32)k[9]) << 8;
			c += ((int32)k[10]) << 16;
			c += ((int32)k[11]) << 24;
			MEDUSA_MIX(a, b, c);
			length -= 12;
			k += 12;
		}

		/*-------------------------------- last block: affect all 32 bits of (c) */
		switch (length)                   /* all the case statements fall through */
		{
			case 12: c += ((int32)k[11]) << 24;
			case 11: c += ((int32)k[10]) << 16;
			case 10: c += ((int32)k[9]) << 8;
			case 9: c += k[8];
			case 8: b += ((int32)k[7]) << 24;
			case 7: b += ((int32)k[6]) << 16;
			case 6: b += ((int32)k[5]) << 8;
			case 5: b += k[4];
			case 4: a += ((int32)k[3]) << 24;
			case 3: a += ((int32)k[2]) << 16;
			case 2: a += ((int32)k[1]) << 8;
			case 1: a += k[0];
				break;
			case 0: return ((int64)b) << 32 | c;   /* zero length strings require no mixing */
		}
	}

	MEDUSA_FINAL(a, b, c);
	return ((int64)b) << 32 | c;
}



#undef MEDUSA_HASH_SIZE
#undef MEDUSA_HASH_MASK
#undef MEDUSA_ROT
#undef MEDUSA_MIX
#undef MEDUSA_FINAL


MEDUSA_END;
