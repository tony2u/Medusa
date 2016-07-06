// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#undef MEDUSA_OS
#undef MEDUSA_DEBUG
#undef MEDUSA_SAFE_CHECK

#undef MEDUSA_LOG
#undef MEDUSA_IS_SIMULATOR

#undef MEDUSA_WINDOWS
#undef MEDUSA_IOS
#undef MEDUSA_MAC
#undef MEDUSA_ANDROID
#undef MEDUSA_LINUX
#undef MEDUSA_POSIX


#ifndef MEDUSA_DISABLE_HTTP
#define MEDUSA_HTTP
#endif

#ifndef MEDUSA_DISABLE_LZMA
#define MEDUSA_LZMA
#endif

#ifndef MEDUSA_DISABLE_LZ4
#define MEDUSA_LZ4
#endif

#ifndef MEDUSA_DISABLE_UNZIP
#define MEDUSA_UNZIP
#endif

#ifndef MEDUSA_DISABLE_ZLIB
#define MEDUSA_ZLIB
#endif





//Features
#define MEDUSA_XML

//Script
#undef MEDUSA_LUA
#undef MEDUSA_LUA_JIT
#undef MEDUSA_JS

#define MEDUSA_SCRIPT_LUA 100
#define MEDUSA_SCRIPT_LUA_JIT 101
#define MEDUSA_SCRIPT_JS 200

#ifndef MEDUSA_DISABLE_SCRIPT

#define MEDUSA_SCRIPT MEDUSA_SCRIPT_LUA_JIT

#if MEDUSA_SCRIPT==MEDUSA_SCRIPT_LUA
#define MEDUSA_LUA MEDUSA_SCRIPT

#elif MEDUSA_SCRIPT==MEDUSA_SCRIPT_LUA_JIT
#define MEDUSA_LUA MEDUSA_SCRIPT_LUA
#define MEDUSA_LUA_JIT MEDUSA_SCRIPT

#elif MEDUSA_SCRIPT==MEDUSA_SCRIPT_JS
#define MEDUSA_JS MEDUSA_SCRIPT
#endif
#endif

#ifndef MEDUSA_DISABLE_SQL
#define MEDUSA_SQL
#endif

//#define MEDUSA_VFP
//#define MEDUSA_NEON

//#define MEDUSA_POSIX_THREADING
//#define MEDUSA_THREADING_MULTIPLE_WAIT


//#define MEDUSA_PROFILE_FEATURE
//#define MEDUSA_VIRTUAL_ENABLED




#define MEDUSA_BIT_X86 1
#define MEDUSA_BIT_X64 2

#define MEDUSA_OS_WINDOWS 100
#define MEDUSA_OS_IOS 200
#define MEDUSA_OS_MAC 300
#define MEDUSA_OS_ANDROID 400
#define MEDUSA_OS_LINUX 500

#define MEDUSA_WEAK_MULTIPLE_DEFINE
#define MEDUSA_FORCE_INLINE
#define MEDUSA_FORCE_NOINLINE
#define MEDUSA_DEPRECATED


//#define MEDUSA_VIRTUAL_ENABLED
#ifdef MEDUSA_VIRTUAL_ENABLED
#define MEDUSA_VIRTUAL virtual
#else
#define MEDUSA_VIRTUAL
#endif

////////////////////////////////////////////////////////////////////////// Win
#if defined(_WIN64)||defined(_WIN32)||defined(WIN32)||defined(WIN64)

#if defined(DEBUG) || defined(_DEBUG)
#define MEDUSA_DEBUG
#define MEDUSA_SAFE_CHECK
#endif


#define MEDUSA_OS MEDUSA_OS_WINDOWS
#define MEDUSA_WINDOWS MEDUSA_OS
#define  MEDUSA_LOG(...)  

#undef MEDUSA_WEAK_MULTIPLE_DEFINE
#define MEDUSA_WEAK_MULTIPLE_DEFINE __declspec(selectany)

#undef MEDUSA_FORCE_INLINE
#define MEDUSA_FORCE_INLINE __forceinline

#undef MEDUSA_FORCE_NOINLINE
#define MEDUSA_FORCE_NOINLINE __declspec(noinline)

#undef MEDUSA_DEPRECATED
#define MEDUSA_DEPRECATED __declspec(deprecated)





#pragma warning(disable:4127)
#pragma warning(disable:4505)
#pragma warning(disable:4100)
#pragma warning(disable:4201)	//nonstandard extension used : nameless struct/union

#pragma warning(disable:4510)
#pragma warning(disable:4512)
#pragma warning(disable:4610)



#ifdef _WIN64
#define MEDUSA_X64 MEDUSA_BIT_X64
#define MEDUSA_BIT MEDUSA_X64
#else
#define MEDUSA_X86 MEDUSA_BIT_X86
#define MEDUSA_BIT MEDUSA_X86


#endif

////////////////////////////////////////////////////////////////////////// Apple
#elif __APPLE__

#include "TargetConditionals.h"

