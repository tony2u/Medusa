// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaCorePreDeclares.h"

MEDUSA_BEGIN;

namespace Endian
{
	inline bool IsLittle() 
	{
		const int32_t x = 1;
		return *(char*)&x == 1;
	}

	inline int ToLittle(int val)
	{
		if (!IsLittle())
		{
			val=((val & 0x000000FF) << 24) + ((val & 0x0000FF00) << 8) + ((val & 0x00FF0000) >> 8) + ((val & 0xFF000000) >> 24);
		}
		return val;
	}
	inline uint32 ToLittle(uint32 val)
	{
		if (!IsLittle())
		{
			val = ((val & 0x000000FF) << 24) + ((val & 0x0000FF00) << 8) + ((val & 0x00FF0000) >> 8) + ((val & 0xFF000000) >> 24);
		}
		return val;
	}


	inline int64 ToLittle(int64 val)
	{
		if (!IsLittle())
		{
			byte* bytes = (byte*)&val;
			byte temp = bytes[0]; bytes[0] = bytes[7]; bytes[7] = temp;
			temp = bytes[1]; bytes[1] = bytes[6]; bytes[6] = temp;
			temp = bytes[2]; bytes[2] = bytes[5]; bytes[5] = temp;
			temp = bytes[3]; bytes[3] = bytes[4]; bytes[4] = temp;
			return val;
		}
		return val;
	}

	inline uint64 ToLittle(uint64 val)
	{
		if (!IsLittle())
		{
			byte* bytes = (byte*)&val;
			byte temp = bytes[0]; bytes[0] = bytes[7]; bytes[7] = temp;
			temp = bytes[1]; bytes[1] = bytes[6]; bytes[6] = temp;
			temp = bytes[2]; bytes[2] = bytes[5]; bytes[5] = temp;
			temp = bytes[3]; bytes[3] = bytes[4]; bytes[4] = temp;
			return val;
		}
		return val;
	}
#ifdef MEDUSA_WINDOWS

#ifndef htonll
	inline uint64_t htonll(uint64_t v)
	{
		union { uint32_t lv[2]; uint64_t llv; } u;
		u.lv[0] = htonl(v >> 32);
		u.lv[1] = htonl(v & 0xFFFFFFFFULL);
		return u.llv;
	}
	
#endif

#ifndef ntohll
	inline uint64_t ntohll(uint64_t v)
	{
		union { uint32_t lv[2]; uint64_t llv; } u;
		u.llv = v;
		return ((uint64_t)ntohl(u.lv[0]) << 32) | (uint64_t)ntohl(u.lv[1]);
	}
#endif

	inline uint64_t HostToNetwork64(uint64_t host64)
	{
		return htonll(host64);
	}

	inline uint32_t HostToNetwork32(uint32_t host32)
	{
		return htonl(host32);
	}

	inline uint16_t HostToNetwork16(uint16_t host16)
	{
		return htons(host16);
	}

	inline uint64_t NetworkToHost64(uint64_t net64)
	{
		return ntohll(net64);
	}

	inline uint32_t NetworkToHost32(uint32_t net32)
	{
		return ntohl(net32);
	}

	inline uint16_t NetworkToHost16(uint16_t net16)
	{
		return ntohs(net16);
	}
#else


	// the inline assembler code makes type blur,
	// so we disable warnings for a while.
#if defined(__clang__) || __GNUC_MINOR__ >= 6
#pragma GCC diagnostic push
#endif
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wold-style-cast"


	inline uint64_t HostToNetwork64(uint64_t host64)
	{
		return htobe64(host64);
	}

	inline uint32_t HostToNetwork32(uint32_t host32)
	{
		return htobe32(host32);
	}

	inline uint16_t HostToNetwork16(uint16_t host16)
	{
		return htobe16(host16);
	}

	inline uint64_t NetworkToHost64(uint64_t net64)
	{
		return be64toh(net64);
	}

	inline uint32_t NetworkToHost32(uint32_t net32)
	{
		return be32toh(net32);
	}

	inline uint16_t NetworkToHost16(uint16_t net16)
	{
		return be16toh(net16);
	}


#if defined(__clang__) || __GNUC_MINOR__ >= 6
#pragma GCC diagnostic pop
#else
#pragma GCC diagnostic warning "-Wconversion"
#pragma GCC diagnostic warning "-Wold-style-cast"
#endif

#endif

}

MEDUSA_END;