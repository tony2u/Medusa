// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "TestPreCompiled.h"
#include "TMXMapLayer.h"


TMXMapLayer::TMXMapLayer(StringRef name/*=StringRef::Empty*/, const IEventArg& e/*=IEventArg::Empty*/) :BaseCaseLayer(name, e)
{
}

TMXMapLayer::~TMXMapLayer(void)
{
}

bool TMXMapLayer::Initialize()
{
	RETURN_FALSE_IF_FALSE(BaseCaseLayer::Initialize());

	TmxTiledMap* tiledMap = TiledMapFactory::Instance().Create("Home.tmx");

	INode* node= tiledMap->Instantiate();
	AddChild(node);

	return true;
}




MEDUSA_IMPLEMENT_LAYER(TMXMapLayer, BaseCaseLayer, StringRef::Empty, StringRef::Empty);

