// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "TestPreDeclares.h"
#include "Game/BaseFeatureLayer.h"

class ShapeFeatureLayer :public BaseFeatureLayer
{
	MEDUSA_DECLARE_LAYER(ShapeFeatureLayer);
public:
	ShapeFeatureLayer(StringRef name=StringRef::Empty,const IEventArg& e=IEventArg::Empty);
	virtual ~ShapeFeatureLayer(void);
};

