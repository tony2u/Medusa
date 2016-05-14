// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaPreCompiled.h"
#include "SceneFactory.h"
#include "Node/Editor/NodeEditorFactory.h"
#include "Core/Log/Log.h"
#include "Core/IO/FileIdRef.h"
#include "Node/Scene/UIScene.h"


MEDUSA_BEGIN;

IScene* SceneFactory::Create(const StringRef& className, const FileIdRef& editorFile, const IEventArg& e /*= IEventArg::Empty*/, NodeCreateFlags flags /*= NodeCreateFlags::None*/)
{
	IScene* scene = nullptr;
	if (editorFile.IsValid())
	{
		scene = (IScene*)NodeEditorFactory::Instance().Create(className, editorFile, e,flags);
		RETURN_SELF_IF_NOT_NULL(scene);
	}

	if (className.IsEmpty())
	{
		scene = new UIScene(StringRef::Empty, e);
	}
	else
	{
		scene = BaseType::Create(className, className, e);	//create scene only use name
	}

	Log::AssertNotNullFormat(scene, "Cannot create scene by name:{}", className);
	scene->Initialize();

	return scene;
}

MEDUSA_END;