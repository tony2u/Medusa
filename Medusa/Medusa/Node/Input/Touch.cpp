// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Touch.h"

MEDUSA_BEGIN;



Touch::Touch()
	:Phase(TouchPhase::Began),
	Id(0),
	Timestamp(0.0),
	Pos(Point2F::Zero),
	PrevPos(Point2F::Zero),

	TapCount(1)
{

}

Touch::Touch(TouchPhase phase, intp id, double timestamp, const Point2F& pos, const Point2F& prevPos, uint tapCount /*= 1*/)
	:Phase(phase),
	Id(id),
	Timestamp(timestamp),
	Pos(pos),
	PrevPos(prevPos),
	TapCount(tapCount)
{

}

Touch::Touch(const Touch& val)
	:Phase(val.Phase),
	Id(val.Id),
	Timestamp(val.Timestamp),
	Pos(val.Pos),
	PrevPos(val.PrevPos),
	TapCount(val.TapCount)
{

}

Touch& Touch::operator=(const Touch& val)
{
	Phase = val.Phase;
	Id = val.Id;
	Timestamp = val.Timestamp;
	Pos = val.Pos;
	PrevPos = val.PrevPos;
	TapCount = val.TapCount;
	return *this;
}

const Touch Touch::Zero;

MEDUSA_END;