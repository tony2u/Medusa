// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Core/IO/Stream/MemoryStream.h"
#include "Core/Memory/Memory.h"
#include "Core/Math/Math.h"

MEDUSA_BEGIN;

MemoryStream::MemoryStream(size_t capacity/*=0*/, bool isExpandable /*= true*/) :mPos(0)
{
	mData = MemoryData::Alloc(capacity);
	mSupportedOperation = StreamDataOperation::ReadWriteSeek;
	if (isExpandable)
	{
		MEDUSA_FLAG_ADD(mSupportedOperation, StreamDataOperation::Grow);
	}
}

MemoryStream::MemoryStream(MemoryData& data)
	: mData(data), mPos(0)
{
	mSupportedOperation = StreamDataOperation::ReadWriteSeek;
}

MemoryStream::MemoryStream(const MemoryData& data)
	: mData(data), mPos(0)
{
	mSupportedOperation = StreamDataOperation::ReadSeek;
}

MemoryStream::MemoryStream(const MemoryStream& other)
	: mData(other.mData),
	mPos(other.mPos),
	mSupportedOperation(other.mSupportedOperation)
{
}

MemoryStream& MemoryStream::operator=(const MemoryStream& other)
{
	if (this != &other)
	{
		Close();
		mData = other.mData;
		mPos = other.mPos;
		mSupportedOperation = other.mSupportedOperation;
	}
	return *this;
}



MemoryStream::MemoryStream(MemoryStream&& other)
	: mData(std::move(other.mData)),
	mPos(other.mPos),
	mSupportedOperation(other.mSupportedOperation)
{

}



MemoryStream& MemoryStream::operator=(MemoryStream&& other)
{
	if (this != &other)
	{
		Close();
		mData = std::move(other.mData);
		mPos = other.mPos;
		mSupportedOperation = other.mSupportedOperation;

		other.mPos = 0;
		other.mSupportedOperation = StreamDataOperation::None;

	}
	return *this;
}


MemoryStream::~MemoryStream(void)
{
	Close();
}

MemoryStream MemoryStream::OpenReadWrite(MemoryData& data)
{
	return MemoryStream(data);
}

MemoryStream MemoryStream::OpenRead(const MemoryData& data)
{
	return MemoryStream(data);
}

MemoryStream MemoryStream::Create(size_t capacity /*= 0*/, bool isExpandable /*= true*/)
{
	return MemoryStream(capacity, isExpandable);
}


size_t MemoryStream::ReleaseToString(HeapString& outString)
{
	mData.ForceRetain();
	outString.ForceSetBuffer((char*)mData.MutableData());
	outString.ForceSetBufferSize(mData.ByteSize());
	outString.ForceSetLength(mPos);
	return mPos;
}

bool MemoryStream::Flush()
{
	return true;
}

bool MemoryStream::Close()
{
	mPos = 0;
	mSupportedOperation = StreamDataOperation::None;
	mData = MemoryData::Empty;

	return true;
}

bool MemoryStream::Seek(intp offset, SeekOrigin direction /*= SeekOrigin::Current*/)const
{
	RETURN_FALSE_IF_FALSE(CanSeek());

	size_t newPos = mPos;
	switch (direction)
	{
	case SeekOrigin::Begin:
		newPos = (size_t)offset;
		break;
	case SeekOrigin::Current:
		newPos += (size_t)offset;
		break;
	case SeekOrigin::End:
		newPos = mData.Size() + (size_t)offset;
		break;
	}

	if (newPos <= (int)mData.Size())
	{
		mPos = newPos;
		return true;
	}
	return false;
}

bool MemoryStream::SetLength(uintp val)
{
	RETURN_FALSE_IF_FALSE(CanWrite());

	if (CanGrow())
	{
		if (mData.Size() < val)
		{
			return Resize((size_t)val);
		}
	}
	else
	{
		if (mData.Size() < val)
		{
			return false;
		}
		mData.ForceSetSize((size_t)val);
	}
	return true;
}

bool MemoryStream::CanGrow() const
{
	return MEDUSA_FLAG_HAS(mSupportedOperation, StreamDataOperation::Grow);
}

bool MemoryStream::Resize(size_t size)
{
	//always to extend to bigger size
	RETURN_FALSE_IF(mData.Size() >= size);
	byte* buffer = mData.MutableData();
	Memory::Realloc(buffer,mData.Size(),size);
	mData.ForceSetData(buffer);
	mData.ForceSetSize(size);
	mData.ForceEnsureRefCount();	//maybe mData is empty before
	return true;
}

size_t MemoryStream::ReadDataTo(MemoryData& outData, DataReadingMode mode/*=DataReadingMode::AlwaysCopy*/)const
{
	RETURN_ZERO_IF_FALSE(CanRead());
	size_t readSize = Math::Min(mData.Size() - (size_t)mPos, outData.Size());

	switch (mode)
	{
	case DataReadingMode::AlwaysCopy:
		Memory::SafeCopy(outData.MutableData(), outData.Size(), mData.Data() + mPos, readSize);
		break;
	case DataReadingMode::DirectMove:
		outData = MemoryData::FromStatic(mData.Data() + mPos, readSize);
		break;
	default:
		break;
	}

	mPos += readSize;
	return readSize;
}

