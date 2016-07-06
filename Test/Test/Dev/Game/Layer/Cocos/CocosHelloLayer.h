// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "TestPreDeclares.h"
#include "Game/BaseCaseLayer.h"


class CocosHelloLayer :public BaseCaseLayer
{
	MEDUSA_NODE_BIND(CocosHelloLayer,BaseCaseLayer, "MainLayer.csb", "");
public:
	CocosHelloLayer(StringRef name=StringRef::Empty,const IEventArg& e=IEventArg::Empty);
	virtual ~CocosHelloLayer(void);
	virtual bool Initialize()override;
	virtual bool OnEnter()override;

protected:
	bool OnStart(INode* sender,IEventArg* e);

};

