// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"

MEDUSA_BEGIN;


class IParticle
{
public:
	IParticle();
	virtual ~IParticle(void);
	virtual bool Initialize();
protected:
};

MEDUSA_END;
