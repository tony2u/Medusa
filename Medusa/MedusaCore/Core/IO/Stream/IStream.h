// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/IO/FileDefines.h"
#include "Core/Memory/Memory.h"
#include "Core/Memory/MemoryData.h"
#include "Core/String/HeapString.h"
#include "StreamDefines.h"
#include "Core/Pattern/ISharable.h"

MEDUSA_BEGIN;

class IStream:public ISharableThreadSafe
{
protected:
	IStream(void) {}
public:
	virtual ~IStream(void) {}
	virtual StreamType Type()const = 0;

public:
	template<class T>
	size_t ReadTo(T& outVal)const
	{
		MemoryByteData data = MemoryByteData::FromStatic((byte*)&outVal, sizeof(T));
		return ReadDataTo(data);
	};

	//So confident that this have to be succeed!
	template<class T>
	T Read()const
	{
		T outVal;
		MemoryByteData data = MemoryByteData::FromStatic((byte*)&outVal, sizeof(T));
		ReadDataTo(data);
		return outVal;
	};

	template<class T, typename TCompare>
	size_t ReadToList(size_t size, List<T, TCompare>& outItems)const
	{
		outItems.Clear();
		size_t count = size / sizeof(T);
		outItems.ReserveSize(count);
		byte* buffer = (byte*)outItems.MutableItems();

		MemoryByteData data = MemoryByteData::FromStatic(buffer, size);
		size_t readSize = ReadDataTo(data);
		outItems.ForceSetCount(readSize / sizeof(T));
		return readSize;
	}

	MemoryByteData ReadBeginToCurrent(DataReadingMode mode = DataReadingMode::AlwaysCopy)const;
	MemoryByteData ReadToEnd(DataReadingMode mode = DataReadingMode::AlwaysCopy)const;
	MemoryByteData ReadData(size_t size, DataReadingMode mode = DataReadingMode::AlwaysCopy)const;

public:
	template<class T>
	size_t Write(const T& val)
	{
		return WriteData(MemoryByteData::FromStatic((byte*)&val, sizeof(T)));
	}

	template<class T>
	size_t Write(const T* begin, const T* end)
	{
		size_t size = (end - begin)*sizeof(T);
		return WriteData(MemoryByteData::FromStatic((byte*)begin, size));
	}

public:
	void SetPosition(uintp val) const { Seek((intp)val, SeekOrigin::Head); }
	uintp LeftLength()const { return Length() - Position(); }
	bool Skip(size_t size) { return Seek((intp)size, SeekOrigin::Current); }
	template<typename T> IStream& operator<<(T val) { Write(val); return *this; }
	template<typename T> const IStream& operator>>(T val)const { ReadTo(val); return *this; }
	size_t CopyTo(IStream& dest, size_t bufferSize = 1024)const;
	size_t ReadToStream(size_t size,IStream& dest, size_t bufferSize=1024)const;


	size_t ReadAllLinesTo(List<HeapString>& outLines, size_t maxCount = 1024, bool isTrim = true, bool ignoreEmptyLine = true)const;
	size_t ReadAllLinesTo(List<WHeapString>& outLines, size_t maxCount = 1024, bool isTrim = true, bool ignoreEmptyLine = true)const;
	size_t ReadDataToString(HeapString& outString)const;
	size_t ReadDataToString(WHeapString& outString)const;

	HeapString ReadString(size_t maxCount = 1024)const;
	WHeapString ReadStringW(size_t maxCount = 1024)const;

	size_t WriteLine();
	size_t WriteLineW();

	size_t WriteLine(const StringRef& str, bool withNullTermitated = false);
	size_t WriteLine(const WStringRef& str, bool withNullTermitated = false);
public:
	bool ReserveSize(size_t size);
	bool ReserveLeftSize(size_t size);

	virtual bool IsPtrAvailable()const { return false; }	//can expose ptr
	virtual const byte* Ptr()const { return nullptr; }
	virtual byte* MutablePtr() { return nullptr; }

	virtual void Rewind()const { Seek(0, SeekOrigin::Head); }

	virtual bool Flush() = 0;
	virtual bool Close() = 0;
	virtual bool IsOpen()const = 0;
	virtual bool IsEnd()const = 0;


	virtual bool Seek(intp offset, SeekOrigin direction = SeekOrigin::Current)const = 0;
	virtual bool SetLength(uintp val) = 0;
	virtual uintp Length()const = 0;
	virtual uintp Position()const = 0;

	virtual size_t ReadDataTo(MemoryByteData& outData, DataReadingMode mode = DataReadingMode::AlwaysCopy) const = 0;
	virtual int PeekChar() const = 0;
	virtual int PeekWChar() const = 0;
	virtual int ReadChar() const = 0;
	virtual int ReadWChar() const = 0;


	
	virtual size_t ReadStringTo(HeapString& outString) const = 0;
	virtual size_t ReadStringTo(WHeapString& outString) const = 0;



	virtual size_t ReadLineToString(HeapString& outString, bool includeNewLine = true) const = 0;
	virtual size_t ReadLineToString(WHeapString& outString, bool includeNewLine = true) const = 0;

	virtual bool WriteChar(char val) = 0;
	virtual bool WriteChar(wchar val) = 0;
	virtual size_t WriteData(const MemoryByteData& data, DataReadingMode mode = DataReadingMode::AlwaysCopy) = 0;

	virtual size_t WriteString(const StringRef& str, bool withNullTermitated = true) = 0;
	virtual size_t WriteString(const WStringRef& str, bool withNullTermitated = true) = 0;


	virtual bool CanRead()const = 0;
	virtual bool CanWrite()const = 0;
	virtual bool CanSeek()const = 0;
	virtual StreamDataOperation Operations()const = 0;
};


MEDUSA_END;