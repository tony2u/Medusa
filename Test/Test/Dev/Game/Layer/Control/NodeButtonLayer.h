// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "TestPreDeclares.h"
#include "Game/BaseCaseLayer.h"

class NodeButtonLayer :public BaseCaseLayer
{
	MEDUSA_NODE(NodeButtonLayer, BaseCaseLayer);
public:
	NodeButtonLayer(StringRef name=StringRef::Empty,const IEventArg& e=IEventArg::Empty);
	virtual ~NodeButtonLayer(void);
	virtual bool Initialize()override;
private:
	void OnTap(INode* sender,TapGestureEventArg& e);

};

MEDUSA_ENABLE_STATIC_CONSTRUCTOR(NodeButtonLayer);
