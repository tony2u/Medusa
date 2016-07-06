// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "IStrokeTemplate.h"

MEDUSA_BEGIN;


IStrokeTemplate::IStrokeTemplate(const StringRef& name /*= StringRef::Empty*/)
	:mName(name)
{

}

IStrokeTemplate::IStrokeTemplate(HeapString&& name)
	: mName(name)
{

}

MEDUSA_END;

