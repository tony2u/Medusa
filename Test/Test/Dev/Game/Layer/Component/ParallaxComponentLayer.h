// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "TestPreDeclares.h"
#include "Game/BaseCaseLayer.h"


class ParallaxComponentLayer :public BaseCaseLayer
{
	MEDUSA_NODE(ParallaxComponentLayer,BaseCaseLayer);
public:
	ParallaxComponentLayer(StringRef name=StringRef::Empty,const IEventArg& e=IEventArg::Empty);
	virtual ~ParallaxComponentLayer(void);
	virtual bool Initialize()override;
	virtual void OnRestart()override;
private:
	ParallaxComponent* mComponent;
	Sprite* mMainSprite;
	const static uint mChildCount = 5;
};

MEDUSA_ENABLE_STATIC_CONSTRUCTOR(ParallaxComponentLayer);
