// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Resource/Model/IModelNode.h"
MEDUSA_BEGIN;
class VirtualModelNode:public IModelNode
{
public:
	VirtualModelNode(StringRef name);
	virtual ~VirtualModelNode(void);
public:
	virtual ModelNodeType Type() const{return ModelNodeType::Virtual;}
};

MEDUSA_END;