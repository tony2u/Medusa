// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "UIScene.h"
#include "Node/Scene/SceneGraph/UISceneGraph.h"
#include "Resource/Camera/CameraFactory.h"
#include "Resource/Camera/Camera.h"
#include "Node/Scene/SceneFactory.h"

MEDUSA_BEGIN;

UIScene::UIScene(StringRef name/*=StringRef::Empty*/, const IEventArg& e /*= IEventArg::Empty*/) :IScene(name, e)
{
	mCamera = CameraFactory::Instance().CreateDefault(StringRef::Empty, true,true, ResourceShareType::Share);
}


UIScene::~UIScene(void)
{

}

bool UIScene::Initialize()
{
	RETURN_FALSE_IF_FALSE(IScene::Initialize());
	SAFE_DELETE(mSceneGraph);
	mSceneGraph = new UISceneGraph(this);
	mSceneGraph->Initialize();

	return true;
}



MEDUSA_IMPLEMENT_SCENE(UIScene, IScene,StringRef::Empty, StringRef::Empty);

MEDUSA_END;
