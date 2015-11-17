// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaPreDeclares.h"
#include "Core/Pattern/IInitializable.h"

MEDUSA_BEGIN;

class IResourceManageable :public IInitializable
{
public:
	virtual void Shrink() {}
	virtual void Clear() {}
	virtual void ReleaseCache() {}
};

MEDUSA_END;