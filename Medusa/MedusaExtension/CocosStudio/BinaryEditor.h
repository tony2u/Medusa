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

	virtual StringRef Name()const override { return "CocosBinary"; }
	virtual FileType Extension()const override { return FileType::csb; }
	virtual StringRef ExtensionString()const override { return FileExtensions::csb; }
	virtual INode* Create(const StringRef& className, const FileIdRef& editorFile, const FileIdRef& scriptFile, const IEventArg& e = IEventArg::Empty, NodeCreateFlags flags = NodeCreateFlags::None) override;
	INode* NodeWithFlatBuffers(const StringRef& className, const flatbuffers::NodeTree *nodeTree, NodeCreateFlags flags = NodeCreateFlags::None);
protected:
	static StringRef GetReaderName(const StringRef &name, const flatbuffers::Options* options);
};

MEDUSA_COCOS_END;
