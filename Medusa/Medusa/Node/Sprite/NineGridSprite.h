// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "Node/INode.h"

MEDUSA_BEGIN;

class NineGridSprite :public INode
{
	MEDUSA_NODE(NineGridSprite,INode);
public:
	NineGridSprite(StringRef name=StringRef::Empty, const IEventArg& e = IEventArg::Empty);
	virtual ~NineGridSprite(void);
	virtual bool Initialize() override;

	const ThicknessF& TexturePadding() const { return mTexturePadding; }
	void SetTexturePadding(const ThicknessF& val) { mTexturePadding = val; }

	bool IsNineGridEnabled() const { return mNineGridEnabled; }
	void EnableNineGrid(bool val);
protected:
	virtual void OnMoveableDirty(MoveableChangedFlags changedFlags) override;
	virtual void OnUpdateMesh();

protected:
	ThicknessF mTexturePadding;
	bool mNineGridEnabled=true;
	
};

MEDUSA_ENABLE_STATIC_CONSTRUCTOR(NineGridSprite);


MEDUSA_END;
