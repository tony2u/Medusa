// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "Core/Assertion/CommonAssert.h"

MEDUSA_BEGIN;

template<typename T,typename TPtr>
struct IEnumerator
{

public:
	virtual ~IEnumerator(){}

	virtual T Current()=0;
	virtual TPtr CurrentPtr() = 0;


	virtual bool MoveNext()=0;
	virtual void Reset()=0;
};


MEDUSA_END;