// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "TestPreDeclares.h"
#include "Game/BaseCaseLayer.h"

class AtlasSpriteLayer :public BaseCaseLayer
{
	MEDUSA_NODE(AtlasSpriteLayer, BaseCaseLayer);
public:
	AtlasSpriteLayer(StringRef name=StringRef::Empty,const IEventArg& e=IEventArg::Empty);
	virtual ~AtlasSpriteLayer(void);
	virtual bool Initialize()override;
};

MEDUSA_ENABLE_STATIC_CONSTRUCTOR(AtlasSpriteLayer);
