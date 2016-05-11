// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/String/HeapString.h"

MEDUSA_BEGIN;

class ISirenFunction
{
public:
	ISirenFunction(const StringRef& name=StringRef::Empty);
	virtual ~ISirenFunction(void);

	virtual bool Parse(SirenAssembly& assembly, StringRef& refProto);;
	virtual bool Execute(SirenAssembly& assembly)const = 0;
protected:
	HeapString mName;
	List<HeapString> mArguments;

};

MEDUSA_END;
