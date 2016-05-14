// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaPreCompiled.h"
#include "LayerFactory.h"
#include "Node/Editor/NodeEditorFactory.h"
#include "Core/Log/Log.h"
#include "Core/IO/FileIdRef.h"
#include "Node/Layer/NormalLayer.h"

MEDUSA_BEGIN;

ILayer* LayerFactory::Create(const StringRef& className, const FileIdRef& editorFile, const IEventArg& e /*= IEventArg::Empty*/, NodeCreateFlags flags /*= LayerCreateFlags::None*/)
{
	ILayer* layer = nullptr;
	if (editorFile.IsValid())
	{
		layer = (ILayer*)NodeEditorFactory::Instance().Create(className, editorFile, e,flags);
		RETURN_SELF_IF_NOT_NULL(layer);
	}

	if (className.IsEmpty())
	{
		layer = new NormalLayer(StringRef::Empty, e);
	}
	else
	{
		layer = BaseType::Create(className, className, e);	//create layer only use name
	}

	Log::AssertNotNullFormat(layer, "Cannot create layer by name:{}", className);
	layer->Initialize();

	return layer;
}


MEDUSA_END;