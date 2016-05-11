// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "NormalLayer.h"
#include "LayerFactory.h"

MEDUSA_BEGIN;

NormalLayer::NormalLayer(StringRef name/*=StringRef::Empty*/, const IEventArg& e/*=IEventArg::Empty*/)
	:ILayer(name, e)
{
	
}

NormalLayer::~NormalLayer(void)
{
}




MEDUSA_IMPLEMENT_LAYER(NormalLayer, ILayer, StringRef::Empty, StringRef::Empty);

MEDUSA_END;
