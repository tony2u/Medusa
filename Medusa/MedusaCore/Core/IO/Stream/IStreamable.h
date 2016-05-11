// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaCorePreDeclares.h"

MEDUSA_BEGIN;

class IStreamable
{
public:
	virtual ~IStreamable() = default;
	virtual bool LoadFrom(IStream& stream) = 0;
	virtual bool SaveTo(IStream& stream)const = 0;
};

MEDUSA_END;