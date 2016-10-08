// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "ILayer.h"
#include "Core/Event/EventArg/IEventArg.h"
#include "Graphics/ResolutionAdapter.h"
#include "Node/NodeFactory.h"
#include "Node/Input/InputDispatcher.h"

MEDUSA_BEGIN;

ILayer::ILayer(StringRef name/*=StringRef::Empty*/, const IEventArg& e/*=IEventArg::Empty*/) :INode(name)
{
	mSize = ResolutionAdapter::Instance().WinSize();
	//SetStretch(ResolutionAdapter::Instance().GetStretch());
	//SetSizeToContent(SizeToContent::WidthAndHeight);
	Start();
	MutableInput().Enable(true);	//default enable input

}


ILayer::~ILayer(void)
{
}

bool ILayer::Initialize()
{
	return true;
}


MEDUSA_END;
