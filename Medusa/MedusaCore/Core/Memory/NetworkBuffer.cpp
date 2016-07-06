// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "NetworkBuffer.h"


MEDUSA_BEGIN;


NetworkBuffer::NetworkBuffer(size_t initialSize /*= mInitialSize*/)
	:mStream(initialSize)
{
	assert(ReadableCount() == 0);
	assert(WritableCount() == initialSize);
}

NetworkBuffer::NetworkBuffer(const MemoryData& data)
	:mStream(data)
{
	mWriteIndex = data.Size();
}

void NetworkBuffer::Retrieve(size_t len)
{
	assert(len <= ReadableCount());
	if (len < ReadableCount())
	{
		mReadIndex += len;
	}
	else
	{
		RetrieveAll();
	}
}


StringRef NetworkBuffer::ReadStringRef(size_t len)
{
	StringRef result((const char*)ReadBegin(), len);
	Retrieve(len);
	return result;
}

HeapString NetworkBuffer::ReadString(size_t len)
{
	HeapString result((const char*)ReadBegin(), len);
	Retrieve(len);
	return result;
}

MemoryData NetworkBuffer::ReadData(size_t len, DataReadingMode mode/* = DataReadingMode::AlwaysCopy*/)
{
	assert(len <= ReadableCount());
	if (mode == DataReadingMode::AlwaysCopy)
	{
		MemoryData result = MemoryData::CopyFrom(ReadBegin(), len);
		Retrieve(len);
		return result;
	}
	else
	{
		MemoryData result = MemoryData::FromStatic(ReadBegin(), len);
		Retrieve(len);
		return result;
	}

}

MemoryData NetworkBuffer::ReadAllData(DataReadingMode mode/* = DataReadingMode::AlwaysCopy*/)
{
	return ReadData(ReadableCount(), mode);;
}


void NetworkBuffer::Write(const byte* data, size_t len)
{
	EnsureWritableCount(len);
	Memory::SafeCopy(WriteBegin(), WritableCount(), data, len);
	HasWritten(len);
}

void NetworkBuffer::Write(const StringRef& val)
{
	return Write((byte*)val.c_str(), val.Length());
}

void NetworkBuffer::Write(const MemoryData& val)
{
	EnsureWritableCount(val.Size());
	Memory::SafeCopy(WriteBegin(), WritableCount(), val.Data(), val.Size());
	HasWritten(val.Size());
}

void NetworkBuffer::RetrieveAll()
{
	mReadIndex = 0;
	mWriteIndex = 0;
}

void NetworkBuffer::RetrieveUntil(const byte* end)
{
	assert(ReadBegin() <= end);
	assert(end <= WriteBegin());
	Retrieve(end - ReadBegin());
}


void NetworkBuffer::EnsureWritableCount(size_t len)
{
	if (WritableCount() < len)
	{
		Reserve(len);
	}
	assert(WritableCount() >= len);
}

void NetworkBuffer::HasWritten(size_t len)
{
	assert(len <= WritableCount());
	mWriteIndex += len;
}

void NetworkBuffer::Unwrite(size_t len)
{
	assert(len <= ReadableCount());
	mWriteIndex -= len;
}


void NetworkBuffer::TryAdjust()
{
	if (IsFull())
	{
		mStream.ReserveSize(Size() * 2);
	}
	else  if (mReadIndex>= Size() / 2)	//write 
	{
		// move readable data to the front, make space inside buffer
		size_t readable = ReadableCount();
		Memory::SafeCopy(mStream.MutablePtr(), mStream.Length(), ReadBegin(), readable);
		mReadIndex = 0;
		mWriteIndex = mReadIndex + readable;
		assert(readable == ReadableCount());
	}
}


void NetworkBuffer::Reserve(size_t len)
{
	if (WritableCount() < len)
	{
		TryAdjust();
		if (WritableCount() < len)
		{
			//still not enough
			mStream.ReserveSize(Size() + len);
		}
	}

}

MEDUSA_END;
