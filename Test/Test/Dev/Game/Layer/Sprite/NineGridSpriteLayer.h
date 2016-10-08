// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "TestPreDeclares.h"
#include "Game/BaseCaseLayer.h"

class NineGridSpriteLayer :public BaseCaseLayer
{
	MEDUSA_NODE(NineGridSpriteLayer, BaseCaseLayer);
public:
	NineGridSpriteLayer(StringRef name=StringRef::Empty,const IEventArg& e=IEventArg::Empty);
	virtual ~NineGridSpriteLayer(void);
	virtual bool Initialize()override;
};

MEDUSA_ENABLE_STATIC_CONSTRUCTOR(NineGridSpriteLayer);
