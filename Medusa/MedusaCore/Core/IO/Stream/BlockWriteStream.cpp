// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Core/IO/Stream/BlockWriteStream.h"
#include "Core/Log/Log.h"
#include "Core/Memory/MemoryData.h"

MEDUSA_BEGIN;


BlockWriteStream::BlockWriteStream(IStream& stream, uint32 blockSize)
	: mSourceStream(&stream),
	mBuffer(blockSize, false)
{
	SAFE_RETAIN(mSourceStream);
}


BlockWriteStream::BlockWriteStream(BlockWriteStream&& other)
	:mSourceStream(nullptr),
	mBlockIndex(other.mBlockIndex)
{
	SAFE_MOVE_REF(mSourceStream, other.mSourceStream);
	other.mBlockIndex = 0;
}


BlockWriteStream& BlockWriteStream::operator=(BlockWriteStream&& other)
{
	if (this != &other)
	{
		Close();
		SAFE_MOVE_REF(mSourceStream, other.mSourceStream);
		mBlockIndex = other.mBlockIndex;

		other.mSourceStream = nullptr;
		other.mBlockIndex = 0;
	}
	return *this;
}

BlockWriteStream::~BlockWriteStream(void)
{

}

bool BlockWriteStream::Close()
{
	Flush();
	SAFE_RELEASE(mSourceStream);

	return true;
}

bool BlockWriteStream::Flush()
{
	WriteCurrentBlock(true);
	if (mSourceStream != nullptr)
	{
		return mSourceStream->Flush();
	}
	return true;
}

bool BlockWriteStream::IsEnd() const
{
	return Position() >= Length();
}


uintp BlockWriteStream::Position() const
{
	uintp prevSize = (mBlockIndex)*mBuffer.Length();
	return prevSize + mBuffer.Position();
}



bool BlockWriteStream::SetLength(uintp val)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void BlockWriteStream::Rewind()const
{
	mBlockIndex = 0;
	mBuffer.Rewind();
}

bool BlockWriteStream::Seek(intp offset, SeekOrigin direction /*= SeekOrigin::Current*/)const
{
	throw std::logic_error("The method or operation is not implemented.");
}

size_t BlockWriteStream::ReadDataTo(MemoryData& outData, DataReadingMode mode/*=DataReadingMode::AlwaysCopy*/)const
{
	throw std::logic_error("The method or operation is not implemented.");
}

size_t BlockWriteStream::WriteData(const MemoryData& data, DataReadingMode mode /*= DataReadingMode::AlwaysCopy*/)
{
	RETURN_ZERO_IF_FALSE(CanWrite());

	size_t dataPos = 0;
	size_t dataSize = data.Size();

	if (mBuffer.Position() > 0)
	{
		size_t bufferLeftLength = mBuffer.LeftLength();
		size_t writeSize = Math::Min(bufferLeftLength, dataSize);
		MemoryData tempData = MemoryData::FromStatic(data.Data(), writeSize);
		writeSize = mBuffer.WriteData(tempData, mode);
		dataPos += writeSize;
		dataSize -= writeSize;

		if (mBuffer.IsEnd())
		{
			WriteCurrentBlock();
			++mBlockIndex;
		}
		else
		{
			//all data write to buffer
			return dataPos;
		}
	}

	//directly write data block per block
	size_t blockSize = mBuffer.Length();
	size_t blockCount = dataSize / blockSize;
	FOR_EACH_SIZE(i, blockCount)
	{
		MemoryData tempData = MemoryData::FromStatic(data.Data() + dataPos, blockSize);
		size_t writeSize = WriteBlock(mBlockIndex, tempData);
		++mBlockIndex;

		dataPos += writeSize;
		dataSize -= writeSize;
	}

	//write left data
	if (dataSize > 0)
	{
		MemoryData tempData = MemoryData::FromStatic(data.Data() + dataPos, dataSize);
		size_t writeSize = mBuffer.WriteData(tempData, mode);
		dataPos += writeSize;
		dataSize -= writeSize;
	}

	return dataPos;
}

