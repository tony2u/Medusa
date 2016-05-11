// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Resource/Model/BaseSingleModel.h"
#include "Geometry/Color4.h"

MEDUSA_BEGIN;

template<typename TMesh>
class BaseSingleTextureModel:public BaseSingleModel<TMesh,IMaterial>
{
public:
	BaseSingleTextureModel(const FileIdRef& fileId,IMaterial* material):BaseSingleModel<TMesh,IMaterial>(fileId),mColor(Color4F::White){}
	virtual ~BaseSingleTextureModel(void){}

protected:
	Color4F mColor;
};

MEDUSA_END;