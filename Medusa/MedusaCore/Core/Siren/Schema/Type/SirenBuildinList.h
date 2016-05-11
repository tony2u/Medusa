// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "SirenBuildinType.h"
MEDUSA_BEGIN;


class SirenBuildinList:public SirenBuildinType
{
public:
	using SirenBuildinType::SirenBuildinType;
	virtual ~SirenBuildinList(void);
public:
	virtual SirenBuildinList* Clone() const override { return (SirenBuildinList*)this; }	//return self

	virtual bool IsTemplate()const override { return true; }
	virtual SirenTypeId Id()const override { return SirenTypeId::List; }

protected:
	HeapString mKeyName;
};

MEDUSA_END;
