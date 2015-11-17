// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "CorePlatform/CorePlatformDefines.h"
#include "CoreLib/CoreLib.h"

#include "CorePlatform/CommonMarcos.h"
#include "CorePlatform/MacroUtility.h"

#if __cplusplus <= 199711L
#ifndef override
#define override
#endif
#endif


#ifdef _MSC_VER

#else

#endif



#ifdef MEDUSA_WINDOWS
typedef __int8  int8;
typedef __int16 int16;
typedef __int32 int32;
typedef __int64 int64;



typedef unsigned __int8  uint8;
typedef unsigned __int16 uint16;
typedef unsigned __int32 uint32;
typedef unsigned __int64 uint64;

typedef unsigned short		ushort;
typedef unsigned long		ulong;
typedef unsigned int		uint;
typedef wchar_t wchar;
typedef unsigned char byte;

typedef HWND MedusaWindowHandle;
typedef intptr_t intptr;
typedef uintptr_t uintptr;

#ifdef MEDUSA_X64
typedef int64 intp;
#else
typedef int32 intp;
#endif

typedef size_t uintp;


#ifndef strtoll
#define strtoll  _strtoi64
#endif // !strtoll


#ifndef strtoull
#define strtoull  _strtoui64
#endif // !strtoull

#define MEDUSA_TRACEA(s) OutputDebugStringA(s)
#define MEDUSA_TRACEW(s) OutputDebugStringW(s)
#define MEDUSA_TRACE(s) MEDUSA_TRACEA(s)

#endif


#if defined (MEDUSA_IOS) || defined( MEDUSA_ANDROID )|| defined( MEDUSA_LINUX)
typedef unsigned short		ushort;
typedef unsigned long		ulong;
typedef unsigned int		uint;

//typedef unsigned int		size_t;
typedef unsigned char byte;
typedef wchar_t wchar;

typedef intptr_t intptr;
typedef uintptr_t uintptr;

typedef int8_t  int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;
typedef int errno_t;

#ifdef MEDUSA_X64
typedef int64 intp;
#else
typedef int32 intp;
#endif

typedef size_t uintp;

typedef intp MedusaWindowHandle;

typedef int SOCKET;

#define MEDUSA_TRACE(s) 
#define MEDUSA_TRACEA(s) 
#define MEDUSA_TRACEW(s) 
#endif


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