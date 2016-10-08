// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "TestPreDeclares.h"
#include "Game/Layer/Action/BaseActionLayer.h"


class MoveToActionLayer :public BaseActionLayer
{
	MEDUSA_NODE(MoveToActionLayer,BaseActionLayer);
public:
	MoveToActionLayer(StringRef name=StringRef::Empty,const IEventArg& e=IEventArg::Empty);
	virtual ~MoveToActionLayer(void);
	virtual void RestartSelfAction()override;
};

MEDUSA_ENABLE_STATIC_CONSTRUCTOR(MoveToActionLayer);
