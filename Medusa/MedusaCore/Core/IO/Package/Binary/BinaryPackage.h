// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/IO/Package/IPackage.h"
#include "Core/IO/Stream/FileStream.h"
#include "BinaryPackageHeader.h"
#include "BinaryPackageBlockHeader.h"


MEDUSA_BEGIN;

/*
custom package format: mpack
Features:
Md5/CRC32C/sha1 check
Tree directory structure
Independent file coding
Diff and merge
Not interrupted before flush
Compact and defrag
encrypt file names


package format:
(Header)
[(BlockHeader)(BlockData)]+

*/

class BinaryPackage :public IPackage
{
	friend class BinaryBlockReadStream;
	friend class BinaryBlockWriteStream;

public:
	BinaryPackage(const StringRef& path, PackagePriority priority = PackagePriority::Downloaded, uint version = 0);
	BinaryPackage(Random& random,const StringRef& path, PackagePriority priority = PackagePriority::Downloaded, uint version = 0);


	virtual ~BinaryPackage(void);

	virtual PackageType Type()const override{ return PackageType::MPAK; }

	virtual bool Initialize() override;
	virtual bool Uninitialize() override;

	virtual bool Flush()override;
	virtual bool Compact() override;

	virtual float SpaceUsage()const override;
	float CalculateSpaceUsageExactly(uint& outFreeSpace)const;
	bool Save()override;
	const BinaryPackageHeader& Header() const { return mHeader; }
public:
	virtual uint BlockSize()const override{ return mHeader.BlockSize(); }
	virtual void SetBlockSize(uint val) override{ mHeader.SetBlockSize(val); }
	virtual uint64 Coders() const override{ return mHeader.Coders(); }
	virtual void SetCoders(uint64 val) override{ mHeader.SetCoders(val); FileStorage::SetCoders(val); }
	virtual HasherType Hasher() const override{ return mHeader.Hasher(); }
	virtual void SetHasher(HasherType val) override{ mHeader.SetHasher(val); }
	virtual PackageFlags Flags() const override{ return mHeader.Flag(); }
	virtual void SetFlags(PackageFlags val) override{ mHeader.SetFlag(val); }

	virtual void SetKey(const MemoryData& val)override;
	virtual bool ValidateKey(const MemoryData& val)const override;
	
protected:
	virtual bool OnCreateDirectory(const StringRef& dir)override;
	virtual bool OnRemoveDirectory(DirectoryEntry& dir)override;
	virtual const IStream* OnReadFile(const FileEntry& file, FileDataType dataType = FileDataType::Binary)const override;
	virtual IStream* OnWriteFile(FileEntry& file, FileOpenMode openMode = FileOpenMode::ReadOnly, FileDataType dataType = FileDataType::Binary) override;
	virtual bool OnRemoveFile(FileEntry& file) override;
	virtual bool OnCopyFile(const FileEntry& from, FileEntry& to)override;
protected:
	virtual bool OnLoaded()override;

	BinaryPackageBlockHeader* AllocFreeBlock();
	void RecycleBlock(BinaryPackageBlockHeader* block);
	void RecycleBlockFrom(uint id);

	void MoveCopyBlock(BinaryPackageBlockHeader& from, BinaryPackageBlockHeader& to, const Dictionary<uint, FileEntry*>& fileEnties);
	const BinaryPackageBlockHeader* ReadBlockTo(uint id, MemoryStream& destStream)const;
	bool WriteBlockTo(uint id,MemoryStream& srcStream);
	BinaryPackageBlockHeader* WriteBlock(BinaryPackageBlockHeader* prevBlock, MemoryStream& srcStream);

	bool LoadBlockHeaders();
	bool SaveBlockHeaders();

	bool LoadFileStorage();
	bool SaveFileStorage();

protected:
	BinaryPackageHeader mHeader;
	mutable FileStream mStream;

	List<BinaryPackageBlockHeader*> mBlockHeaders;
	Random& mRandom;
};

MEDUSA_END;
