// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaExtensionPreDeclares.h"
#include "CocosStudio/CocosDefines.h"
//[PRE_DECLARE_NAMESPCAE] Cocos
#include "Node/Editor/INodeEditor.h"
#include "CoreLib/Common/rapidjson.h"

MEDUSA_COCOS_BEGIN;

class JsonEditor : public INodeEditor
{
public:
	JsonEditor();
	virtual ~JsonEditor();

	virtual StringRef Type()const override { return "CocosJson"; }
	virtual FileType Extension()const override { return FileType::json; }
	virtual StringRef ExtensionString()const override { return FileExtensions::json; }

	virtual INode* Create(const StringRef& className, const FileIdRef& editorFile, const IEventArg& e = IEventArg::Empty, NodeCreateFlags flags = NodeCreateFlags::None) override;
	INode* NodeWithJsonRoot(const StringRef& className, const rapidjson::Value& nodeTree, NodeCreateFlags flags = NodeCreateFlags::None);
	INode* NodeWithJson(const rapidjson::Value& jsonNode, NodeCreateFlags flags = NodeCreateFlags::None);

protected:
	static StringRef GetReaderName(const StringRef& name, const rapidjson::Value& nodeTree);
};

MEDUSA_COCOS_END;
