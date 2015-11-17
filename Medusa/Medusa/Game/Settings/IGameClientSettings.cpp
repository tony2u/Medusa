// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "IGameClientSettings.h"
#include "Core/System/Environment.h"
#include "Core/Geometry/Size2.h"
#include "Core/Log/Log.h"

MEDUSA_BEGIN;

PublishTarget IGameClientSettings::ResultTag() const
{
#ifdef MEDUSA_WINDOWS
	return Tag();
#else
	if (IsDebugEnabled())
	{
		return Tag();
	}
	else
	{
		return Environment::Instance().Target();
	}
#endif
	
}


Size2F IGameClientSettings::DesignWinSize() const
{
	PublishDevices device = ResultTag().Device;
	switch (device.ToInt())
	{
		case PublishDevices::sd.IntValue:
			return Size2F(480, 320);
		case PublishDevices::hd.IntValue:
			return Size2F(MEDUSA_SCREEN_WIDTH,MEDUSA_SCREEN_HEIGHT);		//retina will *2
		default:
			Log::AssertFailed("Error device");
			break;
	}
	return Size2F::Zero;
}


MEDUSA_END;