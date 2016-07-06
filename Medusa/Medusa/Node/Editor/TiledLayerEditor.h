// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "INodeEditor.h"

MEDUSA_BEGIN;

class TiledLayerEditor :public INodeEditor
{
public:
	TiledLayerEditor();
	virtual ~TiledLayerEditor(void);
	virtual StringRef Name()const override { return "Tiled"; }
	virtual FileType Extension()const override { return FileType::tmx; }
	virtual StringRef ExtensionString()const override { return FileExtensions::tmx; }
public:
	using INodeEditor::Create;
	virtual INode* Create(const StringRef& className, const FileIdRef& editorFile, const FileIdRef& scriptFile, const IEventArg& e = IEventArg::Empty, NodeCreateFlags flags = NodeCreateFlags::None)override;
};

MEDUSA_END;
