// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "Core/String/BaseString.h"
#include "Core/Collection/List.h"


MEDUSA_BEGIN;

template<typename T>
class THeapString :public BaseString < T >
{
public:
	THeapString() :BaseString<T>(nullptr, (size_t)0, size_t(0))
	{

	}
	explicit THeapString(size_t size, bool isInitNull = false) :BaseString<T>(Memory::Alloc<T>(size), size, isInitNull)
	{

	}
	THeapString(const T* inBuffer, size_t length) :BaseString<T>(Memory::Alloc<T>(length + 1), length + 1)
	{
		this->Insert(0, inBuffer, length);
	}

	explicit THeapString(T inChar) :BaseString<T>(Memory::Alloc<T>(2), 2)
	{
		this->Push(inChar);
	}

	THeapString(const TStringRef<T>& str) :THeapString<T>(str.c_str(), str.Length())
	{

	}

	THeapString(const THeapString& str) :THeapString<T>(str.c_str(), str.Length())
	{

	}


	THeapString(const BaseString<T>& str) :THeapString<T>(str.c_str(), str.Length())
	{

	}

	THeapString(const std::basic_string<T, std::char_traits<T>, std::allocator<T> >& str) :THeapString<T>(str.c_str(), str.size())
	{

	}


	explicit THeapString(const T* str) :THeapString(str, StdString::GetLength(str))
	{

	}

	template<size_t size>
	explicit THeapString(const T(&str)[size]) :THeapString(str, StdString::GetLength(str))
	{

	}

	explicit THeapString(const TMemoryData<T>& data) :BaseString<T>(nullptr, (size_t)0, size_t(0))
	{
		this->mBuffer = (T*)data.Data();
		this->mBufferSize = data.ByteSize();
		this->mLength = data.LengthAsString();
	}

	virtual ~THeapString()
	{
		Clear();
	}

	THeapString(THeapString&& str)
		:BaseString<T>(str.mBuffer, str.mBufferSize, str.mLength)
	{
		str.mBuffer = nullptr;
		str.mBufferSize = 0;
		str.mLength = 0;
	}

	THeapString& operator=(THeapString&& str)
	{
		Clear();
		this->mBuffer = str.mBuffer;
		this->mBufferSize = str.mBufferSize;
		this->mLength = str.mLength;

		str.mBuffer = nullptr;
		str.mBufferSize = 0;
		str.mLength = 0;
		return *this;
	}



public:
	virtual void Clear()
	{
		SAFE_FREE(this->mBuffer);
		this->mBufferSize = 0;
		this->mLength = 0;
	}

	THeapString& operator=(const THeapString& str)
	{
		return this->operator=(str.ToString());
	}

	THeapString& operator=(const BaseString<T>& str)
	{
		return this->operator=(str.ToString());
	}

	THeapString& operator=(const std::basic_string<T, std::char_traits<T>, std::allocator<T> >& str)
	{
		return this->operator=(TStringRef<T>(str));
	}

	THeapString& operator=(const T* str)
	{
		return this->operator=(TStringRef<T>(str));
	}

	THeapString& operator=(const TStringRef<T>& inString)
	{
		size_t length = inString.Length();
		if (inString.IsEmpty())
		{
			Clear();
		}
		else
		{
			if (length == 0)
			{
				size_t size = Math::GetNewSizeOneAndHalf(this->mBufferSize, length + 1);
				bool isSuccess = this->ResizeHelper(size);
				MEDUSA_ASSERT_TRUE(isSuccess, "");
				UN_USED(isSuccess);
				*this->mBuffer = '\0';
			}
			else
			{
				if (length >= this->mBufferSize)
				{
					size_t size = Math::GetNewSizeOneAndHalf(this->mBufferSize, length + 1);
					bool isSuccess = this->ResizeHelper(size);
					MEDUSA_ASSERT_TRUE(isSuccess, "");
					UN_USED(isSuccess);
				}
				this->mLength = length;
				StdString::CopyStringN(this->mBuffer, this->mBufferSize, inString.Buffer(), this->mLength);
				this->mBuffer[this->mLength] = 0;
			}
		}

		return *this;
	}

