// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "Node/INode.h"

MEDUSA_BEGIN;

/*
sizof(Sprite)==988
*/



class Sprite :public INode
{
	MEDUSA_NODE(Sprite,INode);
public:
	using INode::INode;
	virtual ~Sprite(void);
	virtual bool Initialize() override;
};

MEDUSA_ENABLE_STATIC_CONSTRUCTOR(Sprite);


MEDUSA_END;
