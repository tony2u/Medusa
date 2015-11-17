// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Node/Editor/ISceneEditor.h"

MEDUSA_BEGIN;

class CustomSceneEditor:public ISceneEditor
{
public:
	CustomSceneEditor();
	virtual ~CustomSceneEditor(void);

	virtual SceneEditorType GetType()const override{return SceneEditorType::Custom;}

public:
	using ISceneEditor::CreateLayer;

	virtual ILayer* CreateLayer(const StringRef& layerName, const FileIdRef& editorFile, const IEventArg& e = IEventArg::Empty)override;

};

MEDUSA_END;
