// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "IScrollMathModel.h"

MEDUSA_BEGIN;

class StaticScrollMathModel:public IScrollMathModel
{
public:
	StaticScrollMathModel(ScrollDirection direction = ScrollDirection::FreeFromCurrent);
	virtual ~StaticScrollMathModel(void);
};

MEDUSA_END;
