// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Core/String/StringParser.h"
#include "CoreLib/Common/Unicode/ConvertUTF.h"
#include "CoreLib/Common/milo/itoa_milo.h"
#include "CoreLib/Common/milo/dtoa_milo.h"

MEDUSA_BEGIN;


template<typename TValue>
TValue StringParser::StringToT(const TStringRef<char>& inString, int base /*= 10*/)
{
	return StringTo<TValue>(inString, base);
}

template<typename TValue>
TValue StringParser::StringToT(const TStringRef<wchar_t>& inString, int base /*= 10*/)
{
	return WStringTo<TValue>(inString, base);
}



#pragma region A

template<>
StringParser::ResultString<char, bool> StringParser::ToStringTWithoutSign(const bool& inValue, bool& outSign)
{
	outSign = true;
	ResultString<char, bool> temp;
	temp[0] = inValue ? '1' : '0';
	temp[1] = '\0';
	temp.ForceSetLength(1);
	return temp;
}

template<>
StringParser::ResultString<char, char> StringParser::ToStringTWithoutSign(const char& inValue, bool& outSign)
{
	ResultString<char, char> temp;
	char* end = i32toa_branchlut_without_sign(inValue, temp.MutableBuffer(), outSign);
	temp.ForceSetLength(end - temp.Buffer());
	return temp;
}

template<>
StringParser::ResultString<char, wchar_t> StringParser::ToStringTWithoutSign(const wchar_t& inValue, bool& outSign)
{
	ResultString<char, wchar_t> temp;
	char* end = i32toa_branchlut_without_sign(inValue, temp.MutableBuffer(), outSign);
	temp.ForceSetLength(end - temp.Buffer());
	return temp;
}

template<>
StringParser::ResultString<char, byte> StringParser::ToStringTWithoutSign(const byte& inValue, bool& outSign)
{
	outSign = true;
	ResultString<char, byte> temp;
	char* end = i32toa_branchlut(inValue, temp.MutableBuffer());
	temp.ForceSetLength(end - temp.Buffer());
	return temp;
}

template<>
StringParser::ResultString<char, short> StringParser::ToStringTWithoutSign(const short& inValue, bool& outSign)
{
	ResultString<char, short> temp;
	char* end = i32toa_branchlut_without_sign(inValue, temp.MutableBuffer(), outSign);
	temp.ForceSetLength(end - temp.Buffer());
	return temp;
}

template<>
StringParser::ResultString<char, ushort> StringParser::ToStringTWithoutSign(const ushort& inValue, bool& outSign)
{
	outSign = true;
	ResultString<char, ushort> temp;
	char* end = i32toa_branchlut(inValue, temp.MutableBuffer());
	temp.ForceSetLength(end - temp.Buffer());
	return temp;
}

template<>
StringParser::ResultString<char, int> StringParser::ToStringTWithoutSign(const int& inValue, bool& outSign)
{
	ResultString<char, int32> temp;
	char* end = i32toa_branchlut_without_sign(inValue, temp.MutableBuffer(), outSign);
	temp.ForceSetLength(end - temp.Buffer());
	return temp;
}

template<>
StringParser::ResultString<char, uint> StringParser::ToStringTWithoutSign(const uint& inValue, bool& outSign)
{
	outSign = true;
	ResultString<char, uint> temp;
	char* end = i32toa_branchlut(inValue, temp.MutableBuffer());
	temp.ForceSetLength(end - temp.Buffer());
	return temp;
}

template<>
StringParser::ResultString<char, int64> StringParser::ToStringTWithoutSign(const int64& inValue, bool& outSign)
{
	ResultString<char, int64> temp;
	char* end = i64toa_branchlut_without_sign(inValue, temp.MutableBuffer(), outSign);
	temp.ForceSetLength(end - temp.Buffer());
	return temp;
}

template<>
StringParser::ResultString<char, uint64> StringParser::ToStringTWithoutSign(const uint64& inValue, bool& outSign)
{
	outSign = true;
	ResultString<char, uint64> temp;
	char* end = i64toa_branchlut(inValue, temp.MutableBuffer());
	temp.ForceSetLength(end - temp.Buffer());
	return temp;
}

template<>
StringParser::ResultString<char, float> StringParser::ToStringTWithoutSign(const float& inValue, bool& outSign)
{
	ResultString<char, float> temp;
	char* end = dtoa_milo_without_sign(inValue, temp.MutableBuffer(), outSign);
	temp.ForceSetLength(end - temp.Buffer());
	return temp;
}

