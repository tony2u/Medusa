// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "MedusaCorePreDeclares.h"
#include "Core/String/TStringRef.h"
#include "Core/String/THeapString.h"
#include "Core/String/TStackString.h"
#include "Core/String/StdString.h"


MEDUSA_BEGIN;

namespace StringParser
{
	template<typename TChar, class TValue>
	using ResultString = TStackString<TChar, Compile::DefaultDigitWidth<TValue>::value, false>;

	template<typename TChar, class TValue>
	using HexResultString = TStackString<TChar, Compile::HexDigitWidth<TValue>::value, false>;

	template<class TValue>
	TValue StringToT(const TStringRef<char>& inString, int base = 10);

	template<class TValue>
	TValue StringToT(const TStringRef<wchar_t>& inString, int base = 10);



	template<typename TChar, class TValue>
	StringParser::ResultString<TChar, TValue> ToStringTWithoutSign(const TValue& inValue, bool& outSign);
#pragma region A
	template<class TValue>
	TValue StringTo(const StringRef& inString, int base = 10);

	template<class TValue>
	StringParser::ResultString<char, TValue> ToString(const TValue& inValue);

	long ToInt(const StringRef& str);
	bool TryParseInt(const StringRef& str, long& outVal);
	ulong ToUInt(const StringRef& str);
	bool TryParseUInt(const StringRef& str, ulong& outVal);


	/*
	 bool GBKToUTF8(const StringRef& fromString, HeapString& toString);
	 bool UTF8ToGBK(const StringRef& fromString, HeapString& toString);
	 bool UTF16ToGBK(const StringRef& fromString, HeapString& toString);
	 bool EncodeString(const StringRef& fromString, HeapString& toString, const char* fromCode, const char* toCode);
	*/
#pragma endregion A

#pragma region W

	template<class TValue>
	TValue WStringTo(const WStringRef& inString, int base = 10);

	template<class TValue>
	ResultString<wchar_t, TValue> ToWString(const TValue& inValue);

#pragma endregion W

	template<typename TChar, class TValue>
	typename std::enable_if<std::is_same<TChar, char>::value, StringParser::ResultString<TChar, TValue>>::type ToStringT(const TValue& inValue)
	{
		return StringParser::ToString(inValue);
	}

	template<typename TChar>
	typename std::enable_if<std::is_same<TChar, char>::value, HeapString>::type ToStringT(const HeapString& val)
	{
		return val;
	}

	template<typename TChar>
	typename std::enable_if<std::is_same<TChar, char>::value, HeapString>::type ToStringT(const WHeapString& val)
	{
		return ToA(val);
	}


	template<typename TChar, class TValue>
	typename std::enable_if<std::is_same<TChar, wchar_t>::value, StringParser::ResultString<TChar, TValue>>::type ToStringT(const TValue& inValue)
	{
		return StringParser::ToWString(inValue);
	}

	template<typename TChar>
	typename std::enable_if<std::is_same<TChar, wchar_t>::value, WHeapString>::type ToStringT(const HeapString& val)
	{
		return ToW(val);
	}

	template<typename TChar>
	typename std::enable_if<std::is_same<TChar, wchar_t>::value, WHeapString>::type ToStringT(const WHeapString& val)
	{
		return val;
	}


	intp ConvertToBuffer(const StringRef& inBuffer, WHeapString& outBuffer);
	intp ConvertToBuffer(const char* str, size_t length, WHeapString& outBuffer);

	intp ConvertToBuffer(const WStringRef& inBuffer, HeapString& outBuffer);
	intp ConvertToBuffer(const wchar_t* str, size_t length, HeapString& outBuffer);

	HeapString ToA(const WStringRef& str);
	WHeapString ToW(const StringRef& str);


	template<typename T>
	bool Split(const TStringRef<T>& str, const T* delimiter, List<TStringRef<T> >& outResults, bool removeEmptyEntries = true)
	{
		return Split(str, TStringRef<T>(delimiter), outResults, removeEmptyEntries);
	}

	template<typename T>
	bool Split(const TStringRef<T>& str, const TStringRef<T>& delimiter, List<TStringRef<T> >& outResults,bool removeEmptyEntries=true)
	{
		RETURN_FALSE_IF(str.IsEmpty());

		intp begin = 0;
		intp index = str.IndexOfAny(delimiter, begin);

		if (removeEmptyEntries)
		{
			while (index >= 0)
			{
				if (index > begin)
				{
					outResults.EmplaceBack(str.Buffer() + begin, (size_t)(index - begin));
				}
				begin = index + 1;
				while (delimiter.Contains(str[begin]))	//strip duplicate delimiters
				{
					++begin;
				}
				index = str.IndexOfAny(delimiter, begin);
			}

		}
		else
		{
			while (index >= 0)
			{
				if (index > begin)
				{
					outResults.EmplaceBack(str.Buffer() + begin, (size_t)(index - begin));
				}
				else
				{
					outResults.NewAdd();
				}

				begin = index + 1;
				index = str.IndexOfAny(delimiter, begin);
			}
		}
		
		//add last
		if (removeEmptyEntries)
		{
			if ((size_t)begin < str.Length())
			{
				auto left = str.SubString(begin);
				left = left.TrimAll();
				if (!left.IsEmpty())
				{
					outResults.Add(left);
				}
			}
		}
		else
		{
			if ((size_t)begin < str.Length())
			{
				outResults.EmplaceBack(str.Buffer() + begin, (size_t)(str.Length() - begin));
			}
			else
			{
				outResults.NewAdd();
			}
		}
		

		return !outResults.IsEmpty();
	}

