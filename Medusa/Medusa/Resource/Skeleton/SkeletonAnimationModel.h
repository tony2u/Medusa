// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Collection/Dictionary.h"
#include "Core/String/HeapString.h"

MEDUSA_BEGIN;

class SkeletonAnimationModel
{
public:
	SkeletonAnimationModel(const StringRef& name);
	virtual ~SkeletonAnimationModel(void);
	virtual bool Initialize();

	StringRef Name() const { return mName; }
	float Duration() const { return mDuration; }

	void AddColorTimeline(SkeletonSlotModel* slot, ColorTimelineModel* timeline);
	void AddTextureTimeline(SkeletonSlotModel* slot, StringTimelineModel* timeline);

	void AddRotationTimeline(SkeletonBoneModel* bone, RotationTimelineModel* timeline);
	void AddScaleTimeline(SkeletonBoneModel* bone, ScaleTimelineModel* timeline);
	void AddTranslateTimeline(SkeletonBoneModel* bone, TranslateTimelineModel* timeline);

	void AddVertexTimeline(KeyValuePair<SkeletonSlotModel*, ISkeletonAttachmentModel*> slotAttachment, VertexTimelineModel* timeline);

	DrawOrderTimelineModel* DrawOrderTimeLine() const { return mDrawOrderTimeLine; }
	void SetDrawOrderTimeLine(DrawOrderTimelineModel* val);

	TriggerTimelineModel* TriggerTimeline() const { return mTriggerTimeline; }
	void SetTriggerTimeline(TriggerTimelineModel* val);

	void AddIKTimeline(SkeletonIKModel* ik, IKTimelineModel* timeline);

	ISkeletonModel* SkeletonModel() const { return mSkeletonModel; }
	void SetSkeletonModel(ISkeletonModel* val) { mSkeletonModel = val; }

	const Dictionary<SkeletonSlotModel*, ColorTimelineModel*>& ColorTimelineDict() const { return mColorTimelineDict; }
	const Dictionary<SkeletonSlotModel*, StringTimelineModel*>& TextureTimelineDict() const { return mTextureTimelineDict; }

	const Dictionary<SkeletonBoneModel*, RotationTimelineModel*>& RotationTimelineDcit() const { return mRotationTimelineDcit; }
	const Dictionary<SkeletonBoneModel*, ScaleTimelineModel*>& ScaleTimelineDcit() const { return mScaleTimelineDcit; }
	const Dictionary<SkeletonBoneModel*, TranslateTimelineModel*>& TranslateTimelineDcit() const { return mTranslateTimelineDcit; }
	const Dictionary<KeyValuePair<SkeletonSlotModel*,ISkeletonAttachmentModel*>, VertexTimelineModel*>& VertexTimelineDcit() const { return mVertexTimelineDcit; }
	const Dictionary<SkeletonIKModel*, IKTimelineModel*>& IKTimelineDcit() const { return mIKTimelineDcit; }

	void UpdateTimelineDuration();

	void PreCalculate(float fps);
	void RemovePreCalculated();
protected:
	HeapString mName;
	float mDuration;
	
	Dictionary<SkeletonSlotModel*, ColorTimelineModel*> mColorTimelineDict;	//slot-color
	Dictionary<SkeletonSlotModel*, StringTimelineModel*> mTextureTimelineDict;	//slot-texture

	Dictionary<SkeletonBoneModel*, RotationTimelineModel*> mRotationTimelineDcit;	//bone-rotation
	Dictionary<SkeletonBoneModel*, ScaleTimelineModel*> mScaleTimelineDcit;	//bone-scale
	Dictionary<SkeletonBoneModel*, TranslateTimelineModel*> mTranslateTimelineDcit;	//bone-translate
	Dictionary<KeyValuePair<SkeletonSlotModel*, ISkeletonAttachmentModel*>, VertexTimelineModel*> mVertexTimelineDcit;	//attachment-vertex
	Dictionary<SkeletonIKModel*, IKTimelineModel*> mIKTimelineDcit;						//ik-ik
	DrawOrderTimelineModel* mDrawOrderTimeLine;
	TriggerTimelineModel* mTriggerTimeline;
	

	ISkeletonModel* mSkeletonModel;
	
};

MEDUSA_END;
