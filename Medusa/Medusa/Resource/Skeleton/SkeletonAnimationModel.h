// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Collection/Dictionary.h"
#include "Core/String/HeapString.h"
#include "Core/Pattern/Share.h"
#include "Resource/Timeline/ColorTimelineModel.h"
#include "Resource/Timeline/StringTimelineModel.h"
#include "Resource/Timeline/RotationTimelineModel.h"
#include "Resource/Timeline/ScaleTimelineModel.h"
#include "Resource/Timeline/TranslateTimelineModel.h"
#include "Resource/Timeline/VertexTimelineModel.h"
#include "Resource/Timeline/DrawOrderTimelineModel.h"
#include "Resource/Timeline/TriggerTimelineModel.h"
#include "Resource/Timeline/IKTimelineModel.h"

MEDUSA_BEGIN;

class SkeletonAnimationModel
{
public:
	SkeletonAnimationModel(const StringRef& name);
	virtual ~SkeletonAnimationModel(void);
	virtual bool Initialize();

	StringRef Name() const { return mName; }
	float Duration() const { return mDuration; }

	void AddColorTimeline(SkeletonSlotModel* slot, const Share<ColorTimelineModel>& timeline);
	void AddTextureTimeline(SkeletonSlotModel* slot, const Share<StringTimelineModel>& timeline);

	void AddRotationTimeline(SkeletonBoneModel* bone, const Share<RotationTimelineModel>& timeline);
	void AddScaleTimeline(SkeletonBoneModel* bone, const Share<ScaleTimelineModel>& timeline);
	void AddTranslateTimeline(SkeletonBoneModel* bone, const Share<TranslateTimelineModel>& timeline);

	void AddVertexTimeline(KeyValuePair<SkeletonSlotModel*, ISkeletonAttachmentModel*> slotAttachment, const Share<VertexTimelineModel>& timeline);

	const Share<DrawOrderTimelineModel>& DrawOrderTimeLine() const { return mDrawOrderTimeLine; }
	void SetDrawOrderTimeLine(const Share<DrawOrderTimelineModel>& val);

	const Share<TriggerTimelineModel>& TriggerTimeline() const { return mTriggerTimeline; }
	void SetTriggerTimeline(const Share<TriggerTimelineModel>& val);

	void AddIKTimeline(SkeletonIKModel* ik, const Share<IKTimelineModel>& timeline);

	ISkeletonModel* SkeletonModel() const { return mSkeletonModel; }
	void SetSkeletonModel(ISkeletonModel* val) { mSkeletonModel = val; }

	const Dictionary<SkeletonSlotModel*, Share<ColorTimelineModel>>& ColorTimelineDict() const { return mColorTimelineDict; }
	const Dictionary<SkeletonSlotModel*, Share<StringTimelineModel>>& TextureTimelineDict() const { return mTextureTimelineDict; }

	const Dictionary<SkeletonBoneModel*, Share<RotationTimelineModel>>& RotationTimelineDcit() const { return mRotationTimelineDcit; }
	const Dictionary<SkeletonBoneModel*, Share<ScaleTimelineModel>>& ScaleTimelineDcit() const { return mScaleTimelineDcit; }
	const Dictionary<SkeletonBoneModel*, Share<TranslateTimelineModel>>& TranslateTimelineDcit() const { return mTranslateTimelineDcit; }
	const Dictionary<KeyValuePair<SkeletonSlotModel*,ISkeletonAttachmentModel*>, Share<VertexTimelineModel>>& VertexTimelineDcit() const { return mVertexTimelineDcit; }
	const Dictionary<SkeletonIKModel*, Share<IKTimelineModel>>& IKTimelineDcit() const { return mIKTimelineDcit; }

	void UpdateTimelineDuration();

	void PreCalculate(float fps);
	void RemovePreCalculated();
protected:
	HeapString mName;
	float mDuration;
	
	Dictionary<SkeletonSlotModel*, Share<ColorTimelineModel>> mColorTimelineDict;	//slot-color
	Dictionary<SkeletonSlotModel*, Share<StringTimelineModel>> mTextureTimelineDict;	//slot-texture

	Dictionary<SkeletonBoneModel*, Share<RotationTimelineModel>> mRotationTimelineDcit;	//bone-rotation
	Dictionary<SkeletonBoneModel*, Share<ScaleTimelineModel>> mScaleTimelineDcit;	//bone-scale
	Dictionary<SkeletonBoneModel*, Share<TranslateTimelineModel>> mTranslateTimelineDcit;	//bone-translate
	Dictionary<KeyValuePair<SkeletonSlotModel*, ISkeletonAttachmentModel*>, Share<VertexTimelineModel>> mVertexTimelineDcit;	//attachment-vertex
	Dictionary<SkeletonIKModel*, Share<IKTimelineModel>> mIKTimelineDcit;						//ik-ik

	Share<DrawOrderTimelineModel> mDrawOrderTimeLine;
	Share<TriggerTimelineModel> mTriggerTimeline;
	

	ISkeletonModel* mSkeletonModel;
	
};

MEDUSA_END;
