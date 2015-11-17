// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/IO/Stream/BlockReadStream.h"
#include "Core/IO/Package/Binary/BinaryPackageBlockHeader.h"


MEDUSA_BEGIN;

class BinaryBlockReadStream :public BlockReadStream
{
	typedef List<const BinaryPackageBlockHeader*> BlockHeaderList;
public:
	BinaryBlockReadStream(const IStream& stream, const BinaryPackage& package, const FileEntry& fileEntry);
	virtual ~BinaryBlockReadStream(void);
	virtual StreamType Type()const { return StreamType::BinaryBlockRead; }
	BinaryBlockReadStream(const BinaryBlockReadStream&) = delete;
	BinaryBlockReadStream& operator=(const BinaryBlockReadStream&) = delete;
	BinaryBlockReadStream(BinaryBlockReadStream&& other);
	BinaryBlockReadStream& operator=(BinaryBlockReadStream&& other);
public:
	virtual uintp Length()const;
protected:
	virtual size_t LoadBlockTo(uint blockIndex, MemoryStream& output)const;
	void LoadBlockHeaders();
protected:
	const BinaryPackage* mPackage;
	const FileEntry* mFileEntry;

	BlockHeaderList mBlockHeaders;
};


MEDUSA_END;