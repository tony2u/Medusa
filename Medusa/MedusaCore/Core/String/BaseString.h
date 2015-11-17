// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "Core/String/TStringRef.h"
#include "Core/Assertion/CommonAssert.h"
#include "Core/Hash/HashUtility.h"
#include "Core/Memory/Memory.h"
#include "Core/String/StdString.h"
#include "Core/Math/Math.h"


MEDUSA_BEGIN;


template<typename T>
class BaseString
{
public:
	const static T LineSeparator = StdString::ConstValues<T>::LineSeparator;
public:
	BaseString(T* inBuffer, size_t bufferSize, bool isInitNull = false)
	{
		mLength = 0;
		mBuffer = inBuffer;
		mBufferSize = bufferSize;

		if (mBuffer != nullptr)
		{
			if (isInitNull)
			{
				Memory::Set(mBuffer, (char)0, mBufferSize);
			}
			else
			{
				mBuffer[0] = 0;
			}
		}
	}

	virtual ~BaseString(void)
	{
	}

	/*operator const T*()const
	{
	return mBuffer;
	}*/

	operator TStringRef<T>()const
	{
		return TStringRef<T>(mBuffer, mLength);
	}

protected:
	BaseString(T* inBuffer, size_t bufferSize, size_t length)
		:mBuffer(inBuffer), mBufferSize(bufferSize), mLength(length)
	{

	}

	/*BaseString()
	{

	}*/
public:
	virtual void Clear(){}
	BaseString& operator=(const BaseString& inString)
	{
		size_t length = inString.Length();

		if (length >= mBufferSize)
		{
			size_t size = Math::GetNewSizeOneAndHalf(mBufferSize, length + 1);
			bool isSuccess = ResizeHelper(size);
			MEDUSA_ASSERT_TRUE(isSuccess, "");
			UN_USED(isSuccess);
		}
		mLength = length;
		StdString::CopyStringN(mBuffer, mBufferSize, inString.Buffer(), mLength);

		mBuffer[mLength] = 0;
		return *this;
	}

	BaseString& operator=(const TStringRef<T>& inString)
	{
		size_t length = inString.Length();

		if (length >= mBufferSize)
		{
			size_t size = Math::GetNewSizeOneAndHalf(mBufferSize, length + 1);
			bool isSuccess = ResizeHelper(size);
			MEDUSA_ASSERT_TRUE(isSuccess, "");
			UN_USED(isSuccess);
		}

		mLength = length;
		StdString::CopyStringN(mBuffer, mBufferSize, inString.Buffer(), mLength);

		mBuffer[mLength] = 0;
		return *this;
	}

	BaseString& operator+=(const BaseString& inString)
	{
		Append(inString);
		return *this;
	}

	BaseString& operator+=(const T* inString)
	{
		Append(inString);
		return *this;
	}

	BaseString& operator+=(TStringRef<T> inString)
	{
		Append(inString);
		return *this;
	}

	BaseString& operator+=(T inChar)
	{
		Append(inChar);

		return *this;
	}

	//to be more fast
	bool operator==(const TStringRef<T>& inString)const
	{
		return ToString() == inString;
	}
	bool operator!=(const TStringRef<T>& inString)const
	{
		return ToString() != inString;
	}
	bool operator>(const TStringRef<T>& inString)const
	{
		return ToString() > inString;
	}
	bool operator<(const TStringRef<T>& inString)const
	{
		return ToString() < inString;
	}
	bool operator>=(const TStringRef<T>& inString)const
	{
		return ToString() >= inString;
	}
	bool operator<=(const TStringRef<T>& inString)const
	{
		return ToString() <= inString;
	}

	bool operator==(const BaseString& inString)const
	{
		return ToString() == inString.ToString();
	}
	bool operator!=(const BaseString& inString)const
	{
		return ToString() != inString.ToString();
	}
	bool operator>(const BaseString& inString)const
	{
		return ToString() > inString.ToString();
	}
	bool operator<(const BaseString& inString)const
	{
		return ToString() < inString.ToString();
	}
	bool operator>=(const BaseString& inString)const
	{
		return ToString() >= inString.ToString();
	}
	bool operator<=(const BaseString& inString)const
	{
		return ToString() <= inString.ToString();
	}

