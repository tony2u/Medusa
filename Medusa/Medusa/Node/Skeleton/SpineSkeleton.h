// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "ISkeleton.h"

MEDUSA_BEGIN;

class SpineSkeleton :public ISkeleton
{
public:
	SpineSkeleton(StringRef name,SpineSkeletonModel* model);
	virtual ~SpineSkeleton();
	

};

MEDUSA_END;
