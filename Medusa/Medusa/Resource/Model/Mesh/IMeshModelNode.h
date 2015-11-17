// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Resource/Model/IModelNode.h"
#include "Graphics/GraphicsTypes.h"

MEDUSA_BEGIN;


class IMeshModelNode:public IModelNode
{
public:
	IMeshModelNode(StringRef name):IModelNode(name){}
	virtual ~IMeshModelNode(void){}
	virtual ModelNodeType Type() const{return ModelNodeType::Mesh;}

	virtual const IMesh* BaseMeshPtr() const=0;
	virtual IMesh* MutableBaseMeshPtr()=0;

};

MEDUSA_END;