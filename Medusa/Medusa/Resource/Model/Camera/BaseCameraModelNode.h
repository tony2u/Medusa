// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once


#include "Resource/Model/IModelNode.h"
MEDUSA_BEGIN;

class BaseCameraModelNode:public IModelNode
{
public:
	BaseCameraModelNode(StringRef name);
	virtual ~BaseCameraModelNode(void);
	virtual ModelNodeType Type() const{return ModelNodeType::Camera;}
	virtual Camera* CreateCamera()const{return nullptr;}
};

MEDUSA_END;