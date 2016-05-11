// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/IO/Stream/IStream.h"

MEDUSA_BEGIN;

class MemoryStream :public IStream
{
public:
	MemoryStream(size_t capacity = 0,bool isExpandable=true);
	MemoryStream(MemoryData& data);
	MemoryStream(const MemoryData& data);

	virtual ~MemoryStream(void);
	virtual StreamType Type()const  override{ return StreamType::Memory; }
	MemoryStream(const MemoryStream& other);
	MemoryStream& operator=(const MemoryStream& other);
	MemoryStream(MemoryStream&& other);
	MemoryStream& operator=(MemoryStream&& other);

	static MemoryStream Create(size_t capacity = 0, bool isExpandable = true);
	static MemoryStream OpenRead(const MemoryData& data);
	static MemoryStream OpenReadWrite(MemoryData& data);

public:
	const MemoryData& Buffer() const { return mData; }
	MemoryData& MutableBuffer(){ return mData; }

	void SetBuffer(const MemoryData& val) { mData = val; }

	MemoryData CurrentBuffer() const { return mData.Sub(0, mPos); }
	MemoryData LeftBuffer() const { return mData.Sub(mPos, (size_t)LeftLength()); }

	size_t ReleaseToString(HeapString& outString);

public:
	virtual bool IsPtrAvailable()const override{ return true; }	//can expose ptr

	virtual const byte* Ptr()const override { return mData.Data() + mPos; }
	virtual byte* MutablePtr() override { return mData.MutableData() + mPos; }

	virtual bool Flush() override;
	virtual bool Close() override;
	virtual bool IsOpen()const  override{ return mData.IsValid(); }
	virtual bool IsEnd()const  override{ return mPos >= mData.Size(); }

	virtual bool Seek(intp offset, SeekOrigin direction = SeekOrigin::Current)const override;

	virtual bool SetLength(uintp val) override;
	virtual uintp Length()const  override{ return mData.Size(); }
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
	bool CanGrow()const;
	bool Resize(size_t size);
private:
	MemoryData mData;
	mutable size_t mPos;
	StreamDataOperation mSupportedOperation;
};


MEDUSA_END;