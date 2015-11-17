// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "IAudio.h"

MEDUSA_BEGIN;

class WavAudio:public IAudio
{
public:
	using IAudio::IAudio;
public:
	virtual AudioFileType AudioType()const override { return AudioFileType::wav; }

	static WavAudio* CreateFromFile(const FileIdRef& fileId);
	static WavAudio* CreateFromMemory(const FileIdRef& fileId,MemoryByteData data);

};

MEDUSA_END;