// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Audio/Device/AudioDevice.h"
#include "AudioListener.h"
MEDUSA_BEGIN;

float AudioListener::Volume() 
{
	return AudioDevice::Instance().GetListenerVolume();
}

Point3F AudioListener::Position() 
{
	return AudioDevice::Instance().GetListenerPosition();
}

Point3F AudioListener::Velocity() 
{
	return AudioDevice::Instance().GetListenerVelocity();
}

AudioListenerOrientation AudioListener::Orientation() 
{
	return AudioDevice::Instance().GetListenerOrientation();
}

void AudioListener::SetVolume(float val)
{
	AudioDevice::Instance().SetListenerVolume(val);
}

void AudioListener::SetPosition(const Point3F& val)
{
	AudioDevice::Instance().SetListenerPosition(val);
}

void AudioListener::SetVelocity(const Point3F& val)
{
	AudioDevice::Instance().SetListenerVelocity(val);
}

void AudioListener::SetOrientation(const AudioListenerOrientation& val)
{
	AudioDevice::Instance().SetListenerOrientation(val);
}

MEDUSA_END;