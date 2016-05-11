// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#ifdef MEDUSA_ANDROID

#include "Core/System/Environment.h"
MEDUSA_BEGIN;


HeapString Environment::GetMacAddress()
{
	return HeapString::Empty;
}

bool Environment::IsNetworkAvailable()
{
	return true;
}
uint Environment::GetCPUCount() const
{
	/*
	* - _SC_NPROCESSORS_CONF
	*       The number of processors configured.
	*
	* - _SC_NPROCESSORS_ONLN
	*       The number of processors currently online (available).
	*/

	return sysconf(_SC_NPROCESSORS_ONLN);
}


bool Environment::GetScreenSize(uint& outWidth, uint& outHeight)const
{
	//TODO:init screen size
	outWidth = 0;
	outHeight = 0;
	return true;
}

bool Environment::RequireFullScreen() const
{
	return true;
}

CPUArchitectures Environment::Architecture() const
{
#ifdef MEDUSA_X64
	return CPUArchitectures::X64;
#endif
	return CPUArchitectures::X86;
}

PublishDevices Environment::Device() const
{
	return PublishDevices::hd;
}

PublishLanguages Environment::Language() const
{
	return PublishLanguages::enus;
}

MEDUSA_END;

#endif
