// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "MedusaCorePreDeclares.h"

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

enum class DeviceOrientation
{
	None = 0,
	Portrait = 1,            // Device oriented vertically, home button on the bottom
	PortraitUpsideDown = 2,  // Device oriented vertically, home button on the top
	LandscapeLeft = 3,       // Device oriented horizontally, home button on the right
	LandscapeRight = 4,      // Device oriented horizontally, home button on the left
	FaceUp = 5,              // Device oriented flat, face up
	FaceDown = 6             // Device oriented flat, face down
};

enum class UIOrientation
{
	None = (int)DeviceOrientation::None,
	Portrait = (int)DeviceOrientation::Portrait,
	PortraitUpsideDown = (int)DeviceOrientation::PortraitUpsideDown,
	LandscapeLeft = (int)DeviceOrientation::LandscapeRight,
	LandscapeRight = (int)DeviceOrientation::LandscapeLeft,
	Count = 5,
};




MEDUSA_END;