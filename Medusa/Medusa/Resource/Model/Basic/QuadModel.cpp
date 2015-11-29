// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "QuadModel.h"
#include "Resource/ResourceNames.h"
#include "Resource/Material/IMaterial.h"
#include "Resource/Effect/EffectFactory.h"

MEDUSA_BEGIN;

QuadModel::QuadModel( const FileIdRef& fileId,IMaterial* material,const Rect2F& textureRect )
	:BaseSingleTextureModel(fileId,material),mTextureRect(textureRect)
{
	
}


QuadModel::~QuadModel(void)
{
	
}

bool QuadModel::Initialzie(ModelLoadingOptions loadingOptions/*=ModelLoadingOptions::None*/)
{
	RETURN_FALSE_IF_FALSE(BaseSingleTextureModel::Initialzie(loadingOptions));
	
	//const Size2U& textureSize= mMeshModelNode.Mesh().Material()->FirstTexture()->Size();

	//mMeshModelNode.MutableMesh().Initialize(textureSize, mTextureRect, mColor);

	//mMesh->AppendNormal(Point3F::OneZ,4);

	return true;
}

void QuadModel::SetTextureRect( const Rect2F& val )
{
	mTextureRect = val;
}




MEDUSA_END;