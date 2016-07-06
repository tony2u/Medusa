// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/IO/Stream/IStream.h"
#include "Core/Coder/CoderChain.h"
#include "Core/IO/Stream/MemoryStream.h"
#include "Core/IO/Stream/BlockReadStream.h"

MEDUSA_BEGIN;

class BlockCodeReadStream :public BlockReadStream
{
public:
	BlockCodeReadStream(const Share<const IStream>& stream, uint32 blockSize, const CoderChain& coderChain,const FileEntry& fileEntry);
	virtual ~BlockCodeReadStream(void);
	virtual StreamType Type()const { return StreamType::CodeRead; }
	BlockCodeReadStream(const BlockCodeReadStream&) = delete;
	BlockCodeReadStream& operator=(const BlockCodeReadStream&) = delete;
	BlockCodeReadStream(BlockCodeReadStream&& other);
	BlockCodeReadStream& operator=(BlockCodeReadStream&& other);
public:
	virtual uintp Length()const;
protected:
	virtual size_t LoadBlockTo(uint blockIndex, MemoryStream& output)const;
protected:
	const CoderChain* mCoderChain;
	const FileEntry* mFileEntry;

};


MEDUSA_END;