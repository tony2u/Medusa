// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#ifdef MEDUSA_AL
#include "Audio/AudioTypes.h"

MEDUSA_BEGIN;


class AudioListener
{
public:
	static float Volume();
	static Point3F Position();
	static Point3F Velocity();
	static AudioListenerOrientation Orientation();

	static void SetVolume(float val);
	static void SetPosition(const Point3F& val);
	static void SetVelocity(const Point3F& val);
	static void SetOrientation(const AudioListenerOrientation& val);

};


MEDUSA_END;
#endif