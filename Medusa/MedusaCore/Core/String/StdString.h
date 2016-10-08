// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "MedusaCorePreDeclares.h"
#include "Core/Collection/BitArray.h"
#include "Core/Memory/Memory.h"

MEDUSA_BEGIN;

namespace StdString
{
	static bool IsDigit(int c) { return isdigit(c) != 0; }	//is number
	static bool IsXDigit(int c) { return isxdigit(c) != 0; }	//is hex number

	static bool IsAlpha(int c) { return isalpha(c) != 0; }	//is char
	static bool IsSpaceOrTab(int c) { return c == '\t' || c == ' '; }	//tab or space
	static bool IsSpace(int c) { return isspace(c) != 0; }

	static bool IsControl(int c) { return iscntrl(c) != 0; }
	static bool IsLower(int c) { return islower(c) != 0; }
	static bool IsUpper(int c) { return isupper(c) != 0; }

	static bool IsGraph(int c) { return isgraph(c) != 0; }
	static bool IsPrint(int c) { return isprint(c) != 0; }
	static bool IsPunct(int c) { return ispunct(c) != 0; }	//Checks whether c is a punctuation character.

	static bool IsToken(int c) { return IsAlpha(c) || IsDigit(c) || c == '_'; }	//Checks whether c is a punctuation character.


	bool IsDigit(const char* str);
	bool IsDigit(const wchar_t* str);

	bool IsXDigit(const char* str);
	bool IsXDigit(const wchar_t* str);

	bool IsAlpha(const char* str);
	bool IsAlpha(const wchar_t* str);

	bool IsLower(const char* str);
	bool IsLower(const wchar_t* str);

	bool IsUpper(const char* str);
	bool IsUpper(const wchar_t* str);

	bool IsToken(const char* str);
	bool IsToken(const wchar_t* str);


	static int ToUpper(int c) { return toupper(c); }
	static int ToLower(int c) { return tolower(c); }


	static size_t GetLength(const char* src) { RETURN_ZERO_IF_NULL(src); return ::strlen(src); }
	static size_t GetLength(const wchar_t* src) { RETURN_ZERO_IF_NULL(src); return ::wcslen(src); }

	static int Compare(const char* src, const char* dst) { return ::strcmp(src, dst); }
	static int Compare(const wchar_t* src, const wchar_t* dst) { return ::wcscmp(src, dst); }

	static int CompareN(const char* src, const char* dst, size_t count) { return ::strncmp(src, dst, count); }
	static int CompareN(const wchar_t* src, const wchar_t* dst, size_t count) { return ::wcsncmp(src, dst, count); }

	int CompareIgnoreCase(const char* dst, const char* src);
	int CompareIgnoreCase(const wchar_t* dst, const wchar_t* src);

	int CompareNIgnoreCase(const char* first, const char* last, size_t count);
	int CompareNIgnoreCase(const wchar_t* first, const wchar_t* last, size_t count);

	static const char* FindFirstChar(const char* src, char c) { RETURN_NULL_IF_NULL(src); return ::strchr(src, c); }
	static const wchar_t* FindFirstChar(const wchar_t* src, wchar_t c) { RETURN_NULL_IF_NULL(src); return ::wcschr(src, c); }

	static const char* FindLastChar(const char* src, char c) { RETURN_NULL_IF_NULL(src); return ::strrchr(src, c); }
	static const wchar_t* FindLastChar(const wchar_t* src, wchar_t c) { RETURN_NULL_IF_NULL(src); return ::wcsrchr(src, c); }

	static const char* FindString(const char* src, const char* dst) { RETURN_NULL_IF_NULL(src); return ::strstr(src, dst); }
	static const wchar_t* FindString(const wchar_t* src, const wchar_t* dst) { RETURN_NULL_IF_NULL(src); return ::wcsstr(src, dst); }

	static const char* FindCharAny(const char* src, const char* dst) { RETURN_NULL_IF_NULL(src); return ::strpbrk(src, dst); }
	static const wchar_t* FindCharAny(const wchar_t* src, const wchar_t* dst) { RETURN_NULL_IF_NULL(src); return ::wcspbrk(src, dst); }

