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

BaseFontModel::BaseFontModel( IFont* font,Alignment alignment/*=Alignment::LeftBottom*/,Size2U restrictSize/*=Size2U::Zero*/)
	:BaseMultipleModel(font->Name()),mFont(font),mAlignment(alignment),mColor(Color4F::White),mRestrictSize(restrictSize)
{
	SAFE_RETAIN(mFont);
}


BaseFontModel::~BaseFontModel(void)
{
	SAFE_RELEASE(mFont);
	RemoveAllMeshes();
	SAFE_DELETE_DICTIONARY_VALUE(mCachesMeshes);
}

bool BaseFontModel::Initialzie(ModelLoadingOptions loadingOptions/*=ModelLoadingOptions::None*/)
{
	RETURN_FALSE_IF_FALSE(BaseMultipleModel::Initialzie(loadingOptions));

	
	return true;
}



void BaseFontModel::ResetCachedMeshes()
{
	FOR_EACH_COLLECTION(i,mCachesMeshes)
	{
		IMesh* mesh=i->Value;
		mesh->Clear();
	}
}

INode* BaseFontModel::CreateCloneInstance()
{
	return nullptr;
}

INode* BaseFontModel::CreateReferenceInstance()
{
	return nullptr;
}

MEDUSA_END;