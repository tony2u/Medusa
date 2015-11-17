// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Core/IO/Stream/BlockReadStream.h"
#include "Core/Log/Log.h"
#include "Core/Memory/MemoryData.h"

MEDUSA_BEGIN;


BlockReadStream::BlockReadStream(const IStream& stream,uint32 blockSize)
	: mSourceStream(&stream),
	mBuffer(blockSize, false),
	mBufferLength(0),
	mBlockIndex(Math::UIntMaxValue)
{
	SAFE_RETAIN(mSourceStream);
}


BlockReadStream::BlockReadStream(BlockReadStream&& other)
	:mSourceStream(nullptr),
	mBuffer(std::move(other.mBuffer)),
	mBufferLength(other.mBufferLength),
	mBlockIndex(other.mBlockIndex)

{
	SAFE_MOVE_REF(mSourceStream, other.mSourceStream);
	other.mBufferLength = 0;
	other.mBlockIndex = Math::UIntMaxValue;

}

BlockReadStream& BlockReadStream::operator=(BlockReadStream&& other)
{
	if (this != &other)
	{
		Close();
		SAFE_MOVE_REF(mSourceStream, other.mSourceStream);
		mBuffer = std::move(other.mBuffer);
		mBufferLength = other.mBufferLength;
		mBlockIndex = other.mBlockIndex;

		other.mBlockIndex = 0;
	}
	return *this;
}



BlockReadStream::~BlockReadStream(void)
{
	
}

bool BlockReadStream::Close()
{
	SAFE_RELEASE(mSourceStream);

	return true;
}

bool BlockReadStream::IsEnd() const
{
	return Position() >= Length();
}

bool BlockReadStream::CanRead() const
{
	return !IsEnd();
}

size_t BlockReadStream::LoadCurrentBlock()const
{
	mBuffer.Rewind();
	mBufferLength = LoadBlockTo(mBlockIndex, mBuffer);
	mBuffer.Rewind();
	return mBufferLength;
}


bool BlockReadStream::Flush()
{
	return ((IStream*)mSourceStream)->Flush();
}

uintp BlockReadStream::Position() const
{
	if (mBlockIndex > 0&& mBlockIndex!=Math::UIntMaxValue)
	{
		uintp prevSize = (mBlockIndex - 1)*mBuffer.Length();
		return prevSize + mBuffer.Position();
	}
	return mBuffer.Position();
}

bool BlockReadStream::Seek(intp offset, SeekOrigin direction /*= SeekOrigin::Current*/)const
{
	switch (direction)
	{
	case SeekOrigin::Head:
	{
		RETURN_FALSE_IF(offset<0||(uintp)offset > Length());
		uint blockIndex = (uint)offset / (uint32)mBuffer.Length();
		uint pos = offset % (uint32)mBuffer.Length();

		if (mBlockIndex != blockIndex)
		{
			mBlockIndex = blockIndex;
			LoadCurrentBlock();
			mBuffer.SetPosition(pos);
		}
		else
		{
			mBuffer.SetPosition(pos);
		}

		return true;
	}
	case SeekOrigin::Current:
	{
		intp pos = (intp)Position();
		pos += offset;
		if (pos < 0 || (uintp)pos >= Length())
		{
			return false;
		}

		return Seek(pos, SeekOrigin::Head);
	}
	case SeekOrigin::End:
	{
		offset += Length();
		if (offset < 0 || (uintp)offset >= Length())
		{
			return false;
		}
		return Seek(offset, SeekOrigin::Head);
	}
	default:
		break;
	}
	return false;
}

bool BlockReadStream::SetLength(uintp val)
{
	throw std::logic_error("The method or operation is not implemented.");
}


