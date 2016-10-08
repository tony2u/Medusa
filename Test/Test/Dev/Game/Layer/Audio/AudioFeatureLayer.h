// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "TestPreDeclares.h"
#include "Game/BaseFeatureLayer.h"


class AudioFeatureLayer :public BaseFeatureLayer
{
	MEDUSA_NODE(AudioFeatureLayer, BaseFeatureLayer);
public:
	AudioFeatureLayer(StringRef name=StringRef::Empty,const IEventArg& e=IEventArg::Empty);
	virtual ~AudioFeatureLayer(void);
};

MEDUSA_ENABLE_STATIC_CONSTRUCTOR(AudioFeatureLayer);
