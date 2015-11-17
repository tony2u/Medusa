// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "SkeletonIKModel.h"

MEDUSA_BEGIN;



SkeletonIKModel::SkeletonIKModel(const StringRef& name)
	:mName(name)
{

}


SkeletonIKModel::~SkeletonIKModel(void)
{
	
}

void SkeletonIKModel::AddBone(SkeletonBoneModel* bone)
{
	mBones.Add(bone);
}


MEDUSA_END;