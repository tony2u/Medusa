// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Pattern/Share.h"
#include "Core/Action/Composite/BaseSingleCompositeInfiniteAction.h"
#include "Core/IO/FileId.h"

MEDUSA_BEGIN;

class TypewriterEffect :public BaseSingleCompositeInfiniteAction
{
public:
	TypewriterEffect(float charsPerSecond=20.f);
	virtual ~TypewriterEffect(void);
public:
	virtual bool Initialize(void* target)override;

	virtual TypewriterEffect* Clone()const override;
	static TypewriterEffect* Create(float charsPerSecond);

	virtual bool Reset()override;

	WStringRef Text() const { return mText; }
	void SetText(WStringRef val) { mText = val; }

	float CharsPerSecond() const { return mCharsPerSecond; }
	void SetCharsPerSecond(float val) { mCharsPerSecond = val; }

	float NewLineDelay() const { return mNewLineDelay; }
	void SetNewLineDelay(float val) { mNewLineDelay = val; }

	float PeriodDelay() const { return mPeriodDelay; }
	void SetPeriodDelay(float val) { mPeriodDelay = val; }

	FileIdRef AudioClip() const { return mAudioClip; }
	void SetAudioClip(FileIdRef val) { mAudioClip = val; }
private:
	void SetupTimelineModel();
	void OnCharIndexUpdated(int frameIndex, const uint& charIndex);
private:
	FileId mAudioClip;	//per char
	
	WHeapString mText;
	float mCharsPerSecond = 20.f;
	float mNewLineDelay = 0.f;	// \n
	float mPeriodDelay = 0.f;	// . ! ?
private:
	uint mPrevCharIndex;
};

MEDUSA_END;
