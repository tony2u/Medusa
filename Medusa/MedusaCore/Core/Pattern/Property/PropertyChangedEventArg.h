// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Event/EventArg/IEventArg.h"

MEDUSA_BEGIN;
class PropertyChangedEventArg :public IEventArg
{
	MEDUSA_RTTI(PropertyChangedEventArg,IEventArg);
public:
	PropertyChangedEventArg(StringRef name) :mName(name) {}
	virtual ~PropertyChangedEventArg(void) {}
private:
	StringRef mName;
};

MEDUSA_END;