	T& operator[](size_t index)
	{
		return mBuffer[index];
	}

	T operator[](size_t index)const
	{
		return mBuffer[index];
	}

	T First()const { return mBuffer != nullptr ? *mBuffer : (T)0; }
	T Last()const { return mLength != 0 ? mBuffer[mLength - 1] : (T)0; }

	bool IsEmpty()const
	{
		return mLength == 0 || mBuffer == nullptr || mBufferSize == 0;
	}

	size_t Size()const
	{
		return mBufferSize;
	}

	T* c_str() { return mBuffer; }
	T* MutableBuffer() { return mBuffer; }

	const T* c_str()const { return mBuffer; }
	const T* Buffer()const { return mBuffer; }
	const T* LeftPtr()const { return mBuffer + mLength; }

	TStringRef<T> ToString()const { return TStringRef<T>(mBuffer, mLength); }
	size_t Length() const { return mLength; }
	void ForceSetLength(size_t length) { mLength = length; mBuffer[mLength] = 0; }
	void ForceAppendLength(size_t length) { mLength += length; mBuffer[mLength] = 0; }

	void ForceUpdateLength()
	{
		mLength = mBuffer != nullptr ? StdString::GetLength(mBuffer) : 0;
	}

	size_t LeftLength() const { return mBufferSize - mLength - 1; }

	intp HashCode()const
	{
		return HashUtility::HashString(mBuffer);
	}
public:
	int Compare(const TStringRef<T>& inString, bool isIgnoreCase = false)const
	{
		return ToString().Compare(inString, isIgnoreCase);
	}

	intp IndexOf(T inFindChar)const
	{
		RETURN_OBJECT_IF(IsEmpty(), -1);
		return ToString().IndexOf(inFindChar, 0);
	}

	intp IndexOf(T inFindChar, intp index)const
	{
		RETURN_OBJECT_IF(IsEmpty(), -1);
		return ToString().IndexOf(inFindChar, index);
	}

	intp IndexOf(const TStringRef<T>& inString, intp index = 0)const
	{
		RETURN_OBJECT_IF(IsEmpty(), -1);
		return ToString().IndexOf(inString, index);
	}

	intp IndexOfAny(const TStringRef<T>& inString, intp index = 0)const
	{
		RETURN_OBJECT_IF(IsEmpty(), -1);
		return ToString().IndexOfAny(inString, index);
	}

	intp PrevIndexOf(T inFindChar)const
	{
		RETURN_OBJECT_IF(IsEmpty(), -1);
		return ToString().PrevIndexOf(inFindChar, 0);
	}

	intp PrevIndexOf(T inFindChar, intp index)const
	{
		RETURN_OBJECT_IF(IsEmpty(), -1);
		return ToString().PrevIndexOf(inFindChar, index);
	}

	intp LastIndexOf(T inFindChar)const
	{
		RETURN_OBJECT_IF(IsEmpty(), -1);
		return ToString().LastIndexOf(inFindChar, 0);
	}

	intp LastIndexOf(T inFindChar, intp index)const
	{
		RETURN_OBJECT_IF(IsEmpty(), -1);
		return ToString().LastIndexOf(inFindChar, index);
	}

	intp LastIndexOf(const TStringRef<T>& inString, intp index = 0)const
	{
		RETURN_OBJECT_IF(IsEmpty(), -1);
		return ToString().LastIndexOf(inString, index);
	}

	intp LastIndexOfAny(const TStringRef<T>& inString, intp index = 0)const
	{
		RETURN_OBJECT_IF(IsEmpty(), -1);
		return ToString().LastIndexOfAny(inString, index);
	}

	bool IndicesOf(T val, List<intp>& outIndices)const
	{
		RETURN_OBJECT_IF(IsEmpty(), false);
		return ToString().IndicesOf(val, outIndices);
	}

