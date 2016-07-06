// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#ifdef MEDUSA_AL
#include "Audio/IAudioSource.h"
#include "Resource/Audio/IAudio.h"

MEDUSA_BEGIN;

class StaticAudioSource:public IAudioSource
{
public:
	StaticAudioSource(const StringRef& name=StringRef::Empty);
	virtual ~StaticAudioSource();

	Share<IAudio> GetBuffer() const;
	void SetBuffer(const Share<IAudio>& val);

	void AddBuffer(const Share<IAudio>& val);
protected:
	virtual void OnSetup();
protected:
	List<Share<IAudio>> mBuffers;
};


MEDUSA_END;
#endif