	template<typename T>
	static const T* FindFirstChar(const T* src, size_t length, T c)
	{
		RETURN_NULL_IF(src == nullptr || length == 0);
		const T* end = src + length;
		while (src != end)
		{
			if (*src == c)
			{
				return src;
			}
			++src;
		}
		return nullptr;
	}

	template<typename T>
	static const T* FindLastChar(const T* src, size_t length, T c)
	{
		RETURN_NULL_IF(src == nullptr || length == 0);
		const T* end = src + length - 1;
		const T* begin = src - 1;
		while (end != begin)
		{
			if (*end == c)
			{
				return end;
			}
			--end;
		}
		return nullptr;
	}

	template<typename T>
	static const T* FindString(const T* src, size_t length, const T* val, size_t valLength)
	{
		RETURN_NULL_IF(src == nullptr || length == 0);
		RETURN_NULL_IF(val == nullptr || valLength == 0);

		char firstChar = *val;
		--valLength;
		while (true)
		{
			const T* firstMatch = FindFirstChar(src, length, firstChar);
			RETURN_NULL_IF_NULL(firstMatch);
			length -= firstMatch - src + 1;
			src = firstMatch + 1;
			if (length < valLength)
			{
				return nullptr;	//not enough size
			}

			if (CompareN(src, val + 1, valLength) == 0)
			{
				return src - 1;	//back one char
			}
		}
		return nullptr;
	}

	template<typename T>
	static const T* FindCharAny(const T* src, size_t length, const T* val, size_t valLength)
	{
		RETURN_NULL_IF(src == nullptr || length == 0);
		RETURN_NULL_IF(val == nullptr || valLength == 0);

		const T* end = src + length;
		while (src != end)
		{
			if (FindFirstChar(val, valLength, *src) != nullptr)
			{
				return src;
			}
			++src;
		}
		return nullptr;

	}

	//Get span of character set in string.	strspn("129th","1234567890")==3
	static size_t StringSpan(const char* str, const char* set) { return strspn(str, set); }
	static size_t StringSpan(const wchar_t* str, const wchar_t* set) { return wcsspn(str, set); }


	//Get span until character in string.	strcspn("fcba73","1234567890")==4
	static size_t StringReverseSpan(const char* str, const char* set) { return strcspn(str, set); }
	static size_t StringReverseSpan(const wchar_t* str, const wchar_t* set) { return wcscspn(str, set); }


	static long ToInt(const char* src, char** endPtr, int base) { return ::strtol(src, endPtr, base); }
	static long ToInt(const wchar_t* src, wchar_t** endPtr, int base) { return ::wcstol(src, endPtr, base); }

	static ulong ToUInt(const char* src, char** endPtr, int base) { return ::strtoul(src, endPtr, base); }
	static ulong ToUInt(const wchar_t* src, wchar_t** endPtr, int base) { return ::wcstoul(src, endPtr, base); }


	static double ToDouble(const char* src, char** endPtr) { return ::strtod(src, endPtr); }
	static double ToDouble(const wchar_t* src, wchar_t** endPtr) { return ::wcstod(src, endPtr); }

#ifdef MEDUSA_WINDOWS
	static char* SplitString(char* dest, const char* delim, char** context) { return ::strtok_s(dest, delim, context); }
	static wchar_t* SplitString(wchar_t* dest, const wchar_t* delim, wchar_t** context) { return ::wcstok_s(dest, delim, context); }

	// errno_t SplitString(wchar_t* dest, size_t destSize, const wchar_t* src){ return ::wcscpy_s(dest, destSize, src); }

	static errno_t CopyString(char* dest, size_t destSize, const char* src) { RETURN_OBJECT_IF_NULL(dest, -1); return ::strcpy_s(dest, destSize, src); }
	static errno_t CopyString(wchar_t* dest, size_t destSize, const wchar_t* src) { RETURN_OBJECT_IF_NULL(dest, -1); return ::wcscpy_s(dest, destSize, src); }

	static errno_t CopyStringN(char* dest, size_t destSize, const char* src, size_t count) { RETURN_OBJECT_IF_NULL(dest, -1); return ::strncpy_s(dest, destSize, src, count); }
	static errno_t CopyStringN(wchar_t* dest, size_t destSize, const wchar_t* src, size_t count) { RETURN_OBJECT_IF_NULL(dest, -1); return ::wcsncpy_s(dest, destSize, src, count); }

