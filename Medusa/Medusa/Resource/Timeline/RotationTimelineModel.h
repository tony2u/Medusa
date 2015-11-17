// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Resource/Timeline/ITimelineModel.h"
#include "Core/Geometry/Rotation3.h"

MEDUSA_BEGIN;

class RotationTimelineModel:public ITimelineModel
{
public:
	RotationTimelineModel(const FileIdRef& fileId, float duration = 0.f);
	virtual ~RotationTimelineModel(void);

	void AddRotation(float time, const Rotation3F& rotation, Math::TweenType tweenType, const List<float>& args);

	Rotation3F GetRotation(float time)const;
	virtual void RemovePreCalculated()override;
protected:
	virtual void OnPreCalculateBegin()override;
	virtual void AddPreCalcuatedItem(bool isFound, uint prevFrameIndex, uint nextFrameIndex, float percent) override;
protected:
	List<Rotation3F> mRotations;
	List<Rotation3F> mPreCalcualtedRotations;

};

MEDUSA_END;
