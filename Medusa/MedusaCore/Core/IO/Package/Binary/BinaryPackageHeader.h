// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Collection/List.h"
#include "Core/IO/Package/PackageFlags.h"
#include "Core/Coder/CoderDefines.h"
#include "Core/Coder/CoderInfo.h"
#include "Core/Hash/HasherType.h"

MEDUSA_BEGIN;
//one block can only be owned by one file
struct BinaryPackageHeader
{
	~BinaryPackageHeader() {}
	BinaryPackageHeader(PackageFlags flag = PackageFlags::None);
	void Reset();
	bool ParseFrom(const IStream& stream);
	bool WriteTo(IStream& stream);

	uint32 FormatVersion() const { return mFormatVersion; }
	void SetFormatVersion(uint32 val) { mFormatVersion = val; }

	uint32 ContentVersion() const { return mContentVersion; }
	void SetContentVersion(uint32 val) { mContentVersion = val; }

	uint32 BlockSize() const { return mBlockSize; }
	void SetBlockSize(uint32 val) { mBlockSize = val; }

	uint32 BlockCount() const { return mBlockCount; }
	void SetBlockCount(uint32 val) { mBlockCount = val; }

	PackageFlags Flag() const { return mFlag; }
	void SetFlag(PackageFlags val) { mFlag = val; }

	uint32 FirstFreeBlockId() const { return mFirstFreeBlockId; }
	void SetFirstFreeBlockId(uint32 val) { mFirstFreeBlockId = val; }
	uint32 FreeBlockCount() const { return mFreeBlockCount; }
	void SetFreeBlockCount(uint32 val) { mFreeBlockCount = val; }

	uint64 Coders() const { return mCoders; }
	void SetCoders(uint64 val) { mCoders = val; }

	HasherType Hasher() const { return mHasher; }
	void SetHasher(HasherType val) { mHasher = val; }

	void SetKey(const MemoryByteData& val);
	bool ValidateKey(const MemoryByteData& key)const;
public:
	uint32 FirstBlockOffset()const;
	uint32 GetBlockOffset(uint blockId)const;
	uint32 BlockHeadersOffset() const;
	float SpaceUsage()const;
private:
	uint32 mSignature;
	uint32 mFormatVersion;	//format version

	uint32 mHeaderSize;	//from signature to end
	uint32 mContentVersion;
	PackageFlags mFlag;	//flags to control read

	uint32 mBlockSize;
	uint32 mBlockCount;	//total block count

	uint32 mFirstFreeBlockId;	//a link list to store free blocks
	uint32 mFreeBlockCount;

	HasherType mHasher;
	uint64 mCoders;
	byte mKeyHash[16];

public:
	constexpr static uint32 FixedSignature = 1262571597;	// 'KAPM';	//Little endian, I mean 'MPAK'
	constexpr static uint32 CurrentVersion = 1;
	constexpr static uint32 FixedHeaderSize = 64;


};


MEDUSA_END;