	template<typename T>
	bool Split(const TStringRef<T>& str, const T* delimiter, List<THeapString<T> >& outResults, bool removeEmptyEntries = true)
	{
		return Split(str, TStringRef<T>(delimiter), outResults, removeEmptyEntries);
	}

	template<typename T>
	bool Split(const TStringRef<T>& str, const TStringRef<T>& delimiter, List<THeapString<T> >& outResults, bool removeEmptyEntries = true)
	{
		RETURN_FALSE_IF(str.IsEmpty());

		intp begin = 0;
		intp index = str.IndexOfAny(delimiter, begin);

		if (removeEmptyEntries)
		{
			while (index >= 0)
			{
				if (index > begin)
				{
					outResults.EmplaceBack(str.Buffer() + begin, (size_t)(index - begin));
				}
				begin = index + 1;
				while (delimiter.Contains(str[begin]))	//strip duplicate delimiters
				{
					++begin;
				}
				index = str.IndexOfAny(delimiter, begin);
			}

		}
		else
		{
			while (index >= 0)
			{
				if (index > begin)
				{
					outResults.EmplaceBack(str.Buffer() + begin, (size_t)(index - begin));
				}
				else
				{
					outResults.NewAdd();
				}

				begin = index + 1;
				index = str.IndexOfAny(delimiter, begin);
			}
		}

		//add last
		if (removeEmptyEntries)
		{
			if ((size_t)begin < str.Length())
			{
				auto left = str.SubString(begin);
				left = left.TrimAll();
				if (!left.IsEmpty())
				{
					outResults.Add(left);
				}
			}
		}
		else
		{
			if ((size_t)begin < str.Length())
			{
				outResults.EmplaceBack(str.Buffer() + begin, (size_t)(str.Length() - begin));
			}
			else
			{
				outResults.NewAdd();
			}
		}

		return !outResults.IsEmpty();
	}

	template<typename T, typename TValue>
	bool SplitToValues(const TStringRef<T>& str, const TStringRef<T>& delimiter, List<TValue>& outResults, const TValue* emptyResult=nullptr)
	{
		RETURN_FALSE_IF(str.IsEmpty());

		intp begin = 0;
		intp index = str.IndexOfAny(delimiter, begin);
		if (emptyResult==nullptr)
		{
			while (index >= 0)
			{
				if (index > begin)
				{
					TStringRef<T> tempStr(str.Buffer() + begin, index - begin);
					outResults.NewAdd() = StringTo<TValue>(tempStr);
				}
				begin = index + 1;
				while (delimiter.Contains(str[begin]))	//strip duplicate delimiters
				{
					++begin;
				}
				index = str.IndexOfAny(delimiter, begin);
			}
		}
		else
		{
			while (index >= 0)
			{
				if (index > begin)
				{
					TStringRef<T> tempStr(str.Buffer() + begin, index - begin);
					outResults.NewAdd() = StringTo<TValue>(tempStr);
				}
				else
				{
					outResults.Add(*emptyResult);
				}
				begin = index + 1;
				index = str.IndexOfAny(delimiter, begin);
			}
		}
		

		//add last
		if ((size_t)begin < str.Length())
		{
			TStringRef<T> tempStr(str.Buffer() + begin);
			outResults.NewAdd() = StringTo<TValue>(tempStr);
		}
		else if (emptyResult!=nullptr)
		{
			outResults.Add(*emptyResult);
		}

		return !outResults.IsEmpty();
	}

	template<typename T>
	bool Join(const TStringRef<T>& delimiter, ICollection<TStringRef<T> >& strings, THeapString<T>& outResult)
	{
		outResult.Clear();
		size_t count = strings.Count();
		for(auto& str: strings)
		{
			outResult.Append(str);
			if (i != count - 1)
			{
				outResult.Append(delimiter);
			}
		}

		return !outResult.IsEmpty();
	}

	template<typename T>
	bool SplitToWords(const TStringRef<T>& str, List<THeapString<T> >& outResults)
	{
		return Split(str, StdString::ConstValues<T>::WordSeparators, outResults);
	}



