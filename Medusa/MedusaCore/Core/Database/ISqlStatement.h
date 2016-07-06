// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#ifdef MEDUSA_SQL
#include "Core/String/HeapString.h"
#include "SqlDefines.h"
#include "Core/Pattern/ISharableWithName.h"

MEDUSA_BEGIN;


class ISqlStatement :public ISharableThreadSafeWithName
{
public:
	ISqlStatement(const StringRef& statement, const StringRef& name = StringRef::Empty);
	virtual ~ISqlStatement(void);
public:
	virtual bool Prepare() = 0;
	StringRef Statement()const { return mStatement; }

	uint ParamterCount()const { return mParamterCount; }
protected:
	HeapString mStatement;
	uint mParamterCount = 0;
};

MEDUSA_END;
#endif