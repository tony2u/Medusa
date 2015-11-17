// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/IO/Stream/IStream.h"

MEDUSA_BEGIN;

class SpanStream :public IStream
{
public:
	SpanStream(IStream& stream, uintp limitBegin = 0, uintp litmitSize = 0);
	SpanStream(const IStream& stream, uintp limitBegin = 0, uintp litmitSize = 0);

	virtual ~SpanStream(void);
	virtual StreamType Type()const  override{ return StreamType::Span; }
	SpanStream(const SpanStream&) = delete;
	SpanStream& operator=(const SpanStream&) = delete;
	SpanStream(SpanStream&& other);
	SpanStream& operator=(SpanStream&& other);
public:
	virtual bool IsPtrAvailable()const override { return mSourceStream->IsPtrAvailable(); }	//can expose ptr
	virtual const byte* Ptr()const override { return mSourceStream->Ptr(); }
	virtual byte* MutablePtr() override { return mSourceStream->MutablePtr(); }

	virtual bool Flush() override;
	virtual bool Close() override;
	virtual bool IsOpen()const  override{ return mSourceStream->IsOpen(); }
	virtual bool IsEnd()const override;

	virtual bool Seek(intp offset, SeekOrigin direction = SeekOrigin::Current)const override;

	virtual bool SetLength(uintp val) override;
	virtual uintp Length()const override;
	virtual uintp Position()const  override{ return mSourceStream->Position() - mLimitBegin; }

	virtual size_t ReadDataTo(MemoryByteData& outData, DataReadingMode mode = DataReadingMode::AlwaysCopy)const override;
	virtual size_t WriteData(const MemoryByteData& data, DataReadingMode mode = DataReadingMode::AlwaysCopy) override;

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
	virtual bool CanSeek()const  override{ return mSourceStream->CanSeek(); }
	virtual StreamDataOperation Operations()const override;

private:
	bool IsSourcePosValid()const;
private:
	IStream* mSourceStream;
	bool mIsSourceReadonly;

	uintp mLimitBegin;
	uintp mLimitSize;
};


MEDUSA_END;