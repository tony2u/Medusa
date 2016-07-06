// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Core/IO/Stream/BufferStream.h"
#include "Core/Log/Log.h"
#include "Core/Memory/MemoryData.h"

MEDUSA_BEGIN;


BufferStream::BufferStream(const Share<IStream>& stream, uint bufferSize)
	: mSourceStream(stream),
	mIsSourceReadonly(false),
	mBuffer(bufferSize, false)
{
	mPrevOperation = StreamDataOperation::None;
}

BufferStream::BufferStream(const Share<const IStream>& stream, uint bufferSize)
	: mSourceStream(stream.CastPtr<IStream>()),
	mIsSourceReadonly(true),
	mBuffer(bufferSize, false)
{
	mPrevOperation = StreamDataOperation::None;
}

BufferStream::BufferStream(BufferStream&& other)
	:mSourceStream(std::move(other.mSourceStream)),
	mIsSourceReadonly(other.mIsSourceReadonly),
	mBuffer(std::move(other.mBuffer)),
	mPrevOperation(other.mPrevOperation)
{
	other.mPrevOperation = StreamDataOperation::None;

}

BufferStream& BufferStream::operator=(BufferStream&& other)
{
	if (this != &other)
	{
		Close();
		mSourceStream = std::move(other.mSourceStream);
		mIsSourceReadonly = other.mIsSourceReadonly;
		mBuffer = std::move(other.mBuffer);
		mPrevOperation = other.mPrevOperation;

		other.mPrevOperation = StreamDataOperation::None;
	}
	return *this;
}



BufferStream::~BufferStream(void)
{
	Close();
}


bool BufferStream::IsEnd() const
{
	return Position() >= Length();
}

uintp BufferStream::Length() const
{
	if (mPrevOperation == StreamDataOperation::Read)
	{
		return mSourceStream->Length();
	}
	else if (mPrevOperation == StreamDataOperation::Write)
	{
		uintp newpos = mSourceStream->Position() + mBuffer.Position();
		return Math::Max(mSourceStream->Length(), newpos);
	}

	return mSourceStream->Length();
}

uintp BufferStream::Position() const
{
	if (mPrevOperation == StreamDataOperation::Read)
	{
		return mSourceStream->Position() - (mBufferLength - mBuffer.Position());
	}
	else if (mPrevOperation == StreamDataOperation::Write)
	{
		return mSourceStream->Position() + mBuffer.Position();
	}

	return mSourceStream->Position();
}

bool BufferStream::CanRead() const
{
	if (MEDUSA_FLAG_HAS(Operations(), StreamDataOperation::Read))
	{
		return !IsEnd();
	}
	return false;
}

bool BufferStream::CanWrite() const
{
	return MEDUSA_FLAG_HAS(Operations(), StreamDataOperation::Write);
}

StreamDataOperation BufferStream::Operations() const
{
	return mIsSourceReadonly ? MEDUSA_FLAG_AND(StreamDataOperation::ReadSeek, mSourceStream->Operations()) : mSourceStream->Operations();
}

bool BufferStream::IsReadWrite() const
{
	return MEDUSA_FLAG_HAS(Operations(), StreamDataOperation::ReadWrite);

}

void BufferStream::FlushOnReadWrite(StreamDataOperation curOperation)const
{
	if (IsReadWrite() && mPrevOperation != curOperation)
	{
		BufferStream* stream = const_cast<BufferStream*>(this);	//force cast to non-const
		stream->Flush();

		mPrevOperation = curOperation;
	}
}

bool BufferStream::Flush()
{
	if (mPrevOperation == StreamDataOperation::Read)
	{
		mSourceStream->Seek(mBufferLength - mBuffer.Position());	//roll back unread data
		mBuffer.Rewind();
		mBufferLength = 0;
	}
	else if (mPrevOperation == StreamDataOperation::Write)
	{
		mSourceStream->WriteData(mBuffer.CurrentBuffer());
		mBuffer.Rewind();
		mBufferLength = 0;
	}


	return mSourceStream->Flush();
}