	template<typename T, typename TValue>
	bool TryReadKeyValue(const TStringRef<T>& str, const TStringRef<T>& key, const TStringRef<T>& keyValueDelimter, const TStringRef<T>& pairDelimter, TValue& outValue)
	{
		intp index = str.IndexOf(key);
		RETURN_FALSE_IF(index < 0);
		index += key.Length();
		TStringRef<T> sub(str.c_str() + index, str.Length() - index);
		RETURN_FALSE_IF_FALSE(sub.BeginWith(keyValueDelimter));
		index += keyValueDelimter.Length();
		TStringRef<T> valueStr(str.c_str() + index, str.Length() - index);
		intp endIndex = valueStr.IndexOf(pairDelimter);
		if (endIndex > 0)
		{
			valueStr.ForceSetLength(endIndex);
		}
		else if (endIndex == 0)
		{
			return false;
		}

		outValue = StringParser::StringTo<TValue>(valueStr);
		return true;
	}


	template<typename T, typename TValue>
	bool TryReadKeyValue(const TStringRef<T>& str, const TStringRef<T>& key, T keyValueDelimter, T pairDelimter, TValue& outValue)
	{
		intp index = str.IndexOf(key);
		RETURN_FALSE_IF(index < 0);
		index += key.Length();

		RETURN_FALSE_IF_NOT_EQUAL(str[index], keyValueDelimter);

		++index;
		TStringRef<T> valueStr(str.c_str() + index, str.Length() - index);
		intp endIndex = valueStr.IndexOf(pairDelimter);
		if (endIndex > 0)
		{
			valueStr.ForceSetLength(endIndex);
		}
		else if (endIndex == 0)
		{
			return false;
		}

		outValue = StringParser::StringTo<TValue>(valueStr);
		return true;
	}

	template<typename T, size_t keySize, typename TValue>
	bool TryReadKeyValue(const TStringRef<T>& str, const T(&key)[keySize], T keyValueDelimter, T pairDelimter, TValue& outValue)
	{
		return TryReadKeyValue(str, TStringRef<T>(key), keyValueDelimter, pairDelimter, outValue);
	}


	template<typename T, size_t keySize, size_t keyValueDelimterSize, size_t pairDelimterSize, typename TValue>
	bool TryReadKeyValue(const TStringRef<T>& str, const T(&key)[keySize], const T(&keyValueDelimter)[keyValueDelimterSize], const T(&pairDelimter)[pairDelimterSize], TValue& outValue)
	{
		return TryReadKeyValue(str, TStringRef<T>(key), TStringRef<T>(keyValueDelimter), TStringRef<T>(pairDelimter), outValue);
	}



	template<typename T, typename TValue>
	bool TryReadKeyValues(const TStringRef<T>& str, const TStringRef<T>& key, const TStringRef<T>& keyValueDelimter, const TStringRef<T>& valueDelimter, const TStringRef<T>& pairDelimter, TValue* outValuePtr)
	{
		int index = str.IndexOf(key);
		RETURN_FALSE_IF(index < 0);
		index += key.Length();
		TStringRef<T> sub(str.c_str() + index, str.Length() - index);
		RETURN_FALSE_IF_FALSE(sub.BeginWith(keyValueDelimter));
		index += keyValueDelimter.Length();
		TStringRef<T> valueStr(str.c_str() + index, str.Length() - index);
		int endIndex = valueStr.IndexOf(pairDelimter);
		if (endIndex > 0)
		{
			valueStr.ForceSetLength(endIndex);
		}
		else if (endIndex == 0)
		{
			return false;
		}

		do
		{
			int valueIndex = valueStr.IndexOf(valueDelimter);
			if (valueIndex > 0)
			{
				TStringRef<T> itemStr(valueStr.c_str(), valueIndex);
				*outValuePtr++ = StringParser::StringTo<TValue>(itemStr);
				valueStr.ForceSetBuffer(valueStr.c_str() + valueIndex + valueDelimter.Length());
				valueStr.ForceSetLength(valueStr.Length() - valueIndex - valueDelimter.Length());
			}
			else if (valueIndex <= 0)
			{
				*outValuePtr++ = StringParser::StringTo<TValue>(valueStr);
				break;
			}
		} while (true);

		return true;
	}



