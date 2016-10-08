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
	virtual bool SupportPrecompute()const override{ return false; }

	void AddString(float time, const StringRef& val);

	StringRef GetString(intp index)const;
	StringRef GetString(float time)const;


protected:
	List<HeapString> mStrings;

};

MEDUSA_END;
