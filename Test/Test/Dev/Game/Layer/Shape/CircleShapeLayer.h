// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "TestPreDeclares.h"
#include "Game/BaseCaseLayer.h"


class CircleShapeLayer :public BaseCaseLayer
{
	MEDUSA_DECLARE_LAYER(CircleShapeLayer);
public:
	CircleShapeLayer(StringRef name=StringRef::Empty,const IEventArg& e=IEventArg::Empty);
	virtual ~CircleShapeLayer(void);
	virtual bool Initialize()override;
};

