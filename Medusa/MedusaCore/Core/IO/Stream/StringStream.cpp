// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Core/IO/Stream/StringStream.h"
#include "Core/Memory/Memory.h"
#include "Core/Math/Math.h"

MEDUSA_BEGIN;

StringStream::StringStream(size_t capacity/*=0*/, bool isExpandable /*= true*/) :mPos(0)
{
	mData = new HeapString(capacity);
	mIsOwner = true;
	mIsBufferOwner = true;
	mSupportedOperation = StreamDataOperation::ReadWriteSeek;
	if (isExpandable)
	{
		MEDUSA_FLAG_ADD(mSupportedOperation, StreamDataOperation::Grow);
	}
}

StringStream::StringStream(HeapString& data)
	: mData(&data), mPos(0), mIsOwner(false),mIsBufferOwner(false)
{
	mSupportedOperation = StreamDataOperation::ReadWriteSeek;
}

StringStream::StringStream(const HeapString& data)
	: mData((HeapString*)&data), mPos(0), mIsOwner(false), mIsBufferOwner(false)
{
	mSupportedOperation = StreamDataOperation::ReadSeek;
}

StringStream::StringStream(const StringRef& data)
	: mData(new HeapString()), mPos(0), mIsOwner(true), mIsBufferOwner(false)
{
	mData->ForceSetBuffer((char*)data.c_str());
	mData->ForceSetLength(data.Length());
	mSupportedOperation = StreamDataOperation::ReadSeek;
}

StringStream::StringStream(const StringStream& other)
	:mPos(other.mPos),
	mIsOwner(other.mIsOwner),
	mIsBufferOwner(other.mIsBufferOwner),
	mSupportedOperation(other.mSupportedOperation)
{
	if (other.mIsOwner)
	{
		if (mIsBufferOwner)
		{
			mData = new HeapString(*other.mData);
		}
		else
		{
			mData = new HeapString();
			mData->ForceSetBuffer(other.mData->MutableBuffer());
			mData->ForceSetLength(other.mData->Length());
		}
	}
	else
	{
		mData = other.mData;
	}
}

StringStream& StringStream::operator=(const StringStream& other)
{
	if (this != &other)
	{
		Close();
		mPos = other.mPos;
		mIsOwner = other.mIsOwner;
		mIsBufferOwner = other.mIsBufferOwner;
		mSupportedOperation = other.mSupportedOperation;

		if (other.mIsOwner)
		{
			if (mIsBufferOwner)
			{
				mData = new HeapString(*other.mData);
			}
			else
			{
				mData = new HeapString();
				mData->ForceSetBuffer(other.mData->MutableBuffer());
				mData->ForceSetLength(other.mData->Length());
			}
		}
		else
		{
			mData = other.mData;
		}

	}
	return *this;
}



StringStream::StringStream(StringStream&& other)
	: mData(other.mData),
	mPos(other.mPos),
	mIsOwner(other.mIsOwner),
	mIsBufferOwner(other.mIsBufferOwner),
	mSupportedOperation(other.mSupportedOperation)
{
	other.mPos = 0;
	other.mData = nullptr;
	other.mIsOwner = false;
	other.mIsBufferOwner = false;
	other.mSupportedOperation = StreamDataOperation::None;
}

StringStream& StringStream::operator=(StringStream&& other)
{
	if (this != &other)
	{
		Close();
		mData = std::move(other.mData);
		mPos = other.mPos;
		mIsOwner = other.mIsOwner;
		mIsBufferOwner = other.mIsBufferOwner;
		mSupportedOperation = other.mSupportedOperation;

		other.mData = nullptr;
		other.mPos = 0;
		other.mIsOwner = false;
		other.mIsBufferOwner = false;
		other.mSupportedOperation = StreamDataOperation::None;
	}
	return *this;
}


StringStream::~StringStream(void)
{
	Close();
}

StringStream StringStream::OpenReadWrite(HeapString& data)
{
	return StringStream(data);
}

StringStream StringStream::OpenRead(const HeapString& data)
{
	return StringStream(data);
}

StringStream StringStream::Create(size_t capacity /*= 0*/, bool isExpandable /*= true*/)
{
	return StringStream(capacity, isExpandable);
}

HeapString StringStream::Release()
{
	HeapString str;
	mSupportedOperation = StreamDataOperation::None;
	if (mIsOwner)
	{
		if (!mIsBufferOwner)
		{
			mData->ForceReleaseBuffer();
		}
		else
		{
			str.ForceSetBuffer(mData->MutableBuffer());
			str.ForceSetBufferSize(mData->Size());
			str.ForceSetLength(mPos);
			mData->ForceReleaseBuffer();
		}

		SAFE_DELETE(mData);
		mIsOwner = false;
		mIsBufferOwner = false;
	}
	else
	{
		mData = nullptr;
	}
	mPos = 0;
	return str;
}

