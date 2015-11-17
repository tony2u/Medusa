// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include <windows.h>
#include "Medusa.h"
#include "Content/Content.h"
#include <tchar.h>

USING_MEDUSA;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

	Application::Instance().Initialize();
	bool result= Application::Instance().Start();
	Application::Instance().Uninitialize();
	return result?0:-1;
}
