// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Core/IO/Stream/IStream.h"

MEDUSA_BEGIN;


MemoryData IStream::ReadBeginToCurrent(DataReadingMode mode/*=DataReadingMode::AlwaysCopy*/)const
{
	uintp pos = Position();
	Rewind();
	return ReadData((size_t)pos, mode);
}

MemoryData IStream::ReadToEnd(DataReadingMode mode/*=DataReadingMode::AlwaysCopy*/)const
{
	return ReadData((size_t)LeftLength(), mode);
}

MemoryData IStream::ReadData(size_t size, DataReadingMode mode/*=DataReadingMode::AlwaysCopy*/)const
{
	if (LeftLength() >= size)
	{
		if (Ptr() == nullptr)	//not support direct move
		{
			mode = DataReadingMode::AlwaysCopy;
		}

		switch (mode)
		{
		case DataReadingMode::AlwaysCopy:
		{
			MemoryData data = MemoryData::Alloc(size);
			size_t readSize = ReadDataTo(data, mode);
			data.ForceSetSize(readSize);

			return data;
		}
		break;
		case DataReadingMode::DirectMove:
		{
			MemoryData data;
			data.ForceSetSize(size);
			size_t readSize = ReadDataTo(data, mode);
			data.ForceSetSize(readSize);

			return data;
		}
		break;
		default:
			break;
		}

	}
	return MemoryData::Empty;
}

size_t IStream::CopyTo(IStream& dest, size_t bufferSize/*=1024*/)const
{
	RETURN_ZERO_IF_FALSE(CanRead() && dest.CanWrite());

	size_t realBufferSize = Math::Min(LeftLength(), bufferSize);
	size_t count = 0;

	MemoryData buffer = MemoryData::Alloc(realBufferSize);
	do
	{
		size_t readSize = ReadDataTo(buffer, DataReadingMode::AlwaysCopy);
		BREAK_IF_ZERO(readSize);
		buffer.ForceSetSize(readSize);
		count += dest.WriteData(buffer);
		buffer.ForceSetSize(realBufferSize);
	} while (true);



	return count;
}

size_t IStream::ReadToStream(size_t size, IStream& dest, size_t bufferSize/*=1024*/)const
{
	RETURN_ZERO_IF_FALSE(CanRead() && dest.CanWrite());

	if (dest.IsPtrAvailable())//could directly write
	{
		dest.ReserveLeftSize(size);
		byte* buffer = dest.MutablePtr();
		MemoryData destBuffer = MemoryData::FromStatic(buffer, size);
		return ReadDataTo(destBuffer, DataReadingMode::AlwaysCopy);
	}
	else
	{
		//should use temp  buffer
		size_t count = 0;
		size_t realBufferSize = Math::Min(LeftLength(), bufferSize, size);

		MemoryData tempBuffer = MemoryData::Alloc(realBufferSize);
		do
		{
			size_t readSize = Math::Min(size, realBufferSize);
			tempBuffer.ForceSetSize(readSize);

			readSize = ReadDataTo(tempBuffer, DataReadingMode::AlwaysCopy);
			BREAK_IF_ZERO(readSize);
			tempBuffer.ForceSetSize(readSize);
			count += dest.WriteData(tempBuffer);
			tempBuffer.ForceSetSize(realBufferSize);
			size -= readSize;
		} while (size > 0);
		return count;
	}

}

size_t IStream::ReadDataToString(HeapString& outString, int readCount/*=0*/, bool withNullTermitated /*= false*/)const
{
	RETURN_ZERO_IF_FALSE(CanRead());
	uintp readSize = 0;
	if (readCount == 0)
	{
		readSize = Math::Min(outString.LeftLength(), LeftLength());
	}
	else if (readCount < 0)
	{
		readSize = LeftLength();
		outString.ReserveLeftLength(readSize);
	}
	else
	{
		readSize = Math::Min((size_t)readCount, LeftLength());
		outString.ReserveLeftLength(readSize);
	}

	MemoryData outData = MemoryData::FromStatic((const byte*)outString.LeftPtr(), readSize);
	size_t count = ReadDataTo(outData, DataReadingMode::AlwaysCopy);
	if (withNullTermitated)
	{
		--count;
	}
	outString.ForceAppendLength(count);
	return count;
}

