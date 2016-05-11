// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/IO/Stream/IStream.h"

MEDUSA_BEGIN;

class StringStream :public IStream
{
public:
	StringStream(size_t capacity = 0,bool isExpandable=true);
	StringStream(HeapString& data);
	StringStream(const HeapString& data);
	StringStream(const StringRef& data);


	virtual ~StringStream(void);
	virtual StreamType Type()const  override{ return StreamType::String; }
	StringStream(const StringStream& other);
	StringStream& operator=(const StringStream& other);
	StringStream(StringStream&& other);
	StringStream& operator=(StringStream&& other);

	static StringStream Create(size_t capacity = 0, bool isExpandable = true);
	static StringStream OpenRead(const HeapString& data);
	static StringStream OpenReadWrite(HeapString& data);

public:
	const HeapString& String() const { return *mData; }
	HeapString& MutableString(){ return *mData; }

	HeapString CurrentBuffer() const { return mData->SubString(0, mPos); }
	HeapString LeftBuffer() const { return mData->SubString(mPos, (size_t)LeftLength()); }

	HeapString Release();
public:
	virtual bool IsPtrAvailable()const override{ return true; }	//can expose ptr

	virtual const byte* Ptr()const override { return (byte*)mData->Buffer() + mPos; }
	virtual byte* MutablePtr() override { return (byte*)mData->MutableBuffer() + mPos; }

	virtual bool Flush() override;
	virtual bool Close() override;
	virtual bool IsOpen()const  override{ return true; }
	virtual bool IsEnd()const  override{ return mPos >= mData->Length(); }

	virtual bool Seek(intp offset, SeekOrigin direction = SeekOrigin::Current)const override;

	virtual bool SetLength(uintp val) override;
	virtual uintp Length()const  override{ return mData->Length(); }
	virtual uintp Position()const  override{ return mPos; }

	virtual size_t ReadDataTo(MemoryData& outData, DataReadingMode mode = DataReadingMode::AlwaysCopy)const override;
	virtual size_t WriteData(const MemoryData& data, DataReadingMode mode = DataReadingMode::AlwaysCopy) override;

	virtual int PeekChar()const override;
	virtual int PeekWChar()const override;
	virtual int ReadChar()const override;
	virtual int ReadWChar()const override;
	virtual bool WriteChar(char val) override;
	virtual bool WriteChar(wchar val) override;

	virtual size_t ReadStringTo(HeapString& outString)const override;
	virtual size_t ReadStringTo(WHeapString& outString)const override;

	virtual size_t ReadLineToString(HeapString& outString, bool includeNewLine = true)const override;
	virtual size_t ReadLineToString(WHeapString& outString, bool includeNewLine = true)const override;
	virtual size_t WriteString(const StringRef& str, bool withNullTermitated = true) override;
	virtual size_t WriteString(const WStringRef& str, bool withNullTermitated = true) override;

	virtual bool CanRead()const override;
	virtual bool CanWrite()const override;
	virtual bool CanSeek()const override;
	virtual StreamDataOperation Operations()const override;
private:
	HeapString* mData=nullptr;
	bool mIsOwner = false;
	bool mIsBufferOwner = false;

	mutable size_t mPos;
	StreamDataOperation mSupportedOperation;
};


MEDUSA_END;