	bool IndicesOf(const TStringRef<T>& val, List<intp>& outIndices)const
	{
		RETURN_OBJECT_IF(IsEmpty(), false);
		return ToString().IndicesOf(val, outIndices);
	}

	bool IndicesOfAny(const TStringRef<T>& val, List<intp>& outIndices)const
	{
		RETURN_OBJECT_IF(IsEmpty(), false);
		return ToString().IndicesOfAny(val, outIndices);
	}

	bool Contains(T inFindChar)const
	{
		RETURN_FALSE_IF(IsEmpty());
		return ToString().Contains(inFindChar);
	}

	bool Contains(const TStringRef<T>& inString)const
	{
		RETURN_FALSE_IF(IsEmpty());
		return ToString().Contains(inString);
	}

	bool ContainsAny(const TStringRef<T>&  inString)const
	{
		RETURN_FALSE_IF(IsEmpty());
		return ToString().ContainsAny(inString);
	}


	bool BeginWith(const TStringRef<T>& inString)const
	{
		RETURN_FALSE_IF(IsEmpty());
		return ToString().BeginWith(inString);
	}

	bool BeginWith(T val)const
	{
		RETURN_FALSE_IF(IsEmpty());
		return ToString().BeginWith(val);
	}

	bool EndWith(const TStringRef<T>& inString)const
	{
		RETURN_FALSE_IF(IsEmpty());
		return ToString().EndWith(inString);
	}

	bool EndWith(T val)const
	{
		RETURN_FALSE_IF(IsEmpty());
		return ToString().EndWith(val);
	}

	long ToInt()const
	{
		return ToString().ToInt(10);
	}

	long ToInt(int radix)const
	{
		return ToString().ToInt(radix);
	}

	long ToIntWithFailed(long val)const
	{
		return ToString().ToIntWithFailed(val);
	}
	long ToIntWithFailed(int radix, long val)const
	{
		return ToString().ToIntWithFailed(radix, val);
	}

	bool TryParseInt(long& outResult)const
	{
		RETURN_FALSE_IF(IsEmpty());
		return ToString().TryParseInt(outResult, 10);
	}

	bool TryParseInt(long& outResult, int radix)const
	{
		RETURN_FALSE_IF(IsEmpty());
		return ToString().TryParseInt(outResult, radix);
	}

	double ToDouble()const
	{
		return ToString().ToDouble();
	}
	double ToDoubleWithFailed(double val)const
	{
		return ToString().ToDoubleWithFailed(val);
	}
	bool TryParseDouble(double& outResult)const
	{
		RETURN_FALSE_IF(IsEmpty());
		return ToString().TryParseDouble(outResult);
	}



	size_t Count(T inChar)const
	{
		RETURN_OBJECT_IF(IsEmpty(), 0);
		return ToString().Count(inChar);
	}

	size_t Count(const TStringRef<T>& inString)const
	{
		RETURN_OBJECT_IF(IsEmpty(), 0);
		return ToString().Count(inString);
	}


	void CopyTo(BaseString& outString)const
	{
		RETURN_IF(IsEmpty());
		CopyTo(outString.Buffer(), outString.Size(), 0, mLength);
	}

	void CopyTo(BaseString& outString, size_t length)const
	{
		RETURN_IF(IsEmpty());
		CopyTo(outString.Buffer(), outString.Size(), 0, length);
	}

	void CopyTo(BaseString& outString, size_t beginIndex, size_t length)const
	{
		RETURN_IF(IsEmpty());
		CopyTo(outString.Buffer(), outString.Size());
	}

	void CopyTo(T* outBuffer, size_t outBufferSize)const
	{
		RETURN_IF(IsEmpty());
		CopyTo(outBuffer, outBufferSize, 0, mLength);
	}

	void CopyTo(T* outBuffer, size_t outBufferSize, size_t length)const
	{
		RETURN_IF(IsEmpty());
		CopyTo(outBuffer, outBufferSize, 0, length);
	}