template<>
StringParser::ResultString<char, double> StringParser::ToStringTWithoutSign(const double& inValue, bool& outSign)
{
	ResultString<char, double> temp;
	char* end = dtoa_milo_without_sign(inValue, temp.MutableBuffer(), outSign);
	temp.ForceSetLength(end - temp.Buffer());
	return temp;
}

#ifndef MEDUSA_X64
template<>
StringParser::ResultString<char, long> StringParser::ToStringTWithoutSign(const long& inValue, bool& outSign)
{
	ResultString<char, long> temp;
	char* end = i32toa_branchlut_without_sign(inValue, temp.MutableBuffer(), outSign);
	temp.ForceSetLength(end - temp.Buffer());
	return temp;
}
template<>
StringParser::ResultString<char, ulong> StringParser::ToStringTWithoutSign(const ulong& inValue, bool& outSign)
{
	outSign = true;
	ResultString<char, ulong> temp;
	char* end = i32toa_branchlut(inValue, temp.MutableBuffer());
	temp.ForceSetLength(end - temp.Buffer());
	return temp;
}

#else
template<>
StringParser::ResultString<char, long> StringParser::ToStringTWithoutSign(const long& inValue, bool& outSign)
{
	ResultString<char, long> temp;
	char* end = i64toa_branchlut_without_sign(inValue, temp.MutableBuffer(), outSign);
	temp.ForceSetLength(end - temp.Buffer());
	return temp;
}
template<>
StringParser::ResultString<char, ulong> StringParser::ToStringTWithoutSign(const ulong& inValue, bool& outSign)
{
	outSign = true;
	ResultString<char, ulong> temp;
	char* end = i64toa_branchlut(inValue, temp.MutableBuffer());
	temp.ForceSetLength(end - temp.Buffer());
	return temp;
}
#endif
#pragma endregion A

#pragma region W

template<>
StringParser::ResultString<wchar_t, bool> StringParser::ToStringTWithoutSign(const bool& inValue, bool& outSign)
{
	outSign = true;
	ResultString<wchar_t, bool> temp;
	temp[0] = inValue ? L'1' : L'0';
	temp[1] = L'\0';
	temp.ForceSetLength(1);
	return temp;
}

template<>
StringParser::ResultString<wchar_t, char> StringParser::ToStringTWithoutSign(const char& inValue, bool& outSign)
{
	ResultString<wchar_t, char> temp;
	wchar_t* end = i32toa_branchlut_without_sign(inValue, temp.MutableBuffer(), outSign);
	temp.ForceSetLength(end - temp.Buffer());
	return temp;
}

template<>
StringParser::ResultString<wchar_t, wchar_t> StringParser::ToStringTWithoutSign(const wchar_t& inValue, bool& outSign)
{
	ResultString<wchar_t, wchar_t> temp;
	wchar_t* end = i32toa_branchlut_without_sign(inValue, temp.MutableBuffer(), outSign);
	temp.ForceSetLength(end - temp.Buffer());
	return temp;
}


template<>
StringParser::ResultString<wchar_t, byte> StringParser::ToStringTWithoutSign(const byte& inValue, bool& outSign)
{
	outSign = true;
	ResultString<wchar_t, byte> temp;
	wchar_t* end = i32toa_branchlut(inValue, temp.MutableBuffer());
	temp.ForceSetLength(end - temp.Buffer());
	return temp;
}

template<>
StringParser::ResultString<wchar_t, short> StringParser::ToStringTWithoutSign(const short& inValue, bool& outSign)
{
	ResultString<wchar_t, short> temp;
	wchar_t* end = i32toa_branchlut_without_sign(inValue, temp.MutableBuffer(), outSign);
	temp.ForceSetLength(end - temp.Buffer());
	return temp;
}

template<>
StringParser::ResultString<wchar_t, ushort> StringParser::ToStringTWithoutSign(const ushort& inValue, bool& outSign)
{
	outSign = true;
	ResultString<wchar_t, ushort> temp;
	wchar_t* end = i32toa_branchlut(inValue, temp.MutableBuffer());
	temp.ForceSetLength(end - temp.Buffer());
	return temp;
}
template<>
StringParser::ResultString<wchar_t, int> StringParser::ToStringTWithoutSign(const int& inValue, bool& outSign)
{
	ResultString<wchar_t, int32> temp;
	wchar_t* end = i32toa_branchlut_without_sign(inValue, temp.MutableBuffer(), outSign);
	temp.ForceSetLength(end - temp.Buffer());
	return temp;
}