	template<typename T, typename TValue>
	bool TryReadKeyValues(const TStringRef<T>& str, const TStringRef<T>& key, T keyValueDelimter, T valueDelimter, T pairDelimter, TValue* outValuePtr)
	{
		intp index = str.IndexOf(key);
		RETURN_FALSE_IF(index < 0);
		index += key.Length();

		RETURN_FALSE_IF_NOT_EQUAL(str[index], keyValueDelimter);
		++index;
		TStringRef<T> valueStr(str.c_str() + index, str.Length() - index);
		intp endIndex = valueStr.IndexOf(pairDelimter);
		if (endIndex > 0)
		{
			valueStr.ForceSetLength(endIndex);
		}
		else if (endIndex == 0)
		{
			return false;
		}

		do
		{
			intp valueIndex = valueStr.IndexOf(valueDelimter);
			if (valueIndex > 0)
			{
				TStringRef<T> itemStr(valueStr.c_str(), valueIndex);
				*outValuePtr++ = StringParser::StringTo<TValue>(itemStr);
				valueStr.ForceSetBuffer(valueStr.c_str() + valueIndex + 1);
				valueStr.ForceSetLength(valueStr.Length() - valueIndex - 1);
			}
			else if (valueIndex <= 0)
			{
				*outValuePtr++ = StringParser::StringTo<TValue>(valueStr);
				break;
			}
		} while (true);

		return true;
	}


	template<typename T, size_t keySize, typename TValue>
	bool TryReadKeyValues(const TStringRef<T>& str, const T(&key)[keySize], T keyValueDelimter, T valueDelimter, T pairDelimter, TValue& outValue)
	{
		return TryReadKeyValues(str, TStringRef<T>(key), keyValueDelimter, valueDelimter, pairDelimter, outValue);
	}

	template<typename T, size_t keySize, size_t keyValueDelimterSize, size_t valueDelimterSize, size_t pairDelimterSize, typename TValue>
	bool TryReadKeyValues(const TStringRef<T>& str, const T(&key)[keySize], const T(&keyValueDelimter)[keyValueDelimterSize], const T(&valueDelimter)[valueDelimterSize], const T(&pairDelimter)[pairDelimterSize], TValue& outValue)
	{
		return TryReadKeyValues(str, TStringRef<T>(key), TStringRef<T>(keyValueDelimter), TStringRef<T>(valueDelimter), TStringRef<T>(pairDelimter), outValue);
	}


	template<typename TChar>
	THeapString<TChar> BytesToHexString(const byte* input, size_t length, bool uppercase = true)
	{
		const TChar* hex = uppercase ? StdString::ConstValues<TChar>::HexUpperCase : StdString::ConstValues<TChar>::HexLowerCase;
		THeapString<TChar> str;
		str.ReserveLength(length << 1);
		for (size_t i = 0; i < length; ++i)
		{
			byte t = input[i];
			byte a = t / 16;
			byte b = t % 16;
			str.Append(hex[a]);
			str.Append(hex[b]);
		}
		return str;
	}
	// Convert an integer value to a hexadecimal string.
	// The returned string length is always width long, prefixed by 0 digits.
	// For example, IntToStringHex(0x23, 8) returns the string "00000023".
	template<typename TChar, class TValue>
	StringParser::HexResultString<TChar, TValue> ToHexString(TValue val, uintp width = 0, bool uppercase = true, bool addPrefix = false, bool prefixUpperCase = false)
	{
		const TChar* hex = uppercase ? StdString::ConstValues<TChar>::HexUpperCase : StdString::ConstValues<TChar>::HexLowerCase;
		StringParser::HexResultString<TChar, TValue> str;

		if (addPrefix&&val != 0)
		{
			str.Append((TChar)'0');
			str.Append(prefixUpperCase ? (TChar)'X' : (TChar)'x');
		}

		if (width > 0)
		{
			uintp count = 0;
			while (val > 0)
			{
				val >>= 4;
				++count;
			}
			if (count < width)
			{
				str.Append((TChar)'0', width - count);
			}

			while (val > 0)
			{
				byte b = val % 16;
				str.Append(hex[b]);
				val >>= 4;
			}
		}
		else
		{
			while (val > 0)
			{
				byte b = val % 16;
				str.Append(hex[b]);
				val >>= 4;
			}
		}

		return str;
	}


	template<typename T>
	bool TryExtractUInt(const TStringRef<T>& str, uint& outResult)
	{
		outResult = 0;
		size_t length = str.Length();
		RETURN_FALSE_IF_ZERO(length);
		const T* p = str.c_str();
		FOR_EACH_SIZE(i, length)
		{
			if (StdString::IsDigit(p[i]))
			{
				outResult = StringTo<uint>(TStringRef<T>(p + i, length - i));
				return true;
			}
		}
		return false;
	}

	template<typename T>
	bool TryExtractInt(const TStringRef<T>& str, int& outResult)
	{
		outResult = 0;
		size_t length = str.Length();
		RETURN_FALSE_IF_ZERO(length);

		const T* p = str.c_str();
		FOR_EACH_SIZE(i, length)
		{
			if (StdString::IsDigit(p[i]) || p[i] == StdString::ConstValues<T>::Hyphen)
			{
				outResult = StringTo<int>(TStringRef<T>(p + i, length - i));
				return true;
			}
		}
		return false;
	}

};


MEDUSA_END;