#if defined(DEBUG) || defined(_DEBUG)
#define MEDUSA_DEBUG
#define MEDUSA_SAFE_CHECK
#endif


#if TARGET_OS_IPHONE
#define MEDUSA_OS MEDUSA_OS_IOS
#define MEDUSA_IOS	MEDUSA_OS
#ifdef TARGET_IPHONE_SIMULATOR
#define MEDUSA_IS_SIMULATOR
#else
//#define MEDUSA_MATH_VFP_ENABLED
#endif 

#elif TARGET_OS_MAC
#define MEDUSA_OS MEDUSA_OS_MAC
#define MEDUSA_MAC	MEDUSA_OS
#else
#endif

#ifdef _ARM_ARCH_7
//#define MEDUSA_MATH_NEON_ENABLED
#endif

#define  MEDUSA_LOG(...)  

#undef MEDUSA_WEAK_MULTIPLE_DEFINE
#define MEDUSA_WEAK_MULTIPLE_DEFINE __attribute__((weak))

#undef MEDUSA_FORCE_INLINE
#define MEDUSA_FORCE_INLINE __attribute__((always_inline)) inline

#undef MEDUSA_FORCE_NOINLINE
#define MEDUSA_FORCE_NOINLINE __attribute__((noinline))

#undef MEDUSA_DEPRECATED
#define MEDUSA_DEPRECATED __attribute__((deprecated))

#if __x86_64__ || __ppc64__ ||__LP64__
#define MEDUSA_X64 MEDUSA_BIT_X64
#define MEDUSA_BIT MEDUSA_X64

#else
#define MEDUSA_X86 MEDUSA_BIT_X86
#define MEDUSA_BIT MEDUSA_X86

#endif
#define MEDUSA_POSIX
#ifndef MEDUSA_POSIX_THREADING
#define MEDUSA_POSIX_THREADING
#endif


#elif __ANDROID__
////////////////////////////////////////////////////////////////////////// Android
#if !defined(NDEBUG)
#define MEDUSA_DEBUG
#define MEDUSA_SAFE_CHECK
#endif


#define MEDUSA_OS MEDUSA_OS_ANDROID
#define MEDUSA_ANDROID	MEDUSA_OS
#define  MEDUSA_LOG(...)  __android_log_print(ANDROID_LOG_DEBUG,"Medusa",__VA_ARGS__)

#undef MEDUSA_WEAK_MULTIPLE_DEFINE
#define MEDUSA_WEAK_MULTIPLE_DEFINE __attribute__((weak))

#undef MEDUSA_FORCE_INLINE
#define MEDUSA_FORCE_INLINE inline __attribute__((always_inline))

#undef MEDUSA_FORCE_NOINLINE
#define MEDUSA_FORCE_NOINLINE __attribute__((noinline))

#undef MEDUSA_DEPRECATED
#define MEDUSA_DEPRECATED __attribute__((deprecated))

#if __x86_64__ || __ppc64__
#define MEDUSA_X64 MEDUSA_BIT_X64
#define MEDUSA_BIT MEDUSA_X64
#else
#define MEDUSA_X86 MEDUSA_BIT_X86
#define MEDUSA_BIT MEDUSA_X86
#endif

#define MEDUSA_POSIX
#ifndef MEDUSA_POSIX_THREADING
#define MEDUSA_POSIX_THREADING
#endif

#elif defined(linux)||defined(__linux)||defined(__linux__)
////////////////////////////////////////////////////////////////////////// Linux
#if defined(DEBUG) || defined(_DEBUG)
#define MEDUSA_DEBUG
#define MEDUSA_SAFE_CHECK
#endif

#define MEDUSA_OS MEDUSA_OS_LINUX
#define MEDUSA_LINUX	MEDUSA_OS
#define  MEDUSA_LOG(...) 

#undef MEDUSA_WEAK_MULTIPLE_DEFINE
#define MEDUSA_WEAK_MULTIPLE_DEFINE __attribute__((weak))

#undef MEDUSA_FORCE_INLINE
#define MEDUSA_FORCE_INLINE __attribute__((always_inline))

#undef MEDUSA_FORCE_NOINLINE
#define MEDUSA_FORCE_NOINLINE __attribute__((noinline))

#undef MEDUSA_DEPRECATED
#define MEDUSA_DEPRECATED __attribute__((deprecated))

#if __x86_64__ || __ppc64__
#define MEDUSA_X64 MEDUSA_BIT_X64
#define MEDUSA_BIT MEDUSA_X64
#else
#define MEDUSA_X86 MEDUSA_BIT_X86
#define MEDUSA_BIT MEDUSA_X86
#endif
#define MEDUSA_POSIX
#ifndef MEDUSA_POSIX_THREADING
#define MEDUSA_POSIX_THREADING
#endif

#else
#error "No platform"
#endif

#ifndef MEDUSA_OS
#error  "Can not recognize the target platform(MEDUSA_WINDOWS,MEDUSA_IOS,MEDUSA_ANDROID), compling under a unsupported platform?"
#endif 


