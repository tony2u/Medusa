// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "ISirenFunction.h"

MEDUSA_BEGIN;

class SirenAttributeFunction:public ISirenFunction
{
public:
	SirenAttributeFunction();
	virtual ~SirenAttributeFunction(void);
public:
	virtual bool Execute(SirenAssembly& assembly)const override;
protected:

};

MEDUSA_END;
