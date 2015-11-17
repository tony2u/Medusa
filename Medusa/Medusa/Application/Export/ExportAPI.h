// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#ifdef MEDUSA_WINDOWS
#include <windows.h>
#define MEDUSA_EXPORT_API __declspec(dllexport) 

extern "C"
{
	typedef bool MInitializeApplicationCallback(MedusaWindowHandle parentWindow);
	typedef bool MGameLoopCallback(float interval);
	typedef bool MGameResizeCallback();

	typedef bool MGameCleanUpCallback();

	//////////////////////////////////////////////////////////////////////////

	MEDUSA_EXPORT_API bool MInitializeApplication(HWND hwnd);

	MEDUSA_EXPORT_API bool MGameLoop(float interval);

	MEDUSA_EXPORT_API bool MGameCleanUp();
	MEDUSA_EXPORT_API bool MGameResize();

};


#endif