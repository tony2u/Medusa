// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "IPackage.h"
MEDUSA_BEGIN;


class ZipPackage :public IPackage
{
public:
	using IPackage::IPackage;
	virtual ~ZipPackage(void);

	virtual PackageType Type()const override{ return PackageType::Zip; }
};

MEDUSA_END;