#ifdef __has_builtin
# define MEDUSA_HAS_BUILTIN(x) __has_builtin(x)
#else
# define MEDUSA_HAS_BUILTIN(x) 0
#endif

// Check if exceptions are disabled.
#if __GNUC__ && !__EXCEPTIONS
#define MEDUSA_HAS_EXCEPTIONS 0
#endif

#if _MSC_VER && !_HAS_EXCEPTIONS
#define MEDUSA_HAS_EXCEPTIONS 0
#endif

#ifndef MEDUSA_HAS_EXCEPTIONS
#define MEDUSA_HAS_EXCEPTIONS 1
#endif


#if MEDUSA_HAS_EXCEPTIONS
#define MEDUSA_TRY try
#define MEDUSA_CATCH(x) catch (x)
#define MEDUSA_THROW(x) throw x

#else
#define MEDUSA_TRY 
#define MEDUSA_CATCH(x) if (false)
#define MEDUSA_THROW(x) assert(false)
#endif



#if defined(__GNUC__) && (__GNUC__ >= 4)
#define MEDUSA_CHECK_AS_PRINTF_FORMAT(formatPos, argPos) __attribute__((__format__(printf, formatPos, argPos)))
#elif defined(__has_attribute)
#if __has_attribute(format)
#define MEDUSA_CHECK_AS_PRINTF_FORMAT(formatPos, argPos) __attribute__((__format__(printf, formatPos, argPos)))
#endif 
#else
#define MEDUSA_CHECK_AS_PRINTF_FORMAT(formatPos, argPos)
#endif


#if defined(__GNUC__) && (__GNUC__ >= 4)
#define MEDUSA_CHECK_AS_WPRINTF_FORMAT(formatPos, argPos)
#elif defined(__has_attribute)
#if __has_attribute(format)
#define MEDUSA_CHECK_AS_WPRINTF_FORMAT(formatPos, argPos) 
#endif 
#else
#define MEDUSA_CHECK_AS_WPRINTF_FORMAT(formatPos, argPos)
#endif

#if !defined(MEDUSA_REQUIRES_NULL_TERMINATION)
#if defined(__APPLE_CC__) && (__APPLE_CC__ >= 5549)
#define MEDUSA_REQUIRES_NULL_TERMINATION __attribute__((sentinel(0,1)))
#elif defined(__GNUC__)
#define MEDUSA_REQUIRES_NULL_TERMINATION __attribute__((sentinel))
#else
#define MEDUSA_REQUIRES_NULL_TERMINATION
#endif
#endif

// Check if the compiler can use C++11 features
#if !defined(_MSC_VER) || _MSC_VER >= 1700   // MSVC 2012
#if !defined(__GNUC__) || __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 7)  // gnuc 4.7
#if !(defined(__GNUC__) && defined(__cplusplus) && __cplusplus < 201103L) // g++ -std=c++11
#if !defined(__SUNPRO_CC)
#define MEDUSA_CPP11 1
#define MEDUSA_CPP14 1
#endif
#endif
#endif
#endif

#if __cplusplus>=201103L && !defined(MEDUSA_CPP11)
#define MEDUSA_CPP11 1
#endif // __cplusplus>=201103L


#if __cplusplus>=201402L && !defined(MEDUSA_CPP14)
#define MEDUSA_CPP14 1
#endif // __cplusplus>=201402L


//ref qualifier to indicate a member function call on right value or left value
#undef MEDUSA_HAS_REF_QUALIFIER
#undef MEDUSA_REF_LVALUE

#if defined(__clang__)
# if __has_feature(cxx_reference_qualified_functions)
#  define MEDUSA_HAS_REF_QUALIFIER
# endif
#elif defined(__GNUC__)
# define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
# if GCC_VERSION >= 40801
#  define MEDUSA_HAS_REF_QUALIFIER
# endif
#elif defined(_MSC_VER)
# if _MSC_VER >= 1900 // since MSVS-14 CTP1
#  define MEDUSA_HAS_REF_QUALIFIER
# endif
#endif

#if defined(MEDUSA_HAS_REF_QUALIFIER)
# define MEDUSA_REF_LVALUE &
#else
# define MEDUSA_REF_LVALUE
#endif

//////////////////////////////////////////////////////////////////////////

#undef MEDUSA_LIKELY
#undef MEDUSA_UNLIKELY

#if defined(__GNUC__) && __GNUC__ >= 4
#define MEDUSA_LIKELY(x)   (__builtin_expect((x), 1))
#define MEDUSA_UNLIKELY(x) (__builtin_expect((x), 0))
#else
#define MEDUSA_LIKELY(x)   (x)
#define MEDUSA_UNLIKELY(x) (x)
#endif




#ifndef MEDUSA_DISABLE_VLD
#define MEDUSA_VLD
#endif

//default disable vld
#ifndef MEDUSA_DEBUG
#undef MEDUSA_VLD
#endif

//#define MEDUSA_MEMORY_LEAK_DETECT