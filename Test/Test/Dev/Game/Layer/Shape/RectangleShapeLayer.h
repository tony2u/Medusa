// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "TestPreDeclares.h"
#include "Game/BaseCaseLayer.h"


class RectangleShapeLayer :public BaseCaseLayer
{
	MEDUSA_DECLARE_LAYER(RectangleShapeLayer);
public:
	RectangleShapeLayer(StringRef name=StringRef::Empty,const IEventArg& e=IEventArg::Empty);
	virtual ~RectangleShapeLayer(void);
	virtual bool Initialize()override;
};

