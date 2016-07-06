// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "TestPreDeclares.h"
#include "Game/BaseCaseLayer.h"

class SingleTextureFrameAnimationLayer :public BaseCaseLayer
{
	MEDUSA_NODE(SingleTextureFrameAnimationLayer,BaseCaseLayer);
public:
	SingleTextureFrameAnimationLayer(StringRef name=StringRef::Empty,const IEventArg& e=IEventArg::Empty);
	virtual ~SingleTextureFrameAnimationLayer(void);
	virtual bool Initialize()override;
};

