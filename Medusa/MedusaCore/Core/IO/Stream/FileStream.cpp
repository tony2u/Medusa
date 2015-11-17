// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Core/IO/Stream/FileStream.h"
#include "Core/String/StackString.h"
#include "Core/IO/Directory.h"

MEDUSA_BEGIN;

FileStream::FileStream(void) :mFile(nullptr)
{
}

FileStream::FileStream(StringRef inFileName, FileOpenMode openMode/*=FileOpenMode::ReadOnly*/, FileDataType dataType/*=FileDataType::Binary*/) : mFile(nullptr)
{
	Open(inFileName, openMode, dataType);
}

FileStream::FileStream(FileStream&& other)
	: mFile(other.mFile),
	mFileName(std::move(other.mFileName)),
	mSupportedOperation(other.mSupportedOperation),
	mPrevOperation(other.mPrevOperation)
{
	other.mFile = nullptr;
	other.mSupportedOperation = StreamDataOperation::None;
	other.mPrevOperation = StreamDataOperation::None;
}

FileStream& FileStream::operator=(FileStream&& other)
{
	if (this != &other)
	{
		Close();

		mFile = other.mFile;
		mFileName = std::move(other.mFileName);
		mSupportedOperation = other.mSupportedOperation;
		mPrevOperation = other.mPrevOperation;

		other.mFile = nullptr;
		other.mSupportedOperation = StreamDataOperation::None;
		other.mPrevOperation = StreamDataOperation::None;
	}

	return *this;
}


FileStream::~FileStream(void)
{
	if (mFile != nullptr)
	{
		Close();
	}
}

bool FileStream::OpenReadBinary(StringRef fileName)
{
	return Open(fileName, FileOpenMode::ReadOnly, FileDataType::Binary);
}

bool FileStream::OpenReadText(StringRef fileName)
{
	return Open(fileName, FileOpenMode::ReadOnly, FileDataType::Text);
}

bool FileStream::OpenNewWriteBinary(StringRef fileName)
{
	Directory::CreateDirectoryForFile(fileName);
	return Open(fileName, FileOpenMode::DestoryWriteOrCreate, FileDataType::Binary);
}

bool FileStream::OpenNewWriteText(StringRef fileName)
{
	Directory::CreateDirectoryForFile(fileName);
	return Open(fileName, FileOpenMode::DestoryWriteOrCreate, FileDataType::Text);
}

bool FileStream::Open(StringRef inFileName, FileOpenMode openMode, FileDataType dataType)
{
	RETURN_FALSE_IF_EMPTY(inFileName);

	StackString<4> openModeString;

	mPrevOperation = StreamDataOperation::None;
	mSupportedOperation= StreamDataOperation::Seek;
	switch (openMode)
	{
	case FileOpenMode::ReadOnly:
		openModeString = "r";	//read
		MEDUSA_ADD_FLAG(mSupportedOperation, StreamDataOperation::Read);
		break;
	case FileOpenMode::DestoryWriteOrCreate:
		openModeString = "w";	//write
		MEDUSA_ADD_FLAG(mSupportedOperation, StreamDataOperation::Write);
		MEDUSA_ADD_FLAG(mSupportedOperation, StreamDataOperation::Grow);
		break;
	case FileOpenMode::AppendWriteKeepEOFOrCreate:
		openModeString = "a";	//write
		MEDUSA_ADD_FLAG(mSupportedOperation, StreamDataOperation::Write);
		MEDUSA_ADD_FLAG(mSupportedOperation, StreamDataOperation::Grow);
		break;
	case FileOpenMode::ReadWrite:
		openModeString = "r+";	//read write
		MEDUSA_ADD_FLAG(mSupportedOperation, StreamDataOperation::ReadWrite);
		MEDUSA_ADD_FLAG(mSupportedOperation, StreamDataOperation::Grow);
		break;
	case FileOpenMode::DestoryReadWriteOrCreate:
		openModeString = "w+";	//read write
		MEDUSA_ADD_FLAG(mSupportedOperation, StreamDataOperation::ReadWrite);
		MEDUSA_ADD_FLAG(mSupportedOperation, StreamDataOperation::Grow);
		break;
	case FileOpenMode::AppendReadWriteClearEOFOrCreate:
		openModeString = "a+";	//read write
		MEDUSA_ADD_FLAG(mSupportedOperation, StreamDataOperation::ReadWrite);
		MEDUSA_ADD_FLAG(mSupportedOperation, StreamDataOperation::Grow);
		break;
	default:
		break;
	}



	if (dataType == FileDataType::Binary)
	{
		openModeString += 'b';
	}
	else if (dataType == FileDataType::Text)
	{
		openModeString += 't';
	}

#ifdef MEDUSA_WINDOWS
	fopen_s(&mFile, inFileName.Buffer(), openModeString.Buffer());
#else 
	mFile = fopen(inFileName.Buffer(), openModeString.Buffer());
#endif

	if (mFile != nullptr)
	{
		mFileName = inFileName;
		return true;
	}
	return false;
}

