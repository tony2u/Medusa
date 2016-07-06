// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/String/StringRef.h"
#include "Core/String/HeapString.h"
#include "Core/String/StackString.h"
#include "Core/Pattern/Singleton.h"
#include "Core/System/PublishTarget.h"
#include "SystemDefines.h"
#include "Core/Collection/Array.h"
#include "Core/Pattern/Event.h"

MEDUSA_BEGIN;

class Environment :public Singleton < Environment >
{
	friend class Singleton < Environment >;
	Environment()
	{
		mSupportUIOrientations.SetAll(true);
	}
	~Environment() = default;
public:
	HeapString GetMacAddress();
	bool IsNetworkAvailable();

	uint CPUCount()const;
	bool RequireFullScreen()const;
	bool GetScreenSize(uint& outWidth, uint& outHeight)const;
	CPUArchitectures Architecture()const;
	PublishDevices Device()const;
	PublishLanguages Language()const;
	PublishTarget Target()const { return PublishTarget(PublishVersions::main, Device(), Language()); }

	bool SupportNeon()const
	{
#ifdef __ARM_NEON__
		return true;
#else
		return false;
#endif
	}

	bool SupportVFP()const { return IsArm(); }
	bool IsArm()const
	{
		switch (Architecture())
		{
		case CPUArchitectures::ArmV6:
		case CPUArchitectures::ArmV7:
		case CPUArchitectures::ArmV7S:
		case CPUArchitectures::Arm64:
			return true;
		default:
			return false;
		}
	}
public:
	Event<void(UIOrientation)> OnUIOrientationChanged;

	DeviceOrientation GetDeviceOrientation() const { return mDeviceOrientation; }
	void SetDeviceOrientation(DeviceOrientation val) { mDeviceOrientation = val; }

	UIOrientation GetUIOrientation() const { return mUIOrientation; }
	void SetUIOrientation(UIOrientation val) { mUIOrientation = val; OnUIOrientationChanged(val); }

	bool IsSupport(UIOrientation val)const
	{
		return mSupportUIOrientations[(size_t)val];
	}

	void EnableUIOrientation(UIOrientation orientation, bool val)
	{
		mSupportUIOrientations[(size_t)orientation] = val;
	}

	void EnableUIOrientationLandscape()
	{
		mSupportUIOrientations.SetAll(false);
		EnableUIOrientation(UIOrientation::LandscapeLeft, true);
		EnableUIOrientation(UIOrientation::LandscapeRight, true);
	}
	void EnableUIOrientationPortrait()
	{
		mSupportUIOrientations.SetAll(false);
		EnableUIOrientation(UIOrientation::Portrait, true);
		EnableUIOrientation(UIOrientation::PortraitUpsideDown, true);
	}
protected:
	DeviceOrientation mDeviceOrientation = DeviceOrientation::None;
	UIOrientation mUIOrientation = UIOrientation::None;
	Array<bool, (size_t)UIOrientation::Count> mSupportUIOrientations;
};




MEDUSA_END;