	static errno_t ToUpper(char* dest, size_t destSize) { RETURN_OBJECT_IF_NULL(dest, -1); return ::_strupr_s(dest, destSize); }
	static errno_t ToUpper(wchar_t* dest, size_t destSize) { RETURN_OBJECT_IF_NULL(dest, -1); return ::_wcsupr_s(dest, destSize); }

	static errno_t ToLower(char* dest, size_t destSize) { RETURN_OBJECT_IF_NULL(dest, -1); return ::_strlwr_s(dest, destSize); }
	static errno_t ToLower(wchar_t* dest, size_t destSize) { RETURN_OBJECT_IF_NULL(dest, -1); return ::_wcslwr_s(dest, destSize); }

	static errno_t ReplaceAllTo(char* dest, size_t destSize, char c) { RETURN_OBJECT_IF_NULL(dest, -1); return ::_strset_s(dest, destSize, c); }
	static errno_t ReplaceAllTo(wchar_t* dest, size_t destSize, wchar_t c) { RETURN_OBJECT_IF_NULL(dest, -1); return ::_wcsset_s(dest, destSize, c); }


	static errno_t ReplaceAllToN(char* dest, size_t destSize, char c, size_t count) { RETURN_OBJECT_IF_NULL(dest, -1); return ::_strnset_s(dest, destSize, c, count); }
	static errno_t ReplaceAllToN(wchar_t* dest, size_t destSize, wchar_t c, size_t count) { RETURN_OBJECT_IF_NULL(dest, -1); return ::_wcsnset_s(dest, destSize, c, count); }
#else
	static char* SplitString(char* dest, const char* delim, char** context) { RETURN_NULL_IF_NULL(dest); return ::strtok(dest, delim); }
	static wchar_t* SplitString(wchar_t* dest, const wchar_t* delim, wchar_t** context) { RETURN_NULL_IF_NULL(dest); return ::wcstok(dest, delim, context); }

	// wchar_t* SplitString(wchar_t* dest, size_t destSize, const wchar_t* src){ return ::wcscpy(dest, src); }

	static errno_t CopyString(char* dest, size_t destSize, const char* src) { RETURN_OBJECT_IF_NULL(dest, -1); ::strcpy(dest, src); return 0; }
	static errno_t CopyString(wchar_t* dest, size_t destSize, const wchar_t* src) { RETURN_OBJECT_IF_NULL(dest, -1); ::wcscpy(dest, src); return 0; }

	static errno_t CopyStringN(char* dest, size_t destSize, const char* src, size_t count) { RETURN_OBJECT_IF_NULL(dest, -1); ::strncpy(dest, src, count); return 0; }
	static errno_t CopyStringN(wchar_t* dest, size_t destSize, const wchar_t* src, size_t count) { RETURN_OBJECT_IF_NULL(dest, -1); ::wcsncpy(dest, src, count); return 0; }

	static errno_t ToUpper(char* dest, size_t destSize)
	{
		RETURN_OBJECT_IF_NULL(dest, -1);
		for (; dest; ++dest)
		{
			*dest = toupper(*dest);
		}
		return 0;
	}
	static errno_t ToUpper(wchar_t* dest, size_t destSize)
	{
		RETURN_OBJECT_IF_NULL(dest, -1);
		for (; dest; ++dest)
		{
			*dest = toupper(*dest);
		}
		return 0;
	}

	static errno_t ToLower(char* dest, size_t destSize)
	{
		RETURN_OBJECT_IF_NULL(dest, -1);
		for (; dest; ++dest)
		{
			*dest = tolower(*dest);
		}
		return 0;
	}
	static errno_t ToLower(wchar_t* dest, size_t destSize)
	{
		RETURN_OBJECT_IF_NULL(dest, -1);
		for (; dest; ++dest)
		{
			*dest = tolower(*dest);
		}
		return 0;
	}

	static errno_t ReplaceAllTo(char* dest, size_t destSize, char c)
	{
		RETURN_OBJECT_IF_NULL(dest, -1);
		Memory::Set(dest, c, destSize);
		return 0;
	}
	static errno_t ReplaceAllTo(wchar_t* dest, size_t destSize, wchar_t c) { RETURN_OBJECT_IF_NULL(dest, -1); Memory::Set(dest, c, destSize); return 0; }