bool FileStream::Close()
{
	RETURN_TRUE_IF_NULL(mFile);
	bool result = fclose(mFile) == 0;
	mFile = nullptr;

	return result;
}

bool FileStream::Flush()
{
	return fflush(mFile) == 0 ? true : false;
}

bool FileStream::IsEnd() const
{
	return feof(mFile) != 0;
}

size_t FileStream::WriteData(const MemoryByteData& data, DataReadingMode mode /*= DataReadingMode::AlwaysCopy*/)
{
	RETURN_ZERO_IF_FALSE(CanWrite());
	FlushOnReadWrite(StreamDataOperation::Write);
	return fwrite(data.Data(), 1, data.Size(), mFile);
}

size_t FileStream::ReadDataTo(MemoryByteData& outData, DataReadingMode mode/*=DataReadingMode::AlwaysCopy*/)const
{
	RETURN_ZERO_IF_FALSE(CanRead());
	FlushOnReadWrite(StreamDataOperation::Read);
	//ignore mode
	size_t count = fread(outData.MutableData(), 1, outData.Size(), mFile);
	outData.ForceSetSize(count);
	return count;
}

int FileStream::PeekChar()const
{
	RETURN_OBJECT_IF_FALSE(CanRead(), -1);
	FlushOnReadWrite(StreamDataOperation::Read);
	int c = ReadChar();
	if (c != -1)
	{
		ungetc(c, mFile);
	}
	return c;
}

int FileStream::PeekWChar()const
{
	RETURN_OBJECT_IF_FALSE(CanRead(), -1);
	FlushOnReadWrite(StreamDataOperation::Read);
	int c = ReadWChar();
	if (c != -1)
	{
		ungetwc((ushort)c, mFile);
	}
	return c;
}

int FileStream::ReadChar()const
{
	RETURN_OBJECT_IF_FALSE(CanRead(), -1);
	FlushOnReadWrite(StreamDataOperation::Read);
	return fgetc(mFile);
}

int FileStream::ReadWChar()const
{
	RETURN_OBJECT_IF_FALSE(CanRead(), -1);
	FlushOnReadWrite(StreamDataOperation::Read);
	ushort c = fgetwc(mFile);
	if (c == (ushort)WEOF)
	{
		return -1;
	}
	return (int)c;
}

bool FileStream::WriteChar(char val)
{
	RETURN_FALSE_IF_FALSE(CanWrite());
	FlushOnReadWrite(StreamDataOperation::Write);
	return fputc(val, mFile) != EOF;
}
bool FileStream::WriteChar(wchar val)
{
	RETURN_FALSE_IF_FALSE(CanWrite());
	FlushOnReadWrite(StreamDataOperation::Write);
	return fputwc(val, mFile) != WEOF;
}

size_t FileStream::ReadStringTo(HeapString& outString)const
{
	RETURN_ZERO_IF_FALSE(CanRead());
	FlushOnReadWrite(StreamDataOperation::Read);
	size_t count = 0;
	while (true)
	{
		int result = fgetc(mFile);
		if (result != -1)
		{
			outString.Append((char)result);
			++count;
			BREAK_IF_ZERO(result);
		}
		else
		{
			break;
		}
	}

	return count;
}

