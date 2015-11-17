// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "HelloWorldScene.h"
#include "HelloWorldLayer.h"

HelloWorldScene::HelloWorldScene(StringRef name/*=StringRef::Empty*/, const IEventArg& e /*= IEventArg::Empty*/):Base2DScene(name,e)
{
	
	
}

HelloWorldScene::~HelloWorldScene(void)
{

}

bool HelloWorldScene::Initialize()
{
	RETURN_FALSE_IF_FALSE(Base2DScene::Initialize());

	PushLayer<HelloWorldLayer>();
	
	return true;
}


MEDUSA_IMPLEMENT_SCENE(HelloWorldScene,Base2DScene);
