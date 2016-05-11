// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "WindowsConsoleLogger.h"

MEDUSA_BEGIN;

#ifdef MEDUSA_WINDOWS


WindowsConsoleLogger::~WindowsConsoleLogger(void)
{
}

void WindowsConsoleLogger::OutputLogString( StringRef inString ,LogType logType/*=LogType::Info*/ )
{
	SetLogColor(logType);
	printf("%s",inString.c_str());
}

void WindowsConsoleLogger::OutputLogString( WStringRef inString ,LogType logType/*=LogType::Info*/ )
{
	SetLogColor(logType);
	wprintf(L"%s",inString.c_str());
}

void WindowsConsoleLogger::SetLogColor(LogType logType)
{
	RETURN_IF_EQUAL(mCurrentLogType,logType);
	mCurrentLogType=logType;

	HANDLE console=GetStdHandle(STD_OUTPUT_HANDLE);
	RETURN_IF_EQUAL(console,INVALID_HANDLE_VALUE);

	/*
	wAttributes								
	FOREGROUND_BLUE					1
	FOREGROUND_GREEN				2
	FOREGROUND_RED					4
	FOREGROUND_INTENSITY		8
	BACKGROUND_BLUE					16
	BACKGROUND_GREEN				32
	BACKGROUND_RED					64
	BACKGROUND_INTENSITY		128

	SetConsoleTextAttribute control foreground color using low 4 bit and high 4 bit to background color
	*/
	switch (mCurrentLogType)
	{
	case LogType::Info:
		SetConsoleTextAttribute(console,FOREGROUND_INTENSITY);
		break;
	case LogType::Error:
		SetConsoleTextAttribute(console,FOREGROUND_INTENSITY|FOREGROUND_RED);
		break;
	case LogType::Assert:
		SetConsoleTextAttribute(console,FOREGROUND_INTENSITY|FOREGROUND_RED);
		break;
	default:
		break;
	}
}

#endif

MEDUSA_END;