template<>
StringParser::ResultString<wchar_t, uint> StringParser::ToStringTWithoutSign(const uint& inValue, bool& outSign)
{
	outSign = true;
	ResultString<wchar_t, uint> temp;
	wchar_t* end = i32toa_branchlut(inValue, temp.MutableBuffer());
	temp.ForceSetLength(end - temp.Buffer());
	return temp;
}

template<>
StringParser::ResultString<wchar_t, int64> StringParser::ToStringTWithoutSign(const int64& inValue, bool& outSign)
{
	ResultString<wchar_t, int64> temp;
	wchar_t* end = i64toa_branchlut_without_sign(inValue, temp.MutableBuffer(), outSign);
	temp.ForceSetLength(end - temp.Buffer());
	return temp;
}

template<>
StringParser::ResultString<wchar_t, uint64> StringParser::ToStringTWithoutSign(const uint64& inValue, bool& outSign)
{
	outSign = true;
	ResultString<wchar_t, uint64> temp;
	wchar_t* end = i64toa_branchlut(inValue, temp.MutableBuffer());
	temp.ForceSetLength(end - temp.Buffer());
	return temp;
}

template<>
StringParser::ResultString<wchar_t, float> StringParser::ToStringTWithoutSign(const float& inValue, bool& outSign)
{
	ResultString<wchar_t, float> temp;
	wchar_t* end = dtoa_milo_without_sign(inValue, temp.MutableBuffer(), outSign);
	temp.ForceSetLength(end - temp.Buffer());
	return temp;
}


template<>
StringParser::ResultString<wchar_t, double> StringParser::ToStringTWithoutSign(const double& inValue, bool& outSign)
{
	ResultString<wchar_t, double> temp;
	wchar_t* end = dtoa_milo_without_sign(inValue, temp.MutableBuffer(), outSign);
	temp.ForceSetLength(end - temp.Buffer());
	return temp;
}

#ifndef MEDUSA_X64
template<>
StringParser::ResultString<wchar_t, long> StringParser::ToStringTWithoutSign(const long& inValue, bool& outSign)
{
	ResultString<wchar_t, long> temp;
	wchar_t* end = i32toa_branchlut_without_sign(inValue, temp.MutableBuffer(), outSign);
	temp.ForceSetLength(end - temp.Buffer());
	return temp;
}
template<>
StringParser::ResultString<wchar_t, ulong> StringParser::ToStringTWithoutSign(const ulong& inValue, bool& outSign)
{
	outSign = true;
	ResultString<wchar_t, ulong> temp;
	wchar_t* end = i32toa_branchlut(inValue, temp.MutableBuffer());
	temp.ForceSetLength(end - temp.Buffer());
	return temp;
}

#else
template<>
StringParser::ResultString<wchar_t, long> StringParser::ToStringTWithoutSign(const long& inValue, bool& outSign)
{
	ResultString<wchar_t, long> temp;
	wchar_t* end = i64toa_branchlut_without_sign(inValue, temp.MutableBuffer(), outSign);
	temp.ForceSetLength(end - temp.Buffer());
	return temp;
}
template<>
StringParser::ResultString<wchar_t, ulong> StringParser::ToStringTWithoutSign(const ulong& inValue, bool& outSign)
{
	outSign = true;
	ResultString<wchar_t, ulong> temp;
	wchar_t* end = i64toa_branchlut(inValue, temp.MutableBuffer());
	temp.ForceSetLength(end - temp.Buffer());
	return temp;
}
#endif
#pragma endregion W





#pragma region A

#pragma region StringTo
template<class TValue>
TValue StringParser::StringTo(const StringRef& inString, int base /*= 10*/)
{
	TValue result;
	return result;
}

template<>
StringRef StringParser::StringTo(const StringRef& inString, int base /*= 10*/)
{
	return inString;
}

template<>
HeapString StringParser::StringTo(const StringRef& inString, int base /*= 10*/)
{
	return HeapString(inString);
}


template<>
bool StringParser::StringTo(const StringRef& inString, int base /*= 10*/)
{
	if (inString.Length() != 4)
	{
		return false;
	}

	return inString.Compare("TRUE", true) == 0;
}


template<>
short StringParser::StringTo(const StringRef& inString, int base /*= 10*/)
{
	return (short)strtoul(inString.c_str(), nullptr, base);
}

template<>
ushort StringParser::StringTo(const StringRef& inString, int base /*= 10*/)
{
	return (ushort)strtoul(inString.c_str(), nullptr, base);
}


