// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/IO/Stream/IStream.h"
#include "Core/IO/Stream/MemoryStream.h"

MEDUSA_BEGIN;

class BlockWriteStream :public IStream
{
public:
	BlockWriteStream(IStream& stream, uint32 blockSize);
	virtual ~BlockWriteStream(void);
	BlockWriteStream(const BlockWriteStream&) = delete;
	BlockWriteStream& operator=(const BlockWriteStream&) = delete;
	BlockWriteStream(BlockWriteStream&& other);
	BlockWriteStream& operator=(BlockWriteStream&& other);
public:
	virtual bool Flush() override;
	virtual bool Close() override;
	virtual bool IsOpen()const  override{ return mSourceStream->IsOpen(); }
	virtual bool IsEnd()const override;

	virtual uintp Position()const override;
	virtual bool SetLength(uintp val) override;
	virtual void Rewind() const override;

	virtual bool Seek(intp offset, SeekOrigin direction = SeekOrigin::Current)const override;

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

	virtual bool CanRead()const  override{ return false; }
	virtual bool CanWrite()const  override{ return true; }
	virtual bool CanSeek()const  override{ return false; }
	virtual StreamDataOperation Operations()const override { return StreamDataOperation::Write; }
protected:
	size_t WriteCurrentBlock(bool force=false);
	virtual size_t WriteBlock(uint blockIndex,const MemoryByteData& data)=0;
protected:
	IStream* mSourceStream;
	mutable MemoryStream mBuffer;
	mutable uint mBlockIndex = 0;
};


MEDUSA_END;