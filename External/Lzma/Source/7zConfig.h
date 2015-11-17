#pragma once

//#define  EXTRACT_ONLY
#define  _7ZIP_LARGE_PAGES
#define  _7ZIP_ST
#define ENV_HAVE_WCHAR__H

#ifdef WIN32
#define _7ZIP_PTHREAD_H	"CoreLib/Win/pthread/pthread.h"
#else
#define _7ZIP_PTHREAD_H	<pthread.h>

#ifndef FALSE			/* in case these macros already exist */
#define FALSE	0		/* values of boolean */
#endif
#ifndef TRUE
#define TRUE	1
#endif

#ifndef BOOL
typedef signed char BOOL_7Z;
#endif

typedef void* LPVOID;

#endif

#ifdef __APPLE__
#if __LP64__
#else
#define _LZMA_UINT32_IS_ULONG
#endif
#endif