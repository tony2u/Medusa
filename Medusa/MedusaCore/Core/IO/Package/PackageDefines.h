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

enum class PackageFlags
{
	None=0,
	Readonly=1, 
	EncryptFileNames=2, 
	WriteSaltData=4,
	WholeFileCoding=8
};



MEDUSA_END;