	THeapString operator+(const BaseString<T>& str)const
	{
		THeapString result(*this);
		result += str;
		return result;
	}

	THeapString operator+(const THeapString& str)const
	{
		THeapString result(*this);
		result += str;
		return result;
	}

	THeapString operator+(const TStringRef<T>& str)const
	{
		THeapString result(*this);
		result += str;
		return result;
	}

	THeapString operator+(T c)const
	{
		THeapString result(*this);
		result += c;
		return result;
	}

	THeapString operator+(const std::basic_string<T, std::char_traits<T>, std::allocator<T> >& str)const
	{
		THeapString result(*this);
		result += str;
		return result;
	}

	THeapString operator+(const T* str)const
	{
		THeapString result(*this);
		result += str;
		return result;
	}



	using BaseString<T>::operator +=;
	THeapString& operator+=(const THeapString& inString)
	{
		Append(inString);
		return *this;
	}

	THeapString& operator+=(const std::basic_string<T, std::char_traits<T>, std::allocator<T> >& inString)
	{
		Append(inString.c_str(), inString.size());
		return *this;
	}

	THeapString& operator+=(T c)
	{
		Append(c);
		return *this;
	}

	THeapString& operator+=(const T* str)
	{
		Append(str);
		return *this;
	}

	using BaseString<T>::operator ==;
	using BaseString<T>::operator !=;
	using BaseString<T>::operator >;
	using BaseString<T>::operator <;
	using BaseString<T>::operator >=;
	using BaseString<T>::operator <=;


	//to be more fast
	bool operator==(const THeapString& inString)const
	{
		return this->ToString() == inString.ToString();
	}
	bool operator!=(const THeapString& inString)const
	{
		return this->ToString() != inString.ToString();
	}
	bool operator>(const THeapString& inString)const
	{
		return this->ToString() > inString.ToString();
	}
	bool operator<(const THeapString& inString)const
	{
		return this->ToString() < inString.ToString();
	}
	bool operator>=(const THeapString& inString)const
	{
		return this->ToString() >= inString.ToString();
	}
	bool operator<=(const THeapString& inString)const
	{
		return this->ToString() <= inString.ToString();
	}

	int Compare(const THeapString& inString)const
	{
		return this->ToString().Compare(inString.ToString(), false);
	}

	int Compare(const THeapString& inString, bool isIgnoreCase)const
	{
		return this->ToString().Compare(inString.ToString(), isIgnoreCase);
	}

	using BaseString<T>::IndexOf;
	intp IndexOf(const THeapString& inString)const
	{
		RETURN_OBJECT_IF(this->IsEmpty(), -1);
		return this->ToString().IndexOf(inString, 0);
	}

	intp IndexOf(const THeapString& inString, intp index)const
	{
		RETURN_OBJECT_IF(this->IsEmpty(), -1);
		return this->ToString().IndexOf(inString, index);
	}

	using BaseString<T>::IndexOfAny;
	intp IndexOfAny(const THeapString& inString)const
	{
		RETURN_OBJECT_IF(this->IsEmpty(), -1);
		return this->ToString().IndexOfAny(inString, 0);
	}
	intp IndexOfAny(const THeapString& inString, intp index)const
	{
		RETURN_OBJECT_IF(this->IsEmpty(), -1);
		return this->ToString().IndexOfAny(inString, index);
	}

	using BaseString<T>::LastIndexOf;
	intp LastIndexOf(const THeapString& inString)const
	{
		RETURN_OBJECT_IF(this->IsEmpty(), -1);
		return this->ToString().LastIndexOf(inString);
	}

	intp LastIndexOf(const THeapString& inString, intp beginIndex, intp endIndex)const
	{
		RETURN_OBJECT_IF(this->IsEmpty(), -1);
		return this->ToString().LastIndexOf(inString, beginIndex, endIndex);
	}

