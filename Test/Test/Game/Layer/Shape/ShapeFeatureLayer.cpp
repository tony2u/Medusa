// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "TestPreCompiled.h"
#include "ShapeFeatureLayer.h"
#include "RectangleShapeLayer.h"

ShapeFeatureLayer::ShapeFeatureLayer(StringRef name/*=StringRef::Empty*/, const IEventArg& e/*=IEventArg::Empty*/) :BaseFeatureLayer(name, e)
{
	Register<RectangleShapeLayer>();


}

ShapeFeatureLayer::~ShapeFeatureLayer(void)
{
}


MEDUSA_IMPLEMENT_LAYER(ShapeFeatureLayer, BaseFeatureLayer, StringRef::Empty);