bool BufferStream::Close()
{
	mSourceStream = nullptr;
	mBuffer.Close();
	mBufferLength = 0;

	return true;
}

bool BufferStream::Seek(intp offset, SeekOrigin direction /*= SeekOrigin::Current*/)const
{
	const_cast<BufferStream*>(this)->Flush();
	return mSourceStream->Seek(offset, direction);
}

bool BufferStream::SetLength(uintp val)
{
	return mSourceStream->SetLength(val);
}


size_t BufferStream::ReadDataTo(MemoryData& outData, DataReadingMode mode/*=DataReadingMode::AlwaysCopy*/)const
{
	RETURN_ZERO_IF_FALSE(CanRead());
	FlushOnReadWrite(StreamDataOperation::Read);

	size_t outPos = 0;
	size_t outSize = outData.Size();

	//read left buffer data
	size_t bufferLeftLength = mBufferLength - mBuffer.Position();
	if (bufferLeftLength != 0)
	{
		size_t readSize = Math::Min(bufferLeftLength, outSize);
		MemoryData tempData = MemoryData::FromStatic(outData.MutableData() + outPos, readSize);
		readSize = mBuffer.ReadDataTo(tempData, DataReadingMode::AlwaysCopy);
		outPos += readSize;
		outSize -= readSize;
	}

	//directly read to out data block per block
	size_t blockSize = mBuffer.Length();
	size_t blockCount = outSize / blockSize;
	FOR_EACH_SIZE(i, blockCount)
	{
		MemoryData tempData = MemoryData::FromStatic(outData.MutableData() + outPos, blockSize);
		size_t readSize = mSourceStream->ReadDataTo(tempData);
		outPos += readSize;
		outSize -= readSize;
		if (readSize != blockSize)	//last block
		{
			return outPos;
		}
	}

	//read left data
	if (outSize > 0)
	{
		mBufferLength = mSourceStream->ReadDataTo(mBuffer.MutableBuffer());
		mBuffer.Rewind();
		if (mBufferLength == 0)	//reach end
		{
			return outPos;
		}

		bufferLeftLength = mBufferLength - mBuffer.Position();
		size_t readSize = Math::Min(bufferLeftLength, outSize);
		MemoryData tempData = MemoryData::FromStatic(outData.MutableData() + outPos, readSize);
		readSize = mBuffer.ReadDataTo(tempData, DataReadingMode::AlwaysCopy);
		outPos += readSize;
		outSize -= readSize;
	}

	return outPos;
}

