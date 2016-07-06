// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#ifdef MEDUSA_WINDOWS

#include "Core/System/Console.h"
#include <conio.h>
MEDUSA_BEGIN;

Console::Console()
{
	RegisterCtrlHandler();
}

Console::~Console(void)
{
	
}

BOOL CtrlHandler(DWORD fdwCtrlType)
{
	switch (fdwCtrlType)
	{
		// Handle the CTRL-C signal. 
	case CTRL_C_EVENT:
		Console::Instance().OnCtrlC();
		return(TRUE);
		// CTRL-CLOSE: confirm that the user wants to exit. 
	case CTRL_CLOSE_EVENT:
		Console::Instance().OnCtrlClose();
		return(TRUE);
		// Pass other signals to the next handler. 
	case CTRL_BREAK_EVENT:
		Console::Instance().OnCtrlBreak();
		return TRUE;
	case CTRL_LOGOFF_EVENT:
		return FALSE;
	case CTRL_SHUTDOWN_EVENT:
		return FALSE;
	default:
		return FALSE;
	}
}

void Console::RegisterCtrlHandler()
{
	SetConsoleCtrlHandler((PHANDLER_ROUTINE)CtrlHandler, TRUE);
}


char Console::ReadChar() const
{
	return (char)_getch();
}

bool Console::IsKeyboardHit() const
{
	return _kbhit()!=0;

}


MEDUSA_END;

#endif
