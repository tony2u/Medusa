// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Pattern/Singleton.h"
#include "Node/Editor/ISceneEditor.h"
#include "Core/Pattern/IInitializable.h"

#define MEDUSA_DEFAULT_SCENE_EDITOR XAMLSceneEditor
#include "Node/Editor/XAML/XAMLSceneEditor.h"


MEDUSA_BEGIN;

class SceneEditorFactory:public Singleton<SceneEditorFactory>,IInitializable
{
	friend class Singleton<SceneEditorFactory>;
private:
	SceneEditorFactory();
	~SceneEditorFactory();
	
public:
	virtual bool Initialize()override;
	virtual bool Uninitialize()override;
public:
	void Clear();
	ISceneEditor* GetEditor(SceneEditorType type)const;
	MEDUSA_DEFAULT_SCENE_EDITOR& DefaultEditor()const{return *mDefaultEditor;}

	ISceneEditor* CurrentEditor() const { return mCurrentEditor; }
	void SetCurrentEditor(ISceneEditor* val) { mCurrentEditor = val; }
	void SetCurrentEditor(SceneEditorType type) { mCurrentEditor = GetEditor(type); }
private:
	ISceneEditor* mEditors[(uint)SceneEditorType::Count];
	MEDUSA_DEFAULT_SCENE_EDITOR* mDefaultEditor;
	ISceneEditor* mCurrentEditor;
	
};

MEDUSA_END;