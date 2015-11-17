// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#ifdef MEDUSA_WINDOWS

#include "Core/System/System.h"
#include "Core/IO/Directory.h"
#include "Core/String/StringParser.h"
#include "Core/IO/File.h"
#include "Core/IO/Path.h"

MEDUSA_BEGIN;

System::System(void)
{
	UpdatePaths();
}


void System::UpdatePaths()
{
	char buffer[512];
	GetCurrentDirectoryA(sizeof(buffer), buffer);

	mApplicationPath = buffer;

	mReadonlyPath = mApplicationPath;
	mWritablePath = mApplicationPath;

	::GetTempPathA(sizeof(buffer) / sizeof(char), buffer);
	mTempPath = buffer;

	mReadonlyPath = Path::CombineNoChecks(mReadonlyPath, mReadonlySubPath);
	mWritablePath = Path::CombineNoChecks(mWritablePath, mWritableSubPath);
	mTempPath = Path::CombineNoChecks(mTempPath, mTempSubPath);


}

MEDUSA_END;
#endif
