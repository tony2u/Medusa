// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#ifdef MEDUSA_WINDOWS

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
	SYSTEM_INFO info;
	GetSystemInfo(&info);
	return info.dwNumberOfProcessors;
}

Size2U Environment::ScreenSize()const
{
	if (RequireFullScreen())
	{
		int width = GetSystemMetrics(SM_CXSCREEN);
		int height = GetSystemMetrics(SM_CYSCREEN);

		return Size2U(width, height);
	}
	else
	{
		return Size2U(MEDUSA_SCREEN_WIDTH, MEDUSA_SCREEN_HEIGHT);
	}
	
}

bool Environment::RequireFullScreen() const
{
	return false;
}

CPUArchitectures Environment::Architecture() const
{
#ifdef MEDUSA_X64
	return CPUArchitectures::X64;
#else
	return CPUArchitectures::X86;
#endif
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
