// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"

MEDUSA_BEGIN;

enum class PackageType
{
	Directory,	//treat a directory as a package
	Memory,	//register memory data as file data in package
	MPAK,	//medusa custom package file format
	Zip	//treat a zip file as a package
};

enum class PackagePriority
{
	Memory = 0,	//register in app memory
	App = 1,	//default in app package,in read only path
	Downloaded = 2,	//download from outside, in writable path
};




MEDUSA_END;