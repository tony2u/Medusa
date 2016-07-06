// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "CorePlatform/CorePlatformDefines.h"
#include "CoreLib/CoreLib.h"

#include "CorePlatform/CommonMarcos.h"
#include "CorePlatform/MacroUtility.h"



MEDUSA_BEGIN;

typedef int8_t  int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;


typedef unsigned char byte;
typedef unsigned short ushort;
typedef unsigned long ulong;
typedef unsigned int uint;
typedef wchar_t wchar;

typedef intptr_t intptr;
typedef uintptr_t uintptr;

#ifdef MEDUSA_X64
typedef int64 intp;
#else
typedef int32 intp;
#endif

typedef size_t uintp;


#ifdef MEDUSA_WINDOWS
typedef HWND MedusaWindowHandle;
typedef UINT_PTR MedusaFileDescriptor;

#elif defined (MEDUSA_IOS) || defined( MEDUSA_ANDROID )|| defined( MEDUSA_LINUX)
typedef int SOCKET;
typedef int errno_t;
typedef intp MedusaWindowHandle;
typedef SOCKET MedusaFileDescriptor;
#endif

#define MedusaInvalidFileDescriptor  ((MedusaFileDescriptor)(~0))
#define MedusaInvalidSocket ((SOCKET)(~0))

union int128
{
	char Buffer[16];
	struct
	{
		int64 Low;
		int64 High;
	};
};

union uint128
{
	byte Buffer[16];
	struct
	{
		uint64 Low;
		uint64 High;
	};
};

MEDUSA_END;
