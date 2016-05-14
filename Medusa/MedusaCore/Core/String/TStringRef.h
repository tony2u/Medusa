// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "MedusaCorePreDeclares.h"
#include "Core/Assertion/CommonAssert.h"
#include "Core/Hash/HashUtility.h"
#include "Core/Memory/Memory.h"
#include "Core/Math/Math.h"
#include "Core/String/StdString.h"
#include "Core/Collection/List.h"


MEDUSA_BEGIN;

template<typename T>
class TStringRef
{
public:
	template<size_t size>
	TStringRef(const T(&str)[size])
		:mBuffer(str), mLength(Math::UIntMaxValue)
	{

	}
	TStringRef()
		:mBuffer(nullptr), mLength(0)
	{

	}
	TStringRef(const T* inBuffer)
		:mBuffer(inBuffer), mLength(Math::UIntMaxValue)
	{
	}
	TStringRef(const std::basic_string<T, std::char_traits<T>, std::allocator<T> >& str)
	{
		mBuffer = str.c_str();
		mLength = str.length();
	}

	TStringRef(const T* inBuffer, size_t length)
		:mBuffer(inBuffer), mLength(length)
	{
	}

	explicit TStringRef(const TMemoryData<T>& data)
	{
		mBuffer = (const T*)data.Data();
		mLength = data.LengthAsString();
	}

	~TStringRef(void)
	{
	}

	/*operator const T*()const	//should disable this to prevent 2 overloads have similar conversions
	{
	return mBuffer;
	}*/

	TStringRef(const TStringRef& inString)
	{
		mBuffer = inString.mBuffer;
		mLength = inString.mLength;
	}

	TStringRef& operator=(const TStringRef& inString)
	{
		mBuffer = inString.mBuffer;
		mLength = inString.mLength;
		return *this;
	}

	TStringRef SubString(size_t index)const
	{
		if (IsEmpty())
		{
			return TStringRef::Empty;
		}
		return IsLengthAvailable() ? TStringRef(mBuffer + index, mLength - index) : TStringRef(mBuffer + index);
	}

	TStringRef SubString(size_t index, size_t length)const
	{
		if (IsEmpty())
		{
			return TStringRef::Empty;
		}

		size_t curLength = Length();
		if (curLength < index + length)
		{
			return TStringRef::Empty;
		}

		return TStringRef(mBuffer + index, length);
	}

	TStringRef SubStringTo(size_t index, T nextChar)const
	{
		intp nextIndex = IndexOf(nextChar, index);
		if (nextIndex<0)
		{
			return SubString(index);
		}

		return SubString(index, nextIndex - index);
	}

	THeapString<T> operator+(const TStringRef<T>& inString) const;
	THeapString<T> operator+(T c) const;

public:
	bool operator==(const TStringRef& inString)const
	{
		if (inString.IsEmpty())
		{
			return IsEmpty();
		}

		if (IsEmpty())
		{
			return false;
		}

		return Length() == inString.Length() && StdString::CompareN(mBuffer, inString.Buffer(), Length()) == 0;
	}
	bool operator!=(const TStringRef& inString)const
	{
		return !operator==(inString);
	}
	bool operator>(const TStringRef& inString)const
	{
		if (inString.IsEmpty())
		{
			return !IsEmpty();
		}

		if (IsEmpty())
		{
			return false;
		}
		size_t length = Math::Min(Length(), inString.Length());
		return StdString::CompareN(mBuffer, inString.Buffer(), length + 1) > 0;
	}
	bool operator<(const TStringRef& inString)const
	{
		if (inString.IsEmpty())
		{
			return false;
		}

		if (IsEmpty())
		{
			return true;
		}

		size_t length = Math::Min(Length(), inString.Length());
		return StdString::CompareN(mBuffer, inString.Buffer(), length) < 0;
	}
	bool operator>=(const TStringRef& inString)const
	{
		return !operator<(inString);
	}
	bool operator<=(const TStringRef& inString)const
	{
		return !operator>(inString);
	}

public:
	int Compare(const TStringRef& inString)const
	{
		return Compare(inString, false);
	}
	int Compare(const TStringRef& inString, bool isIgnoreCase)const
	{
		size_t length = Math::Min(Length(), inString.Length());
		if (isIgnoreCase)
		{
			return StdString::CompareNIgnoreCase(mBuffer, inString.Buffer(), length + 1);
		}

		return StdString::CompareN(mBuffer, inString.Buffer(), length + 1);
	}
	intp IndexOf(T inFindChar)const
	{
		return IndexOf(inFindChar, 0);
	}
	intp IndexOf(T inFindChar, intp index)const
	{
		intp length = Length();
		if (index >= length)
		{
			return -1;
		}
		const T* p = StdString::FindFirstChar(mBuffer + index, Length() - index, inFindChar);
		if (p == nullptr)
		{
			return -1;
		}

		return p - mBuffer;
	}
	intp IndexOf(const TStringRef& inString)const
	{
		return IndexOf(inString, 0);
	}

