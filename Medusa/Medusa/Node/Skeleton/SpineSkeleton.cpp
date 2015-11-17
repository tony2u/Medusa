// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "SpineSkeleton.h"
#include "Core/Log/Log.h"
#include "Resource/Skeleton/SpineSkeletonModel.h"

MEDUSA_BEGIN;

SpineSkeleton::SpineSkeleton(StringRef name, SpineSkeletonModel* model)
	:ISkeleton(name, model)
{
	
}


SpineSkeleton::~SpineSkeleton()
{
	
}



MEDUSA_END;
