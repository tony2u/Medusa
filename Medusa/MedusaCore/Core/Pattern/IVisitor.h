// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaCorePreDeclares.h"

MEDUSA_BEGIN;

template<typename T>
class IVisitor
{
public:
	virtual bool Visit(T) = 0;
};

MEDUSA_END;