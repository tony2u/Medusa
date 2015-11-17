// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Geometry/Point2.h"

MEDUSA_BEGIN;

enum class TouchPhase
{
	Began,
	Moved,
	Stationary,	//A finger is touching the surface but hasn't moved since the previous event.
	Ended,
	Cancelled, //The system cancelled tracking for the touch, as when(for example) the user puts the device to his or her face.
};


class Touch
{
public:
	Touch();
	Touch(TouchPhase phase, intp id, double timestamp, const Point2F& pos, const Point2F& prevPos, uint tapCount = 1);

	Touch(const Touch& val);
	Touch& operator=(const Touch& val);

	~Touch(void){}

	bool operator<(const Touch& touch)const{ return Id < touch.Id; }
	bool operator==(const Touch& touch)const { return Id == touch.Id; }

public:
	TouchPhase Phase;
	intp Id;
	double Timestamp;	//since system startup, in seconds

	Point2F Pos;
	Point2F PrevPos;

	uint TapCount;	//The number of times the finger was tapped for this given touch. 

	const static Touch Zero;
};

MEDUSA_END;