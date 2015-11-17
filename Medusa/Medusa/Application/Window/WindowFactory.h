// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "Application/Window/IWindow.h"
#include "Application/Window/win/WinWindow.h"
#include "Application/Window/ios/IOSWindow.h"
#include "Application/Window/android/AndroidWindow.h"
#include "Core/Dynamic/Dynamic.h"


MEDUSA_BEGIN;

class WindowFactory
{
private:
	WindowFactory();
public:
	static IWindow* Create(MedusaWindowHandle parentWindow,StringRef name=StringRef::Empty)
	{
		IWindow* result= Dynamic::CreatePlatformType<IWindow,WinWindow,IOSWindow,AndroidWindow>(parentWindow,name);
		return result;
	}

};

MEDUSA_END;
