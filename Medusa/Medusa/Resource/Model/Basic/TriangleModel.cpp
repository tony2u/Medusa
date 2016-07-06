// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "TriangleModel.h"
#include "Resource/ResourceNames.h"
#include "Resource/Effect/EffectFactory.h"
MEDUSA_BEGIN;


TriangleModel::TriangleModel(const FileIdRef& fileId, const Share<IMaterial>& material)
	:BaseSingleTextureModel(fileId,material)
{

}


TriangleModel::~TriangleModel(void)
{
}

MEDUSA_END;