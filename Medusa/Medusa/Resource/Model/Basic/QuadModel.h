// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Resource/Model/BaseSingleTextureModel.h"
#include "Resource/Material/IMaterial.h"
#include "Core/Geometry/Rect2.h"
#include "Resource/Model/Mesh/Fixed/TextureQuadMesh.h"
MEDUSA_BEGIN;

class QuadModel:public BaseSingleTextureModel<TextureQuadMesh>
{
public:
	QuadModel(const FileIdRef& fileId,IMaterial* material,const Rect2F& textureRect);
	virtual ~QuadModel(void);
public:
	Rect2F& MutableTextureRect() { return mTextureRect; }
	const Rect2F& TextureRect() const { return mTextureRect; }
	void SetTextureRect(const Rect2F& val);
	virtual bool Initialzie(ModelLoadingOptions loadingOptions=ModelLoadingOptions::None);

protected:
	Rect2F mTextureRect;
};

MEDUSA_END;