	void CopyTo(T* outBuffer, size_t outBufferSize, size_t beginIndex, size_t length)const
	{
		RETURN_IF(IsEmpty());
		RETURN_IF(beginIndex + length > mLength);
		RETURN_IF(length > outBufferSize);
		Memory::SafeCopy(outBuffer, outBufferSize, mBuffer + beginIndex, length);
	}

	TStringRef<T> SubString(size_t index)const
	{
		if (IsEmpty())
		{
			return TStringRef<T>::Empty;
		}
		return TStringRef<T>(mBuffer + index, mLength - index);
	}
public:
	void ToCase(bool isLowCase)
	{
		RETURN_IF(IsEmpty());
		if (isLowCase)
		{
			ToLower();
		}
		else
		{
			ToUpper();
		}
	}

	void ToUpper()
	{
		RETURN_IF(IsEmpty());
		StdString::ToUpper(mBuffer, mLength);
	}

	void ToLower()
	{
		RETURN_IF(IsEmpty());
		StdString::ToLower(mBuffer, mLength);
	}

	void Reverse()
	{
		RETURN_IF(IsEmpty());
		StdString::Reverse(mBuffer);
	}

	bool ReplaceAllTo(T inChar)
	{
		RETURN_FALSE_IF(IsEmpty());
		return StdString::ReplaceAllTo(mBuffer, mBufferSize, inChar) == 0;
	}

	bool ReplaceTo(T inChar, size_t count)
	{
		RETURN_FALSE_IF(IsEmpty());
		return StdString::ReplaceAllToN(mBuffer, mBufferSize, inChar, count) == 0;
	}

	bool ReplaceAll(T oldChar, T newChar)
	{
		RETURN_FALSE_IF(IsEmpty());
		RETURN_FALSE_IF(oldChar == newChar);
		RETURN_FALSE_IF(mLength == 0);

		bool isFound = false;
		for (size_t i = 0; i < mLength; ++i)
		{
			if (mBuffer[i] == oldChar)
			{
				mBuffer[i] = newChar;
				isFound = true;
			}
		}
		return isFound;
	}

	bool ReplaceFirst(T oldChar, T newChar)
	{
		RETURN_FALSE_IF(IsEmpty());
		RETURN_FALSE_IF(oldChar == newChar);
		RETURN_FALSE_IF(mLength == 0);

		for (size_t i = 0; i < mLength; ++i)
		{
			if (mBuffer[i] == oldChar)
			{
				mBuffer[i] = newChar;
				return true;
			}
		}
		return false;
	}

	bool ReplaceLast(T oldChar, T newChar)
	{
		RETURN_FALSE_IF(IsEmpty());
		RETURN_FALSE_IF(oldChar == newChar);
		RETURN_FALSE_IF(mLength == 0);

		for (intp i = (intp)mLength - 1; i >= 0; --i)
		{
			if (mBuffer[i] == oldChar)
			{
				mBuffer[i] = newChar;
				return true;
			}
		}
		return false;
	}