template<>
int32 StringParser::StringTo(const StringRef& inString, int base /*= 10*/)
{
	return (int32)strtoul(inString.c_str(), nullptr, base);
}

template<>
uint32 StringParser::StringTo(const StringRef& inString, int base /*= 10*/)
{
	return (uint32)strtoul(inString.c_str(), nullptr, base);
}

template<>
int64 StringParser::StringTo(const StringRef& inString, int base /*= 10*/)
{
	return strtoll(inString.c_str(), nullptr, base);
}

template<>
uint64 StringParser::StringTo(const StringRef& inString, int base /*= 10*/)
{
	return strtoull(inString.c_str(), nullptr, base);
}

#ifndef MEDUSA_X64
template<>
long StringParser::StringTo(const StringRef& inString, int base /*= 10*/)
{
	return (long)strtol(inString.c_str(), nullptr, base);
}

template<>
ulong StringParser::StringTo(const StringRef& inString, int base /*= 10*/)
{
	return (uint32)strtoul(inString.c_str(), nullptr, base);
}

#else
template<>
long StringParser::StringTo(const StringRef& inString, int base /*= 10*/)
{
	return (long)strtoll(inString.c_str(), nullptr, base);
}

template<>
ulong StringParser::StringTo(const StringRef& inString, int base /*= 10*/)
{
	return (ulong)strtoull(inString.c_str(), nullptr, base);
}
#endif



template<>
char StringParser::StringTo(const StringRef& inString, int base /*= 10*/)
{
	return (char)strtol(inString.c_str(), nullptr, base);
}

template<>
wchar_t StringParser::StringTo(const StringRef& inString, int base /*= 10*/)
{
	return (wchar_t)strtol(inString.c_str(), nullptr, base);
}

template<>
unsigned char StringParser::StringTo(const StringRef& inString, int base /*= 10*/)
{
	return (unsigned char)strtoul(inString.c_str(), nullptr, base);
}


template<>
float StringParser::StringTo(const StringRef& inString, int base /*= 10*/)
{
	return (float)strtod(inString.c_str(), nullptr);
}

template<>
double StringParser::StringTo(const StringRef& inString, int base /*= 10*/)
{
	return atof(inString.Buffer());
}

#pragma endregion StringTo

#pragma region ToString

template<>
StringParser::ResultString<char, bool> StringParser::ToString(const bool& inValue)
{
	return inValue ? StringParser::ResultString<char, bool>("true") : StringParser::ResultString<char, bool>("false");
}

template<>
StringParser::ResultString<char, char> StringParser::ToString(const char& inValue)
{
	ResultString<char, char> temp;
	temp[0] = inValue;
	temp[1] = '\0';
	temp.ForceSetLength(1);
	return temp;
}

template<>
StringParser::ResultString<char, byte> StringParser::ToString(const byte& inValue)
{
	ResultString<char, byte> temp;
	temp[0] = (char)inValue;
	temp[1] = '\0';
	temp.ForceSetLength(1);
	return temp;
}

template<>
StringParser::ResultString<char, short> StringParser::ToString(const short& inValue)
{
	ResultString<char, short> temp;
	char* end = i32toa_branchlut(inValue, temp.MutableBuffer());
	temp.ForceSetLength(end - temp.Buffer());
	return temp;
}
template<>
StringParser::ResultString<char, ushort> StringParser::ToString(const ushort& inValue)
{
	ResultString<char, ushort> temp;
	char* end = i32toa_branchlut(inValue, temp.MutableBuffer());
	temp.ForceSetLength(end - temp.Buffer());
	return temp;
}

template<>
StringParser::ResultString<char, int32> StringParser::ToString(const int32& inValue)
{
	ResultString<char, int32> temp;
	char* end = i32toa_branchlut(inValue, temp.MutableBuffer());
	temp.ForceSetLength(end - temp.Buffer());
	return temp;
}

template<>
StringParser::ResultString<char, uint32> StringParser::ToString(const uint32& inValue)
{
	ResultString<char, uint32> temp;
	char* end = u32toa_branchlut(inValue, temp.MutableBuffer());
	temp.ForceSetLength(end - temp.Buffer());
	return temp;
}


template<>
StringParser::ResultString<char, int64> StringParser::ToString(const int64& inValue)
{
	ResultString<char, int64> temp;
	char* end = i64toa_branchlut(inValue, temp.MutableBuffer());
	temp.ForceSetLength(end - temp.Buffer());
	return temp;
}

