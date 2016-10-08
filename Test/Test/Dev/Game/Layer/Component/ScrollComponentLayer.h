// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "TestPreDeclares.h"
#include "Game/BaseCaseLayer.h"


class ScrollComponentLayer :public BaseCaseLayer
{
	MEDUSA_NODE(ScrollComponentLayer, BaseCaseLayer);
public:
	ScrollComponentLayer(StringRef name=StringRef::Empty,const IEventArg& e=IEventArg::Empty);
	virtual ~ScrollComponentLayer(void);
	virtual bool Initialize()override;
	virtual void OnRestart()override;
private:
	ScrollComponent* mComponent;
	const static uint mChildCount = 3;

};

MEDUSA_ENABLE_STATIC_CONSTRUCTOR(ScrollComponentLayer);