	bool ReplaceAll(const TStringRef<T>& oldString, const TStringRef<T>& newString)
	{
		RETURN_FALSE_IF(IsEmpty());
		size_t oldLength = oldString.Length();
		size_t newLength = newString.Length();
		if (oldLength == newLength)
		{
			T* index = (T*)StdString::FindString(mBuffer, oldString.Buffer());
			while (index != nullptr)
			{
				Memory::SafeCopy(index, mBuffer + mBufferSize - index, newString.Buffer(), newLength);
				index += oldLength;
				index = (T*)StdString::FindString(index, oldString.Buffer());
			}
		}
		else if (oldLength > newLength)
		{
			T* index = (T*)StdString::FindString(mBuffer, oldString.Buffer());
			while (index != nullptr)
			{
				Memory::SafeCopy(index, mBuffer + mBufferSize - index, newString.Buffer(), newLength);
				index += newLength;

				Memory::SetZero(index, oldLength - newLength);
				index += oldLength - newLength;

				index = (T*)StdString::FindString(index, oldString.Buffer());
			}

			//do a compress 
			T* w = mBuffer;
			T* r = mBuffer;
			T* oldEnd = mBuffer + mLength;
			while (r != oldEnd)
			{
				if (*r == 0)
				{
					++r;
				}
				else
				{
					*w++ = *r++;
				}
			}

			*w = 0;

			mLength = w - mBuffer;
		}
		else
		{
			//find all str indices
			size_t dis = newLength - oldLength;
			List<intp> indices;
			if (!IndicesOf(oldString, indices))
			{
				return true;
			}
			//resize
			uintp count = indices.Count();
			size_t growLength = dis*count;
			if (mLength + growLength >= mBufferSize)
			{
				size_t newSize = Math::GetNewSizeOneAndHalf(mBufferSize, mLength + growLength + 1);
				RETURN_FALSE_IF_FALSE(ResizeHelper(newSize));
			}

			//copy str
			T* newEnd = mBuffer + mLength + growLength;	//not include '\0' after resize
			*newEnd = '\0';		//set '\0'
			T* oldEnd = mBuffer + mLength;	//include '\0'
			FOR_EACH_INT_END_BEGIN(i, (intp)count - 1, 0)
			{
				intp index = indices[i];
				T* curBegin = mBuffer + index;
				T* curEnd = curBegin + oldLength;

				intp leftCount = oldEnd - curEnd;
				Memory::SafeCopy(newEnd - leftCount, leftCount, curEnd, leftCount);//copy left str
				newEnd -= leftCount;

				Memory::SafeCopy(newEnd - newLength, newLength, newString.c_str(), newLength);//copy new str
				newEnd -= newLength;
				oldEnd = curBegin;
			}


			mLength += growLength;
			return true;

		}
		return true;
	}

	bool ReplaceFirst(const TStringRef<T>& oldString, const TStringRef<T>& newString)
	{
		RETURN_FALSE_IF(IsEmpty());

		intp index = IndexOf(oldString);
		if (index < 0)
		{
			return false;
		}

		size_t oldLength = oldString.Length();
		size_t newLength = newString.Length();

		if (oldLength == newLength)
		{
			Memory::SafeCopy(mBuffer + index, mBufferSize - index, newString.Buffer(), oldLength);
		}
		else if (oldLength > newLength)
		{
			Memory::SafeCopy(mBuffer + index, mBufferSize - index, newString.Buffer(), newLength);
			RemoveAt(index + newLength, oldLength - newLength);
		}
		else
		{
			size_t dis = newLength - oldLength;
			if (mLength + dis >= mBufferSize)
			{
				size_t newSize = Math::GetNewSizeOneAndHalf(mBufferSize, mLength + dis + 1);
				RETURN_FALSE_IF_FALSE(ResizeHelper(newSize));
			}

			//copy last string
			Memory::SafeCopy(mBuffer + index + newLength, mBufferSize + index - newLength, mBuffer + index + oldLength, mLength - index - oldLength);
			//copy new string
			Memory::SafeCopy(mBuffer + index, mBufferSize + index, newString.Buffer(), newLength);
			mLength += dis;
		}
		return true;
	}



	bool ReplaceLast(const TStringRef<T>& oldString, const TStringRef<T>& newString)
	{
		RETURN_FALSE_IF(IsEmpty());

		intp index = LastIndexOf(oldString);
		if (index < 0)
		{
			return false;
		}

		size_t oldLength = oldString.Length();
		size_t newLength = newString.Length();

		if (oldLength == newLength)
		{
			Memory::SafeCopy(mBuffer + index, mBufferSize - index, newString.Buffer(), oldLength);
		}
		else if (oldLength > newLength)
		{
			Memory::SafeCopy(mBuffer + index, mBufferSize - index, newString.Buffer(), newLength);
			RemoveAt(index + newLength, oldLength - newLength);
		}
		else
		{
			size_t dis = newLength - oldLength;
			if (mLength + dis >= mBufferSize)
			{
				size_t newSize = Math::GetNewSizeOneAndHalf(mBufferSize, mLength + dis + 1);
				RETURN_FALSE_IF_FALSE(ResizeHelper(newSize));
			}

			//copy last string
			Memory::SafeCopy(mBuffer + index + newLength, mBufferSize + index - newLength, mBuffer + index + oldLength, mLength - index - oldLength);
			//copy new string
			Memory::SafeCopy(mBuffer + index, mBufferSize + index, newString.Buffer(), newLength);
			mLength += dis;
		}

		return true;
	}


