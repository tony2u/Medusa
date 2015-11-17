// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "Core/IO/FileDefines.h"
#include "Core/String/StringRef.h"
#include "Core/String/HeapString.h"
#include "Core/Collection/List.h"



MEDUSA_BEGIN;

class Directory
{
public:
	Directory(void) = delete;
	~Directory(void) = delete;

	static bool CreateDir(const StringRef& dir);
	static bool CreateDirRecursively(const StringRef& dir);

	static bool RemoveDir(const StringRef& dir);
	static bool RemoveDirRecursively(const StringRef& dir);


	static bool CreateDirectoryForFile(const StringRef& filePath);
	static bool Exists(const StringRef& dir);

	static void Copy(const StringRef& fromDir, const StringRef& toDir, bool isRecursively = true);
	static void Move(const StringRef& fromDir, const StringRef& toDir, bool isRecursively = true);
	static bool Rename(StringRef oldName, StringRef newName);


	static void GetFiles(const StringRef& dir, List<HeapString>& outFiles, bool isRecursively = false, const StringRef& searchPattern = StringRef::Empty);
	static void GetDirectories(const StringRef& dir, List<HeapString>& outDirectories, bool isRecursively = true, const StringRef& searchPattern = StringRef::Empty);

	static void SearchFiles(const StringRef& searchPath, List<HeapString>& outFiles, bool recursively = true);
	static void SearchDirectories(const StringRef& searchPath, List<HeapString>& outDirectories, bool recursively = true);


private:
	static bool IsFitSearchPattern(const StringRef& fileName, const StringRef& searchPattern);
};

MEDUSA_END;