// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Resource/Model/IModelNode.h"
#include "Graphics/GraphicsTypes.h"

MEDUSA_BEGIN;



class BaseLightModelNode:public IModelNode
{
public:
	BaseLightModelNode(StringRef name);
	virtual ~BaseLightModelNode(void);
	virtual ModelNodeType Type() const{return ModelNodeType::Light;}
	virtual GraphicsLightType LightType() const=0;
	virtual ILight* CreateLight()const{return nullptr;}
};

MEDUSA_END;