template<>
StringParser::ResultString<char, uint64> StringParser::ToString(const uint64& inValue)
{
	ResultString<char, uint64> temp;
	char* end = u64toa_branchlut(inValue, temp.MutableBuffer());
	temp.ForceSetLength(end - temp.Buffer());
	return temp;
}


#ifndef MEDUSA_X64
template<>
StringParser::ResultString<char, long> StringParser::ToString(const long& inValue)
{
	ResultString<char, long> temp;
	char* end = i32toa_branchlut(inValue, temp.MutableBuffer());
	temp.ForceSetLength(end - temp.Buffer());
	return temp;
}

template<>
StringParser::ResultString<char, ulong> StringParser::ToString(const ulong& inValue)
{
	ResultString<char, ulong> temp;
	char* end = u32toa_branchlut(inValue, temp.MutableBuffer());
	temp.ForceSetLength(end - temp.Buffer());
	return temp;
}

#else
template<>
StringParser::ResultString<char, long> StringParser::ToString(const long& inValue)
{
	ResultString<char, long> temp;
	char* end = i64toa_branchlut(inValue, temp.MutableBuffer());
	temp.ForceSetLength(end - temp.Buffer());
	return temp;
}

template<>
StringParser::ResultString<char, ulong> StringParser::ToString(const ulong& inValue)
{
	ResultString<char, ulong> temp;
	char* end = u64toa_branchlut(inValue, temp.MutableBuffer());
	temp.ForceSetLength(end - temp.Buffer());
	return temp;
}
#endif




template<>
StringParser::ResultString<char, float> StringParser::ToString(const float& inValue)
{
	ResultString<char, float> temp;
	char* end = dtoa_milo(inValue, temp.MutableBuffer());
	temp.ForceSetLength(end - temp.Buffer());
	return temp;
}

template<>
StringParser::ResultString<char, double> StringParser::ToString(const double& inValue)
{
	ResultString<char, double> temp;
	char* end = dtoa_milo(inValue, temp.MutableBuffer());
	temp.ForceSetLength(end - temp.Buffer());
	return temp;
}


template<class TValue>
StringParser::ResultString<char, TValue> StringParser::ToString(const TValue& inValue)
{
	return ResultString<char, TValue>("");
}


#pragma endregion ToString

/*
bool StringParser::EncodeString(const StringRef& fromString, HeapString& toString, const char* fromCode, const char* toCode)
{
	RETURN_TRUE_IF_EMPTY(fromString);
	iconv_t iconvH;
	iconvH = iconv_open(fromCode, toCode);
	if (iconvH == 0)
	{
		return false;
	}

	//#ifdef MEDUSA_WINDOWS

	char* strChar = (char*)fromString.c_str();
	char** pin = &strChar;
	size_t strLength = fromString.Length();
	char* outbuf = (char*)malloc(strLength * 4);
	char* pBuff = outbuf;
	memset(outbuf, 0, strLength * 4);
	size_t outLength = strLength * 4;
#if defined(MEDUSA_IOS)||defined(MEDUSA_ANDROID)||defined(MEDUSA_LINUX)
	if (-1 == iconv(iconvH, pin, &strLength, &outbuf, &outLength))
#else
	if (-1 == iconv(iconvH, (const char**)pin, &strLength, &outbuf, &outLength))
#endif

	{
		SAFE_FREE(pBuff);
		iconv_close(iconvH);
		return false;
	}
	toString = pBuff;
	iconv_close(iconvH);

	SAFE_FREE(pBuff);
	//#endif
	return true;
}

bool StringParser::GBKToUTF8(const StringRef& fromString, HeapString& toString)
{
	return EncodeString(fromString, toString, "gb2312", "utf-8");
}

bool StringParser::UTF8ToGBK(const StringRef& fromString, HeapString& toString)
{
	return EncodeString(fromString, toString, "utf-8", "gb2312");
}

bool StringParser::UTF16ToGBK(const StringRef& fromString, HeapString& toString)
{
	return EncodeString(fromString, toString, "utf-16", "gb2312");
}

*/
#pragma endregion A

#pragma region W

#pragma region WStringTo

template<class TValue>
TValue StringParser::WStringTo(const WStringRef& inString, int base /*= 10*/)
{
	TValue result;
	return result;
}

template<>
WStringRef StringParser::WStringTo(const WStringRef& inString, int base /*= 10*/)
{
	return inString;
}

