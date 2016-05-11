// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/IO/Stream/BlockWriteStream.h"
#include "Core/IO/Package/Binary/BinaryPackageBlockHeader.h"

MEDUSA_BEGIN;

class BinaryBlockWriteStream :public BlockWriteStream
{
	typedef List<BinaryPackageBlockHeader*> BlockHeaderList;

public:
	BinaryBlockWriteStream(IStream& stream, BinaryPackage& package, FileEntry& fileEntry);
	virtual ~BinaryBlockWriteStream(void);
	virtual StreamType Type()const override{ return StreamType::BinaryBlockWrite; }
	BinaryBlockWriteStream(const BinaryBlockWriteStream&) = delete;
	BinaryBlockWriteStream& operator=(const BinaryBlockWriteStream&) = delete;
	BinaryBlockWriteStream(BinaryBlockWriteStream&& other);
	BinaryBlockWriteStream& operator=(BinaryBlockWriteStream&& other);
public:
	virtual uintp Length()const override;
	virtual bool Close()override;

protected:
	virtual size_t WriteBlock(uint blockIndex, const MemoryData& data)override;
	void LoadBlockHeaders();
protected:
	BinaryPackage* mPackage;
	FileEntry* mFileEntry;
	BlockHeaderList mBlockHeaders;

};


MEDUSA_END;