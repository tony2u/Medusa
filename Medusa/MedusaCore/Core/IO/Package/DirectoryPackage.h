// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "IPackage.h"
MEDUSA_BEGIN;


class DirectoryPackage :public IPackage
{
public:
	DirectoryPackage(const StringRef& path, PackagePriority priority = PackagePriority::Downloaded, uint version = 0, bool isRecursively = true, const StringRef& searchPattern = StringRef::Empty);
	
	virtual ~DirectoryPackage(void);

	virtual PackageType Type()const override{ return PackageType::Directory; }

	virtual bool Initialize() override;
	virtual bool Uninitialize() override;

public:
	virtual uint BlockSize()const override{ return mBlockSize; }
	virtual void SetBlockSize(uint val) override{ mBlockSize=val; }
	virtual uint64 Coders() const override{ return mCoderChain.Coders(); }
	virtual HasherType Hasher() const override{ return mHasher; }
	virtual void SetHasher(HasherType val) override{ mHasher=val; }

	virtual PackageFlags Flags() const override{ return mFlags; }
	virtual void SetFlags(PackageFlags val) override{ mFlags = val; }
protected:
	virtual bool OnCreateDirectory(const StringRef& dir)override;
	virtual bool OnRemoveDirectory(DirectoryEntry& dir)override;
	virtual const IStream* OnReadFile(const FileEntry& file, FileDataType dataType = FileDataType::Binary)const override;
	virtual IStream* OnWriteFile(FileEntry& file, FileOpenMode openMode = FileOpenMode::ReadOnly, FileDataType dataType = FileDataType::Binary) override;
	virtual bool OnRemoveFile(FileEntry& file) override;

protected:
	PackageFlags mFlags;

	bool mIsRecursively;
	HeapString mSearchPattern;

	uint mBlockSize;
	HasherType mHasher = HasherType::None;
};

MEDUSA_END;