template<>
WHeapString StringParser::WStringTo(const WStringRef& inString, int base /*= 10*/)
{
	return WHeapString(inString);
}

template<>
bool StringParser::WStringTo(const WStringRef& inString, int base /*= 10*/)
{
	if (inString.Length() != 4)
	{
		return false;
	}

	return inString.Compare(L"TRUE", true) == 0;
}

template<>
int32 StringParser::WStringTo(const WStringRef& inString, int base /*= 10*/)
{
	return (int32)wcstol(inString.Buffer(), nullptr, base);
}

template<>
uint32 StringParser::WStringTo(const WStringRef& inString, int base /*= 10*/)
{
	return (uint32)wcstoul(inString.c_str(), nullptr, base);
}

template<>
int64 StringParser::WStringTo(const WStringRef& inString, int base /*= 10*/)
{
#ifdef MEDUSA_WINDOWS
	return _wcstoi64(inString.c_str(), nullptr, base);
#endif
#ifdef MEDUSA_IOS
	return wcstoll(inString.c_str(), nullptr, base);
#endif

#ifdef MEDUSA_ANDROID
	std::wstringstream ss;
	ss << inString.c_str();
	int64 r;
	ss >> r;
	return r;
#endif

}

template<>
uint64 StringParser::WStringTo(const WStringRef& inString, int base /*= 10*/)
{
#ifdef MEDUSA_WINDOWS
	return _wcstoui64(inString.c_str(), nullptr, base);
#endif
#ifdef MEDUSA_IOS
	return wcstoull(inString.c_str(), nullptr, base);
#endif

#ifdef MEDUSA_ANDROID
	std::wstringstream ss;
	ss << inString.c_str();
	uint64 r;
	ss >> r;
	return r;
#endif

}

#ifndef MEDUSA_X64
template<>
long StringParser::WStringTo(const WStringRef& inString, int base /*= 10*/)
{
	return (long)wcstol(inString.Buffer(), nullptr, base);
}

template<>
ulong StringParser::WStringTo(const WStringRef& inString, int base /*= 10*/)
{
	return (ulong)wcstoul(inString.c_str(), nullptr, base);
}
#else
template<>
long StringParser::WStringTo(const WStringRef& inString, int base /*= 10*/)
{
#ifdef MEDUSA_WINDOWS
	return (long)_wcstoi64(inString.c_str(), nullptr, base);
#else
	return wcstoll(inString.c_str(), nullptr, base);
#endif

}

template<>
ulong StringParser::WStringTo(const WStringRef& inString, int base /*= 10*/)
{
#ifdef MEDUSA_WINDOWS
	return (ulong)_wcstoui64(inString.c_str(), nullptr, base);
#else
	return wcstoull(inString.c_str(), nullptr, base);
#endif

}
#endif



template<>
char StringParser::WStringTo(const WStringRef& inString, int base /*= 10*/)
{
	return (char)wcstol(inString.c_str(), nullptr, base);
}

template<>
wchar_t StringParser::WStringTo(const WStringRef& inString, int base /*= 10*/)
{
	return (wchar_t)wcstol(inString.c_str(), nullptr, base);
}

template<>
unsigned char StringParser::WStringTo(const WStringRef& inString, int base /*= 10*/)
{
	return (unsigned char)wcstol(inString.c_str(), nullptr, base);
}

template<>
short StringParser::WStringTo(const WStringRef& inString, int base /*= 10*/)
{
	return (short)wcstol(inString.c_str(), nullptr, base);
}

template<>
ushort StringParser::WStringTo(const WStringRef& inString, int base /*= 10*/)
{
	return (ushort)wcstol(inString.c_str(), nullptr, base);
}

template<>
float StringParser::WStringTo(const WStringRef& inString, int base /*= 10*/)
{
	return (float)wcstod(inString.c_str(), nullptr);
}

template<>
double StringParser::WStringTo(const WStringRef& inString, int base /*= 10*/)
{
	return (float)wcstod(inString.c_str(), nullptr);
}


#pragma endregion WStringTo

#pragma region ToWString

template<>
StringParser::ResultString<wchar_t, bool> StringParser::ToWString(const bool& inValue)
{
	return inValue ? ResultString<wchar_t, bool>(L"true") : ResultString<wchar_t, bool>(L"false");
}

template<>
StringParser::ResultString<wchar_t, char> StringParser::ToWString(const char& inValue)
{
	ResultString<wchar_t, char> temp;
	temp[0] = inValue;
	temp[1] = '\0';
	temp.ForceSetLength(1);
	return temp;
}

