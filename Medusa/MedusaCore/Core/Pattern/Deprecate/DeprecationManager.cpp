// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "DeprecationManager.h"
#include "Core/String/HeapString.h"
#include "Core/String/StackString.h"
#include "Core/String/StringParser.h"


MEDUSA_BEGIN;


void DeprecationManager::AddDeprecateFunction( const char* funcName,const char* comment,const char* fileName,const char* lineName )
{
	mDeprecatedFunction[funcName]=comment;
	//char txt[1024];
	HeapString str;

	str.Format("==>Deprecated:{}\t{}\t{}\t{}\n",funcName,comment,fileName,lineName);
	MEDUSA_TRACE(str.c_str());
}

DeprecationManager::~DeprecationManager()
{
	MEDUSA_TRACE( "*************************************************************\n" );
	MEDUSA_TRACE( "WARNING. You are using the following deprecated functions:\n" );

	HeapString str;
	FOR_EACH_COLLECTION_STL(i,mDeprecatedFunction)
	{
		const char* funcName=i->first;
		const char* comment=i->second;
		str.Format("==>Deprecated:{}\t{}\n",funcName,comment);
		MEDUSA_TRACE (str.c_str());
	}
	MEDUSA_TRACE( "*************************************************************\n" );
	mDeprecatedFunction.clear();
}

MEDUSA_END;