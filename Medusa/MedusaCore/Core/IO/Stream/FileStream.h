// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "Core/IO/FileDefines.h"
#include "Core/IO/Stream/IStream.h"
#include "Core/String/HeapString.h"

MEDUSA_BEGIN;

class FileStream :public IStream
{
public:
	FileStream(void);
	FileStream(StringRef inFileName, FileOpenMode openMode = FileOpenMode::ReadOnly, FileDataType dataType = FileDataType::Binary);
	virtual ~FileStream(void);
	virtual StreamType Type()const  override{ return StreamType::File; }

	FileStream(const FileStream&) = delete;
	FileStream& operator=(const FileStream&) = delete;
	FileStream(FileStream&& other);
	FileStream& operator=(FileStream&& other);

public:
	bool OpenReadBinary(StringRef fileName);
	bool OpenReadText(StringRef fileName);
	bool OpenNewWriteBinary(StringRef fileName);
	bool OpenNewWriteText(StringRef fileName);
	bool Open(StringRef inFileName, FileOpenMode openMode = FileOpenMode::ReadOnly, FileDataType dataType = FileDataType::Binary);

	int Printf(const char* inStringFormat, ...);
	int Scanf(const char* inStringFormat, ...);
	int GetLastErrorID()const;
	void ClearError()const;
	static FILE* CreateTempFile();
	int GetFileHandle()const;
	bool IsErrorInFile()const;
	bool GetCurrentPos(fpos_t* outPosition)const;
	bool SetCurrentPos(const fpos_t* inNewPosition);

	bool SetBuffer(FileBufferMode mode, byte* buffer, size_t size)const;
	bool WriteBack(int inBackChar);
	FILE* GetFile() const { return mFile; }
	virtual bool IsOpen()const  override{ return mFile != nullptr; }
	virtual bool IsEnd()const override;

public:
	virtual void Rewind()const override;

	virtual bool Flush() override;
	virtual bool Close() override;
	virtual bool Seek(intp offset, SeekOrigin direction = SeekOrigin::Current)const override;
	virtual bool SetLength(uintp val) override;
	virtual uintp Length()const override;
	virtual uintp Position()const override;

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
	virtual bool CanSeek()const  override{ return true; }
	virtual StreamDataOperation Operations()const override;
private:
	bool IsReadWrite()const;
	void FlushOnReadWrite(StreamDataOperation curOperation)const;
private:
	FILE* mFile;
	HeapString mFileName;
	StreamDataOperation mSupportedOperation;
	mutable StreamDataOperation mPrevOperation;
};


MEDUSA_END;