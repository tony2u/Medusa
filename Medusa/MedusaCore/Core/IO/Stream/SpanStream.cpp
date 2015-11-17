// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Core/IO/Stream/SpanStream.h"
#include "Core/Log/Log.h"
#include "Core/Memory/MemoryData.h"

MEDUSA_BEGIN;


SpanStream::SpanStream(IStream& stream, uintp limitBegin/*= 0*/, uintp limitSize/*=0*/)
	:mSourceStream(&stream), mIsSourceReadonly(false),mLimitBegin(limitBegin), mLimitSize(limitSize)
{
	MEDUSA_ASSERT_LESS_EQUAL(mLimitBegin, mSourceStream->Length(), "Invalid limitBegin");

	if (mLimitSize != 0)
	{
		MEDUSA_ASSERT_LESS_EQUAL(mLimitBegin + mLimitSize, mSourceStream->Length(), "Invalid limitSize");
	}

	SAFE_RETAIN(mSourceStream);
}

SpanStream::SpanStream(const IStream& stream, uintp limitBegin/*= 0*/, uintp limitSize/*=0*/)
	:mSourceStream((IStream*)&stream), mIsSourceReadonly(true),mLimitBegin(limitBegin), mLimitSize(limitSize)
{
	MEDUSA_ASSERT_LESS_EQUAL(mLimitBegin, mSourceStream->Length(), "Invalid limitBegin");

	if (mLimitSize != 0)
	{
		MEDUSA_ASSERT_LESS_EQUAL(mLimitBegin + mLimitSize, mSourceStream->Length(), "Invalid limitSize");
	}

	SAFE_RETAIN(mSourceStream);
}


SpanStream::SpanStream(SpanStream&& other)
	:mSourceStream(nullptr), 
	mIsSourceReadonly(other.mIsSourceReadonly),
	mLimitBegin(other.mLimitBegin),
	mLimitSize(other.mLimitSize)
{
	SAFE_MOVE_REF(mSourceStream, other.mSourceStream);
	other.mLimitBegin = 0;
	other.mLimitSize = 0;
}

SpanStream& SpanStream::operator=(SpanStream&& other)
{
	if (this != &other)
	{
		Close();
		SAFE_MOVE_REF(mSourceStream, other.mSourceStream);
		mIsSourceReadonly = other.mIsSourceReadonly;
		mLimitBegin = other.mLimitBegin;
		mLimitSize = other.mLimitSize;

		other.mLimitBegin = 0;
		other.mLimitSize = 0;

	}
	return *this;
}



SpanStream::~SpanStream(void)
{
	Close();
}

bool SpanStream::IsSourcePosValid() const
{
	RETURN_FALSE_IF_NULL(mSourceStream);
	uintp pos = mSourceStream->Position();
	RETURN_FALSE_IF_FALSE(pos >= mLimitBegin);
	return mLimitSize == 0 ? true : pos <= mLimitBegin + mLimitSize;
}

bool SpanStream::IsEnd() const
{
	return mSourceStream->IsEnd() || (mLimitSize != 0 && mSourceStream->Position() <= mLimitBegin + mLimitSize);
}

uintp SpanStream::Length() const
{
	return mLimitSize != 0 ? mLimitSize : mSourceStream->Length() - mLimitBegin;
}


bool SpanStream::CanRead() const
{
	if (MEDUSA_HAS_FLAG(Operations(), StreamDataOperation::Read))
	{
		return IsSourcePosValid();
	}
	return false;
}

bool SpanStream::CanWrite() const
{
	if (MEDUSA_HAS_FLAG(Operations(), StreamDataOperation::Write))
	{
		return IsSourcePosValid();
	}
	return false;
}

StreamDataOperation SpanStream::Operations() const
{
	return mIsSourceReadonly ? MEDUSA_AND_FLAG(StreamDataOperation::ReadSeek, mSourceStream->Operations()) : mSourceStream->Operations();
}

bool SpanStream::Flush()
{
	return mSourceStream->Flush();
}

bool SpanStream::Close()
{
	SAFE_RELEASE(mSourceStream);

	mSourceStream = nullptr;
	mLimitBegin = 0;
	mLimitSize = 0;

	return true;
}

bool SpanStream::Seek(intp offset, SeekOrigin direction /*= SeekOrigin::Current*/)const
{
	RETURN_FALSE_IF_FALSE(CanSeek());
	uintp pos = 0;
	uintp originalPos = Position();

	if (mLimitSize != 0)
	{
		switch (direction)
		{
		case SeekOrigin::Head:
			pos = (intp)mLimitBegin + offset;
			break;
		case SeekOrigin::Current:
			pos = (intp)originalPos + offset;
			break;
		case SeekOrigin::End:
			pos = (intp)mLimitSize + offset;
			break;
		default:
			break;
		}
	}
	else
	{
		switch (direction)
		{
		case SeekOrigin::Head:
			pos = (intp)mLimitBegin + offset;
			break;
		case SeekOrigin::Current:
			pos = (intp)originalPos + offset;
			break;
		case SeekOrigin::End:
			pos = (intp)mSourceStream->Length() + offset;
			break;
		default:
			break;
		}
	}


	RETURN_FALSE_IF_FALSE(mSourceStream->Seek(pos, SeekOrigin::Head));
	if (!IsSourcePosValid())
	{
		//roll back
		mSourceStream->SetPosition(originalPos);
		return false;
	}
	return true;
}