bool StringStream::Flush()
{
	return true;
}

bool StringStream::Close()
{
	mPos = 0;
	mSupportedOperation = StreamDataOperation::None;
	if (mIsOwner)
	{
		if (!mIsBufferOwner)
		{
			mData->ForceReleaseBuffer();
		}

		SAFE_DELETE(mData);
		mIsOwner = false;
		mIsBufferOwner = false;
	}
	else
	{
		mData = nullptr;
	}

	return true;
}

bool StringStream::Seek(intp offset, SeekOrigin direction /*= SeekOrigin::Current*/)const
{
	RETURN_FALSE_IF_FALSE(CanSeek());

	size_t newPos = mPos;
	switch (direction)
	{
	case SeekOrigin::Head:
		newPos = (size_t)offset;
		break;
	case SeekOrigin::Current:
		newPos += (size_t)offset;
		break;
	case SeekOrigin::End:
		newPos = mData->Length() + (size_t)offset;
		break;
	}

	if (newPos <= (int)mData->Length())
	{
		mPos = newPos;
		return true;
	}
	return false;
}

bool StringStream::SetLength(uintp val)
{
	RETURN_FALSE_IF_FALSE(CanWrite());

	if (mData->Length() < val)
	{
		mData->ReserveLength((size_t)val);
	}

	mData->ForceSetLength(val);
	return true;
}


size_t StringStream::ReadDataTo(MemoryData& outData, DataReadingMode mode/*=DataReadingMode::AlwaysCopy*/)const
{
	RETURN_ZERO_IF_FALSE(CanRead());
	size_t readSize = Math::Min(mData->Length() - (size_t)mPos, outData.Size());

	switch (mode)
	{
	case DataReadingMode::AlwaysCopy:
		Memory::SafeCopy(outData.MutableData(), outData.Size(), (byte*)mData->Buffer() + mPos, readSize);
		break;
	case DataReadingMode::DirectMove:
		outData = MemoryData::FromStatic((byte*)mData->Buffer() + mPos, readSize);
		break;
	default:
		break;
	}

	mPos += readSize;
	return readSize;
}

size_t StringStream::WriteData(const MemoryData& data, DataReadingMode mode /*= DataReadingMode::AlwaysCopy*/)
{
	RETURN_ZERO_IF_FALSE(CanWrite());

	StringRef str((char*)data.Data(), data.Size());
	mData->Append(str);
	return data.Size();
}

int StringStream::PeekChar()const
{
	RETURN_OBJECT_IF_FALSE(CanRead(), -1);
	return *(mData->c_str() + mPos);
}

int StringStream::PeekWChar()const
{
	RETURN_OBJECT_IF_FALSE(CanRead(), -1);
	if (mPos + sizeof(wchar) - 1 >= mData->Size())
	{
		return -1;
	}
	return *(wchar*)(mData->c_str() + mPos);
}


int StringStream::ReadChar()const
{
	RETURN_OBJECT_IF_FALSE(CanRead(), -1);
	return *(mData->c_str() + mPos++);
}

int StringStream::ReadWChar()const
{
	RETURN_OBJECT_IF_FALSE(CanRead(), -1);
	if (mPos + sizeof(wchar) - 1 >= mData->Size())
	{
		return -1;
	}
	int c = *(wchar*)(mData->c_str() + mPos);
	mPos += sizeof(wchar);
	return c;
}

bool StringStream::WriteChar(char val)
{
	RETURN_FALSE_IF_FALSE(CanWrite());
	mData->Append(val);
	++mPos;
	return true;
}

bool StringStream::WriteChar(wchar val)
{
	RETURN_FALSE_IF_FALSE(CanWrite());

	mData->ReserveLeftLength(sizeof(wchar));
	*(wchar*)(mData->c_str() + mPos) = val;
	mPos += sizeof(wchar);
	return true;
}

size_t StringStream::ReadStringTo(HeapString& outString)const
{
	RETURN_ZERO_IF_FALSE(CanRead());

	char* buffer = (char*)mData->c_str() + mPos;
	size_t size = LeftLength();

	size_t i = 0;
	for (; i < size; ++i)
	{
		if (buffer[i] == '\0')
		{
			outString.Append(buffer, i);
			mPos += i + 1;
			return i + 1;
		}
	}

	if (i == size)
	{
		//reach end
		outString.Append(buffer, i);
		mPos += i;
		return i;
	}

	return 0;
}

size_t StringStream::ReadStringTo(WHeapString& outString)const
{
	RETURN_ZERO_IF_FALSE(CanRead());

	const wchar* begin = (const wchar*)mData->c_str() + mPos;
	const wchar* end = (const wchar*)mData->c_str() + mData->Size();
	const wchar* cur = begin;
	for (; cur < end; ++cur)
	{
		if (*cur == L'\0')
		{
			outString.Append(begin, cur - begin);
			size_t count = (cur - begin + 1)*sizeof(wchar_t);
			mPos += count;
			return count;
		}
	}

	if (cur >= end)
	{
		--cur;	//roll back one wchar
		//reach end
		outString.Append(begin, cur - begin);
		size_t count = (cur - begin + 1)*sizeof(wchar_t);
		mPos += count;
		return count;
	}

	return 0;
}

