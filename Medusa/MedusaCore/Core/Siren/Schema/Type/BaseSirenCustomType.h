// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "ISirenType.h"

MEDUSA_BEGIN;

class BaseSirenCustomType:public ISirenType
{
public:
	BaseSirenCustomType();
	virtual ~BaseSirenCustomType(void);
public:
	virtual bool IsBuildIn()const override { return false; }
	virtual bool IsTemplate()const override { return false; }

	virtual bool AddAttribute(StringRef name, StringRef val) { return false; }
	virtual bool SetAttribute(const StringRef& val) { return false; }

	BaseSirenCustomType* ParentType() const { return mParentType; }
	void SetParentType(BaseSirenCustomType* val);

	virtual bool Merge(const BaseSirenCustomType& other) = 0;

	virtual bool IsGenerate()const = 0;
	virtual StringRef Directory()const { return StringRef::Empty; }

protected:
	BaseSirenCustomType* mParentType=nullptr;
};

MEDUSA_END;
