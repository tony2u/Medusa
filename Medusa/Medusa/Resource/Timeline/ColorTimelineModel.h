// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Resource/Timeline/ITimelineModel.h"
#include "Geometry/Color4.h"

MEDUSA_BEGIN;

class ColorTimelineModel:public ITimelineModel
{
public:
	ColorTimelineModel(const FileIdRef& fileId, float duration = 0.f);
	virtual ~ColorTimelineModel(void);


	void AddColor(float time, const Color4F& color);

	Color4F GetColor(float time)const;
	virtual void RemovePreCalculated()override;

protected:
	virtual void OnPreCalculateBegin()override;
	virtual void AddPreCalcuatedItem(bool isFound, uint prevFrameIndex, uint nextFrameIndex, float percent) override;
protected:
	List<Color4F> mColors;
	List<Color4F> mPreCalculatedColors;

};

MEDUSA_END;
