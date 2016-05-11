// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "ILayer.h"
#include "Core/Command/EventArg/IEventArg.h"
#include "Node/Layer/LayerFactory.h"
#include "Graphics/ResolutionAdapter.h"


MEDUSA_BEGIN;

ILayer::ILayer(StringRef name/*=StringRef::Empty*/, const IEventArg& e/*=IEventArg::Empty*/) :INode(name)
{
	mSize = ResolutionAdapter::Instance().WinSize();
	SetStretch(Stretch::Fill);
	SetSizeToContent(SizeToContent::WidthAndHeight);
	Start();
}


ILayer::~ILayer(void)
{
}

bool ILayer::Initialize()
{
	return true;
}


MEDUSA_IMPLEMENT_LAYER(ILayer, INode, StringRef::Empty, StringRef::Empty);


MEDUSA_END;