size_t FileStream::ReadStringTo(WHeapString& outString)const
{
	RETURN_ZERO_IF_FALSE(CanRead());
	FlushOnReadWrite(StreamDataOperation::Read);
	size_t count = 0;

	while (true)
	{
		int result = fgetwc(mFile);
		if (result != -1&&result!= (ushort)WEOF)
		{
			++count;
			outString.Append((wchar)result);
			BREAK_IF_ZERO(result);
		}
		else
		{
			break;
		}
	}

	return count;
}
size_t FileStream::ReadLineToString(HeapString& outString, bool includeNewLine/*=true*/)const
{
	RETURN_ZERO_IF_FALSE(CanRead());
	FlushOnReadWrite(StreamDataOperation::Read);
	const uint initialLineCount = 128;
	outString.ReserveLength(initialLineCount);
	size_t oldPos = Position();

	//first time read
	char* str = fgets(outString.c_str(), static_cast<int>(outString.Size()), mFile);
	if (str == nullptr)
	{
		outString.Clear();
		return Position() - oldPos;
	}
	outString.ForceUpdateLength();

	
	if (outString.EndWith(StdString::ConstValues<char>::Return) || outString.EndWith(StdString::ConstValues<char>::LineSeparator))
	{
		//current line is completed
	}
	else
	{
		//continue to read line
		do
		{
			outString.ReserveLength(outString.Size() + initialLineCount);
			char* p = outString.MutableBuffer() + outString.Length();
			uint size = (uint)outString.Size() - (uint)outString.Length();
			char* str2 = fgets(p, size, mFile);
			if (str2 == nullptr)
			{
				//to the file end
				break;
			}
			outString.ForceUpdateLength();
			if (outString.EndWith(StdString::ConstValues<char>::Return) || outString.EndWith(StdString::ConstValues<char>::LineSeparator))
			{
				//to line end
				break;
			}
		} while (true);
	}

	if (!includeNewLine)
	{
		outString.RemoveEndAny(StdString::ConstValues<char>::NewLineChars);
	}

	return Position() - oldPos;
}

size_t FileStream::ReadLineToString(WHeapString& outString, bool includeNewLine/*=true*/)const
{
	RETURN_ZERO_IF_FALSE(CanRead());
	FlushOnReadWrite(StreamDataOperation::Read);
	const uint initialLineCount = 128;
	outString.ReserveLength(initialLineCount);
	size_t oldPos = Position();

	wchar* str = fgetws(outString.c_str(), static_cast<int>(outString.Size()), mFile);
	if (str == nullptr)
	{
		outString.Clear();
		return false;
	}
	outString.ForceUpdateLength();

	if (outString.EndWith(StdString::ConstValues<wchar>::Return) || outString.EndWith(StdString::ConstValues<wchar>::LineSeparator))
	{
		//current line is completed
	}
	else
	{
		//continue to read line
		do
		{
			outString.ReserveLength(outString.Size() + initialLineCount);
			wchar* p = outString.MutableBuffer() + outString.Length();
			uint size = (uint)outString.Size() - (uint)outString.Length();
			wchar* str2 = fgetws(p, size, mFile);
			if (str2 == nullptr)
			{
				//to the file end
				break;
			}
			outString.ForceUpdateLength();
			if (outString.EndWith(StdString::ConstValues<wchar>::Return) || outString.EndWith(StdString::ConstValues<wchar>::LineSeparator))
			{
				//to line end
				break;
			}
		} while (true);
	}


	if (!includeNewLine)
	{
		outString.RemoveEndAny(StdString::ConstValues<wchar>::NewLineChars);
	}
	return Position() - oldPos;
}

size_t FileStream::WriteString(const StringRef& str, bool withNullTermitated /*= true*/)
{
	RETURN_ZERO_IF_FALSE(CanWrite());
	FlushOnReadWrite(StreamDataOperation::Write);
	if (fputs(str.c_str(), mFile) == EOF)
	{
		return 0;
	}

	if (withNullTermitated)
	{
		fputc('\0', mFile);	//fputs won't copy '\0'
	}
	return str.Length();
}

size_t FileStream::WriteString(const WStringRef& str, bool withNullTermitated /*= true*/)
{
	RETURN_ZERO_IF_FALSE(CanWrite());
	FlushOnReadWrite(StreamDataOperation::Write);
	if (fputws(str.c_str(), mFile) == EOF)
	{
		return 0;
	}

	if (withNullTermitated)
	{
		fputwc(L'\0', mFile);	//fputws won't copy '\0'
	}
	return str.Length();
}

bool FileStream::CanWrite() const
{
	return MEDUSA_HAS_FLAG(mSupportedOperation, StreamDataOperation::Write);
}

StreamDataOperation FileStream::Operations() const
{
	return mSupportedOperation;
}

bool FileStream::CanRead() const
{
	if (MEDUSA_HAS_FLAG(mSupportedOperation, StreamDataOperation::Read))
	{
		return !IsEnd();
	}
	return false;
}

bool FileStream::IsReadWrite() const
{
	return MEDUSA_HAS_FLAG(mSupportedOperation, StreamDataOperation::ReadWrite);
}

