// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#ifdef MEDUSA_SCRIPT
#include "MedusaPreDeclares.h"
#include "Core/Pattern/ISettings.h"
MEDUSA_BEGIN;

class IJsonSettings :public ISettings
{
public:
	virtual void* GetAddress(const StringRef& name)const;
	
};


MEDUSA_END;

#endif