size_t BufferStream::WriteData(const MemoryData& data, DataReadingMode mode /*= DataReadingMode::AlwaysCopy*/)
{
	RETURN_ZERO_IF_FALSE(CanWrite());
	FlushOnReadWrite(StreamDataOperation::Write);

	size_t dataPos = 0;
	size_t dataSize = data.Size();

	if (mBuffer.Position() > 0)
	{
		size_t bufferLeftLength = mBuffer.LeftLength();
		size_t writeSize = Math::Min(bufferLeftLength, dataSize);
		MemoryData tempData = MemoryData::FromStatic(data.Data() + dataPos, writeSize);
		writeSize = mBuffer.WriteData(tempData);
		dataPos += writeSize;
		dataSize -= writeSize;

		if (mBuffer.IsEnd())
		{
			//flush
			mSourceStream->WriteData(mBuffer.CurrentBuffer());
			mBuffer.Rewind();
			mBufferLength = 0;
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
		size_t writeSize = mSourceStream->WriteData(tempData);
		dataPos += writeSize;
		dataSize -= writeSize;
	}

	//write left data
	if (dataSize > 0)
	{
		MemoryData tempData = MemoryData::FromStatic(data.Data() + dataPos, blockSize);
		size_t writeSize = mBuffer.WriteData(tempData);
		dataPos += writeSize;
		dataSize -= writeSize;
	}

	return dataPos;
}

int BufferStream::PeekChar()const
{
	RETURN_OBJECT_IF_FALSE(CanRead(), -1);
	FlushOnReadWrite(StreamDataOperation::Read);

	size_t bufferLeftLength = mBufferLength - mBuffer.Position();
	if (bufferLeftLength == 0)
	{
		mBufferLength = mSourceStream->ReadDataTo(mBuffer.MutableBuffer());
		mBuffer.Rewind();
		if (mBufferLength == 0)	//reach end
		{
			return -1;
		}
	}

	return mBuffer.PeekChar();
}

int BufferStream::PeekWChar()const
{
	RETURN_OBJECT_IF_FALSE(CanRead(), -1);
	FlushOnReadWrite(StreamDataOperation::Read);


	int c = ReadWChar();
	if (c != -1)
	{
		Seek(-(intp)sizeof(wchar_t));
	}

	return c;
}

int BufferStream::ReadChar()const
{
	RETURN_OBJECT_IF_FALSE(CanRead(), -1);
	FlushOnReadWrite(StreamDataOperation::Read);

	size_t bufferLeftLength = mBufferLength - mBuffer.Position();
	if (bufferLeftLength == 0)
	{
		mBufferLength = mSourceStream->ReadDataTo(mBuffer.MutableBuffer());
		mBuffer.Rewind();
		if (mBufferLength == 0)	//reach end
		{
			return -1;
		}
	}

	return mBuffer.ReadChar();
}

int BufferStream::ReadWChar()const
{
	RETURN_OBJECT_IF_FALSE(CanRead(), -1);
	FlushOnReadWrite(StreamDataOperation::Read);

	wchar_t c;
	MemoryData tempData = MemoryData::FromStatic((byte*)&c, sizeof(wchar_t));
	size_t readSize = ReadDataTo(tempData);
	if (readSize != sizeof(wchar_t))
	{
		return -1;
	}
	return c;
}

bool BufferStream::WriteChar(char val)
{
	RETURN_FALSE_IF_FALSE(CanWrite());
	FlushOnReadWrite(StreamDataOperation::Write);

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
			mSourceStream->WriteData(mBuffer.CurrentBuffer());
			mBuffer.Rewind();
			mBufferLength = 0;
			return mBuffer.WriteChar(val);
		}
	}
	return mBuffer.WriteChar(val);
}

bool BufferStream::WriteChar(wchar val)
{
	RETURN_FALSE_IF_FALSE(CanWrite());
	FlushOnReadWrite(StreamDataOperation::Write);

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

				mSourceStream->WriteData(mBuffer.CurrentBuffer());
				mBuffer.Rewind();
				mBufferLength = 0;

				tempData = MemoryData::FromStatic((byte*)&val + bufferLeftLength, sizeof(wchar_t) - bufferLeftLength);
				mBuffer.WriteData(tempData);
				return true;
			}
			else
			{
				mSourceStream->WriteData(mBuffer.CurrentBuffer());
				mBuffer.Rewind();
				mBufferLength = 0;

				return mBuffer.WriteChar(val);
			}
		}
	}
	return mBuffer.WriteChar(val);
}

size_t BufferStream::ReadStringTo(HeapString& outString)const
{
	RETURN_FALSE_IF_FALSE(CanRead());
	FlushOnReadWrite(StreamDataOperation::Read);

	size_t totalReadCount = 0;
	while (true)
	{
		size_t bufferLeftLength = mBufferLength - mBuffer.Position();
		if (bufferLeftLength == 0)
		{
			mBufferLength = mSourceStream->ReadDataTo(mBuffer.MutableBuffer());
			mBuffer.Rewind();
			if (mBufferLength == 0)	//reach end
			{
				return totalReadCount;
			}
			bufferLeftLength = mBufferLength;
		}

		const char* buffer = (const char*)mBuffer.Ptr();
		size_t size = bufferLeftLength;
		size_t i = 0;
		for (; i < size; ++i)
		{
			if (buffer[i] == '\0')
			{
				outString.Append(buffer, i);
				totalReadCount += i;
				mBuffer.Skip(i);
				return totalReadCount;
			}
		}

		if (i == size)	//reach buffer end
		{
			outString.Append(buffer, i);
			totalReadCount += i;
			mBuffer.Skip(i);
		}
	}

	return totalReadCount;
}