	static errno_t ReplaceAllToN(char* dest, size_t destSize, char c, size_t count) { RETURN_OBJECT_IF_NULL(dest, -1); Memory::Set(dest, c, count); return 0; }
	static errno_t ReplaceAllToN(wchar_t* dest, size_t destSize, wchar_t c, size_t count) { RETURN_OBJECT_IF_NULL(dest, -1); Memory::Set(dest, c, count); return 0; }
#endif


	char* Reverse(char* dest);
	wchar_t* Reverse(wchar_t* dest);

#ifdef MEDUSA_WINDOWS
	static int VSPrintf(char* dest, size_t destSize, const char* format, va_list p) { return ::vsprintf_s(dest, destSize, format, p); }
	static int VSPrintf(wchar_t* dest, size_t destSize, const wchar_t* format, va_list p) { return ::vswprintf_s(dest, destSize, format, p); }
#else
	static int VSPrintf(char* dest, size_t destSize, const char* format, va_list p) { return ::vsprintf(dest, format, p); }
	static int VSPrintf(wchar_t* dest, size_t destSize, const wchar_t* format, va_list p) { return ::vswprintf(dest, destSize, format, p); }
#endif

#ifdef MEDUSA_WINDOWS
	static int VSNPrintf(char* dest, size_t destSize, size_t count, const char* format, va_list p) { return ::_vsnprintf_s(dest, destSize, count, format, p); }
	static int VSNPrintf(wchar_t* dest, size_t destSize, size_t count, const wchar_t* format, va_list p) { return ::_vsnwprintf_s(dest, destSize, count, format, p); }
#else
	static int VSNPrintf(char* dest, size_t destSize, size_t count, const char* format, va_list p) { return ::vsnprintf(dest, count, format, p); }
	static int VSNPrintf(wchar_t* dest, size_t destSize, size_t count, const wchar_t* format, va_list p) { return ::vswprintf(dest, count, format, p); }
#endif

#ifdef MEDUSA_WINDOWS
	static int GetFormatLength(const char* format, va_list p) { return ::_vscprintf(format, p); }
	static int GetFormatLength(const wchar_t* format, va_list p) { return ::_vscwprintf(format, p); }
#else
	static int GetFormatLength(const char* format, va_list p) { va_list args; va_copy(args, p); return ::vsnprintf(nullptr, 0, format, args); }
	static int GetFormatLength(const wchar_t* format, va_list p)
	{
		// Unlike vsnprintf(), vswprintf() does not tell you how many
		// characters would have been written if there was space enough in
		// the buffer - it just reports an error when there is not enough
		// space.  Assume a moderately large machine so kilobytes of wchar_t
		// on the stack is not a problem.
		int bufferSize = 128;
		const static int maxBufferSize = 1024 * 1024;

		do
		{
			va_list args;
			va_copy(args, p);
			wchar_t buffer[bufferSize];	//supported in C99
			int result = vswprintf(buffer, sizeof(buffer) / sizeof(buffer[0]), format, args);
			if (result >= 0)
				return result;
			bufferSize *= 2;
		} while (bufferSize < maxBufferSize);
		return -1;

	}
#endif


#ifdef MEDUSA_WINDOWS
	static int SPrintf(char* dest, size_t destSize, const char* format, ...)
	{
		va_list args;
		va_start(args, format);
		int result = ::vsprintf_s(dest, destSize, format, args);
		va_end(args);
		return result;
	}
	static int SPrintf(wchar_t* dest, size_t destSize, const wchar_t* format, ...)
	{
		va_list args;
		va_start(args, format);
		int result = ::vswprintf_s(dest, destSize, format, args);
		va_end(args);
		return result;
	}

#else
	static int SPrintf(char* dest, size_t destSize, const char* format, ...)
	{
		va_list args;
		va_start(args, format);
		int result = ::vsprintf(dest, format, args);
		va_end(args);
		return result;
	}
	static int SPrintf(wchar_t* dest, size_t destSize, const wchar_t* format, ...)
	{
		va_list args;
		va_start(args, format);
		int result = ::vswprintf(dest, destSize, format, args);
		va_end(args);
		return result;
	}

#endif




	template<typename T>
	struct ConstValues;	//[IGNORE_PRE_DECLARE]


