// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "StdString.h"

MEDUSA_BEGIN;

#define MEDUSA_STRING_ALL(str,func) while (*str != '\0') { if (func(*str) == 0) { return false; }++str; }return true;
namespace StdString
{
	bool IsDigit(const char* str)
	{
		RETURN_FALSE_IF_NULL(str);
		MEDUSA_STRING_ALL(str, isdigit);
	}

	bool IsDigit(const wchar_t* str)
	{
		RETURN_FALSE_IF_NULL(str);
		MEDUSA_STRING_ALL(str, isdigit);
	}

	bool IsXDigit(const char* str)
	{
		RETURN_FALSE_IF_NULL(str);
		MEDUSA_STRING_ALL(str, isxdigit);
	}

	bool IsXDigit(const wchar_t* str)
	{
		RETURN_FALSE_IF_NULL(str);
		MEDUSA_STRING_ALL(str, isxdigit);
	}

	bool IsAlpha(const char* str)
	{
		RETURN_FALSE_IF_NULL(str);
		MEDUSA_STRING_ALL(str, isalpha);
	}

	bool IsAlpha(const wchar_t* str)
	{
		RETURN_FALSE_IF_NULL(str);
		MEDUSA_STRING_ALL(str, isalpha);
	}

	bool IsLower(const char* str)
	{
		RETURN_FALSE_IF_NULL(str);
		MEDUSA_STRING_ALL(str, islower);
	}

	bool IsLower(const wchar_t* str)
	{
		RETURN_FALSE_IF_NULL(str);
		MEDUSA_STRING_ALL(str, islower);
	}

	bool IsUpper(const char* str)
	{
		RETURN_FALSE_IF_NULL(str);
		MEDUSA_STRING_ALL(str, isupper);
	}

	bool IsUpper(const wchar_t* str)
	{
		RETURN_FALSE_IF_NULL(str);
		MEDUSA_STRING_ALL(str, isupper);
	}


	wchar_t* Reverse(wchar_t* dest)
	{
		RETURN_NULL_IF_NULL(dest);
		wchar_t *start = dest;
		wchar_t *left = dest;
		wchar_t ch;

		while (*dest++);                 /* find end of string */

		dest -= 2;

		while (left < dest)
		{
			ch = *left;
			*left++ = *dest;
			*dest-- = ch;
		}

		return(start);
	}

	char* Reverse(char* dest)
	{
		RETURN_NULL_IF_NULL(dest);
		char *start = dest;
		char *left = dest;
		char ch;

		while (*dest++);                 /* find end of string */

		dest -= 2;

		while (left < dest)
		{
			ch = *left;
			*left++ = *dest;
			*dest-- = ch;
		}

		return(start);
	}

	int CompareNIgnoreCase(const wchar_t* first, const wchar_t* last, size_t count)
	{
		wchar_t f, l;
		int result = 0;

		if (count)
		{
			do
			{
				f = (wchar_t)tolower(*first);
				l = (wchar_t)tolower(*last);
				first++;
				last++;
			} while ((--count) && f && (f == l));

			result = (int)(f - l);
		}
		return result;
		//return ::_wcsnicmp(src,dst,count);
	}

	int CompareNIgnoreCase(const char* first, const char* last, size_t count)
	{
		if (count)
		{
			int f = 0;
			int l = 0;

			do
			{

				if (((f = (unsigned char)(*(first++))) >= 'A') &&
					(f <= 'Z'))
					f -= 'A' - 'a';

				if (((l = (unsigned char)(*(last++))) >= 'A') &&
					(l <= 'Z'))
					l -= 'A' - 'a';

			} while (--count && f && (f == l));

			return (f - l);
		}
		else
		{
			return 0;
		}
		//return ::_strnicmp(src,dst,count);
	}

	int CompareIgnoreCase(const wchar_t* dst, const wchar_t* src)
	{
		wchar_t f, l;
		do
		{
			f = (wchar_t)tolower(*dst);
			l = (wchar_t)tolower(*src);
			dst++;
			src++;
		} while ((f) && (f == l));
		return (int)(f - l);
	}