size_t BufferStream::ReadStringTo(WHeapString& outString)const
{
	RETURN_FALSE_IF_FALSE(CanRead());
	FlushOnReadWrite(StreamDataOperation::Read);

	size_t totalReadCount = 0;
	while (true)
	{
		size_t bufferLeftLength = mBufferLength - mBuffer.Position();
		if (bufferLeftLength == 0)
		{
			mBufferLength = mSourceStream->ReadDataTo(mBuffer.MutableBuffer());
			mBuffer.Rewind();
			if (mBufferLength == 0)	//reach end
			{
				return totalReadCount;
			}
			bufferLeftLength = mBufferLength;
		}

		const wchar_t* buffer = (const wchar_t*)mBuffer.Ptr();
		size_t size = bufferLeftLength / sizeof(wchar_t);
		size_t i = 0;
		for (; i < size; ++i)
		{
			if (buffer[i] == L'\0')
			{
				outString.Append(buffer, i);
				totalReadCount += i*sizeof(wchar_t);
				mBuffer.Skip(i*sizeof(wchar_t));
				return totalReadCount;
			}
		}

		if (i == size)	//reach buffer end
		{
			outString.Append(buffer, i);
			totalReadCount += i*sizeof(wchar_t);
			mBuffer.Skip(i*sizeof(wchar_t));
			bufferLeftLength = mBufferLength - mBuffer.Position();
		}

		if (bufferLeftLength != 0)
		{
			//some data still left, size < sizeof(wchar_t)
			//copy left data to top
			MemoryData& buffer2 = mBuffer.MutableBuffer();
			Memory::SafeCopy(buffer2.MutableData(), buffer2.Size(), buffer2.Data() + mBuffer.Position(), bufferLeftLength);
			mBuffer.SetPosition(bufferLeftLength);

			//read need data
			MemoryData tempData = MemoryData::FromStatic(buffer2.Data(), mBuffer.Length() - bufferLeftLength);
			mBufferLength = mSourceStream->ReadDataTo(tempData) + bufferLeftLength;
			mBuffer.Rewind();
		}
	}

	return totalReadCount;
}

size_t BufferStream::ReadLineToString(HeapString& outString, bool includeNewLine/*=true*/)const
{
	RETURN_FALSE_IF_FALSE(CanRead());
	FlushOnReadWrite(StreamDataOperation::Read);

	size_t totalReadCount = 0;
	while (true)
	{
		size_t bufferLeftLength = mBufferLength - mBuffer.Position();
		if (bufferLeftLength == 0)
		{
			mBufferLength = mSourceStream->ReadDataTo(mBuffer.MutableBuffer());
			mBuffer.Rewind();
			if (mBufferLength == 0)	//reach end
			{
				return totalReadCount;
			}
			bufferLeftLength = mBufferLength;
		}

		const char* buffer = (const char*)mBuffer.Ptr();
		size_t size = bufferLeftLength;
		size_t i = 0;
		for (; i < size; ++i)
		{
			if (StdString::ConstValues<char>::IsNewLine(buffer[i]))
			{
				if (includeNewLine)
				{
					//check next char
					outString.Append(buffer, i + 1);

					if (i + 1 < size)
					{
						if (StdString::ConstValues<char>::IsNewLine(buffer[i + 1]))
						{
							++i;
						}
						outString.Append(buffer[i + 1]);
						totalReadCount += i;
						mBuffer.Skip(i);
						return totalReadCount;
					}
					else
					{
						totalReadCount += i;
						mBuffer.Skip(i);
						

						//reach current buffer end
						mBufferLength = mSourceStream->ReadDataTo(mBuffer.MutableBuffer());
						mBuffer.Rewind();
						if (mBufferLength == 0)	//reach end
						{
							return totalReadCount;
						}
						int nextChar= mBuffer.PeekChar();
						if (nextChar==-1)
						{
							return totalReadCount;
						}

						if (StdString::ConstValues<char>::IsNewLine((char)nextChar))
						{
							outString.Append((char)nextChar);
							++totalReadCount;
							mBuffer.Skip(1);
						}
						return totalReadCount;

					}

				}
				else
				{
					outString.Append(buffer, i);	//not read '\n'
					totalReadCount += i;

					if (i + 1 < size)
					{
						if (StdString::ConstValues<char>::IsNewLine(buffer[i + 1]))
						{
							++i;
						}

						mBuffer.Skip(i);
					}
					else
					{
						mBuffer.Skip(i);

						//reach current buffer end
						mBufferLength = mSourceStream->ReadDataTo(mBuffer.MutableBuffer());
						mBuffer.Rewind();
						if (mBufferLength == 0)	//reach end
						{
							return totalReadCount;
						}
						int nextChar = mBuffer.PeekChar();
						if (nextChar == -1)
						{
							return totalReadCount;
						}

						if (StdString::ConstValues<char>::IsNewLine((char)nextChar))
						{
							mBuffer.Skip(1);
						}

					}
					return totalReadCount;

				}

			}
			else if (buffer[i] == '\0')
			{
				outString.Append(buffer, i);
				totalReadCount += i;
				mBuffer.Skip(i);
				return totalReadCount;
			}
		}

		if (i == size)	//reach buffer end
		{
			outString.Append(buffer, i);
			totalReadCount += i;
			mBuffer.Skip(i);
		}
	}

	return totalReadCount;
}

