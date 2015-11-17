// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Resource/Model/BaseSingleTextureModel.h"
#include "Resource/Model/Mesh/Fixed/TextureTriangleMesh.h"
#include "Resource/Material/IMaterial.h"

MEDUSA_BEGIN;

class TriangleModel:public BaseSingleTextureModel<TextureTriangleMesh>
{
public:
	TriangleModel(const FileIdRef& fileId,IMaterial* material);
	virtual ~TriangleModel(void);

};

MEDUSA_END;