// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "TriangleModel.h"
#include "Resource/ResourceNames.h"
#include "Resource/Effect/EffectFactory.h"
MEDUSA_BEGIN;


TriangleModel::TriangleModel(const FileIdRef& fileId,IMaterial* material)
	:BaseSingleTextureModel(fileId,material)
{

	IEffect* effect=EffectFactory::Instance().CreateSinglePassDefault(RenderPassNames::Texture);
	mMeshModelNode.MutableMesh().SetEffect(effect);
	mMeshModelNode.MutableMesh().SetMaterial(material);
}


TriangleModel::~TriangleModel(void)
{
}

MEDUSA_END;