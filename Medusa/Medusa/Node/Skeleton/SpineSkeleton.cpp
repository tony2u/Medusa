// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "SpineSkeleton.h"
#include "Core/Log/Log.h"
#include "Resource/Skeleton/SpineSkeletonModel.h"
#include "Node/NodeFactory.h"
MEDUSA_BEGIN;

SpineSkeleton::SpineSkeleton(StringRef name, const Share<SpineSkeletonModel>& model)
	:ISkeleton(name, model)
{
	
}


SpineSkeleton::SpineSkeleton(const StringRef& name /*= StringRef::Empty*/, const IEventArg& e /*= IEventArg::Empty*/)
	:ISkeleton(name, e)
{

}

SpineSkeleton::~SpineSkeleton()
{
	
}

MEDUSA_IMPLEMENT_NODE(SpineSkeleton);

MEDUSA_END;
