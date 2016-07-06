// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "TestPreDeclares.h"
#include "Game/BaseCaseLayer.h"


class TTFLayer :public BaseCaseLayer
{
	MEDUSA_NODE(TTFLayer, BaseCaseLayer);
public:
	TTFLayer(StringRef name=StringRef::Empty,const IEventArg& e=IEventArg::Empty);
	virtual ~TTFLayer(void);
	virtual bool Initialize()override;


};

