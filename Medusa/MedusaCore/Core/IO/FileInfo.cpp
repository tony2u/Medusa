// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "FileInfo.h"
#include "Core/IO/Path.h"

MEDUSA_BEGIN;

StringRef FileInfo::ExtractExtension(StringRef file)
{
	intp index= file.LastIndexOf('.');
	if (index>0)
	{
		return file.SubString(index);
	}
	return StringRef::Empty;
}


FileType FileInfo::ExtractType(StringRef filePath)
{
	StringRef ext=ExtractExtension(filePath);
	return CheckFileType(ext);
}


FileInfo::FileInfo(StringRef filePath):mFullPath(filePath)
{
	MEDUSA_ASSERT_NOT_EMPTY(mFullPath,"");

	intp index=mFullPath.LastIndexOf('.');
	if (index>0)
	{
		size_t length=(size_t)(mFullPath.Length()-index);
		filePath.CopyTo(mFileExtension.MutableBuffer(),mFileExtension.Size(),(size_t)(index),length);
		mFileExtension.ForceSetLength(length);
		mFileType=CheckFileType(mFileExtension);


		intp index2= filePath.LastIndexOfAny(Path::DirectorySeparatorChars);
		if (index2>0)
		{
			mFullName= mFullPath.SubString(index2+1);
			mName=mFullPath.SubString(index2+1,index-index2-1);
			mDirectoryPath=mFullPath.SubString(0,index2);
		}
		else
		{
			mFullName=mFullPath;
			mName=mFullPath;
		}
	}
	else
	{
		mFileType = FileType::Unknown;
		mDirectoryPath=mFullPath;

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

FileType FileInfo::CheckFileType( StringRef fileExt )
{
	if (fileExt.IsEmpty())
	{
		return FileType::Unknown;
	}

	fileExt=fileExt.SubString(1);	//remove '.' at head

	FileType* fileType= mFileExtDict.TryGetValue(fileExt);
	if (fileType!=nullptr)
	{
		return *fileType;
	}

	return FileType::Unknown;
}


bool FileInfo::IsImageFile()const
{
	return IsImageFile(mFileType);
}

bool FileInfo::IsImageFile(FileType fileType)
{
	switch(fileType)
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


bool FileInfo::IsShaderFile()const
{
	switch(mFileType)
	{
	case FileType::fsh:
	case FileType::vsh:
		return true;
	default:
		return false;
	}
}

void FileInfo::OnInitFileExtDict()
{
	mFileExtDict.Add("png",FileType::png);
	mFileExtDict.Add("jpeg",FileType::jpeg);
	mFileExtDict.Add("gif",FileType::gif);
	mFileExtDict.Add("pvr",FileType::pvr);

	mFileExtDict.Add("pcm", FileType::pcm);
	mFileExtDict.Add("wav", FileType::wav);
	mFileExtDict.Add("ogg", FileType::ogg);

	mFileExtDict.Add("fsh",FileType::fsh);
	mFileExtDict.Add("vsh",FileType::vsh);
	mFileExtDict.Add("pod",FileType::pod);
	mFileExtDict.Add("pfx",FileType::pfx);
	mFileExtDict.Add("ttf",FileType::ttf);
	mFileExtDict.Add("fnt",FileType::fnt);
	mFileExtDict.Add("json", FileType::json);
	mFileExtDict.Add("xml", FileType::xml);
	mFileExtDict.Add("bin", FileType::bin);
	mFileExtDict.Add("atlas", FileType::atlas);
	mFileExtDict.Add("mpf", FileType::mpf);


	mFileExtDict.Add("zip", FileType::zip);
	mFileExtDict.Add("mpk", FileType::mpk);

	//others
	mFileExtDict.Add("jpg",FileType::jpeg);

	//Uppercase
	mFileExtDict.Add("PNG", FileType::png);
	mFileExtDict.Add("JPEG", FileType::jpeg);
	mFileExtDict.Add("GIF", FileType::gif);
	mFileExtDict.Add("PVR", FileType::pvr);

	mFileExtDict.Add("PCM", FileType::pcm);
	mFileExtDict.Add("WAV", FileType::wav);
	mFileExtDict.Add("OGG", FileType::ogg);

	mFileExtDict.Add("FSH", FileType::fsh);
	mFileExtDict.Add("VSH", FileType::vsh);
	mFileExtDict.Add("POD", FileType::pod);
	mFileExtDict.Add("PFX", FileType::pfx);
	mFileExtDict.Add("TTF", FileType::ttf);
	mFileExtDict.Add("FNT", FileType::fnt);
	mFileExtDict.Add("JSON", FileType::json);
	mFileExtDict.Add("XML", FileType::xml);
	mFileExtDict.Add("BIN", FileType::bin);
	mFileExtDict.Add("ATLAS", FileType::atlas);
	mFileExtDict.Add("MPF", FileType::mpf);

	mFileExtDict.Add("ZIP", FileType::zip);
	mFileExtDict.Add("MPK", FileType::mpk);

	//others
	mFileExtDict.Add("JPG", FileType::jpeg);

}

Dictionary<StringRef,FileType> FileInfo::mFileExtDict;

MEDUSA_IMPLEMENT_STATIC_CONSTRUCTOR(FileInfo,OnInitFileExtDict);

MEDUSA_END;