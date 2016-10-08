// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "TypewriterEffect.h"
#include "Node/INode.h"
#include "Node/Control/Label/ILabel.h"
#include "Audio/AudioEngine.h"
#include "Resource/Timeline/TConstantTimelineModel.h"
#include "Node/Action/Timeline/TConstantTimeline.h"
MEDUSA_BEGIN;

TypewriterEffect::TypewriterEffect(float charsPerSecond)
	:BaseSingleCompositeInfiniteAction(),
	mCharsPerSecond(charsPerSecond),
	mPrevCharIndex(Math::UIntMaxValue)
{
}


TypewriterEffect::~TypewriterEffect(void)
{
}

bool TypewriterEffect::Initialize(void* target)
{
	SetupTimelineModel();
	RETURN_FALSE_IF_FALSE(BaseSingleCompositeInfiniteAction::Initialize(target));
	INode* node = (INode*)mTarget;
	if (!node->IsA<ILabel>())
	{
		Log::AssertFailed("TypewriterEffect only accept target inherit from ILabel");
		return false;
	}



	return true;
}


void TypewriterEffect::SetupTimelineModel()
{
	auto model = new TConstantTimelineModel<uint>(FileId::Empty);
	//pre compute model
	uint count = mText.Length();
	float delay = 1.f / mCharsPerSecond;
	float dt = 0.f;

	model->Add(0.f, 0);

	FOR_EACH_SIZE(i,count)
	{
		wchar c = mText[i];

		bool isNewline = StdString::WConstants::IsNewLine(c);
		bool isPeriod = StdString::WConstants::IsPeriod(c);
		if (isNewline)
		{
			dt += mNewLineDelay;
		}
		else if (isPeriod)
		{
			dt += mPeriodDelay;
		}
		else
		{
			dt += delay;
		}

		model->Add(dt, i+1);	//next char time
	}
	model->Initialize();

	auto timeline = new TConstantTimeline<uint>(model);
	timeline->KeepAlive(true);
	timeline->OnValueUpdated += Bind(&TypewriterEffect::OnCharIndexUpdated, this);
	SetInnerAction(timeline);
}

void TypewriterEffect::OnCharIndexUpdated(int frameIndex, const uint& charIndex)
{
	if (mPrevCharIndex != charIndex&&charIndex < mText.Length())
	{
		auto str = mText.SubString(0, charIndex + 1);
		ILabel* node = (ILabel*)mTarget;
		node->SetString(str);

		uint charCount = (uint)(charIndex - mPrevCharIndex);
		mPrevCharIndex = charIndex;

		FOR_EACH_SIZE(i, charCount)
		{
			AudioEngine::Instance().PlayEffect(mAudioClip);
		}
	}
}

TypewriterEffect* TypewriterEffect::Create(float charsPerSecond)
{
	return new TypewriterEffect(charsPerSecond);
}


bool TypewriterEffect::Reset()
{
	RETURN_FALSE_IF_FALSE(BaseSingleCompositeInfiniteAction::Reset());

	ILabel* node = (ILabel*)mTarget;
	if (node!=nullptr)
	{
		node->SetString(StringRef::Empty);
	}
	mPrevCharIndex = Math::UIntMaxValue;
	return true;
}

TypewriterEffect* TypewriterEffect::Clone() const
{
	return new TypewriterEffect(mCharsPerSecond);
}


MEDUSA_END;
