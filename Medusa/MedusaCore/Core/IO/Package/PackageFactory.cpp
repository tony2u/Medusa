// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "PackageFactory.h"
#include "Core/IO/Package/DirectoryPackage.h"
#include "Core/IO/Package/MemoryPackage.h"
#include "Core/IO/Package/Binary/BinaryPackage.h"
#include "Core/IO/Package/ZipPackage.h"
#include "Core/IO/FileInfo.h"

MEDUSA_BEGIN;

bool PackageFactory::IsPackage(const StringRef& filePath)
{
	return IsPackage(FileInfo::ExtractType(filePath));
}

bool PackageFactory::IsPackage(FileType fileType)
{
	switch (fileType)
	{
	case FileType::zip:
	case FileType::mpk:
		return true;
	default:
		return false;
	}
}

IPackage* PackageFactory::Create(FileType fileType, const StringRef& path, PackagePriority priority /*= PackagePriority::Downloaded*/, uint version /*= 0*/)
{
	switch (fileType)
	{
	case FileType::zip:
		//return new ZipPackage(path, priority, version);
	case FileType::mpk:
		return new BinaryPackage(path, priority, version);
	default:
		return nullptr;
	}
}

IPackage* PackageFactory::Create(PackageType packageType, const StringRef& path, PackagePriority priority /*= PackagePriority::Downloaded*/, uint version /*= 0*/)
{
	IPackage* resultPackage = nullptr;
	switch (packageType)
	{
	case PackageType::Directory:
		resultPackage = new DirectoryPackage(path, priority, version);
		break;
	case PackageType::Memory:
		resultPackage = new MemoryPackage(path, priority, version);
		break;
	case PackageType::MPAK:
		resultPackage = new BinaryPackage(path, priority, version);
		break;
	case PackageType::Zip:
		//resultPackage = new DirectoryPackage(path, priority, version);
		break;
	default:
		break;
	}
	return resultPackage;
}



MEDUSA_END;

