// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "Node/INode.h"

MEDUSA_BEGIN;

class IShape :public INode
{
	MEDUSA_RTTI(IShape,INode);
public:
	using INode::INode;
	virtual ~IShape(void);
	virtual bool Initialize()override;
};

MEDUSA_END;
