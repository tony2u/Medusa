// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/IO/FileDefines.h"
#include "Core/String/StackString.h"
#include "Core/String/StringRef.h"
#include "Core/Pattern/StaticConstructor.h"
#include "Core/Collection/Dictionary.h"
#include "Core/Collection/Array.h"

MEDUSA_BEGIN;

class FileInfo
{
	//MEDUSA_DECLARE_STATIC_CONSTRUCTOR();
public:
	FileInfo(StringRef filePath);
	~FileInfo(void);
public:
	FileType Type() const { return mFileType; }
	StringRef Extension() const { return mFileExtension; }
	StringRef FullPath() const { return mFullPath; }
	StringRef FullName() const { return mFullName; }
	StringRef Name() const { return mName; }

	StringRef Directory() const { return mDirectoryPath; }

	bool IsFile() const { return mDirectoryPath.IsEmpty(); }
	bool IsImageFile()const;
	bool IsShaderFile()const;
	bool IsScriptFile()const;

	static FileType ExtractType(StringRef filePath);
	bool operator<(const FileInfo& info)const{return mFullPath<info.mFullPath;}
	static bool IsImageFile(FileType fileType);
	static bool IsScriptFile(FileType fileType);
	static bool IsShaderFile(FileType fileType);

	
private:
	static FileType CheckFileType(StringRef fileExt);
	static void OnInitFileExtDict();
	
public:
	static Array<StringRef,(uint)FileType::Count> Extensions;
private:
	static Dictionary<StringRef,FileType> mFileExtDict;
	StackString<16> mFileExtension;
	HeapString mFullPath;
	HeapString mFullName;
	HeapString mName;


	HeapString mDirectoryPath;

	FileType mFileType;
};


MEDUSA_END;