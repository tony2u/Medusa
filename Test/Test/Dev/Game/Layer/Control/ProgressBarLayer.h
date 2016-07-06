// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "TestPreDeclares.h"
#include "Game/BaseCaseLayer.h"

class ProgressBarLayer :public BaseCaseLayer
{
	MEDUSA_NODE(ProgressBarLayer, BaseCaseLayer);
public:
	ProgressBarLayer(StringRef name=StringRef::Empty,const IEventArg& e=IEventArg::Empty);
	virtual ~ProgressBarLayer(void);
	virtual bool Initialize()override;
};

