// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#ifdef MEDUSA_LINUX

#include "Core/System/Console.h"
MEDUSA_BEGIN;


Console::Console()
{
	RegisterCtrlHandler();
}

Console::~Console(void)
{

}

void my_handler(int s) 
{
	Console::Instance().OnCtrlC();
	exit(1);
}




void Console::RegisterCtrlHandler()
{
	struct sigaction sigIntHandler;
	sigIntHandler.sa_handler = my_handler;
	sigemptyset(&sigIntHandler.sa_mask);
	sigIntHandler.sa_flags = 0;
	sigaction(SIGINT, &sigIntHandler, NULL);
}


MEDUSA_END;

#endif
