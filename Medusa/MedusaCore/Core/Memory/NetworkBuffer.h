// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/System/BitConverter.h"
#include "Core/Memory/Memory.h"
#include "Core/String/StringRef.h"
#include "Core/IO/Stream/StreamDefines.h"
#include "Core/IO/Stream/MemoryStream.h"
MEDUSA_BEGIN;


/// A buffer class modeled after org.jboss.netty.buffer.ChannelBuffer
///
/// 
/// +------------------+------------------+
/// |  readable bytes  |  writable bytes  |
/// |     (CONTENT)    |                  |
/// +------------------+------------------+
/// |                  |                  |
/// readerIndex  <=  writerIndex    <=   size
/// 

class NetworkBuffer
{
	constexpr static size_t mInitialSize = 1024*256;	//256K
public:
	explicit NetworkBuffer(size_t initialSize = mInitialSize);
	NetworkBuffer(const MemoryData& data);


	size_t ReadableCount() const { return mWriteIndex - mReadIndex; }
	size_t WritableCount() const { return mStream.Length() - mWriteIndex; }

	const byte* ReadBegin() const { return mStream.Ptr() + mReadIndex; }
	byte* WriteBegin() { return mStream.MutablePtr() + mWriteIndex; }

public:
	void Retrieve(size_t len);
	void RetrieveAll();
	void RetrieveUntil(const byte* end);

	template<typename T>
	void Retrieve() { Retrieve(sizeof(T)); }
public:
	StringRef ReadStringRef(size_t len);
	HeapString ReadString(size_t len);

	MemoryData ReadData(size_t len, DataReadingMode mode = DataReadingMode::AlwaysCopy);
	MemoryData ReadAllData(DataReadingMode mode = DataReadingMode::AlwaysCopy);

public:
	template<typename T>
	T PeekInteger() const
	{
		assert(ReadableCount() >= sizeof(T));
		T val = *(T*)ReadBegin();
		return BitConverter::NetworkToHost(val);
	}

	template<typename T>
	typename std::enable_if<std::is_integral<T>::value, T>::type Peek()const
	{
		return PeekInteger<T>();
	}
public:
	template<typename T>
	T ReadInteger()
	{
		T result = PeekInteger<T>();
		Retrieve<T>();
		return result;
	}

	template<typename T>
	typename std::enable_if<std::is_integral<T>::value, T>::type Read()
	{
		return ReadInteger<T>();
	}

public:
	template<typename T>
	void WriteInteger(T val)
	{
		T result = BitConverter::HostToNetwork(val);
		Write((const byte*)&result, sizeof(T));
	}

	template<typename T>
	typename std::enable_if<std::is_integral<T>::value, void>::type Write(T val)
	{
		WriteInteger(val);
	}

	void Write(const byte* data, size_t len);
	void Write(const StringRef& val);
	void Write(const MemoryData& val);


public:
	void EnsureWritableCount(size_t len);
	void HasWritten(size_t len);
	void Unwrite(size_t len);

	void TryAdjust();
	void Reserve(size_t len);

	size_t Size()const { return mStream.Length(); }
	bool IsFull()const { return WritableCount() == 0; }

private:
	MemoryStream mStream;

	size_t mReadIndex = 0;	//use index instead of ptr, as buffer will realloc
	size_t mWriteIndex = 0;

};

MEDUSA_END;