size_t StringStream::ReadLineToString(HeapString& outString, bool includeNewLine/*=true*/)const
{
	RETURN_ZERO_IF_FALSE(CanRead());

	char* buffer = (char*)mData->c_str();
	size_t size = mData->Size();
	size_t oldPos = mPos;

	while (true)
	{
		if (mPos >= size)
		{
			outString.Append(buffer + oldPos, mPos - oldPos);
			return mPos - oldPos;
		}

		switch (buffer[mPos])
		{
		case '\0':
			outString.Append(buffer + oldPos, mPos - oldPos);
			return mPos - oldPos;
		case StdString::ConstValues<char>::LineSeparator:
		case StdString::ConstValues<char>::Return:
			if (includeNewLine)
			{
				++mPos;	//skip '\n'
				if (mPos < size&&StdString::ConstValues<char>::IsNewLine(buffer[mPos]))		//\r\n
				{
					++mPos;
				}
				outString.Append(buffer + oldPos, mPos - oldPos);	//include '\n'
			}
			else
			{
				outString.Append(buffer + oldPos, mPos - oldPos);
				++mPos;	//skip '\n'
				if (mPos < size&&StdString::ConstValues<char>::IsNewLine(buffer[mPos]))		//\r\n
				{
					++mPos;
				}
			}

			return mPos - oldPos;
		default:
			break;
		}
		++mPos;
	}
	return mPos - oldPos;
}

size_t StringStream::ReadLineToString(WHeapString& outString, bool includeNewLine/*=true*/)const
{
	RETURN_ZERO_IF_FALSE(CanRead());
	wchar* buffer = (wchar*)mData->c_str();
	size_t size = mData->Size() / sizeof(wchar);
	mPos /= sizeof(wchar);
	size_t oldPos = mPos;

	while (true)
	{
		if (mPos >= size)
		{
			outString.Append(buffer + oldPos, mPos - oldPos);
			mPos *= sizeof(wchar);

			return mPos - oldPos;
		}

		switch (buffer[mPos])
		{
		case L'\0':
			outString.Append(buffer + oldPos, mPos - oldPos);
			mPos *= sizeof(wchar);

			return mPos - oldPos;
		case StdString::ConstValues<wchar>::LineSeparator:
		case StdString::ConstValues<wchar>::Return:
			if (includeNewLine)
			{
				++mPos;
				if (mPos + 1 < size&&StdString::ConstValues<wchar>::IsNewLine(buffer[mPos + 1]))
				{
					++mPos;
				}
				outString.Append(buffer + oldPos, mPos - oldPos);	//include '\n'
			}
			else
			{
				outString.Append(buffer + oldPos, mPos - oldPos);	//include '\n'
				++mPos;
				if (mPos + 1 < size&&StdString::ConstValues<wchar>::IsNewLine(buffer[mPos + 1]))
				{
					++mPos;
				}
			}
			mPos *= sizeof(wchar);

			return mPos - oldPos;
		default:
			break;
		}
		++mPos;
	}
	return mPos - oldPos;
}

size_t StringStream::WriteString(const StringRef& str, bool withNullTermitated /*= true*/)
{
	RETURN_ZERO_IF_FALSE(CanWrite());
	mData->Append(str);
	size_t size = str.Length();
	if (withNullTermitated)
	{
		size += WriteChar('\0') ? sizeof(char) : 0;
	}
	return size;
}

size_t StringStream::WriteString(const WStringRef& str, bool withNullTermitated /*= true*/)
{
	RETURN_ZERO_IF_FALSE(CanWrite());

	HeapString aStr=StringParser::ToA(str);
	mData->Append(aStr);
	size_t size = aStr.Length();
	if (withNullTermitated)
	{
		size += WriteChar(L'\0') ? sizeof(wchar_t) : 0;
	}
	return size;
}

bool StringStream::CanRead() const
{
	if (MEDUSA_FLAG_HAS(mSupportedOperation, StreamDataOperation::Read))
	{
		return mPos < mData->Length();
	}
	return false;
}

bool StringStream::CanWrite() const
{
	if (MEDUSA_FLAG_HAS(mSupportedOperation, StreamDataOperation::Write))
	{
		return (mPos < mData->Size());
	}
	return false;
}

bool StringStream::CanSeek() const
{
	return MEDUSA_FLAG_HAS(mSupportedOperation, StreamDataOperation::Seek);
}

StreamDataOperation StringStream::Operations() const
{
	return mSupportedOperation;
}


MEDUSA_END;

