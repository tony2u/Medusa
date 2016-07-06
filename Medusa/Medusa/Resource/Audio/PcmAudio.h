// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#ifdef MEDUSA_AL
#include "IAudio.h"

MEDUSA_BEGIN;

class PcmAudio:public IAudio
{
public:
	using IAudio::IAudio;
public:
	virtual AudioFileType AudioType()const override { return AudioFileType::pcm; }
};

MEDUSA_END;
#endif