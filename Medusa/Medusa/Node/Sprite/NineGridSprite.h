// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "Node/INode.h"

MEDUSA_BEGIN;

class NineGridSprite :public INode
{
	
	MEDUSA_DECLARE_RTTI;
public:
	NineGridSprite(StringRef name=StringRef::Empty);
	virtual ~NineGridSprite(void);
	virtual bool Initialize() override;

protected:
	virtual void OnMoveableDirty(MoveableChangedFlags changedFlags) override;
	virtual void OnUpdateMesh();
protected:
	
};

MEDUSA_END;