template<>
StringParser::ResultString<wchar_t, byte> StringParser::ToWString(const byte& inValue)
{
	ResultString<wchar_t, byte> temp;
	temp[0] = (wchar_t)inValue;
	temp[1] = '\0';
	temp.ForceSetLength(1);
	return temp;
}

template<>
StringParser::ResultString<wchar_t, short> StringParser::ToWString(const short& inValue)
{
	ResultString<wchar_t, short> temp;
	wchar_t* end = i32toa_branchlut(inValue, temp.MutableBuffer());
	temp.ForceSetLength(end - temp.Buffer());
	return temp;
}

template<>
StringParser::ResultString<wchar_t, ushort> StringParser::ToWString(const ushort& inValue)
{
	ResultString<wchar_t, ushort> temp;
	wchar_t* end = i32toa_branchlut(inValue, temp.MutableBuffer());
	temp.ForceSetLength(end - temp.Buffer());
	return temp;
}


template<>
StringParser::ResultString<wchar_t, int32> StringParser::ToWString(const int32& inValue)
{
	ResultString<wchar_t, int32> temp;
	wchar_t* end = i32toa_branchlut(inValue, temp.MutableBuffer());
	temp.ForceSetLength(end - temp.Buffer());
	return temp;
}

template<>
StringParser::ResultString<wchar_t, uint32> StringParser::ToWString(const uint32& inValue)
{
	ResultString<wchar_t, uint32> temp;
	wchar_t* end = u32toa_branchlut(inValue, temp.MutableBuffer());
	temp.ForceSetLength(end - temp.Buffer());
	return temp;
}


template<>
StringParser::ResultString<wchar_t, int64> StringParser::ToWString(const int64& inValue)
{
	ResultString<wchar_t, int64> temp;
	wchar_t* end = i64toa_branchlut(inValue, temp.MutableBuffer());
	temp.ForceSetLength(end - temp.Buffer());
	return temp;
}

template<>
StringParser::ResultString<wchar_t, uint64> StringParser::ToWString(const uint64& inValue)
{
	ResultString<wchar_t, uint64> temp;
	wchar_t* end = u64toa_branchlut(inValue, temp.MutableBuffer());
	temp.ForceSetLength(end - temp.Buffer());
	return temp;
}


#ifndef MEDUSA_X64
template<>
StringParser::ResultString<wchar_t, long> StringParser::ToWString(const long& inValue)
{
	ResultString<wchar_t, long> temp;
	wchar_t* end = i32toa_branchlut(inValue, temp.MutableBuffer());
	temp.ForceSetLength(end - temp.Buffer());
	return temp;
}

template<>
StringParser::ResultString<wchar_t, ulong> StringParser::ToWString<ulong>(const ulong& inValue)
{
	ResultString<wchar_t, ulong> temp;
	wchar_t* end = u32toa_branchlut(inValue, temp.MutableBuffer());
	temp.ForceSetLength(end - temp.Buffer());
	return temp;
}

#else
template<>
StringParser::ResultString<wchar_t, long> StringParser::ToWString(const long& inValue)
{
	ResultString<wchar_t, long> temp;
	wchar_t* end = i64toa_branchlut(inValue, temp.MutableBuffer());
	temp.ForceSetLength(end - temp.Buffer());
	return temp;
}

template<>
StringParser::ResultString<wchar_t, ulong> StringParser::ToWString<ulong>(const ulong& inValue)
{
	ResultString<wchar_t, ulong> temp;
	wchar_t* end = u64toa_branchlut(inValue, temp.MutableBuffer());
	temp.ForceSetLength(end - temp.Buffer());
	return temp;
}


#endif


template<>
StringParser::ResultString<wchar_t, float> StringParser::ToWString(const float& inValue)
{
	ResultString<wchar_t, float> temp;
	wchar_t* end = dtoa_milo(inValue, temp.MutableBuffer());
	temp.ForceSetLength(end - temp.Buffer());
	return temp;
}

template<>
StringParser::ResultString<wchar_t, double> StringParser::ToWString(const double& inValue)
{
	ResultString<wchar_t, double> temp;
	wchar_t* end = dtoa_milo(inValue, temp.MutableBuffer());
	temp.ForceSetLength(end - temp.Buffer());
	return temp;

}

template<class TValue>
StringParser::ResultString<wchar_t, TValue> StringParser::ToWString(const TValue& inValue)
{
	return ResultString<wchar_t, TValue>(L"");
}


#pragma endregion ToString


#pragma endregion W




