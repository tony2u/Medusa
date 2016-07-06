// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/String/StringRef.h"
#include "Core/Pattern/Delegate.h"
#include "Core/Pattern/Singleton.h"
#include "Core/String/HeapString.h"
#include "Core/IO/Directory.h"
#include "Core/IO/Path.h"

MEDUSA_BEGIN;


class System :public Singleton<System>
{
	friend class Singleton<System>;
	System(void);
	~System(void) {}
public:

#ifdef MEDUSA_ANDROID
	void SetApkPath(StringRef apkPath, StringRef apkWritePath) { mApplicationPath = apkPath; mWritablePath = apkWritePath; }
#endif
	StringRef WorkingPath()const { return mWorkingPath; }
	void SetWorkingPath(StringRef val) { mWorkingPath = val; }


	StringRef ApplicationPath()const { return mApplicationPath; }
	StringRef ReadonlyPath()const { return mReadonlyPath; }
	StringRef WritablePath()const { return mWritablePath; }
	StringRef TempPath()const { return mTempPath; }

	void Initialize(StringRef readonlySubPath = StringRef::Empty, StringRef writableSubPath = StringRef::Empty, StringRef tempSubPath = StringRef::Empty)
	{
		mReadonlySubPath = readonlySubPath;
		mWritableSubPath = writableSubPath;
		mTempSubPath = tempSubPath;

		UpdatePaths();
		MakeAllPathExists();
	}

	StringRef ReadonlySubPath() const { return mReadonlySubPath; }
	void SetReadonlySubPath(StringRef val) { mReadonlySubPath = val; UpdatePaths(); }

	StringRef WritableSubPath() const { return mWritableSubPath; }
	void SetWritableSubPath(StringRef val) { mWritableSubPath = val; UpdatePaths(); MakeAllPathExists(); }

	StringRef TempSubPath() const { return mTempSubPath; }
	void SetTempSubPath(StringRef val) { mTempSubPath = val; UpdatePaths(); MakeAllPathExists(); }

	void MakeAllPathExists()
	{
		Directory::CreateDir(WritablePath());
		Directory::CreateDir(TempPath());
	}

	HeapString GetReadonlyPath(StringRef fileName) const { return Path::CombineNoChecks(ReadonlyPath(), fileName); }
	HeapString GetWritablePath(StringRef fileName) const { return Path::CombineNoChecks(WritablePath(), fileName); }
	HeapString GetTempPath(StringRef fileName) const { return Path::CombineNoChecks(TempPath(), fileName); }

	static WHeapString DefaultFontName();
	static bool ContainsFont(WStringRef fontName);
	static MemoryData GetFontData(WStringRef fontName = WStringRef::Empty);

	StringRef CurrentFontName() const { return mCurrentFontName; }
	void SetCurrentFontName(StringRef val) { mCurrentFontName = val; }
private:
	void UpdatePaths();
private:
	HeapString mWorkingPath;

	HeapString mApplicationPath;
	HeapString mReadonlyPath;
	HeapString mWritablePath;
	HeapString mTempPath;

	HeapString mReadonlySubPath;
	HeapString mWritableSubPath;
	HeapString mTempSubPath;

	HeapString mCurrentFontName;
};

MEDUSA_END;