	using BaseString<T>::LastIndexOfAny;
	intp LastIndexOfAny(const THeapString& inString)const
	{
		RETURN_OBJECT_IF(this->IsEmpty(), -1);
		return this->ToString().LastIndexOfAny(inString, 0);
	}

	intp LastIndexOfAny(const THeapString& inString, intp beginIndex, intp endIndex)const
	{
		RETURN_OBJECT_IF(this->IsEmpty(), -1);
		return this->ToString().LastIndexOfAny(inString, beginIndex, endIndex);
	}

	using BaseString<T>::Contains;
	bool Contains(const THeapString& inString)const
	{
		RETURN_FALSE_IF(this->IsEmpty());
		return this->ToString().Contains(inString);
	}

	using BaseString<T>::ContainsAny;
	bool ContainsAny(const THeapString&  inString)const
	{
		RETURN_FALSE_IF(this->IsEmpty());
		return this->ToString().ContainsAny(inString);
	}

	using BaseString<T>::BeginWith;
	bool BeginWith(const THeapString& inString)const
	{
		RETURN_FALSE_IF(this->IsEmpty());
		return this->ToString().BeginWith(inString);
	}

	using BaseString<T>::EndWith;
	bool EndWith(const THeapString& inString)const
	{
		RETURN_FALSE_IF(this->IsEmpty());
		return this->ToString().EndWith(inString);
	}

	using BaseString<T>::Count;
	size_t Count(const THeapString& inString)const
	{
		RETURN_OBJECT_IF(this->IsEmpty(), 0);
		return this->ToString().Count(inString);
	}

	using BaseString<T>::CopyTo;
	void CopyTo(THeapString& outString)const
	{
		RETURN_IF(this->IsEmpty());
		CopyTo(outString.MutableBuffer(), outString.Size(), 0, this->mLength);
	}

	using BaseString<T>::ReplaceAll;
	bool ReplaceAll(const THeapString& oldString, const THeapString& newString)
	{
		return ReplaceAll(oldString.ToString(), newString.ToString());
	}

	bool ReplaceAll(const TStringRef<T>& oldString, const THeapString& newString)
	{
		return ReplaceAll(oldString, newString.ToString());
	}

	bool ReplaceAll(const THeapString& oldString, const TStringRef<T>& newString)
	{
		return ReplaceAll(oldString.ToString(), newString);
	}


	using BaseString<T>::ReplaceFirst;
	bool ReplaceFirst(const THeapString& oldString, const THeapString& newString)
	{
		return ReplaceFirst(oldString.ToString(), newString.ToString());
	}
	bool ReplaceFirst(const TStringRef<T>& oldString, const THeapString& newString)
	{
		return ReplaceFirst(oldString, newString.ToString());
	}

	bool ReplaceFirst(const THeapString& oldString, const TStringRef<T>& newString)
	{
		return ReplaceFirst(oldString.ToString(), newString);
	}


	using BaseString<T>::ReplaceLast;
	bool ReplaceLast(const THeapString& oldString, const THeapString& newString)
	{
		return ReplaceLast(oldString.ToString(), newString.ToString());
	}
	bool ReplaceLast(const TStringRef<T>& oldString, const THeapString& newString)
	{
		return ReplaceLast(oldString, newString.ToString());
	}

	bool ReplaceLast(const THeapString& oldString, const TStringRef<T>& newString)
	{
		return ReplaceLast(oldString.ToString(), newString);
	}

	using BaseString<T>::RemoveBeginAny;
	bool RemoveBeginAny(const THeapString& chars)
	{
		return RemoveBeginAny(chars.ToString());
	}

	using BaseString<T>::RemoveBeginAnyExclude;
	bool RemoveBeginAnyExclude(const THeapString& chars)
	{
		return RemoveBeginAnyExclude(chars.ToString());
	}

	using BaseString<T>::RemoveEndAny;
	bool RemoveEndAny(const THeapString& chars)
	{
		return RemoveEndAny(chars.ToString());
	}