intp StringParser::ConvertToBuffer(const StringRef& inBuffer, WHeapString& outBuffer)
{
	return ConvertToBuffer(inBuffer.Buffer(), inBuffer.Length(), outBuffer);
}

intp StringParser::ConvertToBuffer(const char* str, size_t length, WHeapString& outBuffer)
{
	outBuffer.Clear();
	if (length == 0)
	{
		return 0;
	}

	outBuffer.ReserveSize(length + 1);
	const UTF8* sourceStart = reinterpret_cast<const UTF8*>(str);
	const UTF8* sourceEnd = sourceStart + length;
	constexpr bool isUTF16 = sizeof(wchar_t) == 2;
	if (isUTF16)
	{
		UTF16* targetStart = reinterpret_cast<UTF16*>(outBuffer.MutableBuffer());
		UTF16* targetEnd = targetStart + length;
		ConversionResult res = ConvertUTF8toUTF16(&sourceStart, sourceEnd, &targetStart, targetEnd, strictConversion);
		*targetStart = 0;
		if (res == conversionOK)
		{
			intp count = targetStart - reinterpret_cast<UTF16*>(outBuffer.MutableBuffer());
			outBuffer.ForceSetLength(count);
			return count;
		}
	}
	else
	{
		UTF32* targetStart = reinterpret_cast<UTF32*>(outBuffer.MutableBuffer());
		UTF32* targetEnd = targetStart + length;
		ConversionResult res = ConvertUTF8toUTF32(&sourceStart, sourceEnd, &targetStart, targetEnd, strictConversion);
		*targetStart = 0;
		if (res == conversionOK)
		{
			intp count = targetStart - reinterpret_cast<UTF32*>(outBuffer.MutableBuffer());
			outBuffer.ForceSetLength(count);
			return count;
		}
	}

	return 0;

}

intp StringParser::ConvertToBuffer(const WStringRef& inBuffer, HeapString& outBuffer)
{
	return ConvertToBuffer(inBuffer.Buffer(), inBuffer.Length(), outBuffer);
}


intp StringParser::ConvertToBuffer(const wchar_t* str, size_t length, HeapString& outBuffer)
{
	outBuffer.Clear();
	if (length == 0)
	{
		return 0;
	}


	constexpr bool isUTF16 = sizeof(wchar_t) == 2;
	if (isUTF16)
	{
		//sizeof(wchar_t)==2
		size_t utf8Size = length * 3 + 1;
		outBuffer.ReserveSize(utf8Size);

		const UTF16* sourceStart = reinterpret_cast<const UTF16*>(str);
		const UTF16* sourceEnd = sourceStart + length;
		UTF8* targetStart = reinterpret_cast<UTF8*>(outBuffer.MutableBuffer());
		UTF8* targetEnd = targetStart + utf8Size;
		ConversionResult res = ConvertUTF16toUTF8(&sourceStart, sourceEnd, &targetStart, targetEnd, strictConversion);
		*targetStart = 0;
		if (res == conversionOK)
		{
			intp count = targetStart - reinterpret_cast<UTF8*>(outBuffer.MutableBuffer());
			outBuffer.ForceSetLength(count);
			return count;
		}
	}
	else
	{
		//sizeof(wchar_t)==4
		size_t utf8Size = length * 4 + 1;
		outBuffer.ReserveSize(utf8Size);

		const UTF32* sourceStart = reinterpret_cast<const UTF32*>(str);
		const UTF32* sourceEnd = sourceStart + length;
		UTF8* targetStart = reinterpret_cast<UTF8*>(outBuffer.MutableBuffer());
		UTF8* targetEnd = targetStart + utf8Size;
		ConversionResult res = ConvertUTF32toUTF8(&sourceStart, sourceEnd, &targetStart, targetEnd, strictConversion);
		*targetStart = 0;
		if (res == conversionOK)
		{
			intp count = targetStart - reinterpret_cast<UTF8*>(outBuffer.MutableBuffer());
			outBuffer.ForceSetLength(count);
			return count;
		}
	}

	return 0;
}

HeapString StringParser::ToA(const WStringRef& str)
{
	HeapString tempBuffer;
	ConvertToBuffer(str.c_str(), str.Length(), tempBuffer);
	return tempBuffer;
}

WHeapString StringParser::ToW(const StringRef& str)
{
	WHeapString tempBuffer;
	ConvertToBuffer(str.c_str(), str.Length(), tempBuffer);
	return tempBuffer;
}


MEDUSA_END;