size_t MemoryStream::WriteData(const MemoryData& data, DataReadingMode mode /*= DataReadingMode::AlwaysCopy*/)
{
	RETURN_ZERO_IF_FALSE(CanWrite());

	if (mode == DataReadingMode::DirectMove&&mPos == 0)
	{
		mData = data;
		mSupportedOperation = StreamDataOperation::ReadWriteSeek;
		return data.Size();
	}

	size_t writeSize = data.Size();
	size_t newSize = (size_t)mPos + data.Size();

	if (newSize > mData.Size())
	{
		if (CanGrow())
		{
			newSize = Math::GetNewSizeOneAndHalf(mData.Size(), newSize);
			Resize(newSize);
		}
		else
		{
			writeSize = mData.Size() - (size_t)mPos;
		}
	}

	Memory::SafeCopy(mData.MutableData() + mPos, mData.Size() - (size_t)mPos, data.Data(), writeSize);
	mPos += writeSize;
	return writeSize;



}

int MemoryStream::PeekChar()const
{
	RETURN_OBJECT_IF_FALSE(CanRead(), -1);
	return *(mData.Data() + mPos);
}

int MemoryStream::PeekWChar()const
{
	RETURN_OBJECT_IF_FALSE(CanRead(), -1);
	if (mPos + sizeof(wchar) - 1 >= mData.Size())
	{
		return -1;
	}
	return *(wchar*)(mData.Data() + mPos);
}


int MemoryStream::ReadChar()const
{
	RETURN_OBJECT_IF_FALSE(CanRead(), -1);
	return *(mData.Data() + mPos++);
}

int MemoryStream::ReadWChar()const
{
	RETURN_OBJECT_IF_FALSE(CanRead(), -1);
	if (mPos + sizeof(wchar) - 1 >= mData.Size())
	{
		return -1;
	}
	int c = *(wchar*)(mData.Data() + mPos);
	mPos += sizeof(wchar);
	return c;
}

bool MemoryStream::WriteChar(char val)
{
	RETURN_FALSE_IF_FALSE(CanWrite());

	if (mPos >= mData.Size())
	{
		RETURN_FALSE_IF_FALSE(CanGrow());
		size_t newSize = (size_t)mPos + 1;
		newSize = Math::GetNewSizeOneAndHalf(mData.Size(), newSize);
		Resize(newSize);
	}

	*(mData.MutableData() + mPos++) = val;
	return true;
}

bool MemoryStream::WriteChar(wchar val)
{
	RETURN_FALSE_IF_FALSE(CanWrite());

	if (mPos + sizeof(wchar) - 1 >= mData.Size())
	{
		RETURN_FALSE_IF_FALSE(CanGrow());
		size_t newSize = (size_t)mPos + sizeof(wchar);
		newSize = Math::GetNewSizeOneAndHalf(mData.Size(), newSize);
		Resize(newSize);
	}

	*(wchar*)(mData.Data() + mPos) = val;
	mPos += sizeof(wchar);
	return true;
}

size_t MemoryStream::ReadStringTo(HeapString& outString)const
{
	RETURN_ZERO_IF_FALSE(CanRead());

	char* buffer = (char*)mData.Data() + mPos;
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

size_t MemoryStream::ReadStringTo(WHeapString& outString)const
{
	RETURN_ZERO_IF_FALSE(CanRead());

	const wchar* begin = (const wchar*)mData.Data() + mPos;
	const wchar* end = (const wchar*)mData.Data() + mData.Size();
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

size_t MemoryStream::ReadLineToString(HeapString& outString, bool includeNewLine/*=true*/)const
{
	RETURN_ZERO_IF_FALSE(CanRead());

	char* buffer = (char*)mData.Data();
	size_t size = mData.Size();
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

size_t MemoryStream::ReadLineToString(WHeapString& outString, bool includeNewLine/*=true*/)const
{
	RETURN_ZERO_IF_FALSE(CanRead());
	wchar* buffer = (wchar*)mData.Data();
	size_t size = mData.Size() / sizeof(wchar);
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

size_t MemoryStream::WriteString(const StringRef& str, bool withNullTermitated /*= true*/)
{
	RETURN_ZERO_IF_FALSE(CanWrite());

	MemoryData data = str.ToData().Cast<byte>();
	size_t size = WriteData(data);
	if (withNullTermitated)
	{
		size += WriteChar('\0') ? sizeof(char) : 0;
	}
	return size;
}

size_t MemoryStream::WriteString(const WStringRef& str, bool withNullTermitated /*= true*/)
{
	RETURN_ZERO_IF_FALSE(CanWrite());
	MemoryData data = str.ToData().Cast<byte>();
	size_t size = WriteData(data);
	if (withNullTermitated)
	{
		size += WriteChar(L'\0') ? sizeof(wchar_t) : 0;
	}
	return size;
}

bool MemoryStream::CanRead() const
{
	if (MEDUSA_FLAG_HAS(mSupportedOperation, StreamDataOperation::Read))
	{
		return mPos < mData.Size();
	}
	return false;
}

bool MemoryStream::CanWrite() const
{
	if (MEDUSA_FLAG_HAS(mSupportedOperation, StreamDataOperation::Write))
	{
		return (CanGrow() || mPos < mData.Size());
	}
	return false;
}

bool MemoryStream::CanSeek() const
{
	return MEDUSA_FLAG_HAS(mSupportedOperation, StreamDataOperation::Seek);
}

StreamDataOperation MemoryStream::Operations() const
{
	return mSupportedOperation;
}


MEDUSA_END;