	bool RemoveBeginAny(const TStringRef<T>& chars)
	{
		RETURN_FALSE_IF(IsEmpty());
		T* p = mBuffer;

		for (size_t i = 0; i < mLength; ++i)
		{
			if (chars.Contains(mBuffer[i]))
			{
				++p;
			}
			else
			{
				break;
			}
		}
		return RemoveAt(0, p - mBuffer);
	}

	bool RemoveBeginAnyExclude(const TStringRef<T>& chars)
	{
		RETURN_FALSE_IF(IsEmpty());
		T* p = mBuffer;

		for (size_t i = 0; i < mLength; ++i)
		{
			if (!chars.Contains(mBuffer[i]))
			{
				++p;
			}
			else
			{
				break;
			}
		}
		return RemoveAt(0, p - mBuffer);
	}

	bool RemoveBegin(T inChar)
	{
		RETURN_FALSE_IF(IsEmpty());
		T* p = mBuffer;

		for (size_t i = 0; i < mLength; ++i)
		{
			if (mBuffer[i] == inChar)
			{
				++p;
			}
			else
			{
				break;
			}
		}
		return RemoveAt(0, p - mBuffer);
	}

	bool RemoveBeginExclude(T inChar)
	{
		RETURN_FALSE_IF(IsEmpty());
		T* p = mBuffer;

		for (size_t i = 0; i < mLength; ++i)
		{
			if (mBuffer[i] != inChar)
			{
				++p;
			}
			else
			{
				break;
			}
		}
		return RemoveAt(0, p - mBuffer);
	}

	bool RemoveEnd(T inChar)
	{
		RETURN_FALSE_IF(IsEmpty());
		T* p = mBuffer + mLength - 1;

		for (intp i = mLength - 1; i >= 0; --i)
		{
			if (mBuffer[i] == inChar)
			{
				--p;
			}
			else
			{
				break;
			}
		}
		return RemoveAt(p - mBuffer + 1);
	}

	bool RemoveEndExclude(T inChar)
	{
		RETURN_FALSE_IF(IsEmpty());
		T* p = mBuffer + mLength - 1;

		for (intp i = mLength - 1; i >= 0; --i)
		{
			if (mBuffer[i] != inChar)
			{
				--p;
			}
			else
			{
				break;
			}
		}
		return RemoveAt(p - mBuffer + 1);
	}

	bool RemoveEndAny(const TStringRef<T>& chars)
	{
		RETURN_FALSE_IF(IsEmpty());
		T* p = mBuffer + mLength - 1;

		for (intp i = mLength - 1; i >= 0; --i)
		{
			if (chars.Contains(mBuffer[i]))
			{
				--p;
			}
			else
			{
				break;
			}
		}
		return RemoveAt(p - mBuffer + 1);
	}

	bool RemoveEndAnyExclude(const TStringRef<T>& chars)
	{
		RETURN_FALSE_IF(IsEmpty());
		T* p = mBuffer + mLength - 1;

		for (intp i = mLength - 1; i >= 0; --i)
		{
			if (!chars.Contains(mBuffer[i]))
			{
				--p;
			}
			else
			{
				break;
			}
		}
		return RemoveAt(p - mBuffer + 1);
	}

	bool WriteChar(T inChar)	//alias
	{
		return Insert(mLength, inChar, 1);
	}

	bool Append(T inChar)
	{
		return Insert(mLength, inChar, 1);
	}

	bool Append(T inChar, size_t count)
	{
		return Insert(mLength, inChar, count);
	}

	bool Append(const TStringRef<T>& inString)
	{
		return Insert(mLength, inString);
	}

	bool Append(const T* buffer, size_t length)
	{
		return Insert(mLength, buffer, length);
	}

	bool AppendLine()
	{
		return Append(LineSeparator);
	}

