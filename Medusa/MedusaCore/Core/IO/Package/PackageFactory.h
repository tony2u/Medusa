// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "IPackage.h"
#include "PackageDefines.h"
#include "Core/Pattern/Singleton.h"

MEDUSA_BEGIN;

class PackageFactory :public Singleton<PackageFactory>
{
	friend class Singleton<PackageFactory>;
	PackageFactory() {}
	~PackageFactory(){}
public:
	static bool IsPackage(const StringRef& filePath);
	static bool IsPackage(FileType fileType);
	static IPackage* Create(FileType fileType, const StringRef& path, PackagePriority priority = PackagePriority::Downloaded, uint version = 0);
	static IPackage* Create(PackageType packageType, const StringRef& path, PackagePriority priority = PackagePriority::Downloaded, uint version = 0);

};

MEDUSA_END;
