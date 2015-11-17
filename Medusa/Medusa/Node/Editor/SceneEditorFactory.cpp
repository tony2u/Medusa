// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "SceneEditorFactory.h"


MEDUSA_BEGIN;

SceneEditorFactory::SceneEditorFactory():mDefaultEditor(nullptr),mCurrentEditor(nullptr)
{

}

SceneEditorFactory::~SceneEditorFactory()
{
	Uninitialize();
}

bool SceneEditorFactory::Initialize()
{
	mDefaultEditor=new MEDUSA_DEFAULT_SCENE_EDITOR();
	mEditors[(uint)mDefaultEditor->GetType()]=mDefaultEditor;
	mCurrentEditor=mDefaultEditor;
	return true;
}

bool SceneEditorFactory::Uninitialize()
{
	SAFE_DELETE_ARRAY_EACH(mEditors);
	mDefaultEditor=nullptr;
	return true;
}

ISceneEditor* SceneEditorFactory::GetEditor(SceneEditorType type) const
{
	return mEditors[(uint)type];
}


MEDUSA_END;