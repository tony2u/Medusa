// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "SkeletonSlotModel.h"

MEDUSA_BEGIN;



SkeletonSlotModel::SkeletonSlotModel(const StringRef& name)
	:mName(name), 
	mColor(Color4F::White)
{

}


SkeletonSlotModel::~SkeletonSlotModel(void)
{
	
}



MEDUSA_END;