size_t BufferStream::ReadLineToString(WHeapString& outString, bool includeNewLine/*=true*/)const
{
	RETURN_FALSE_IF_FALSE(CanRead());
	FlushOnReadWrite(StreamDataOperation::Read);
	size_t totalReadCount = 0;
	while (true)
	{
		size_t bufferLeftLength = mBufferLength - mBuffer.Position();
		if (bufferLeftLength == 0)
		{
			mBufferLength = mSourceStream->ReadDataTo(mBuffer.MutableBuffer());
			mBuffer.Rewind();
			if (mBufferLength == 0)	//reach end
			{
				return totalReadCount;
			}
			bufferLeftLength = mBufferLength;
		}

		const wchar_t* buffer = (const wchar_t*)mBuffer.Ptr();
		size_t size = bufferLeftLength / sizeof(wchar_t);
		size_t i = 0;
		for (; i < size; ++i)
		{
			if (StdString::ConstValues<wchar_t>::IsNewLine(buffer[i]))
			{
				if (includeNewLine)
				{
					outString.Append(buffer, i+1);	//+1 to mean length
					//check next char

					if (i + 1 < size)
					{
						if (StdString::ConstValues<wchar_t>::IsNewLine(buffer[i + 1]))
						{
							++i;
						}
						outString.Append(buffer[i + 1]);
						totalReadCount += i*sizeof(wchar_t);
						mBuffer.Skip(i*sizeof(wchar_t));
						return totalReadCount;
					}
					else
					{
						totalReadCount += i*sizeof(wchar_t);
						mBuffer.Skip(i*sizeof(wchar_t));

						bufferLeftLength = mBufferLength - mBuffer.Position();
						if (bufferLeftLength!=0)	//left some data,cross buffer edge
						{
							int nextChar = ReadWChar();
							if (nextChar == -1)
							{
								return totalReadCount;
							}

							if (StdString::ConstValues<wchar_t>::IsNewLine((wchar_t)nextChar))
							{
								outString.Append((wchar_t)nextChar);
								totalReadCount += sizeof(wchar_t);
							}
							else
							{
								Seek(-(intp)sizeof(wchar_t),SeekOrigin::Current);
							}
						}
						else
						{
							//reach current buffer end
							mBufferLength = mSourceStream->ReadDataTo(mBuffer.MutableBuffer());
							mBuffer.Rewind();
							if (mBufferLength < sizeof(wchar_t))	//reach end
							{
								return totalReadCount;
							}
							int nextChar = mBuffer.PeekWChar();
							if (nextChar == -1)
							{
								return totalReadCount;
							}

							if (StdString::ConstValues<wchar_t>::IsNewLine((wchar_t)nextChar))
							{
								outString.Append((wchar_t)nextChar);
								totalReadCount += sizeof(wchar_t);
								mBuffer.Skip(sizeof(wchar_t));
							}
						}
						
						return totalReadCount;

					}
				}
				else
				{
					outString.Append(buffer, i);	//not read '\n'
					totalReadCount += i*sizeof(wchar_t);
					//check next char
					if (i + 1 < size)
					{
						if (StdString::ConstValues<wchar_t>::IsNewLine(buffer[i + 1]))
						{
							++i;
						}

						mBuffer.Skip(i*sizeof(wchar_t));
					}
					else
					{
						mBuffer.Skip(i*sizeof(wchar_t));
						bufferLeftLength = mBufferLength - mBuffer.Position();
						if (bufferLeftLength != 0)	//left some data,cross buffer edge
						{
							int nextChar = ReadWChar();
							if (nextChar == -1)
							{
								return totalReadCount;
							}

							if (!StdString::ConstValues<wchar_t>::IsNewLine((wchar_t)nextChar))
							{
								Seek(-(intp)sizeof(wchar_t), SeekOrigin::Current);
							}
						}
						else
						{
							//reach current buffer end
							mBufferLength = mSourceStream->ReadDataTo(mBuffer.MutableBuffer());
							mBuffer.Rewind();
							if (mBufferLength < sizeof(wchar_t))	//reach end
							{
								return totalReadCount;
							}
							int nextChar = mBuffer.PeekWChar();
							if (nextChar == -1)
							{
								return totalReadCount;
							}

							if (StdString::ConstValues<wchar_t>::IsNewLine((wchar_t)nextChar))
							{
								mBuffer.Skip(sizeof(wchar_t));
							}
						}

					}
					return totalReadCount;
				}

			}

			if (buffer[i] == L'\0')
			{
				outString.Append(buffer, i);
				totalReadCount += i*sizeof(wchar_t);
				mBuffer.Skip(i*sizeof(wchar_t));
				return totalReadCount;
			}
		}

		if (i == size)	//reach buffer end
		{
			outString.Append(buffer, i);
			totalReadCount += i*sizeof(wchar_t);
			mBuffer.Skip(i*sizeof(wchar_t));
			bufferLeftLength = mBufferLength - mBuffer.Position();
		}

		if (bufferLeftLength != 0)
		{
			//some data still left, size < sizeof(wchar_t)
			//copy left data to top
			MemoryData& buffer2 = mBuffer.MutableBuffer();
			Memory::SafeCopy(buffer2.MutableData(), buffer2.Size(), buffer2.Data() + mBuffer.Position(), bufferLeftLength);
			mBuffer.SetPosition(bufferLeftLength);

			//read need data
			MemoryData tempData = MemoryData::FromStatic(buffer2.Data(), mBuffer.Length() - bufferLeftLength);
			mBufferLength = mSourceStream->ReadDataTo(tempData) + bufferLeftLength;
			mBuffer.Rewind();
		}
	}

	return totalReadCount;
}

size_t BufferStream::WriteString(const StringRef& str, bool withNullTermitated /*= true*/)
{
	RETURN_ZERO_IF_FALSE(CanWrite());
	FlushOnReadWrite(StreamDataOperation::Write);
	MemoryData data = str.ToData().Cast<byte>();
	size_t size = WriteData(data);
	if (withNullTermitated)
	{
		size += WriteChar('\0') ? sizeof(char) : 0;
	}
	return size;
}

size_t BufferStream::WriteString(const WStringRef& str, bool withNullTermitated /*= true*/)
{
	RETURN_ZERO_IF_FALSE(CanWrite());
	FlushOnReadWrite(StreamDataOperation::Write);
	MemoryData data = str.ToData().Cast<byte>();
	size_t size = WriteData(data);
	if (withNullTermitated)
	{
		size += WriteChar(L'\0') ? sizeof(wchar_t) : 0;
	}
	return size;
}

MEDUSA_END;
