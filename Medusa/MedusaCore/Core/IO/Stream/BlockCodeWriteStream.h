// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/IO/Stream/BlockWriteStream.h"
#include "Core/Coder/CoderChain.h"

MEDUSA_BEGIN;

class BlockCodeWriteStream :public BlockWriteStream
{
public:
	BlockCodeWriteStream(const Share<IStream>& stream, uint32 blockSize, const CoderChain& coderChain,FileEntry& fileEntry);
	virtual ~BlockCodeWriteStream(void);
	virtual StreamType Type()const { return StreamType::CodeWrite; }
	BlockCodeWriteStream(const BlockCodeWriteStream&) = delete;
	BlockCodeWriteStream& operator=(const BlockCodeWriteStream&) = delete;
	BlockCodeWriteStream(BlockCodeWriteStream&& other);
	BlockCodeWriteStream& operator=(BlockCodeWriteStream&& other);
public:
	virtual uintp Length()const;
protected:
	virtual size_t WriteBlock(uint blockIndex, const MemoryData& data);
	void WriteOffset(size_t dataSize);
protected:
	const CoderChain* mCoderChain=nullptr;
	FileEntry* mFileEntry=nullptr;

};


MEDUSA_END;