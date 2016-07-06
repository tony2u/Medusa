// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "BaseFontModel.h"
#include "Core/String/StringParser.h"
#include "Core/Log/Log.h"
#include "Resource/Font/TextLayout/TextLayouter.h"
#include "Node/Sprite/Sprite.h"

MEDUSA_BEGIN;

BaseFontModel::BaseFontModel(const Share<IFont>& font,Alignment alignment/*=Alignment::LeftBottom*/,Size2U restrictSize/*=Size2U::Zero*/)
	:BaseMultipleModel(font->Name()),mFont(font),mAlignment(alignment),mColor(Color4F::White),mRestrictSize(restrictSize)
{
	
}


BaseFontModel::~BaseFontModel(void)
{
	mFont = nullptr;
	RemoveAllMeshes();
	mCachesMeshes.Clear();
}

bool BaseFontModel::Initialize(ModelLoadingOptions loadingOptions/*=ModelLoadingOptions::None*/)
{
	RETURN_FALSE_IF_FALSE(BaseMultipleModel::Initialize(loadingOptions));

	
	return true;
}



void BaseFontModel::ResetCachedMeshes()
{
	for (auto i : mCachesMeshes)
	{
		auto mesh=i.Value;
		mesh->Clear();
	}
}




MEDUSA_END;