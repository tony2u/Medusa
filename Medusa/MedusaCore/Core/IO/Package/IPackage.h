// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/IO/FileDefines.h"
#include "Core/System/PublishTarget.h"
#include "PackageDefines.h"
#include "PackageFlags.h"
#include "Core/Pattern/IInitializable.h"
#include "Core/Coder/CoderDefines.h"
#include "Core/Coder/CoderChain.h"
#include "Core/IO/Storage/FileStorage.h"

MEDUSA_BEGIN;

class IPackage :public FileStorage
{
public:
	IPackage(const StringRef& path, PackagePriority priority = PackagePriority::Downloaded, uint version = 0);
	IPackage() {}
	virtual ~IPackage();
	int Compare(const IPackage& other)const;
	bool operator<(const IPackage& other)const;


	StringRef Path() const { return mPath; }
	void SetPath(StringRef val) { mPath = val; }

	PackagePriority Priority() const { return mPriority; }
	void SetPriority(PackagePriority val) { mPriority = val; }

	uint Version() const { return mVersion; }
	void SetVersion(uint val) { mVersion = val; }

	virtual PackageFlags Flags() const = 0;
	virtual void SetFlags(PackageFlags val) = 0;

	virtual PackageType Type()const = 0;
public:
	virtual bool IsReadOnly()const override { return Flags().IsReadonly(); }
	void SetReadonly(bool val);
	bool IsEncryptFileNames()const { return Flags().IsEncryptFileNames(); }
	void EnableEncryptFileNames(bool val);
	bool IsWriteSaltData()const { return Flags().IsWriteSaltData(); }
	void EnableWriteSaltData(bool val);
	virtual bool IsWholeFileCoding()const override { return Flags().IsWholeFileCoding(); }
	void EnableWholeFileCoding(bool val);


public:
	virtual bool Flush() { return true; }
	virtual bool Compact() { return true; }
	virtual float SpaceUsage()const { return 1.f; }

	bool Merge(const IPackage& other);
	IPackage* CreateDiff(const IPackage& other, const StringRef& diffPath);
	bool IsDataCompatiable(const IPackage& other)const;
	FileSystem* Parent() const { return mParent; }
	void SetParent(FileSystem* val) { mParent = val; }
protected:
	virtual void OnFileAdded(FileEntry& file)override;
	virtual void OnFileRemoved(FileEntry& file)override;
	virtual bool OnCopyFile(const FileEntry& from, FileEntry& to);

protected:
	HeapString mPath;	//package file path
	PackagePriority mPriority;
	uint mVersion;
	FileSystem* mParent = nullptr;

};


MEDUSA_END;
