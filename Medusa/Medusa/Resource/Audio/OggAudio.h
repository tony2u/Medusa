// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#if  defined(MEDUSA_OGG)&&defined(MEDUSA_AL)
#include "IAudio.h"

MEDUSA_BEGIN;

class OggAudio:public IAudio
{
public:
	using IAudio::IAudio;
public:
	virtual AudioFileType AudioType()const override { return AudioFileType::ogg; }

	static OggAudio* CreateFromFile(const FileIdRef& fileId);
	static OggAudio* CreateFromMemory(const FileIdRef& fileId,MemoryData data);

};

MEDUSA_END;
#endif