size_t BlockReadStream::ReadDataTo(MemoryByteData& outData, DataReadingMode mode/*=DataReadingMode::AlwaysCopy*/)const
{
	RETURN_ZERO_IF_FALSE(CanRead());

	size_t outPos = 0;
	size_t outSize = outData.Size();

	//read left buffer data
	size_t bufferLeftLength = mBufferLength - mBuffer.Position();
	if (bufferLeftLength != 0)
	{
		size_t readSize = Math::Min(bufferLeftLength, outSize);
		MemoryByteData tempData = MemoryByteData::FromStatic(outData.MutableData(), readSize);
		readSize = mBuffer.ReadDataTo(tempData, DataReadingMode::AlwaysCopy);
		outPos += readSize;
		outSize -= readSize;
	}

	if (outSize > 0)
	{
		mBuffer.Rewind();
		mBufferLength = 0;

		//directly read to out data block per block
		size_t blockSize = mBuffer.Length();
		size_t blockCount = outSize / blockSize;
		FOR_EACH_SIZE(i, blockCount)
		{
			MemoryByteData tempData = MemoryByteData::FromStatic(outData.MutableData() + outPos, blockSize);
			MemoryStream tempStream(tempData);
			++mBlockIndex;
			size_t readSize = LoadBlockTo(mBlockIndex, tempStream);
			outPos += readSize;
			outSize -= readSize;
			if (readSize != blockSize)	//reach file end
			{
				return outPos;
			}
		}
	}

	//read left data
	if (outSize > 0)
	{
		++mBlockIndex;
		LoadCurrentBlock();

		if (mBufferLength == 0)	//reach end
		{
			return outPos;
		}

		bufferLeftLength = mBufferLength - mBuffer.Position();
		size_t readSize = Math::Min(bufferLeftLength, outSize);
		MemoryByteData tempData = MemoryByteData::FromStatic(outData.MutableData() + outPos, readSize);
		readSize = mBuffer.ReadDataTo(tempData, DataReadingMode::AlwaysCopy);
		outPos += readSize;
		outSize -= readSize;
	}

	return outPos;
}

size_t BlockReadStream::WriteData(const MemoryByteData& data, DataReadingMode mode /*= DataReadingMode::AlwaysCopy*/)
{
	throw std::logic_error("The method or operation is not implemented.");
}

int BlockReadStream::PeekChar()const
{
	RETURN_OBJECT_IF_FALSE(CanRead(), -1);
	size_t bufferLeftLength = mBufferLength - mBuffer.Position();
	if (bufferLeftLength == 0)
	{
		++mBlockIndex;
		LoadCurrentBlock();
		if (mBufferLength == 0)	//reach end
		{
			return -1;
		}
	}

	return mBuffer.PeekChar();
}

int BlockReadStream::PeekWChar()const
{
	RETURN_OBJECT_IF_FALSE(CanRead(), -1);
	int c = ReadWChar();
	if (c != -1)
	{
		Seek(-(intp)sizeof(wchar_t));
	}

	return c;
}


int BlockReadStream::ReadChar()const
{
	RETURN_OBJECT_IF_FALSE(CanRead(), -1);

	size_t bufferLeftLength = mBufferLength - mBuffer.Position();
	if (bufferLeftLength == 0)
	{
		++mBlockIndex;
		LoadCurrentBlock();
		if (mBufferLength == 0)	//reach end
		{
			return -1;
		}
	}

	return mBuffer.ReadChar();
}

int BlockReadStream::ReadWChar()const
{
	RETURN_OBJECT_IF_FALSE(CanRead(), -1);
	wchar_t c;
	MemoryByteData tempData = MemoryByteData::FromStatic((byte*)&c, sizeof(wchar_t));
	size_t readSize = ReadDataTo(tempData);
	if (readSize != sizeof(wchar_t))
	{
		return -1;
	}
	return c;
}

bool BlockReadStream::WriteChar(char val)
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool BlockReadStream::WriteChar(wchar val)
{
	throw std::logic_error("The method or operation is not implemented.");
}


