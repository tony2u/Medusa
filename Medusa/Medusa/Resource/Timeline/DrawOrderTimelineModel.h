// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Resource/Timeline/ITimelineModel.h"
#include "Geometry/Point3.h"

MEDUSA_BEGIN;

class DrawOrderTimelineModel:public ITimelineModel
{
public:
	DrawOrderTimelineModel(const FileIdRef& fileId, float duration = 0.f);
	virtual ~DrawOrderTimelineModel(void);

	List<uint>& NewDrawOrderList();
	void AddDrawOrderFrame(float time);

	bool IsDrawOrderChanged(float prevTime,float currentTime)const;

	const List<uint>& GetDrawOrder(float time)const;
	virtual void RemovePreCalculated()override;
protected:
	virtual void OnPreCalculateBegin()override;
	virtual void AddPreCalcuatedItem(bool isFound, uint prevFrameIndex, uint nextFrameIndex, float percent) override;

protected:
	List<List<uint>, NoCompare> mDrawOrderList;	//index to find node in other place
	List<List<uint>, NoCompare> mPreCalculatedDrawOrderList;
};

MEDUSA_END;
