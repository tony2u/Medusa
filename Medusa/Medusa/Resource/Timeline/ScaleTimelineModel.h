// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Resource/Timeline/ITimelineModel.h"
#include "Geometry/Scale3.h"

MEDUSA_BEGIN;

class ScaleTimelineModel:public ITimelineModel
{
public:
	ScaleTimelineModel(const FileIdRef& fileId, float duration = 0.f);
	virtual ~ScaleTimelineModel(void);

	void AddScale(float time, const Scale3F& scale, Math::TweenType tweenType, const List<float>& args);
	Scale3F GetScale(float time)const;

	virtual void RemovePreCalculated()override;
protected:
	virtual void OnPreCalculateBegin()override;
	virtual void AddPreCalcuatedItem(bool isFound, uint prevFrameIndex, uint nextFrameIndex, float percent) override;
protected:
	List<Scale3F> mScales;
	List<Scale3F> mPreCalculatedScales;

};

MEDUSA_END;
