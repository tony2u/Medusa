// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "TestPreDeclares.h"
#include "Game/BaseCaseLayer.h"


class ParallaxScrollComponentLayer :public BaseCaseLayer
{
	MEDUSA_NODE(ParallaxScrollComponentLayer, BaseCaseLayer);
public:
	ParallaxScrollComponentLayer(StringRef name=StringRef::Empty,const IEventArg& e=IEventArg::Empty);
	virtual ~ParallaxScrollComponentLayer(void);
	virtual bool Initialize()override;
	virtual void OnRestart()override;
	void OnKeyDown(INode* sender, KeyDownEventArg& e);
private:
	ParallaxScrollComponent* mComponent;
	const static uint mChildCount = 5;
	
};

