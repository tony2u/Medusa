// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "TestPreDeclares.h"
#include "Game/BaseFeatureLayer.h"

class PerformanceFeatureLayer :public BaseFeatureLayer
{
	MEDUSA_NODE(PerformanceFeatureLayer,BaseFeatureLayer);
public:
	PerformanceFeatureLayer(StringRef name=StringRef::Empty,const IEventArg& e=IEventArg::Empty);
	virtual ~PerformanceFeatureLayer(void);
};

