// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Core/IO/Stream/FileCodeWriteStream.h"
#include "Core/Log/Log.h"
#include "Core/Memory/MemoryData.h"
#include "Core/Hash/HasherFactory.h"
#include "Core/IO/Storage/FileEntry.h"
#include "Core/Coder/CoderChain.h"

MEDUSA_BEGIN;


FileCodeWriteStream::FileCodeWriteStream(IStream& stream, const CoderChain& coderChain, FileEntry& fileEntry)
	: mSourceStream(&stream),
	mFileEntry(&fileEntry),
	mCoderChain(&coderChain)
{
	SAFE_RETAIN(mSourceStream);

	mFileEntry->MutableCoderOffsets().Clear();
	mBuffer.Rewind();

	mFileEntry->SetSize(0);
	mFileEntry->SetOriginalSize(0);
}

FileCodeWriteStream::FileCodeWriteStream(FileCodeWriteStream&& other)
	:mSourceStream(nullptr),
	mFileEntry(other.mFileEntry),
	mCoderChain(std::move(other.mCoderChain)),
	mBuffer(std::move(other.mBuffer))
{
	SAFE_MOVE_REF(mSourceStream, other.mSourceStream);
	other.mFileEntry = nullptr;
	other.mCoderChain = nullptr;
}

FileCodeWriteStream& FileCodeWriteStream::operator=(FileCodeWriteStream&& other)
{
	if (this != &other)
	{
		Close();
		SAFE_MOVE_REF(mSourceStream, other.mSourceStream);
		mCoderChain = other.mCoderChain;
		mFileEntry = other.mFileEntry;
		mBuffer = std::move(other.mBuffer);

		other.mFileEntry = nullptr;
		other.mCoderChain = nullptr;
	}
	return *this;
}

FileCodeWriteStream::~FileCodeWriteStream(void)
{
	Close();
}

bool FileCodeWriteStream::IsEnd() const
{
	return mBuffer.IsEnd();
}

uintp FileCodeWriteStream::Length() const
{
	return mBuffer.Length();
}

bool FileCodeWriteStream::CanRead() const
{
	return false;
}

bool FileCodeWriteStream::CanWrite() const
{
	return mBuffer.CanWrite();
}

bool FileCodeWriteStream::Flush()
{
	return mBuffer.Flush();
}

bool FileCodeWriteStream::Close()
{
	auto data= mBuffer.CurrentBuffer();
	MemoryStream input(data);

	mFileEntry->SetOriginalSize((uint32)data.Size());
	size_t writeSize= mCoderChain->Encode(input, *mSourceStream);
	SAFE_RELEASE(mSourceStream);
	mBuffer.Rewind();
	mFileEntry->SetSize((uint32)writeSize);

	return true;
}

bool FileCodeWriteStream::Seek(intp offset, SeekOrigin direction /*= SeekOrigin::Current*/)const
{
	return mBuffer.Seek(offset, direction);
}

bool FileCodeWriteStream::SetLength(uintp val)
{
	return mBuffer.SetLength(val);
}


size_t FileCodeWriteStream::ReadDataTo(MemoryData& outData, DataReadingMode mode/*=DataReadingMode::AlwaysCopy*/)const
{
	return mBuffer.ReadDataTo(outData, mode);
}

size_t FileCodeWriteStream::WriteData(const MemoryData& data, DataReadingMode mode /*= DataReadingMode::AlwaysCopy*/)
{
	return mBuffer.WriteData(data, mode);
}

int FileCodeWriteStream::PeekChar()const
{
	throw std::logic_error("The method or operation is not implemented.");
}

int FileCodeWriteStream::PeekWChar()const
{
	throw std::logic_error("The method or operation is not implemented.");
}


int FileCodeWriteStream::ReadChar()const
{
	throw std::logic_error("The method or operation is not implemented.");
}

int FileCodeWriteStream::ReadWChar()const
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool FileCodeWriteStream::WriteChar(char val)
{
	return mBuffer.WriteChar(val);
}

bool FileCodeWriteStream::WriteChar(wchar val)
{
	return mBuffer.WriteChar(val);
}

size_t FileCodeWriteStream::ReadStringTo(HeapString& outString)const
{
	throw std::logic_error("The method or operation is not implemented.");
}

size_t FileCodeWriteStream::ReadStringTo(WHeapString& outString)const
{
	throw std::logic_error("The method or operation is not implemented.");
}

size_t FileCodeWriteStream::ReadLineToString(HeapString& outString, bool includeNewLine/*=true*/)const
{
	throw std::logic_error("The method or operation is not implemented.");
}

size_t FileCodeWriteStream::ReadLineToString(WHeapString& outString, bool includeNewLine/*=true*/)const
{
	throw std::logic_error("The method or operation is not implemented.");
}

size_t FileCodeWriteStream::WriteString(const StringRef& str, bool withNullTermitated /*= true*/)
{
	return mBuffer.WriteString(str, withNullTermitated);
}

size_t FileCodeWriteStream::WriteString(const WStringRef& str, bool withNullTermitated /*= true*/)
{
	return mBuffer.WriteString(str, withNullTermitated);
}

MEDUSA_END;
