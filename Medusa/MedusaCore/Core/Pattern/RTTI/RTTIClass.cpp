// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"

#include "Core/Pattern/RTTI/RTTIClass.h"


MEDUSA_BEGIN;

int RTTIClass::GetInheritDistance(const RTTIClass* baseClass) const
{
	RETURN_ZERO_IF_EQUAL(this, baseClass);
	const RTTIClass* tryBaseClass = mBaseClass;
	int distance = 1;
	while (tryBaseClass != nullptr&&tryBaseClass != baseClass)
	{
		tryBaseClass = tryBaseClass->BaseClass();
		++distance;
	}

	return tryBaseClass != nullptr ? distance : -1;
}

int RTTIClass::GetInheritDistance(const RTTIClass& baseClass) const
{
	return GetInheritDistance(&baseClass);
}

MEDUSA_END;