	using BaseString<T>::RemoveEndAnyExclude;
	bool RemoveEndAnyExclude(const THeapString& chars)
	{
		return RemoveEndAnyExclude(chars.ToString());
	}

	using BaseString<T>::Append;
	bool Append(const THeapString& inString)
	{
		return Insert(this->mLength, inString);
	}

	using BaseString<T>::AppendLine;
	bool AppendLine(const THeapString& inString)
	{
		if (Insert(this->mLength, inString))
		{
			return Append(this->LineSeparator);
		}
		return false;
	}

	using BaseString<T>::Push;
	bool Push(const THeapString& inString)
	{
		return Insert(0, inString);
	}

	using BaseString<T>::Insert;
	bool Insert(size_t index, const THeapString& inString)
	{
		return Insert(index, inString.Buffer(), inString.Length());
	}

	using BaseString<T>::RemoveAll;
	bool RemoveAll(const THeapString& inString)
	{
		return RemoveAll(inString.ToString());
	}

	using BaseString<T>::RemoveFirst;
	bool RemoveFirst(const THeapString& inString)
	{
		return RemoveFirst(inString.ToString());
	}

	using BaseString<T>::RemoveLast;
	bool RemoveLast(const THeapString& inString)
	{
		return RemoveLast(inString.ToString());
	}
public:

	THeapString SubString(size_t index)const
	{
		return SubString(index, this->mLength - index);
	}

	THeapString SubString(size_t index, size_t length)const
	{
		MEDUSA_ASSERT_FALSE(this->IsEmpty(), "Null string");
		return THeapString(TStringRef<T>(this->mBuffer + index, length));
	}

	bool ReserveSize(size_t size)
	{
		RETURN_TRUE_IF(this->mBufferSize >= size);

		return this->ResizeHelper(size);
	}

	bool ReserveLength(size_t length)
	{
		return this->ReserveSize(length + 1);
	}

	bool ReserveLeftLength(size_t length)
	{
		size_t leftLength = this->LeftLength();
		if (length > leftLength)
		{
			return this->ReserveSize(this->mBufferSize + length - leftLength);
		}
		return true;
	}

	void ReleaseExtraSize()
	{
		RETURN_IF_ZERO(this->mBufferSize);

		if (this->mLength == 0)
		{
			SAFE_FREE(this->mBuffer);
			this->mBufferSize = 0;
		}
		else
		{
			RETURN_IF_EQUAL(this->mBufferSize, this->mLength + 1);	//+1 to store '\0'
			this->mBufferSize = this->mLength + 1;
			Memory::Realloc(this->mBuffer, this->mBufferSize);
		}
	}

	void ForceSetBuffer(T* buffer) { if (this->mBuffer != nullptr) { SAFE_FREE(this->mBuffer); }this->mBuffer = buffer; }
	T* ForceReleaseBuffer() { T* buffer = this->mBuffer; this->mBuffer = nullptr; return buffer; }
	void ForceSetBufferSize(size_t bufferSize) { this->mBufferSize = bufferSize; }

protected:
	virtual bool ResizeHelper(size_t size)
	{
		if (this->mBufferSize >= size&&this->mBuffer != nullptr)
		{
			return true;
		}

		Memory::Realloc(this->mBuffer, size);

		if (this->mBuffer != nullptr)
		{
			this->mBufferSize = size;
			return true;
		}
		return false;
	}
public:
	const static THeapString Empty;
};

template<typename T>
THeapString<T> operator+(T inFirstChar, const THeapString<T>& inSecondString)
{
	THeapString<T> result(inFirstChar);
	result += inSecondString;
	return result;
}

template<typename T>
MEDUSA_WEAK_MULTIPLE_DEFINE const THeapString<T> THeapString<T>::Empty;
//[PRE_DECLARE_BEGIN]
typedef THeapString<char> HeapString;
typedef THeapString<wchar_t> WHeapString;
//[PRE_DECLARE_END]

MEDUSA_END;
