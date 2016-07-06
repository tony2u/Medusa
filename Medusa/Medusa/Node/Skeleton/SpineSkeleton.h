// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "ISkeleton.h"

MEDUSA_BEGIN;

class SpineSkeleton :public ISkeleton
{

	MEDUSA_NODE(SpineSkeleton, ISkeleton);
public:
	SpineSkeleton(const StringRef& name = StringRef::Empty, const IEventArg& e = IEventArg::Empty);

	SpineSkeleton(StringRef name,const Share<SpineSkeletonModel>& model);
	virtual ~SpineSkeleton();
	

};

MEDUSA_END;
