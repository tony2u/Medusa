// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "INodeEditor.h"

MEDUSA_BEGIN;

class TieldLayerEditor :public INodeEditor
{
public:
	TieldLayerEditor();
	virtual ~TieldLayerEditor(void);
	virtual StringRef Type()const override { return "Tiled"; }
	virtual FileType Extension()const override { return FileType::tmx; }
public:
	using INodeEditor::Create;
	virtual INode* Create(const StringRef& className, const FileIdRef& editorFile, const IEventArg& e = IEventArg::Empty)override;
};

MEDUSA_END;
