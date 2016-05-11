// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "File.h"
#include "Core/Log/Log.h"
#include "Core/IO/Stream/FileStream.h"


MEDUSA_BEGIN;

bool File::Exists(StringRef filePath, int permission)
{
	/*
		mode Value						Checks File For
		00                              Existence only
		02                              Write permission
		04                              Read permission
		06                              Read and write permission

		*/

	FileMode outFileMode;
	if (GetFileMode(filePath, outFileMode))
	{
		if (outFileMode == FileMode::File)
		{
			return true;
		}
	}

	return false;

	//#ifdef MEDUSA_WINDOWS
	//	return _access(filePath.Buffer(),permission)!=-1;
	//#else 
	//	return access(filePath.Buffer(),permission)!=-1;
	//
	//#endif

}


bool File::Delete(StringRef filePath)
{
	return remove(filePath.c_str()) == 0;
}

bool File::GetFileMode(StringRef filePath, FileMode& outFileMode)
{
	struct stat buf;
	const char* path = filePath.c_str();
	int result = stat(path, &buf);
	if (result == 0)
	{
		if (buf.st_mode&S_IFDIR)
		{
			outFileMode = FileMode::Directory;
		}
		else
		{
			outFileMode = FileMode::File;
		}

		return true;
	}
	else
	{
		if (errno == ENOENT)
		{
			//file not exists
			return false;
		}
		else
		{
			return false;
		}
	}
}

bool File::Copy(StringRef srcFilePath, StringRef destFilePath)
{
	FileStream srcFile;
	FileStream destFile;
	byte buffer[1024];
	MemoryData data = MemoryData::FromStatic(buffer);
	if (srcFile.OpenReadBinary(srcFilePath) && destFile.OpenNewWriteBinary(destFilePath))
	{
		while (true)
		{
			size_t readCount = srcFile.ReadDataTo(data);
			if (readCount == 0)
			{
				return true;
			}
			data.ForceSetSize(readCount);
			destFile.WriteData(data);
		}

	}

	return false;
}

bool File::Move(StringRef srcFilePath, StringRef destFilePath)
{
	if (File::Copy(srcFilePath, destFilePath))
	{
		return File::Delete(srcFilePath);
	}
	return false;
}

bool File::Rename(StringRef oldName, StringRef newName)
{
	return rename(oldName.c_str(), newName.c_str()) == 0;
}


bool File::ReadAllTextTo(StringRef filePath, HeapString& outString)
{
	FileStream reader(filePath, FileOpenMode::ReadOnly, FileDataType::Text);
	if (reader.IsOpen())
	{
		outString.ReserveLength(reader.Length());
		reader.ReadStringTo(outString);
		return true;
	}
	return false;

}


bool File::ReadAllTextTo(StringRef filePath, WHeapString& outString)
{
	FileStream reader(filePath, FileOpenMode::ReadOnly, FileDataType::Text);
	if (reader.IsOpen())
	{
		outString.ReserveLength(reader.Length());
		reader.ReadStringTo(outString);
		return true;
	}
	return false;

}

HeapString File::ReadAllText(StringRef filePath)
{
	HeapString text;
	ReadAllTextTo(filePath, text);
	return text;
}


bool File::WriteAllText(StringRef filePath, StringRef str)
{
	FileStream writer(filePath, FileOpenMode::DestoryWriteOrCreate, FileDataType::Text);
	if (writer.IsOpen())
	{
		return writer.WriteString(str,false) == str.Length();
	}
	return false;
}

bool File::WriteAllText(StringRef filePath, WStringRef str)
{
	FileStream writer(filePath, FileOpenMode::DestoryWriteOrCreate, FileDataType::Text);
	if (writer.IsOpen())
	{
		return writer.WriteString(str,false) == str.Length();
	}
	return false;
}

bool File::ReadAllLines(StringRef filePath, List<HeapString>& outLines, size_t maxCount/*=1024*/, bool isTrim/*=true*/, bool ignoreEmptyLine/*=true*/)
{
	FileStream reader(filePath, FileOpenMode::ReadOnly, FileDataType::Text);
	if (reader.IsOpen())
	{
		reader.ReadAllLinesTo(outLines, maxCount, isTrim, ignoreEmptyLine);
		return true;
	}

	return false;
}

MemoryData File::ReadAllData(StringRef filePath)
{
	FileStream stream;
	if (stream.OpenReadBinary(filePath))
	{
		return stream.ReadToEnd();
	}

	return MemoryData::Empty;
}

MemoryData File::ReadAllDataPriority(StringRef firstPath, StringRef secondPath)
{
	//try to read data from first path
	if (File::Exists(firstPath))
	{
		return File::ReadAllData(firstPath);
	}
	else
	{
		//try to read data from second path
		if (File::Exists(secondPath))
		{
			return File::ReadAllData(secondPath);
		}
		else
		{
			return MemoryData::Empty;
		}
	}
}

std::unique_ptr<FileStream> File::OpenTextReader(StringRef filePath)
{
	std::unique_ptr<FileStream> fs(new FileStream());
	if (!fs->OpenReadText(filePath))
	{
		return nullptr;
	}
	return fs;
}

std::unique_ptr<FileStream> File::OpenBinaryReader(StringRef filePath)
{
	std::unique_ptr<FileStream> fs(new FileStream());
	if (!fs->OpenReadBinary(filePath))
	{
		return nullptr;
	}
	return fs;
}

bool File::WriteAllData( StringRef filePath, MemoryData data)
{
	FileStream stream;
	if (stream.OpenNewWriteBinary(filePath))
	{
		return stream.WriteData(data) > 0;
	}

	return false;
}

MEDUSA_END;

