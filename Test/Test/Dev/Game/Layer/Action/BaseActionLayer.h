// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "TestPreDeclares.h"
#include "Game/BaseCaseLayer.h"


class BaseActionLayer :public BaseCaseLayer
{
	MEDUSA_NODE(BaseActionLayer, BaseCaseLayer);
public:
	BaseActionLayer(StringRef name = StringRef::Empty, const IEventArg& e = IEventArg::Empty);
	virtual ~BaseActionLayer(void);
	virtual bool Initialize()override;
	virtual void OnRestart() override;
	virtual void RestartSelfAction() {}
protected:
	INode* mSprite;
};

