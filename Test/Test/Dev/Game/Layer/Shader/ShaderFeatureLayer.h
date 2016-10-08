// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "TestPreDeclares.h"
#include "Game/BaseFeatureLayer.h"

class ShaderFeatureLayer :public BaseFeatureLayer
{
	MEDUSA_NODE(ShaderFeatureLayer,BaseFeatureLayer);
public:
	ShaderFeatureLayer(StringRef name=StringRef::Empty,const IEventArg& e=IEventArg::Empty);
	virtual ~ShaderFeatureLayer(void);
};

MEDUSA_ENABLE_STATIC_CONSTRUCTOR(ShaderFeatureLayer);
