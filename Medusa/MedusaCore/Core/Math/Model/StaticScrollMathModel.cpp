// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "StaticScrollMathModel.h"

MEDUSA_BEGIN;


StaticScrollMathModel::StaticScrollMathModel(ScrollDirection direction /*= ScrollDirection::FreeFromCurrent*/)
	:IScrollMathModel(direction)
{

}

StaticScrollMathModel::~StaticScrollMathModel(void)
{

}



MEDUSA_END;
