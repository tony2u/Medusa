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

MEDUSA_BEGIN;

enum class CPUArchitectures
{
	Unknow,
	X86,
	X64,
	ArmV6,
	ArmV7,
	ArmV7S,
	Arm64
};

class Environment :public Singleton < Environment >
{
	friend class Singleton < Environment >;
private:
	Environment() = default;
	~Environment() = default;
public:
	HeapString GetMacAddress();
	bool IsNetworkAvailable();

	uint GetCPUCount()const;
	bool RequireFullScreen()const;
	bool GetScreenSize(uint& outWidth,uint& outHeight)const;
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

	bool SupportVFP()const
	{
		return IsArm();
	}

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
};




MEDUSA_END;

