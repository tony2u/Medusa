// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "TieldLayerEditor.h"
#include "Resource/Map/Tiled/TiledMapFactory.h"
#include "Node/Layer/LayerFactory.h"
#include "Node/Layer/ILayer.h"

MEDUSA_BEGIN;
TieldLayerEditor::TieldLayerEditor()
{

}

TieldLayerEditor::~TieldLayerEditor(void)
{

}

INode* TieldLayerEditor::Create(const StringRef& className, const FileIdRef& editorFile, const IEventArg& e/*=IEventArg::Empty*/)
{
	RETURN_NULL_IF_EMPTY(editorFile);
	auto* map = TiledMapFactory::Instance().Create(editorFile);
	if (map == nullptr)
	{
		Log::FormatError("Cannot create layer:{}", editorFile.Name);
		return nullptr;
	}

	INode* layer = map->Instantiate(className);
	if (layer == nullptr)
	{
		Log::FormatError("Cannot create layer:{}", editorFile.Name);
	}

	return layer;
}



MEDUSA_END;