void FileStream::FlushOnReadWrite(StreamDataOperation curOperation)const
{
	/*
	Be sure to call fseek before you write, both to seek back to the beginning of the string you're trying to overwrite,
	and because an fseek or fflush is always required between reading and writing in the read/write "+" modes.
	http://stackoverflow.com/questions/1713819/why-fseek-or-fflush-is-always-required-between-reading-and-writing-in-the-read-w
	*/

	if (IsReadWrite() && mPrevOperation != curOperation)
	{
		fflush(mFile);
		mPrevOperation = curOperation;
	}

}

bool FileStream::Seek(intp offset, SeekOrigin direction /*= SeekOrigin::Current*/)const
{
	RETURN_FALSE_IF_FALSE(CanSeek());
	return fseek(mFile, (long)offset, (int)direction) == 0;
}

int FileStream::Printf(const char* inStringFormat, ...)
{
	RETURN_ZERO_IF_FALSE(CanWrite());
	FlushOnReadWrite(StreamDataOperation::Write);
	va_list args;
	va_start(args, inStringFormat);
	int tWriteSize = fprintf(mFile, inStringFormat, args);
	va_end(args);
	return tWriteSize;
}

int FileStream::Scanf(const char* inStringFormat, ...)
{
	RETURN_ZERO_IF_FALSE(CanRead());
	FlushOnReadWrite(StreamDataOperation::Read);
	va_list args;
	va_start(args, inStringFormat);
#ifdef MEDUSA_WINDOWS
	int tReadSize = fscanf_s(mFile, inStringFormat, args);
#else 
	int tReadSize = fscanf(mFile, inStringFormat, args);
#endif

	va_end(args);
	return tReadSize;
}

int FileStream::GetLastErrorID()const
{
	return ferror(mFile);
}

void FileStream::ClearError()const
{
	return clearerr(mFile);
}

void FileStream::Rewind()const
{
	return rewind(mFile);
}

FILE* FileStream::CreateTempFile()
{
#ifdef MEDUSA_WINDOWS
	FILE* file;
	tmpfile_s(&file);
	return file;

#else
	return tmpfile();
#endif

}

int FileStream::GetFileHandle()const
{
#ifdef MEDUSA_WINDOWS
	return _fileno(mFile);
#else
	return fileno(mFile);
#endif
}

bool FileStream::IsErrorInFile()const
{
	return ferror(mFile) == 0 ? false : true;
}


bool FileStream::GetCurrentPos(fpos_t* outPosition)const
{
	return fgetpos(mFile, outPosition) == 0 ? true : false;
}

bool FileStream::SetCurrentPos(const fpos_t* inNewPosition)
{
	RETURN_ZERO_IF_FALSE(CanSeek());
	return fsetpos(mFile, inNewPosition) == 0 ? true : false;
}

bool FileStream::SetBuffer(FileBufferMode mode, byte* buffer, size_t size) const
{
	return setvbuf(mFile, (char*)buffer, (int)mode, size) == 0 ? true : false;
}

bool FileStream::WriteBack(int inBackChar)
{
	RETURN_ZERO_IF_FALSE(CanWrite());
	FlushOnReadWrite(StreamDataOperation::Write);
	return ungetc(inBackChar, mFile) != EOF;
}

uintp FileStream::Position() const
{
	return ftell(mFile);
}

uintp FileStream::Length() const
{
#ifdef MEDUSA_WINDOWS
#ifdef MEDUSA_X64
	int filedes = _fileno(mFile);
	return _filelengthi64(filedes);
#else
	int filedes = _fileno(mFile);
	return  _filelength(filedes);
#endif

#elif defined( MEDUSA_LINUX )
	struct stat stbuf;
	fstat(mFile->_fileno, &stbuf);
	return stbuf.st_size;
#else
	struct stat stbuf;
	fstat(mFile->_file, &stbuf);
	return stbuf.st_size;
#endif

}

bool FileStream::SetLength(uintp val)
{
	RETURN_FALSE_IF_FALSE(CanWrite());

#ifdef MEDUSA_WINDOWS
	int filedes = _fileno(mFile);
	return _chsize_s(filedes, val) == 0;
#elif defined( MEDUSA_LINUX )
	//http://linux.die.net/man/2/ftruncate
#ifdef MEDUSA_X64
	ftruncate64(mFile->_fileno, val);
#else
	ftruncate(mFile->_fileno, val);
#endif
	return true;

#else
#ifdef MEDUSA_X64
	ftruncate(mFile->_file, val);
#else
	ftruncate(mFile->_file, val);
#endif

	return true;

#endif
}





MEDUSA_END;
