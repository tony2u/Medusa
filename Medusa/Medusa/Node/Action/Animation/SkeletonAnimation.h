// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "IAnimation.h"
#include "Core/Collection/KeyValuePair.h"
#include "Core/Collection/List.h"

MEDUSA_BEGIN;

class SkeletonAnimation :public IAnimation
{
public:
	SkeletonAnimation(SkeletonAnimationModel* model, bool isRepeatForever = false, float beforeDelay = 0.f, float repeatDuration = 0.f, float afterDelay = 0.f, const StringRef& name = StringRef::Empty);
	virtual ~SkeletonAnimation();

	virtual bool Initialize(void* target)override;

	SkeletonAnimationModel* Model() const { return mModel; }
	void SetModel(SkeletonAnimationModel* val) { mModel = val; }

	virtual bool Start()override;
	virtual bool Stop()override;
	virtual bool Reset()override;

protected:
	virtual bool OnUpdate(float prevElapsed, float dt, float blend = 1.f) override;
protected:
	SkeletonAnimationModel* mModel;

	List<ITimeline*> mTimelines;

	List<KeyValuePair<SkeletonBone*, ScaleTimelineModel*>> mBoneScaleTimelines;
	List<KeyValuePair<SkeletonBone*, RotationTimelineModel*>> mBoneRotaionTimelines;
	List<KeyValuePair<SkeletonBone*, TranslateTimelineModel*>> mBoneTranslateTimelines;

	List<KeyValuePair<SkeletonIK*, IKTimelineModel*>> mIKTimelines;

};
MEDUSA_END;