	int CompareIgnoreCase(const char* dst, const char* src)
	{
		int f, l;

		do
		{
			if (((f = (unsigned char)(*(dst++))) >= 'A') && (f <= 'Z'))
				f -= 'A' - 'a';
			if (((l = (unsigned char)(*(src++))) >= 'A') && (l <= 'Z'))
				l -= 'A' - 'a';
		} while (f && (f == l));

		return(f - l);
	}


	//we have to add definition for constexpr,or it'll cause "Undefined symbols" error when linking
	constexpr char ConstValues<char>::Zero;
	constexpr char ConstValues<char>::Return;
	constexpr char ConstValues<char>::LineSeparator;
	constexpr char ConstValues<char>::Tab;
	constexpr char ConstValues<char>::Space;
	constexpr char ConstValues<char>::Hyphen;
	constexpr char ConstValues<char>::Slash;
	constexpr char ConstValues<char>::Backslash;

	constexpr char ConstValues<char>::OpenAngle;
	constexpr char ConstValues<char>::CloseAngle;
	constexpr char ConstValues<char>::Equal;
	constexpr char ConstValues<char>::OpenBrace;
	constexpr char ConstValues<char>::CloseBrace;
	constexpr char ConstValues<char>::Comma;
	constexpr char ConstValues<char>::Colon;

	const char ConstValues<char>::TrimChars[] = " \t\r\n\v\f\r";
	const char ConstValues<char>::Empty[] = "";
	const char ConstValues<char>::WordSeparators[] = " \t\r\n\v\f";
	const char ConstValues<char>::NewLineChars[] = "\r\n";
	const char ConstValues<char>::TrueString[] = "true";
	const char ConstValues<char>::FalseString[] = "false";
	const char ConstValues<char>::TrueStringUppercase[] = "TRUE";
	const char ConstValues<char>::FalseStringUppercase[] = "FALSE";
	const char ConstValues<char>::HexUpperCase[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
	const char ConstValues<char>::HexLowerCase[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };


	//we have to add definition for constexpr,or it'll cause "Undefined symbols" error when linking
	constexpr wchar_t ConstValues<wchar_t>::Zero;
	constexpr wchar_t ConstValues<wchar_t>::Return;
	constexpr wchar_t ConstValues<wchar_t>::LineSeparator;
	constexpr wchar_t ConstValues<wchar_t>::Tab;
	constexpr wchar_t ConstValues<wchar_t>::Space;
	constexpr wchar_t ConstValues<wchar_t>::Hyphen;
	constexpr wchar_t ConstValues<wchar_t>::Slash;
	constexpr wchar_t ConstValues<wchar_t>::Backslash;

	constexpr wchar_t ConstValues<wchar_t>::OpenAngle;
	constexpr wchar_t ConstValues<wchar_t>::CloseAngle;
	constexpr wchar_t ConstValues<wchar_t>::Equal;
	constexpr wchar_t ConstValues<wchar_t>::OpenBrace;
	constexpr wchar_t ConstValues<wchar_t>::CloseBrace;
	constexpr wchar_t ConstValues<wchar_t>::Comma;
	constexpr wchar_t ConstValues<wchar_t>::Colon;

	const wchar_t ConstValues<wchar_t>::TrimChars[] = L" \t\r\n\v\f\r\x0085\x00a0";
	const wchar_t ConstValues<wchar_t>::Empty[] = L"";
	const wchar_t ConstValues<wchar_t>::WordSeparators[] = L" \t\r\n\v\f";
	const wchar_t ConstValues<wchar_t>::NewLineChars[] = L"\r\n";
	const wchar_t ConstValues<wchar_t>::TrueString[] = L"true";
	const wchar_t ConstValues<wchar_t>::FalseString[] = L"false";
	const wchar_t ConstValues<wchar_t>::TrueStringUppercase[] = L"TRUE";
	const wchar_t ConstValues<wchar_t>::FalseStringUppercase[] = L"FALSE";
	const wchar_t ConstValues<wchar_t>::HexUpperCase[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
	const wchar_t ConstValues<wchar_t>::HexLowerCase[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

}


#undef MEDUSA_STRING_ALL

MEDUSA_END;