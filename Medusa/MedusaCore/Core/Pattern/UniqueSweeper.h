// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Pattern/Sweeper.h"

MEDUSA_BEGIN;


template<typename T>
class UniqueSweeper :public Sweeper<T*>
{
protected:
	virtual void OnRelease(T* item)const override
	{
		delete item;
	}

};

MEDUSA_END;
