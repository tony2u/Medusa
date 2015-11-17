// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Base3DScene.h"
#include "Resource/Camera/CameraFactory.h"
#include "Node/Scene/SceneFactory.h"

MEDUSA_BEGIN;

Base3DScene::Base3DScene(StringRef name/*=StringRef::Empty*/, const IEventArg& e /*= IEventArg::Empty*/) :IScene(name,e)
{
	mCamera = CameraFactory::Instance().CreateDefault(StringRef::Empty, false,true, ResourceShareType::Share);
	mCamera->Retain();
}


Base3DScene::~Base3DScene(void)
{
}

bool Base3DScene::Initialize()
{
	RETURN_FALSE_IF_FALSE(IScene::Initialize());

	return true;
}

MEDUSA_IMPLEMENT_RTTI(Base3DScene, IScene);

MEDUSA_END;