	intp IndexOf(const TStringRef& inString, intp index)const
	{
		intp length = Length();
		if (index >= length)
		{
			return -1;
		}

		const T* p = StdString::FindString(mBuffer + index, Length() - index, inString.c_str(), inString.Length());
		if (p == nullptr)
		{
			return -1;
		}

		return p - mBuffer;
	}
	intp IndexOfAny(const TStringRef& inString)const
	{
		return IndexOfAny(inString, 0);
	}
	intp IndexOfAny(const TStringRef& inString, intp index)const
	{
		intp length = Length();
		if (index >= length)
		{
			return -1;
		}

		const T* p = StdString::FindCharAny(mBuffer + index, Length() - index, inString.c_str(), inString.Length());
		if (p == nullptr)
		{
			return -1;
		}

		return p - mBuffer;
	}

	intp PrevIndexOf(T inFindChar)const
	{
		return PrevIndexOf(inFindChar, 0);
	}
	intp PrevIndexOf(T inFindChar, intp index)const
	{
		RETURN_OBJECT_IF_TRUE(IsEmpty(), -1);
		for (const T* p = mBuffer + index; p >= mBuffer; --p)
		{
			if (*p == inFindChar)
			{
				return p - mBuffer;
			}
		}

		return -1;
	}

	intp LastIndexOf(T inFindChar)const
	{
		RETURN_OBJECT_IF_TRUE(IsEmpty(), -1);
		return LastIndexOf(inFindChar, 0, Length() - 1);
	}
	intp LastIndexOf(T inFindChar, intp beginIndex, intp endIndex)const
	{
		RETURN_OBJECT_IF_TRUE(IsEmpty(), -1);

		size_t length = Length();
		if (beginIndex > (intp)length - 1)
		{
			return -1;
		}

		if (endIndex < beginIndex)
		{
			return -1;
		}

		for (const T* p = mBuffer + endIndex; p >= mBuffer + beginIndex; --p)
		{
			if (*p == inFindChar)
			{
				return p - mBuffer - beginIndex;
			}
		}
		return -1;

	}
	intp LastIndexOf(const TStringRef& inString)const
	{
		RETURN_OBJECT_IF_TRUE(IsEmpty(), -1);
		return LastIndexOf(inString, 0, Length() - 1);
	}

	intp LastIndexOf(const TStringRef& inString, intp beginIndex, intp endIndex)const
	{
		RETURN_OBJECT_IF_TRUE(IsEmpty(), -1);
		size_t length = inString.Length();
		if (length > Length() - beginIndex)
		{
			return -1;
		}

		if (endIndex < beginIndex)
		{
			return -1;
		}


		intp findEndIndex = length - 1;
		const T* inBuffer = inString.Buffer();

		intp j, ti;
		for (intp i = endIndex; i >= beginIndex; i--)
		{
			if (inBuffer[findEndIndex] == mBuffer[i])
			{
				for (j = findEndIndex, ti = i; j >= 0 && ti >= 0; --j, --ti)
				{
					if (inBuffer[j] != mBuffer[ti])
					{
						break;
					}
				}
				++j;
				if (j == 0 && i - ti == findEndIndex + 1)
				{
					return (i - findEndIndex);
				}
			}
		}
		return -1;
	}

	intp LastIndexOfAny(const TStringRef& inString)const
	{
		RETURN_OBJECT_IF_TRUE(IsEmpty(), -1);
		return LastIndexOfAny(inString, 0, Length() - 1);
	}

	intp LastIndexOfAny(const TStringRef& inString, intp beginIndex, intp endIndex)const
	{
		RETURN_OBJECT_IF_TRUE(IsEmpty(), -1);
		intp length = Length();
		if (length == 0 || beginIndex < 0 || beginIndex >= length || endIndex < beginIndex)
		{
			return -1;
		}

		for (intp i = endIndex; i >= beginIndex; --i)
		{
			if (inString.Contains(mBuffer[i]))
			{
				return i;
			}
		}

		return -1;
	}

	bool IndicesOf(T val, List<intp>& outIndices)const
	{
		RETURN_FALSE_IF(IsEmpty());
		intp begin = 0;
		while (true)
		{
			intp index = IndexOf(val, begin);
			BREAK_IF(index < 0);
			outIndices.Add(index);
			begin = index + 1;
		}
		return !outIndices.IsEmpty();
	}
	bool IndicesOf(const TStringRef& val, List<intp>& outIndices)const
	{
		RETURN_FALSE_IF(IsEmpty());
		intp begin = 0;
		while (true)
		{
			intp index = IndexOf(val, begin);
			BREAK_IF(index < 0);
			outIndices.Add(index);
			begin = index + 1;
		}
		return !outIndices.IsEmpty();
	}