	template<>
	struct ConstValues < char >//[IGNORE_PRE_DECLARE]
	{
		static bool IsNewLine(char c) { return c == Return || c == LineSeparator; }
		static bool IsEmptyChar(char c) { return c == Space || IsControlChar(c); }
		static bool IsControlChar(char c) { return c == Return || c == LineSeparator || c == Tab || c == '\f' || c == '\v'; }
		static bool IsPeriod(char c) { return c == '.' || c == '?' || c == '!' || c == ','; }

		constexpr static char Zero = '\0';
		constexpr static char Return = '\r';
		constexpr static char LineSeparator = '\n';
		constexpr static char Tab = '\t';
		constexpr static char Space = ' ';
		constexpr static char Hyphen = '-';
		constexpr static char Slash = '/';
		constexpr static char Backslash = '\\';

		constexpr static char OpenAngle = '<';
		constexpr static char CloseAngle = '>';
		constexpr static char Equal = '=';
		constexpr static char OpenBrace = '{';
		constexpr static char CloseBrace = '}';
		constexpr static char Comma = ',';
		constexpr static char Colon = ':';


		const static char TrimChars[];
		const static char Empty[];
		const static char WordSeparators[];
		const static char NewLineChars[];
		const static char TrueString[];
		const static char FalseString[];
		const static char TrueStringUppercase[];
		const static char FalseStringUppercase[];

		const static char HexUpperCase[16];
		const static char HexLowerCase[16];
		const static char Numbers[10];

	};

	template<>
	struct ConstValues < wchar_t >//[IGNORE_PRE_DECLARE]
	{
		static bool IsNewLine(wchar_t c) { return c == Return || c == LineSeparator; }
		static bool IsEmptyChar(wchar_t c) { return c == Space || IsControlChar(c); }
		static bool IsControlChar(wchar_t c) { return c == Return || c == LineSeparator || c == Tab || c == L'\f' || c == L'\v'; }
		static bool IsPeriod(wchar_t c) { return c == L'.' || c == L'?' || c == L'!' || c == L','|| c == L'¡£' || c == L'£¿' || c == L'£¡' || c == L'£¬'; }

		constexpr static wchar_t Zero = L'\0';
		constexpr static wchar_t Return = L'\r';
		constexpr static wchar_t LineSeparator = L'\n';
		constexpr static wchar_t Tab = L'\t';
		constexpr static wchar_t Space = L' ';
		constexpr static wchar_t Hyphen = L'-';
		constexpr static wchar_t Slash = L'/';
		constexpr static wchar_t Backslash = L'\\';

		constexpr static wchar_t OpenAngle = L'<';
		constexpr static wchar_t CloseAngle = L'>';
		constexpr static wchar_t Equal = L'=';
		constexpr static wchar_t OpenBrace = L'{';
		constexpr static wchar_t CloseBrace = L'}';
		constexpr static wchar_t Comma = L',';
		constexpr static wchar_t Colon = L':';

		const static wchar_t TrimChars[];
		const static wchar_t Empty[];
		const static wchar_t WordSeparators[];
		const static wchar_t NewLineChars[];
		const static wchar_t TrueString[];
		const static wchar_t FalseString[];
		const static wchar_t TrueStringUppercase[];
		const static wchar_t FalseStringUppercase[];

		const static wchar_t HexUpperCase[16];
		const static wchar_t HexLowerCase[16];

		const static wchar_t Numbers[10];

	};

	using Constants = ConstValues<char>;
	using WConstants = ConstValues<wchar_t>;


	template<typename T>
	static bool IsWordSeparator(T c)
	{
		static bool isInitialized = false;
		static BitArray<128> bitArray;
		if (!isInitialized)
		{
			bitArray.ClearZero();
			FOR_EACH_ARRAY(i, ConstValues<T>::WordSeparators)
			{
				bitArray.Set(ConstValues<T>::WordSeparators[i], true);
			}

			isInitialized = true;
		}

		return bitArray.Get(c);
	}


	static uint ParseUInt(const char* begin, char** next) { return (uint)strtoul(begin, next, 10); }
	static uint ParseUInt(const wchar_t* begin, wchar_t** next) { return (uint)wcstol(begin, next, 10); }

	template<size_t size>
	constexpr static size_t StaticLength(const char(&str)[size])
	{
		return size - 1;
	}
};





MEDUSA_END;
