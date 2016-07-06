// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Core/IO/Stream/HashStream.h"
#include "Core/Log/Log.h"
#include "Core/Memory/MemoryData.h"
#include "Core/Hash/HasherFactory.h"

MEDUSA_BEGIN;


HashStream::HashStream(const Share<IStream>& stream, HasherType hasher, Delegate<void(StringRef)> onComplete/* = nullptr*/)
	: mSourceStream(stream), mIsSourceReadonly(false), mOnComplete(onComplete)
{
	mHasher = HasherFactory::Instance().Create(hasher);
	Log::AssertNotNullFormat(mHasher, "Cannot create hasher:{}", hasher);
}
HashStream::HashStream(const Share<const IStream>& stream, HasherType hasher, Delegate<void(StringRef)> onComplete/* = nullptr*/)
	: mSourceStream(stream.CastPtr<IStream>()), mIsSourceReadonly(true), mOnComplete(onComplete)
{
	mHasher = HasherFactory::Instance().Create(hasher);
	Log::AssertNotNullFormat(mHasher, "Cannot create hasher:{}", hasher);
}

HashStream::HashStream(HashStream&& other)
	:mSourceStream(std::move(other.mSourceStream)),
	mIsSourceReadonly(other.mIsSourceReadonly),
	mHasher(other.mHasher),
	mOnComplete(std::move(other.mOnComplete))
{
	other.mHasher = nullptr;
}

HashStream& HashStream::operator=(HashStream&& other)
{
	if (this != &other)
	{
		Close();
		mSourceStream = std::move(other.mSourceStream);
		mIsSourceReadonly = other.mIsSourceReadonly;
		mHasher = other.mHasher;
		other.mHasher = nullptr;
		mOnComplete = std::move(other.mOnComplete);
	}
	return *this;
}

HashStream::~HashStream(void)
{
	Close();
}

bool HashStream::IsEnd() const
{
	return mSourceStream->IsEnd();
}

uintp HashStream::Length() const
{
	return mSourceStream->Length();
}

bool HashStream::CanRead() const
{
	if (MEDUSA_FLAG_HAS(Operations(), StreamDataOperation::Read))
	{
		return mSourceStream->CanRead();
	}
	return false;
}

bool HashStream::CanWrite() const
{
	if (MEDUSA_FLAG_HAS(Operations(), StreamDataOperation::Write))
	{
		return mSourceStream->CanWrite();
	}
	return false;
}

StreamDataOperation HashStream::Operations() const
{
	return mIsSourceReadonly ? MEDUSA_FLAG_AND(StreamDataOperation::ReadSeek, mSourceStream->Operations()) : mSourceStream->Operations();
}

bool HashStream::Flush()
{
	return mSourceStream->Flush();
}

bool HashStream::Close()
{
	mSourceStream = nullptr;
	if (mOnComplete != nullptr&&mHasher != nullptr)
	{
		mHasher->Final();
		mOnComplete(mHasher->ToString());
	}

	SAFE_DELETE(mHasher);

	return true;
}

bool HashStream::Seek(intp offset, SeekOrigin direction /*= SeekOrigin::Current*/)const
{
	return mSourceStream->Seek(offset, direction);
}

bool HashStream::SetLength(uintp val)
{
	return mSourceStream->SetLength(val);
}


size_t HashStream::ReadDataTo(MemoryData& outData, DataReadingMode mode/*=DataReadingMode::AlwaysCopy*/)const
{
	size_t count = mSourceStream->ReadDataTo(outData, mode);
	mHasher->Process(outData);
	return count;

}

size_t HashStream::WriteData(const MemoryData& data, DataReadingMode mode /*= DataReadingMode::AlwaysCopy*/)
{
	mHasher->Process(data);
	return mSourceStream->WriteData(data, mode);
}

int HashStream::PeekChar()const
{
	return mSourceStream->PeekChar();
}

int HashStream::PeekWChar()const
{
	return mSourceStream->PeekWChar();
}


int HashStream::ReadChar()const
{
	int c = mSourceStream->ReadChar();
	if (c != -1)
	{
		char cc = (char)c;
		mHasher->Process(&cc, sizeof(char));
	}
	return c;
}

int HashStream::ReadWChar()const
{
	int c = mSourceStream->ReadWChar();
	if (c != -1)
	{
		wchar cc = (wchar)c;
		mHasher->Process(&cc, sizeof(wchar));
	}
	return c;
}

bool HashStream::WriteChar(char val)
{
	mHasher->Process(&val, sizeof(char));

	return mSourceStream->WriteChar(val);
}

bool HashStream::WriteChar(wchar val)
{
	mHasher->Process(&val, sizeof(wchar));
	return mSourceStream->WriteChar(val);
}


size_t HashStream::ReadStringTo(HeapString& outString)const
{
	size_t oldPos = outString.Length();
	size_t readCount = mSourceStream->ReadStringTo(outString);
	RETURN_ZERO_IF_ZERO(readCount);

	mHasher->Process(outString.c_str() + oldPos, outString.Length() - oldPos);
	return readCount;
}

size_t HashStream::ReadStringTo(WHeapString& outString)const
{
	size_t oldPos = outString.Length();
	size_t readCount = mSourceStream->ReadStringTo(outString);
	RETURN_ZERO_IF_ZERO(readCount);

	mHasher->Process(outString.c_str() + oldPos, (outString.Length() - oldPos)*sizeof(wchar_t));
	return readCount;

}

size_t HashStream::ReadLineToString(HeapString& outString, bool includeNewLine/*=true*/)const
{
	size_t oldPos = outString.Length();
	size_t readCount = mSourceStream->ReadLineToString(outString, includeNewLine);
	RETURN_ZERO_IF_ZERO(readCount);

	mHasher->Process(outString.c_str() + oldPos, (outString.Length() - oldPos)*sizeof(char));
	return readCount;
}

size_t HashStream::ReadLineToString(WHeapString& outString, bool includeNewLine/*=true*/)const
{
	size_t oldPos = outString.Length();
	size_t readCount = mSourceStream->ReadLineToString(outString, includeNewLine);
	RETURN_ZERO_IF_ZERO(readCount);

	mHasher->Process(outString.c_str() + oldPos, (outString.Length() - oldPos)*sizeof(wchar_t));
	return readCount;
}

size_t HashStream::WriteString(const StringRef& str, bool withNullTermitated /*= true*/)
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

size_t HashStream::WriteString(const WStringRef& str, bool withNullTermitated /*= true*/)
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

MEDUSA_END;
