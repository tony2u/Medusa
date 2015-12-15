// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaPreCompiled.h"
#include "LayerFactory.h"
#include "Node/Editor/SceneEditorFactory.h"
#include "Core/Log/Log.h"
#include "Core/IO/FileIdRef.h"

MEDUSA_BEGIN;

ILayer* LayerFactory::CreateLayer(const StringRef& className, const StringRef& editorFile, const IEventArg& e /*= IEventArg::Empty*/, LayerCreateFlags createFlags /*= LayerCreateFlags::None*/)
{
	auto* editor = SceneEditorFactory::Instance().CurrentEditor();
	if (editor != nullptr)
	{
		return editor->CreateLayer(className, editorFile, e);
	}

	ILayer* layer =Create(className, className, e);
	Log::AssertNotNullFormat(layer, "Cannot create layer by name:{}", className.c_str());
	layer->Initialize();

	return layer;
}


MEDUSA_END;