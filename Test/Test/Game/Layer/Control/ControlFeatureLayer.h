// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "TestPreDeclares.h"
#include "Game/BaseFeatureLayer.h"

class ControlFeatureLayer :public BaseFeatureLayer
{
	MEDUSA_DECLARE_LAYER(ControlFeatureLayer);
public:
	ControlFeatureLayer(StringRef name=StringRef::Empty,const IEventArg& e=IEventArg::Empty);
	virtual ~ControlFeatureLayer(void);
};

