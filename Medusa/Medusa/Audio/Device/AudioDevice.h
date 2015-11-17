// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "IAudioDevice.h"

#undef MEDUSA_AUDIO_TYPE

#ifdef MEDUSA_AL
#include "OpenALDevice.h"
#define MEDUSA_AUDIO_TYPE OpenALDevice
#endif



MEDUSA_BEGIN;

class AudioDevice
{
public:
	static MEDUSA_AUDIO_TYPE& Instance()
	{
		static AudioDevice device;
		return device.GetDevice();
	}

	
private:
	MEDUSA_AUDIO_TYPE& GetDevice() { return mDevice; }
private:
	MEDUSA_AUDIO_TYPE mDevice;
};

MEDUSA_END;