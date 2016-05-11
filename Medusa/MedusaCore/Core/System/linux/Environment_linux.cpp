// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#ifdef MEDUSA_LINUX

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
	return get_nprocs();
}

bool Environment::GetScreenSize(uint& outWidth, uint& outHeight)const
{
	outWidth = 0;
	outHeight = 0;
	return true;
}
bool Environment::RequireFullScreen() const
{
	return false;
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
