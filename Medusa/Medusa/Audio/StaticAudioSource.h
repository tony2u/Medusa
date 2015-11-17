// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Audio/IAudioSource.h"

MEDUSA_BEGIN;

class StaticAudioSource:public IAudioSource
{
public:
	StaticAudioSource(const StringRef& name=StringRef::Empty);
	virtual ~StaticAudioSource();

	IAudio* GetBuffer() const;
	void SetBuffer(IAudio* val);

	void AddBuffer(IAudio* val);
protected:
	virtual void OnSetup();
protected:
	List<IAudio*> mBuffers;
};


MEDUSA_END;