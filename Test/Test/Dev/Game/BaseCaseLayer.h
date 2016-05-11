// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "TestPreDeclares.h"
#include "Node/Layer/ILayer.h"

class BaseCaseLayer :public ILayer
{
	MEDUSA_DECLARE_LAYER(BaseCaseLayer);
public:
	BaseCaseLayer(StringRef name = StringRef::Empty, const IEventArg& e = IEventArg::Empty);
	virtual ~BaseCaseLayer(void);
	virtual bool Initialize()override;
	virtual void OnRestart() {}

};

