// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "TestPreDeclares.h"
#include "Game/BaseCaseLayer.h"


class POD3DLayer :public BaseCaseLayer
{
	MEDUSA_DECLARE_LAYER(POD3DLayer);
public:
	POD3DLayer(StringRef name=StringRef::Empty,const IEventArg& e=IEventArg::Empty);
	virtual ~POD3DLayer(void);
	virtual bool Initialize()override;
};

