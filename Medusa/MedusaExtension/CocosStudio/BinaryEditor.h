// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaExtensionPreDeclares.h"
#include "CocosStudio/CocosDefines.h"
//[PRE_DECLARE_NAMESPCAE] Cocos
#include "ExtensionLib/Common/flatbuffers.h"
#include "CocosStudio/CSParseBinary_generated.h"
#include "Node/Editor/INodeEditor.h"

MEDUSA_COCOS_BEGIN;

class BinaryEditor : public INodeEditor
{
public:
	BinaryEditor();
	virtual ~BinaryEditor();

	virtual StringRef Type()const override { return "CocosBinary"; }
	virtual FileType Extension()const override { return FileType::csb; }
	virtual INode* Create(const StringRef& className, const FileIdRef& editorFile, const IEventArg& e = IEventArg::Empty) override;
	INode* NodeWithFlatBuffers(const StringRef& className, const flatbuffers::NodeTree *nodeTree);
protected:
	static StringRef GetReaderName(const StringRef &name, const flatbuffers::Options* options);
};

MEDUSA_COCOS_END;
