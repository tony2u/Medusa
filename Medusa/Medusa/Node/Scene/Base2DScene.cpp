// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Base2DScene.h"
#include "Node/Scene/SceneGraph/UISceneGraph.h"
#include "Resource/Camera/CameraFactory.h"
#include "Resource/Camera/Camera.h"

MEDUSA_BEGIN;

Base2DScene::Base2DScene(StringRef name/*=StringRef::Empty*/, const IEventArg& e /*= IEventArg::Empty*/) :IScene(name, e)
{
	mCamera = CameraFactory::Instance().CreateDefault(StringRef::Empty, true,true, ResourceShareType::Share);
}


Base2DScene::~Base2DScene(void)
{

}

bool Base2DScene::Initialize()
{
	RETURN_FALSE_IF_FALSE(IScene::Initialize());
	mSceneGraph = new UISceneGraph(this);
	mSceneGraph->Initialize();

	return true;
}



MEDUSA_IMPLEMENT_RTTI(Base2DScene, IScene);

MEDUSA_END;