size_t BlockReadStream::ReadStringTo(HeapString& outString)const
{
	RETURN_FALSE_IF_FALSE(CanRead());

	size_t totalReadCount = 0;
	while (true)
	{
		size_t bufferLeftLength = mBufferLength - mBuffer.Position();
		if (bufferLeftLength == 0)
		{
			++mBlockIndex;
			LoadCurrentBlock();
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

size_t BlockReadStream::ReadStringTo(WHeapString& outString)const
{
	RETURN_FALSE_IF_FALSE(CanRead());

	size_t totalReadCount = 0;
	while (true)
	{
		size_t bufferLeftLength = mBufferLength - mBuffer.Position();
		if (bufferLeftLength == 0)
		{
			++mBlockIndex;
			LoadCurrentBlock();
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
			totalReadCount += i;
			mBuffer.Skip(i);
			bufferLeftLength = mBufferLength - mBuffer.Position();
		}

		if (bufferLeftLength != 0)
		{
			//read left data
			wchar_t c = 0;
			MemoryByteData wcharBuffer1 = MemoryByteData::FromStatic((byte*)&c, bufferLeftLength);
			mBuffer.ReadDataTo(wcharBuffer1);

			++mBlockIndex;
			LoadCurrentBlock();
			size_t length2 = sizeof(wchar_t) - bufferLeftLength;
			if (mBufferLength < length2)	//reach end
			{
				return totalReadCount;
			}

			MemoryByteData wcharBuffer2 = MemoryByteData::FromStatic((byte*)&c + bufferLeftLength, sizeof(wchar_t) - bufferLeftLength);
			mBuffer.ReadDataTo(wcharBuffer2);

			if (c == L'\0')
			{
				return totalReadCount;
			}
			else
			{
				outString.Append(c);
			}

		}
	}

	return totalReadCount;

}

size_t BlockReadStream::ReadLineToString(HeapString& outString, bool includeNewLine/*=true*/)const
{
	RETURN_FALSE_IF_FALSE(CanRead());

	size_t totalReadCount = 0;
	while (true)
	{
		size_t bufferLeftLength = mBufferLength - mBuffer.Position();
		if (bufferLeftLength == 0)
		{
			++mBlockIndex;
			LoadCurrentBlock();
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
						++mBlockIndex;
						LoadCurrentBlock();
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
						++mBlockIndex;
						LoadCurrentBlock();
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

size_t BlockReadStream::ReadLineToString(WHeapString& outString, bool includeNewLine/*=true*/)const
{
	RETURN_FALSE_IF_FALSE(CanRead());
	size_t totalReadCount = 0;
	while (true)
	{
		size_t bufferLeftLength = mBufferLength - mBuffer.Position();
		if (bufferLeftLength == 0)
		{
			++mBlockIndex;
			LoadCurrentBlock();
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
					outString.Append(buffer, i + 1);	//+1 to mean length
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
						if (bufferLeftLength != 0)	//left some data,cross buffer edge
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
								Seek(-(intp)sizeof(wchar_t), SeekOrigin::Current);
							}
						}
						else
						{
							//reach current buffer end
							++mBlockIndex;
							LoadCurrentBlock();
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
							++mBlockIndex;
							LoadCurrentBlock();
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
			mBuffer.Skip(i);
			bufferLeftLength = mBufferLength - mBuffer.Position();
		}

		if (bufferLeftLength != 0)
		{
			//read left data
			wchar_t c = 0;
			MemoryByteData wcharBuffer1 = MemoryByteData::FromStatic((byte*)&c, bufferLeftLength);
			mBuffer.ReadDataTo(wcharBuffer1);

			++mBlockIndex;
			LoadCurrentBlock();

			size_t length2 = sizeof(wchar_t) - bufferLeftLength;
			if (mBufferLength < length2)	//reach end
			{
				return totalReadCount;
			}

			MemoryByteData wcharBuffer2 = MemoryByteData::FromStatic((byte*)&c + bufferLeftLength, sizeof(wchar_t) - bufferLeftLength);
			mBuffer.ReadDataTo(wcharBuffer2);

			if (StdString::ConstValues<wchar_t>::IsNewLine(c))
			{
				if (includeNewLine)
				{
					outString.Append(c);
					totalReadCount += sizeof(wchar_t);

					//check next char
					c = (wchar_t)mBuffer.ReadWChar();
					if (c == -1)
					{
						return totalReadCount;
					}

					if (StdString::ConstValues<wchar_t>::IsNewLine(c))
					{
						outString.Append(c);
						totalReadCount += sizeof(wchar_t);
					}
					else
					{
						mBuffer.Seek(-(intp)sizeof(wchar_t), SeekOrigin::Current);
					}
				}
				else
				{
					//check next char
					c = (wchar_t)mBuffer.ReadWChar();

					if (c != -1 && !StdString::ConstValues<wchar_t>::IsNewLine(c))
					{
						mBuffer.Seek(-(intp)sizeof(wchar_t), SeekOrigin::Current);
					}
				}

				return totalReadCount;
			}
			else if (c == L'\0')
			{
				return totalReadCount;
			}
			else
			{
				outString.Append(c);
			}
		}
	}

	return totalReadCount;
}

size_t BlockReadStream::WriteString(const StringRef& str, bool withNullTermitated /*= true*/)
{
	throw std::logic_error("The method or operation is not implemented.");
}

size_t BlockReadStream::WriteString(const WStringRef& str, bool withNullTermitated /*= true*/)
{
	throw std::logic_error("The method or operation is not implemented.");
}

MEDUSA_END;