	bool AppendLine(T inChar)
	{
		if (Insert(mLength, inChar, 1))
		{
			return Append(LineSeparator);
		}

		return false;
	}

	bool AppendLine(T inChar, size_t count)
	{
		if (Insert(mLength, inChar, count))
		{
			return Append(LineSeparator);
		}

		return false;
	}

	bool AppendLine(const TStringRef<T>& inString)
	{
		if (Insert(mLength, inString))
		{
			return Append(LineSeparator);
		}
		return false;
	}

	bool AppendLine(const T* buffer, size_t length)
	{
		if (Insert(mLength, buffer, length))
		{
			return Append(LineSeparator);
		}
		return false;
	}

	bool Push(T inChar)
	{
		return Insert(0, inChar, 1);
	}

	bool Push(T inChar, size_t count)
	{
		return Insert(0, inChar, count);
	}

	bool Push(const TStringRef<T>& inString)
	{
		return Insert(0, inString);
	}

	/*bool Push(const BaseString<T>& inString)
	{
		return Insert(0, inString);
	}*/

	bool Insert(size_t index, T inChar)
	{
		return Insert(index, inChar, 1);
	}

	bool Insert(size_t index, T inChar, size_t count)
	{
		RETURN_FALSE_IF_ZERO(inChar);
		RETURN_FALSE_IF_ZERO(count);
		RETURN_FALSE_IF(index > mLength);

		if (mLength + count >= mBufferSize)
		{
			size_t size = Math::GetNewSizeOneAndHalf(mBufferSize, mLength + count + 1);
			RETURN_FALSE_IF_FALSE(ResizeHelper(size));
		}

		if (count == 1)
		{
			if (index != mLength)
			{
				Memory::SafeCopy(mBuffer + index + count, mBufferSize - index - count, mBuffer + index, mLength - index);
			}

			mBuffer[index] = inChar;
		}
		else
		{
			Memory::SafeCopy(mBuffer + index + count, mBufferSize - index - count, mBuffer + index, mLength - index);
			Memory::Set(mBuffer + index, inChar, count);
		}
		mLength += count;
		mBuffer[mLength] = 0;

		return true;
	}


	bool Insert(size_t index, const TStringRef<T>& inString)
	{
		return Insert(index, inString.Buffer(), inString.Length());
	}

	//bool Insert(size_t index, const BaseString<T>& inString)
	//{
	//	return Insert(index, inString.Buffer(), inString.Length());
	//}

	bool Insert(size_t index, const T* buffer, size_t length)
	{
		RETURN_FALSE_IF_NULL(buffer);
		RETURN_FALSE_IF_ZERO(length);
		RETURN_FALSE_IF(index > mLength);

		if (mLength + length >= mBufferSize)
		{
			size_t size = Math::GetNewSizeOneAndHalf(mBufferSize, mLength + length + 1);
			RETURN_FALSE_IF_FALSE(ResizeHelper(size));
		}

		RETURN_FALSE_IF(mLength + length > mBufferSize);
		Memory::SafeCopy(mBuffer + index + length, mBufferSize - index - length, mBuffer + index, mLength - index + 1);	//+1 to copy '\0'
		Memory::SafeCopy(mBuffer + index, mBufferSize - index, buffer, length);
		mLength += length;
		mBuffer[mLength] = 0;

		return true;
	}

	bool RemoveAll(T inChar)
	{
		RETURN_FALSE_IF(IsEmpty());
		T* p = mBuffer;

		for (size_t i = 0; i < mLength; ++i)
		{
			if (mBuffer[i] != inChar)
			{
				*p = mBuffer[i];
				++p;
			}
		}

		++p;
		*p = 0;
		mLength = p - mBuffer;

		return true;
	}

	bool RemoveFirst()
	{
		return RemoveAt(0);
	}

	bool RemoveFirst(T inChar)
	{
		RETURN_FALSE_IF(IsEmpty());
		intp index = IndexOf(inChar);
		if (index >= 0)
		{
			return RemoveAt(index);
		}
		return false;
	}

