// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "IOSConsoleLogger.h"

#ifdef MEDUSA_IOS
MEDUSA_BEGIN;


IOSConsoleLogger::~IOSConsoleLogger(void)
{
}

void IOSConsoleLogger::OutputLogString( StringRef inString ,LogType logType/*=LogType::Info*/ )
{
    printf(inString.c_str());
   // NSString *pStr = [[NSString alloc] initWithCString:inString  encoding:NSASCIIStringEncoding];
   
   // NSLog(@"%@",pStr);
}

void IOSConsoleLogger::OutputLogString( WStringRef inString ,LogType logType/*=LogType::Info*/ )
{
    wprintf(inString.c_str());
   // NSString *pStr = [[NSString alloc] initWithCString:inString  encoding:NSASCIIStringEncoding];
   
   // NSLog(@"%@",pStr);
}

MEDUSA_END;
#endif