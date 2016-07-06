#pragma once
#include "CorePlatform/CorePlatformDefines.h"

#ifdef MEDUSA_MEMORY_LEAK_DETECT
#ifdef MEDUSA_WINDOWS

#ifdef MEDUSA_DEBUG
#define _CRTDBG_MAP_ALLOC

#include <stdlib.h>
#include "crtdbg.h"


inline void* debug_malloc(const char* file, int line, size_t size)
{
	return malloc(size);
}

inline void debug_free(const char* file, int line, void* p)
{
	free(p);
}

inline void* operator new(size_t size, const char *file, int line)
{
	return debug_malloc(file, line, size);
}

#define DEBUG_NEW   new( _NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW

namespace std
{
	//put in std namespace to avoid std::malloc error
	inline void* debug_malloc(const char* file, int line, size_t size)
	{
		return malloc(size);
	}

	inline void debug_free(const char* file, int line, void* p)
	{
		free(p);
	}
}

#define malloc(size) debug_malloc(__FILE__, __LINE__, size)
#define free(ptr) debug_free (__FILE__, __LINE__, ptr);

#else
#define DEBUG_NEW
#endif



namespace Medusa
{
	namespace MemoryLeakDetector
	{
		//place at first in main
		inline void Start()
		{
#ifdef MEDUSA_DEBUG
			_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
#endif
		}

		//break at how many times to alloc memory
		inline void SetBreakPoint(int memoryAllocTimes)
		{
#ifdef MEDUSA_DEBUG
			_CrtSetBreakAlloc(memoryAllocTimes);
#endif
		}

	}
}

#endif
#endif