	bool RemoveLast(T inChar)
	{
		RETURN_FALSE_IF(IsEmpty());
		intp index = LastIndexOf(inChar);
		if (index >= 0)
		{
			return RemoveAt(index);
		}
		return false;
	}

	bool RemoveLast()
	{
		return RemoveAt(mLength - 1);
	}
	bool RemoveAt(size_t index)
	{
		return RemoveAt(index, 1);
	}

	bool RemoveAt(size_t index, size_t length)
	{
		RETURN_FALSE_IF(IsEmpty());
		RETURN_FALSE_IF(index + length > mLength);
		Memory::SafeCopy(mBuffer + index, mBufferSize - index, mBuffer + index + length, mLength - index - length + 1);	//+1 to copy '\0'
		mLength -= length;
		return true;
	}

	bool RemoveFrom(size_t index)
	{
		return RemoveAt(index, mLength - index);
	}

	bool RemoveAll(const TStringRef<T>& inString)
	{
		RETURN_FALSE_IF(IsEmpty());
		T *w = mBuffer;
		T* r = mBuffer;
		const T *p = inString.Buffer();
		const T *q = p;
		bool isFound = false;

		while (*r != 0)
		{
			if (*p == 0)
			{
				p = q;
			}

			if (*r != *p)
			{
				*w++ = *r++;
				p = q;
				isFound = true;
			}
			else
			{
				++r;
				++p;
			}
		}

		if (*p != 0)
		{
			r -= p - inString.Buffer();
			StdString::CopyString(w, mBufferSize + mBuffer - w, r);
			mLength += p - inString.Buffer();
		}
		else
		{
			*w = 0;
			mLength = w - mBuffer;
		}
		return isFound;
	}

	bool RemoveFirst(const TStringRef<T>& inString)
	{
		RETURN_FALSE_IF(IsEmpty());
		intp index = IndexOf(inString);
		if (index >= 0)
		{
			return RemoveAt(index, inString.Length());
		}
		return false;
	}
	bool RemoveLast(const TStringRef<T>& inString)
	{
		RETURN_FALSE_IF(IsEmpty());
		intp index = LastIndexOf(inString);
		if (index >= 0)
		{
			return RemoveAt(index, inString.Length());
		}
		return false;
	}

	bool TrimAll()
	{
		bool isSuccess1 = TrimBegin();
		bool isSuccess2 = TrimEnd();

		return isSuccess1 || isSuccess2;
	}

	bool TrimBegin()
	{
		return RemoveBeginAny(StdString::ConstValues<T>::TrimChars);
	}

	bool TrimEnd()
	{
		return RemoveEndAny(StdString::ConstValues<T>::TrimChars);
	}

	bool FormatC(const T* format, ...)
	{
		RETURN_FALSE_IF_NULL(format);
		va_list args;
		va_start(args, format);
		FormatC(format, args);
		va_end(args);
		return true;
	}

	bool FormatC(const T* format, va_list args)
	{
		RETURN_FALSE_IF_NULL(format);
		int length = StdString::GetFormatLength(format, args);
		size_t size = length + 1;	//for 0
		RETURN_FALSE_IF(size <= 0);

		if (size >= mBufferSize)
		{
			size_t newSize = Math::GetNewSizeOneAndHalf(mBufferSize, size);

			RETURN_FALSE_IF_FALSE(ResizeHelper(newSize));
		}
		StdString::VSPrintf(mBuffer, size, format, args);
		mLength = length;

		return true;
	}



	template<typename... TArgs>
	bool Format(const T* format, const TArgs&... args);

	template<typename... TArgs>
	bool AppendFormat(const T* format, const TArgs&... args);

	bool Format(const T* format)
	{
		Clear();
		*this = format;
		return true;
	}

	bool AppendFormat(const T* format)
	{
		return Append(format);
	}

	MemoryData<T> ToMemoryData()const { return MemoryData<T>::FromStatic(mBuffer, mLength); }
protected:
	virtual bool ResizeHelper(size_t size) { return false; }
protected:
	T* mBuffer = nullptr;
	size_t mBufferSize = 0;
	size_t mLength = 0;
};




MEDUSA_END;