// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
//
#include <stdio.h>
#include <tchar.h>
#include <SDKDDKVer.h>

#include "Case/MatrixTest.h"
#include "Case/CollectionTest.h"
#include "Case/OtherTest.h"
#include "Case/FormatTest.h"
#include "Case/CodeTest.h"

#include "Core/Siren/Siren.h"



int _tmain(int argc, _TCHAR* argv[])
{
	Log::Initialize();
	FileSystem::Instance().Initialize();

	system("PAUSE");

	FileSystem::Instance().Uninitialize();
	Log::Uninitialize();

	return 0;

}