// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Resource/Timeline/ITimelineModel.h"
#include "Core/String/HeapString.h"

MEDUSA_BEGIN;

class StringTimelineModel:public ITimelineModel
{
public:
	StringTimelineModel(const FileIdRef& fileId, float duration = 0.f);
	virtual ~StringTimelineModel(void);

	void AddString(float time, const StringRef& val);

	StringRef GetString(intp index)const;
	StringRef GetString(float time)const;


	virtual void RemovePreCalculated()override;
protected:
	virtual void OnPreCalculateBegin()override;
	virtual void AddPreCalcuatedItem(bool isFound, uint prevFrameIndex, uint nextFrameIndex, float percent) override;

protected:
	List<HeapString> mStrings;
	List<HeapString> mPreCalculatedStrings;

};

MEDUSA_END;
