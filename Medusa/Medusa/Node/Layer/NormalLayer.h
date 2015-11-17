// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "ILayer.h"

MEDUSA_BEGIN;
class NormalLayer :public ILayer
{
	MEDUSA_DECLARE_LAYER(NormalLayer);
public:
	NormalLayer(StringRef name = StringRef::Empty, const IEventArg& e = IEventArg::Empty);
	virtual ~NormalLayer(void);

};

MEDUSA_END;
