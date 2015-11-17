// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "BaseSkeletonTextureAttachmentModel.h"


MEDUSA_BEGIN;


BaseSkeletonTextureAttachmentModel::BaseSkeletonTextureAttachmentModel(const StringRef& name, TextureAtlasRegion* region)
	:ISkeletonAttachmentModel(name),
	mRegion(region),
	mSize(Size3F::Zero),
	mColor(Color4F::White)
{
	

}


BaseSkeletonTextureAttachmentModel::~BaseSkeletonTextureAttachmentModel(void)
{

}



MEDUSA_END;