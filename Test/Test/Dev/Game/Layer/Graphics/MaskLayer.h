// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "TestPreDeclares.h"
#include "Game/BaseCaseLayer.h"

class MaskLayer :public BaseCaseLayer
{
	MEDUSA_NODE(MaskLayer, BaseCaseLayer);
public:
	MaskLayer(StringRef name=StringRef::Empty,const IEventArg& e=IEventArg::Empty);
	virtual ~MaskLayer(void);
	virtual bool Initialize()override;
	void OnSrcChanged(INode* sender, TapGestureEventArg& e);
	void OnDestChanged(INode* sender, TapGestureEventArg& e);

protected:
	Sprite* mBackSrite;
	Sprite* mFrontSprite;

};

MEDUSA_ENABLE_STATIC_CONSTRUCTOR(MaskLayer);
