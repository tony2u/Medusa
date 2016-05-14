// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "FileInfo.h"
#include "Core/IO/Path.h"
#include "FileDefines.h"

MEDUSA_BEGIN;


FileType FileInfo::ExtractType(StringRef filePath)
{
	StringRef ext = Path::GetExtension(filePath);
	return CheckFileType(ext);
}


FileInfo::FileInfo(StringRef filePath) :mFullPath(filePath)
{
	MEDUSA_ASSERT_NOT_EMPTY(mFullPath, "");

	intp index = mFullPath.LastIndexOf('.');
	if (index > 0)
	{
		size_t length = (size_t)(mFullPath.Length() - index);
		filePath.CopyTo(mFileExtension.MutableBuffer(), mFileExtension.Size(), (size_t)(index), length);
		mFileExtension.ForceSetLength(length);
		mFileType = CheckFileType(mFileExtension);


		intp index2 = filePath.LastIndexOfAny(Path::DirectorySeparatorChars);
		if (index2 > 0)
		{
			mFullName = mFullPath.SubString(index2 + 1);
			mName = mFullPath.SubString(index2 + 1, index - index2 - 1);
			mDirectoryPath = mFullPath.SubString(0, index2);
		}
		else
		{
			mFullName = mFullPath;
			mName = mFullPath;
		}
	}
	else
	{
		mFileType = FileType::None;
		mDirectoryPath = mFullPath;

		intp index2 = filePath.LastIndexOfAny(Path::DirectorySeparatorChars);
		if (index2 > 0)
		{
			mFullName = mFullPath.SubString(index2 + 1);
			mName = mFullName;
		}
		else
		{
			mFullName = mFullPath;
			mName = mFullPath;
		}
	}
}


FileInfo::~FileInfo(void)
{
}

FileType FileInfo::CheckFileType(StringRef fileExt)
{
	const static StaticConstructor mStaticConstructor(OnInitFileExtDict);

	if (fileExt.IsEmpty())
	{
		return FileType::None;
	}

	FileType* fileType = mFileExtDict.TryGet(fileExt);
	if (fileType != nullptr)
	{
		return *fileType;
	}

	//find lower
	StackString<32> upperExt = fileExt;
	upperExt.ToLower();
	fileType = mFileExtDict.TryGet(upperExt);
	if (fileType != nullptr)
	{
		return *fileType;
	}

	return FileType::None;
}


bool FileInfo::IsImageFile()const
{
	return IsImageFile(mFileType);
}

bool FileInfo::IsScriptFile()const
{
	return IsScriptFile(mFileType);
}

bool FileInfo::IsImageFile(FileType fileType)
{
	switch (fileType)
	{
	case FileType::jpeg:
	case FileType::png:
	case FileType::pvr:
	case FileType::gif:
		return true;
	default:
		return false;

	}
}
bool FileInfo::IsScriptFile(FileType fileType)
{
	switch (fileType)
	{
	case FileType::lua:
		return true;
	default:
		return false;

	}
}

bool FileInfo::IsShaderFile(FileType fileType)
{
	switch (fileType)
	{
	case FileType::fsh:
	case FileType::vsh:
		return true;
	default:
		return false;

	}
}


bool FileInfo::IsShaderFile()const
{
	return IsShaderFile(mFileType);
}


StringRef FileInfo::FileTypeToString(FileType fileType)
{
	return Extensions[(uint)fileType];
}

void FileInfo::OnInitFileExtDict()
{
	Extensions.SetAll(nullptr);
	Extensions[(uint)FileType::png] = FileExtensions::png;
	Extensions[(uint)FileType::jpeg] = FileExtensions::jpeg;
	Extensions[(uint)FileType::gif] = FileExtensions::gif;
	Extensions[(uint)FileType::pvr] = FileExtensions::pvr;

	Extensions[(uint)FileType::pcm] = FileExtensions::pcm;
	Extensions[(uint)FileType::wav] = FileExtensions::wav;
	Extensions[(uint)FileType::ogg] = FileExtensions::ogg;

	Extensions[(uint)FileType::fsh] = FileExtensions::fsh;
	Extensions[(uint)FileType::vsh] = FileExtensions::vsh;
	Extensions[(uint)FileType::pod] = FileExtensions::pod;
	Extensions[(uint)FileType::pfx] = FileExtensions::pfx;
	Extensions[(uint)FileType::ttf] = FileExtensions::ttf;
	Extensions[(uint)FileType::fnt] = FileExtensions::fnt;
	Extensions[(uint)FileType::json] = FileExtensions::json;
	Extensions[(uint)FileType::xml] = FileExtensions::xml;
	Extensions[(uint)FileType::bin] = FileExtensions::bin;
	Extensions[(uint)FileType::atlas] = FileExtensions::atlas;
	Extensions[(uint)FileType::zip] = FileExtensions::zip;
	Extensions[(uint)FileType::tmx] = FileExtensions::tmx;
	Extensions[(uint)FileType::xaml] = FileExtensions::xaml;
	Extensions[(uint)FileType::plist] = FileExtensions::plist;
	Extensions[(uint)FileType::bplist] = FileExtensions::bplist;
	Extensions[(uint)FileType::matlas] = FileExtensions::matlas;
	Extensions[(uint)FileType::mpk] = FileExtensions::mpk;
	Extensions[(uint)FileType::mp] = FileExtensions::mp;
	Extensions[(uint)FileType::mpb] = FileExtensions::mpb;
	Extensions[(uint)FileType::csb] = FileExtensions::csb;
	Extensions[(uint)FileType::lua] = FileExtensions::lua;

	FOR_EACH_SIZE(i, Extensions.Size)
	{
		StringRef ext = Extensions[i];
		if (ext != nullptr)
		{
			FileType type = (FileType)i;
			mFileExtDict.Add(ext, type);
		}
	}

	//alias
	mFileExtDict.Add(FileExtensions::jpg, FileType::jpeg);

}

Array<StringRef, (uint)FileType::Count> FileInfo::Extensions;

Dictionary<StringRef, FileType> FileInfo::mFileExtDict;

//MEDUSA_IMPLEMENT_STATIC_CONSTRUCTOR(FileInfo, OnInitFileExtDict);

MEDUSA_END;