int BlockWriteStream::PeekChar()const
{
	throw std::logic_error("The method or operation is not implemented.");
}

int BlockWriteStream::PeekWChar()const
{
	throw std::logic_error("The method or operation is not implemented.");
}


int BlockWriteStream::ReadChar()const
{
	throw std::logic_error("The method or operation is not implemented.");
}

int BlockWriteStream::ReadWChar()const
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool BlockWriteStream::WriteChar(char val)
{
	RETURN_FALSE_IF_FALSE(CanWrite());

	if (mBuffer.Position() > 0)
	{
		size_t bufferLeftLength = mBuffer.LeftLength();
		if (bufferLeftLength >= 1)
		{
			return mBuffer.WriteChar(val);
		}
		else
		{
			//flush
			WriteCurrentBlock();
			return mBuffer.WriteChar(val);
		}
	}
	return mBuffer.WriteChar(val);
}

bool BlockWriteStream::WriteChar(wchar val)
{
	RETURN_FALSE_IF_FALSE(CanWrite());

	if (mBuffer.Position() > 0)
	{
		size_t bufferLeftLength = mBuffer.LeftLength();
		if (bufferLeftLength >= sizeof(wchar_t))
		{
			return mBuffer.WriteChar(val);
		}
		else
		{
			if (bufferLeftLength > 0)	//< wchar_t
			{
				auto tempData = MemoryData::FromStatic((byte*)&val, bufferLeftLength);
				mBuffer.WriteData(tempData);

				WriteCurrentBlock();

				tempData = MemoryData::FromStatic((byte*)&val + bufferLeftLength, sizeof(wchar_t) - bufferLeftLength);
				mBuffer.WriteData(tempData);
				return true;
			}
			else
			{
				WriteCurrentBlock();
				return mBuffer.WriteChar(val);
			}
		}
	}
	return mBuffer.WriteChar(val);
}


size_t BlockWriteStream::ReadStringTo(HeapString& outString)const
{
	throw std::logic_error("The method or operation is not implemented.");
}

size_t BlockWriteStream::ReadStringTo(WHeapString& outString)const
{
	throw std::logic_error("The method or operation is not implemented.");

}

size_t BlockWriteStream::ReadLineToString(HeapString& outString, bool includeNewLine/*=true*/)const
{
	throw std::logic_error("The method or operation is not implemented.");
}

size_t BlockWriteStream::ReadLineToString(WHeapString& outString, bool includeNewLine/*=true*/)const
{
	throw std::logic_error("The method or operation is not implemented.");
}

size_t BlockWriteStream::WriteString(const StringRef& str, bool withNullTermitated /*= true*/)
{
	RETURN_ZERO_IF_FALSE(CanWrite());
	MemoryData data = str.ToData().Cast<byte>();
	size_t size = WriteData(data);
	if (withNullTermitated)
	{
		WriteChar('\0');
		++size;
	}
	return size;
}

size_t BlockWriteStream::WriteString(const WStringRef& str, bool withNullTermitated /*= true*/)
{
	RETURN_ZERO_IF_FALSE(CanWrite());
	MemoryData data = str.ToData().Cast<byte>();
	size_t size = WriteData(data);
	if (withNullTermitated)
	{
		WriteChar(L'\0');
		size += sizeof(wchar_t);
	}
	return size;
}

size_t BlockWriteStream::WriteCurrentBlock(bool force/*=false*/)
{
	if (!force&&!mBuffer.IsEnd())
	{
		return 0;
	}

	if (mBuffer.Position() == 0)
	{
		return 0;
	}

	MemoryData data = mBuffer.CurrentBuffer();
	size_t resultSize = WriteBlock(mBlockIndex, data);
	mBuffer.Rewind();
	return resultSize;
}


MEDUSA_END;

