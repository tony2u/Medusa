// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "TestPreDeclares.h"
#include "Game/BaseFeatureLayer.h"

class ComponentFeatureLayer :public BaseFeatureLayer
{
	MEDUSA_NODE(ComponentFeatureLayer, BaseFeatureLayer);
public:
	ComponentFeatureLayer(StringRef name=StringRef::Empty,const IEventArg& e=IEventArg::Empty);
	virtual ~ComponentFeatureLayer(void);
};

