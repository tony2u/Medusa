// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Resource/Model/IModelNode.h"
#include "Graphics/GraphicsTypes.h"
#include "Resource/Material/IMaterial.h"

MEDUSA_BEGIN;


class IMeshModelNode:public IModelNode
{
public:
	IMeshModelNode(StringRef name):IModelNode(name){}
	virtual ~IMeshModelNode(void){}
	virtual ModelNodeType Type() const{return ModelNodeType::Mesh;}

	virtual Share<const IMesh> BaseMeshPtr() const=0;
	virtual Share<IMesh> MutableBaseMeshPtr()=0;

	const Share<IMaterial>& Material() const { return mMaterial; }
	void SetMaterial(const Share<IMaterial>& val) { mMaterial = val; }
protected:
	Share<IMaterial> mMaterial;
	
};

MEDUSA_END;