	bool IndicesOfAny(const TStringRef& val, List<intp>& outIndices)const
	{
		RETURN_FALSE_IF(IsEmpty());
		intp begin = 0;
		while (true)
		{
			intp index = IndexOfAny(val, begin);
			BREAK_IF(index < 0);
			outIndices.Add(index);
			begin = index + 1;
		}
		return !outIndices.IsEmpty();
	}

	bool Contains(T inFindChar)const
	{
		return IndexOf(inFindChar) >= 0;
	}
	bool Contains(const TStringRef& inString)const
	{
		return IndexOf(inString) >= 0;
	}
	bool ContainsAny(const TStringRef& inString)const
	{
		return IndexOfAny(inString) >= 0;
	}
	bool BeginWith(const TStringRef& inString)const
	{
		size_t length = inString.Length();
		if (length > Length())
		{
			return false;
		}

		if (Length() == 0)
		{
			return length == 0;
		}
		else
		{
			if (length == 0)
			{
				return true;
			}
		}

		const T* buffer = inString.Buffer();
		size_t i = 0;
		while (*buffer != 0)
		{
			if (i > Length() || mBuffer[i++] != *buffer++)
			{
				return false;
			}
		}

		return true;
	}
	bool BeginWith(T val)const
	{
		return mBuffer != nullptr&&*mBuffer == val;
	}

	bool EndWith(const TStringRef& inString)const
	{
		size_t length = inString.Length();
		if (length > Length())
		{
			return false;
		}

		if (Length() == 0)
		{
			return length == 0;
		}
		else
		{
			if (length == 0)
			{
				return true;
			}
		}

		const T* buffer = inString.Buffer();

		size_t i = Length() - 1;
		const T* pEnd = buffer + length - 1;
		--buffer;

		while (pEnd != buffer)
		{
			if (*pEnd-- != mBuffer[i--])
			{
				return false;
			}
		}

		return true;
	}
	bool EndWith(T val)const
	{
		size_t length = Length();
		return length != 0 && mBuffer[length - 1] == val;
	}

	long ToInt()const
	{
		return ToInt(10);
	}
	long ToInt(int radix)const
	{
		return StdString::ToInt(mBuffer, nullptr, radix);
	}

	long ToIntWithFailed(long val)const
	{
		long result;
		if (TryParseInt(result))
		{
			return result;
		}
		return val;
	}
	long ToIntWithFailed(int radix, long val)const
	{
		long result;
		if (TryParseInt(result, radix))
		{
			return result;
		}
		return val;
	}

	bool TryParseInt(long& outResult)const
	{
		return TryParseInt(outResult, 10);
	}
	bool TryParseInt(long& outResult, int radix)const
	{
		RETURN_FALSE_IF(IsEmpty());
		T* endPtr;
		outResult = StdString::ToInt(mBuffer, &endPtr, radix);
		return endPtr != mBuffer;
	}
	bool TryParseUInt(ulong& outResult)const
	{
		return TryParseUInt(outResult, 10);
	}
	bool TryParseUInt(ulong& outResult, int radix)const
	{
		RETURN_FALSE_IF(IsEmpty());
		T* endPtr;
		outResult = StdString::ToUInt(mBuffer, &endPtr, radix);
		return endPtr != mBuffer;
	}

	double ToDouble()const
	{
		return StdString::ToDouble(mBuffer, nullptr);
	}
	double ToDoubleWithFailed(double val)const
	{
		double result;
		if (TryParseDouble(result))
		{
			return result;
		}
		return val;
	}

	bool TryParseDouble(double& outResult)const
	{
		RETURN_FALSE_IF(IsEmpty());
		T* endPtr;
		outResult = StdString::ToDouble(mBuffer, &endPtr);
		return endPtr != mBuffer;
	}
	size_t Count(T inChar)const
	{
		RETURN_ZERO_IF(IsEmpty());
		size_t count = 0;
		const T* p = mBuffer;

		while ((*p) != 0)
		{
			if (*p == inChar)
			{
				++count;
			}
			++p;
		}
		return count;
	}
	size_t Count(const TStringRef& inString)const
	{
		RETURN_ZERO_IF(IsEmpty());
		size_t length = inString.Length();
		size_t srcLength = Length();

		if (length > srcLength)
		{
			return 0;
		}

		size_t count = 0;
		const T* p = mBuffer;
		const T* end = mBuffer + srcLength;

		while ((*p) != 0)
		{
			srcLength = end - p;
			p = StdString::FindString(p, srcLength, inString.Buffer(), inString.Length());
			if (p != nullptr)
			{
				count++;
				p += length;
			}
			else
			{
				break;
			}

		}
		return count;
	}
	void CopyTo(T* outBuffer, size_t outBufferSize)const
	{
		RETURN_IF(IsEmpty());
		size_t length = Length();
		RETURN_IF(length > outBufferSize);

		Memory::SafeCopy(outBuffer, outBufferSize, mBuffer, length);
	}
	void CopyTo(T* outBuffer, size_t outBufferSize, size_t length)const
	{
		RETURN_IF(IsEmpty());
		Memory::SafeCopy(outBuffer, outBufferSize, 0, length);

	}
	void CopyTo(T* outBuffer, size_t outBufferSize, size_t beginIndex, size_t length)const
	{
		RETURN_IF(IsEmpty());
		RETURN_IF(length > outBufferSize);

		size_t myLength = Length();
		RETURN_IF(beginIndex + length > myLength + 1);

		Memory::SafeCopy(outBuffer, outBufferSize, mBuffer + beginIndex, length);
	}

