// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "CustomSceneEditor.h"


MEDUSA_BEGIN;
CustomSceneEditor::CustomSceneEditor()
{

}

CustomSceneEditor::~CustomSceneEditor(void)
{

}

ILayer* CustomSceneEditor::CreateLayer(const StringRef& layerName, const FileIdRef& editorFile, const IEventArg& e/*=IEventArg::Empty*/)
{
	return nullptr;
}



MEDUSA_END;
