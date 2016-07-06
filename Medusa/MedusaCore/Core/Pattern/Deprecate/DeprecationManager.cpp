// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "DeprecationManager.h"
#include "Core/String/HeapString.h"
#include "Core/String/StackString.h"
#include "Core/String/StringParser.h"
#include "Core/Log/Log.h"


MEDUSA_BEGIN;


void DeprecationManager::AddDeprecateFunction( const char* funcName,const char* comment,const char* fileName,const char* lineName )
{
	mDeprecatedFunction[funcName]=comment;

	Log::FormatInfo("==>Deprecated:{}\t{}\t{}\t{}\n",funcName,comment,fileName,lineName);
}

DeprecationManager::~DeprecationManager()
{
	Log::Info( "*************************************************************\n" );
	Log::Info( "WARNING. You are using the following deprecated functions:\n" );

	HeapString str;
	for (const auto& i : mDeprecatedFunction)
	{
		const char* funcName=i.first;
		const char* comment=i.second;
		str.Format("==>Deprecated:{}\t{}\n",funcName,comment);
		Log::Info(str);
	}
	Log::Info( "*************************************************************\n" );
	mDeprecatedFunction.clear();
}

MEDUSA_END;