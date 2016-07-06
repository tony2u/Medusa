// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#ifdef MEDUSA_ANDROID

#include "Core/System/System.h"
#include "Core/IO/Directory.h"
#include "Core/String/StringParser.h"
#include "Core/IO/File.h"
#include "Core/IO/Path.h"
#include "Core/Log/Log.h"

MEDUSA_BEGIN;

System::System( void )
{
	UpdatePaths();
}


void System::UpdatePaths()
{
	mReadonlyPath="assets";

	mTempPath=mWritablePath;
	mReadonlyPath=Path::CombineNoChecks(mReadonlyPath,mReadonlySubPath);
	mWritablePath=Path::CombineNoChecks(mWritablePath,mWritableSubPath);
	mTempPath=Path::CombineNoChecks(mTempPath,mTempSubPath);

	Log::Info(mApplicationPath);
	Log::Info(mReadonlyPath);
	Log::Info(mWritablePath);

}


WHeapString System::DefaultFontName()
{
	return WHeapString::Empty;
}

MemoryData System::GetFontData(WStringRef fontName /*= WStringRef::Empty*/)
{
	return MemoryData::Empty;
}

bool System::ContainsFont(WStringRef fontName)
{
	return false;
}

MEDUSA_END;

#endif
