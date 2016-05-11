// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "SirenBuildinType.h"
MEDUSA_BEGIN;


class SirenBuildinDictionary:public SirenBuildinType
{
public:
	using SirenBuildinType::SirenBuildinType;
	virtual ~SirenBuildinDictionary(void);
public:
	virtual SirenBuildinDictionary* Clone() const override { return (SirenBuildinDictionary*)this; }	//return self

	virtual bool IsTemplate()const override { return true; }
	virtual SirenTypeId Id()const override { return SirenTypeId::Dictionary; }

protected:
	HeapString mKeyName;
	HeapString mValueName;

};

MEDUSA_END;
