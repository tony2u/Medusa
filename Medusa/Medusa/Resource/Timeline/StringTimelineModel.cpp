// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "StringTimelineModel.h"

MEDUSA_BEGIN;


StringTimelineModel::StringTimelineModel(const FileIdRef& fileId, float duration /*= 0.f*/)
	:ITimelineModel(fileId, duration)
{

}


StringTimelineModel::~StringTimelineModel(void)
{
}


void StringTimelineModel::AddString(float time, const StringRef& val)
{
	mStrings.Add(val);
	AddFrame(time, (uint)mStrings.Count() - 1);
}


StringRef StringTimelineModel::GetString(intp index) const
{
	const StringRef& str = mStrings[index];
	return str;
}

StringRef StringTimelineModel::GetString(float time) const
{
	intp index = GetSteppedFrameIndex(time);
	return mStrings[index];
}


MEDUSA_END;