// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "TestPreDeclares.h"
#include "Game/BaseFeatureLayer.h"

class ThreeDFeatureLayer :public BaseFeatureLayer
{
	MEDUSA_NODE(ThreeDFeatureLayer, BaseFeatureLayer);
public:
	ThreeDFeatureLayer(StringRef name=StringRef::Empty,const IEventArg& e=IEventArg::Empty);
	virtual ~ThreeDFeatureLayer(void);
};

MEDUSA_ENABLE_STATIC_CONSTRUCTOR(ThreeDFeatureLayer);