	TStringRef<T> TrimAll()const
	{
		return TrimBegin().TrimEnd();
	}

	TStringRef<T> TrimBegin()const
	{
		RETURN_SELF_IF_EMPTY(*this);
		const T* p = mBuffer;
		const T* end = mBuffer + Length();

		TStringRef<T> trimChars = StdString::ConstValues<T>::TrimChars;

		while (p != end)
		{
			if (trimChars.Contains(*p))
			{
				++p;
			}
			else
			{
				break;
			}
		}

		return TStringRef<T>(p, Length() + mBuffer - p);
	}

	TStringRef<T> TrimEnd()const
	{
		RETURN_SELF_IF_EMPTY(*this);
		const T* p = mBuffer + Length() - 1;
		const T* begin = mBuffer - 1;
		TStringRef<T> trimChars = StdString::ConstValues<T>::TrimChars;

		while (p != begin)
		{
			if (trimChars.Contains(*p))
			{
				--p;
			}
			else
			{
				break;
			}
		}

		return TStringRef<T>(mBuffer, p - mBuffer + 1);
	}

	/*
		void Split(const TStringRef& delimiter,List<THeapString<T> >& outResults )const
		{
		RETURN_IF(IsNull());
		size_t size=Length()+1;
		T* copyBuffer=Memory::Alloc<T>(size);
		Memory::SafeCopy(copyBuffer,size,mBuffer,size);

		T* context;
		T* result=StdString::SplitString(copyBuffer,delimiter.Buffer(),&context);
		while (result!=nullptr)
		{
		outResults.Append(THeapString<T>(result));
		result=StdString::SplitString(nullptr,delimiter.Buffer(),&context);
		}

		free(copyBuffer);
		}
		*/
public:
	T operator[](size_t index)const
	{
		return mBuffer[index];
	}

	T First()const { return mBuffer != nullptr ? *mBuffer : (T)0; }
	T Last()const
	{
		size_t length = Length();
		return length != 0 ? mBuffer[length - 1] : (T)0;
	}

	bool IsEmpty()const
	{
		return mBuffer == nullptr || *mBuffer == 0 || mLength == 0;
	}

	bool IsNullTermitated()const
	{
		return !IsEmpty() && mBuffer[Length()] == '\0';
	}

	bool IsRefEqualsTo(const TStringRef& other)const
	{
		return mBuffer == other.Buffer();
	}

	bool IsEqualsTo(const TStringRef& other)const
	{
		return *this == other;
	}

	size_t Length()const
	{
		if (mLength == Math::UIntMaxValue)
		{
			mLength = mBuffer == nullptr ? 0 : StdString::GetLength(mBuffer);
		}

		return mLength;
	}

	intp HashCode()const { return (intp)HashUtility::HashString(mBuffer, mBuffer + Length()); }
	const T* Buffer()const { return mBuffer; }
	const T* c_str()const { return mBuffer; }
	void ForceSetBuffer(const T* buffer) { mBuffer = buffer; }
	void ForceSetLength(size_t length) { mLength = length; }
	void ForceUpdateLength() { mLength = Math::UIntMaxValue; }
	TMemoryData<T> ToData()const { return TMemoryData<T>::FromStatic(mBuffer, Length()); }


private:
	bool IsLengthAvailable()const { return mLength != Math::UIntMaxValue; }
protected:
	const T* mBuffer;
	mutable size_t mLength;
public:
	const static TStringRef Empty;

};

template<typename T>
MEDUSA_WEAK_MULTIPLE_DEFINE const TStringRef<T> TStringRef<T>::Empty;

//[PRE_DECLARE_BEGIN]
typedef TStringRef<char> StringRef;
typedef TStringRef<wchar_t> WStringRef;
//[PRE_DECLARE_END]


MEDUSA_END;
