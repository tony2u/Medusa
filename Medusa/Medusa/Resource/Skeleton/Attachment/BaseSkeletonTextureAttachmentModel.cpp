// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "BaseSkeletonTextureAttachmentModel.h"
#include "Resource/TextureAtlas/TextureAtlasPage.h"
#include "Resource/TextureAtlas/TextureAtlas.h"
#include "Resource/TextureAtlas/TextureAtlasRegion.h"




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
	if (mRegion!=nullptr)
	{
		mRegion->Page()->Atlas()->Release();
	}
}



MEDUSA_END;