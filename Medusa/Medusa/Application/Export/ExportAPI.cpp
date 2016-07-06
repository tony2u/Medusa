// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
//this file will only be included in Win32
#ifdef MEDUSA_WINDOWS

#include "Application/Application.h"
#include "Application/Export/ExportAPI.h"


USING_MEDUSA;


extern "C"
{
	MEDUSA_EXPORT_API bool MInitializeApplication( HWND parentWindow )
	{
		Application::Instance().Initialize(parentWindow);

		return true;
	}

	MEDUSA_EXPORT_API bool MGameLoop( float interval )
	{
		return Application::Instance().UpdateAndDraw(interval);
	}

	MEDUSA_EXPORT_API bool MGameCleanUp()
	{
		return Application::Instance().Uninitialize();
	}

	MEDUSA_EXPORT_API bool MGameResize()
	{
		return Application::Instance().Resize();
		return true;
	}
}

#endif