bool SpanStream::SetLength(uintp val)
{
	RETURN_FALSE_IF_FALSE(CanWrite());
	if (mLimitSize != 0)
	{
		if (val > mLimitSize)
		{
			Log::FormatError("Cannot set proxy stream length:{} > limit size:{}", val, mLimitSize);
			return false;
		}
		else
		{
			mLimitSize = val;
			return true;
		}
	}
	else
	{
		uintp newLength = mLimitBegin + val;
		return mSourceStream->SetLength(newLength);
	}
}


size_t SpanStream::ReadDataTo(MemoryByteData& outData, DataReadingMode mode/*=DataReadingMode::AlwaysCopy*/)const
{
	RETURN_ZERO_IF_FALSE(CanRead());
	size_t readSize = Math::Min((size_t)LeftLength(), outData.Size());

	MemoryByteData temp = outData;
	temp.ForceSetSize(readSize);
	size_t result = mSourceStream->ReadDataTo(temp, mode);
	return result;

}

size_t SpanStream::WriteData(const MemoryByteData& data, DataReadingMode mode /*= DataReadingMode::AlwaysCopy*/)
{
	RETURN_ZERO_IF_FALSE(CanWrite());
	if (mLimitSize == 0)
	{
		return mSourceStream->WriteData(data);
	}

	size_t newSize = Math::Min(data.Size(), (size_t)LeftLength());
	MemoryByteData tempData = data;
	tempData.ForceSetSize(newSize);

	return mSourceStream->WriteData(tempData,mode);
}

int SpanStream::PeekChar()const
{
	RETURN_OBJECT_IF_FALSE(CanRead(), -1);
	return mSourceStream->PeekChar();
}

int SpanStream::PeekWChar()const
{
	RETURN_OBJECT_IF_FALSE(CanRead(), -1);
	if (Position() + sizeof(wchar) - 1 >= Length())
	{
		return -1;
	}
	return mSourceStream->PeekWChar();
}


int SpanStream::ReadChar()const
{
	RETURN_OBJECT_IF_FALSE(CanRead(), -1);
	return mSourceStream->ReadChar();
}

int SpanStream::ReadWChar()const
{
	RETURN_OBJECT_IF_FALSE(CanRead(), -1);
	if (Position() + sizeof(wchar) - 1 >= Length())
	{
		return -1;
	}
	return mSourceStream->ReadWChar();
}

bool SpanStream::WriteChar(char val)
{
	RETURN_FALSE_IF_FALSE(CanWrite());
	return mSourceStream->WriteChar(val);
}

bool SpanStream::WriteChar(wchar val)
{
	RETURN_FALSE_IF_FALSE(CanWrite());

	if (Position() + sizeof(wchar) - 1 >= Length())
	{
		return false;
	}
	return mSourceStream->WriteChar(val);
}

size_t SpanStream::ReadStringTo(HeapString& outString)const
{
	RETURN_ZERO_IF_FALSE(CanRead());

	uintp oldPos = Position();
	uintp oldLength = outString.Length();
	size_t readCount = mSourceStream->ReadStringTo(outString);
	RETURN_ZERO_IF_ZERO(readCount);

	if (!IsSourcePosValid())
	{
		SetPosition(oldPos);
		outString.ForceSetLength(oldLength);
		return 0;
	}
	return readCount;
}

size_t SpanStream::ReadStringTo(WHeapString& outString)const
{
	RETURN_ZERO_IF_FALSE(CanRead());

	uintp oldPos = Position();
	uintp oldLength = outString.Length();

	size_t readCount = mSourceStream->ReadStringTo(outString);
	RETURN_ZERO_IF_ZERO(readCount);

	if (!IsSourcePosValid())
	{
		SetPosition(oldPos);
		outString.ForceSetLength(oldLength);
		return 0;
	}
	return readCount;

}

size_t SpanStream::ReadLineToString(HeapString& outString, bool includeNewLine/*=true*/)const
{
	RETURN_ZERO_IF_FALSE(CanRead());
	uintp oldLength = outString.Length();
	uintp pos = Position();

	size_t readCount = mSourceStream->ReadLineToString(outString, includeNewLine);
	RETURN_ZERO_IF_ZERO(readCount);

	if (!IsSourcePosValid())
	{
		uintp adjustPos = mLimitBegin + mLimitSize;
		SetPosition(adjustPos);
		outString.ForceSetLength(oldLength);
		return adjustPos-pos;
	}
	return readCount;
}

size_t SpanStream::ReadLineToString(WHeapString& outString, bool includeNewLine/*=true*/)const
{
	RETURN_ZERO_IF_FALSE(CanRead());
	uintp oldLength = outString.Length();
	uintp pos = Position();
	size_t readCount = mSourceStream->ReadLineToString(outString, includeNewLine);
	RETURN_ZERO_IF_ZERO(readCount);

	if (!IsSourcePosValid())
	{
		uintp adjustPos = mLimitBegin + mLimitSize;
		SetPosition(adjustPos);

		outString.ForceSetLength(oldLength);
		return adjustPos - pos;
	}
	return readCount;
}

size_t SpanStream::WriteString(const StringRef& str, bool withNullTermitated /*= true*/)
{
	RETURN_ZERO_IF_FALSE(CanWrite());
	MemoryByteData data = str.ToData().Cast<byte>();

	size_t size = WriteData(data);
	if (withNullTermitated)
	{
		WriteChar('\0');
		++size;
	}
	return size;
}

size_t SpanStream::WriteString(const WStringRef& str, bool withNullTermitated /*= true*/)
{
	RETURN_ZERO_IF_FALSE(CanWrite());
	MemoryByteData data = str.ToData().Cast<byte>();
	size_t size = WriteData(data);
	if (withNullTermitated)
	{
		WriteChar('\0');
		++size;
	}
	return size;
}

MEDUSA_END;
