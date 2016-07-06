// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "TestPreCompiled.h"
#include "TestScene.h"
#include "TestLayer.h"
#include "Game/Layer/Cocos/CocosHelloLayer.h"


TestScene::TestScene(StringRef name/*=StringRef::Empty*/, const IEventArg& e /*= IEventArg::Empty*/)
	:UIScene(name,e)
{

}

TestScene::~TestScene(void)
{

}

bool TestScene::Initialize()
{
	RETURN_FALSE_IF_FALSE(UIScene::Initialize());
	PushLayer<TestLayer>();
	//PushLayer<CocosHelloLayer>();

	//SceneManager::Instance().Current()->PushLayer<CocosFeatureLayer>();

	return true;
}

MEDUSA_IMPLEMENT_NODE(TestScene);