size_t IStream::ReadDataToString(WHeapString& outString, int readCount/*=0*/, bool withNullTermitated /*= false*/)const
{
	RETURN_ZERO_IF_FALSE(CanRead());

	uintp readSize = 0;
	if (readCount == 0)
	{
		readSize = Math::Min(outString.LeftLength()*sizeof(wchar_t), LeftLength());
	}
	else if (readCount < 0)
	{
		readSize = LeftLength();
		outString.ReserveLeftLength(readSize/sizeof(wchar_t));
	}
	else
	{
		readSize = Math::Min((size_t)readCount, LeftLength());
		outString.ReserveLeftLength(readSize/sizeof(wchar_t));
	}

	MemoryData outData = MemoryData::FromStatic((const byte*)outString.LeftPtr(), readSize*sizeof(wchar_t));
	size_t count = ReadDataTo(outData, DataReadingMode::AlwaysCopy);

	if (withNullTermitated)
	{
		count -= sizeof(wchar_t);
	}

	outString.ForceAppendLength(count / sizeof(wchar_t));

	return count;
}

size_t IStream::ReadAllLinesTo(List<HeapString>& outLines, size_t maxCount/*=1024*/, bool isTrim/*=true*/, bool ignoreEmptyLine/*=true*/)const
{
	size_t count = 0;
	HeapString temp;
	temp.ReserveLength(maxCount);
	while (true)
	{
		temp.Clear();
		size_t readCount = ReadLineToString(temp);
		count += readCount;
		BREAK_IF_ZERO(readCount);
		if (ignoreEmptyLine)
		{
			CONTINUE_IF_EMPTY(temp);
		}

		if (isTrim)
		{
			temp.TrimAll();
		}
		outLines.Add(temp);
		temp.ForceSetLength(0);
	}
	return count;
}


size_t IStream::ReadAllLinesTo(List<WHeapString>& outLines, size_t maxCount/*=1024*/, bool isTrim/*=true*/, bool ignoreEmptyLine/*=true*/)const
{
	size_t count = 0;
	WHeapString temp;
	temp.ReserveLength(maxCount);
	while (true)
	{
		temp.Clear();
		size_t readCount = ReadLineToString(temp);
		count += readCount;
		BREAK_IF_ZERO(readCount);
		if (ignoreEmptyLine)
		{
			CONTINUE_IF_EMPTY(temp);
		}

		if (isTrim)
		{
			temp.TrimAll();
		}
		outLines.Add(temp);
		temp.ForceSetLength(0);
	}
	return count;
}

HeapString IStream::ReadString(size_t maxCount /*= 1024*/)const
{
	if (!CanRead())
	{
		return HeapString::Empty;
	}
	HeapString str;
	ReadStringTo(str);
	return str;
}

WHeapString IStream::ReadStringW(size_t maxCount /*= 1024*/)const
{
	if (!CanRead())
	{
		return WHeapString::Empty;
	}
	WHeapString str;
	ReadStringTo(str);
	return str;
}

size_t IStream::WriteLine()
{
	return Write(StdString::ConstValues<char>::LineSeparator);
}



size_t IStream::WriteLineW()
{
	return Write(StdString::ConstValues<wchar>::LineSeparator);
}

size_t IStream::WriteLine(const StringRef& str, bool withNullTermitated/* = false*/)
{
	if (withNullTermitated)
	{
		return WriteString(str, false) + WriteLine() + Write('\0');
	}
	else
	{
		return WriteString(str, false) + WriteLine();
	}
}

size_t IStream::WriteLine(const WStringRef& str, bool withNullTermitated /*= false*/)
{
	if (withNullTermitated)
	{
		return WriteString(str, false) + WriteLineW() + Write('\0');
	}
	else
	{
		return WriteString(str, false) + WriteLineW();
	}
}

bool IStream::ReserveSize(size_t size)
{
	if (size <= Length())
	{
		return true;
	}
	return SetLength(size);
}


bool IStream::ReserveLeftSize(size_t size)
{
	if (size < LeftLength())
	{
		return true;
	}
	return SetLength(Position() + size);
}


MEDUSA_END;
