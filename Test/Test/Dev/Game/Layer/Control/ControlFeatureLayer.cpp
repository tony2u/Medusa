// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "TestPreCompiled.h"
#include "ControlFeatureLayer.h"
#include "TextureButtonLayer.h"
#include "NodeButtonLayer.h"

#include "ProgressBarLayer.h"
#include "ListBoxLayer.h"
#include "TableBoxLayer.h"

#include "EditBoxLayer.h"


ControlFeatureLayer::ControlFeatureLayer(StringRef name/*=StringRef::Empty*/, const IEventArg& e/*=IEventArg::Empty*/) :BaseFeatureLayer(name, e)
{
	Register<TextureButtonLayer>();
	Register<NodeButtonLayer>();

	Register<ProgressBarLayer>();
	Register<ListBoxLayer>();
	Register<TableBoxLayer>();
	Register<EditBoxLayer>();

}

ControlFeatureLayer::~ControlFeatureLayer(void)
{
}


MEDUSA_IMPLEMENT_NODE(ControlFeatureLayer);

