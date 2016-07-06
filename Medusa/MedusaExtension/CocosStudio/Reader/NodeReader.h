// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
// 解析Node文件被引用时产生的node对象   CocoStudio 中一个node文件被引用会产生一个Node和一个ProjectNode
#pragma once
#include "MedusaExtensionPreDeclares.h"
#include "CocosStudio/CocosDefines.h"
//[PRE_DECLARE_NAMESPCAE] Cocos
#include "INodeReader.h"
MEDUSA_COCOS_BEGIN;

class NodeReader : public INodeReader
{
	MEDUSA_RTTI(NodeReader, INodeReader);
public:
	NodeReader() {};
	virtual ~NodeReader() {};
public:
	virtual INode* CreateNodeWithFlatBuffers(INodeEditor& editor, const flatbuffers::Table* nodeOptions, const StringRef& className = StringRef::Empty, NodeCreateFlags flags = NodeCreateFlags::None) override;
	virtual INode* CreateNodeWithJson(INodeEditor& editor, const rapidjson::Value& nodeTree, const StringRef& className = StringRef::Empty, NodeCreateFlags flags = NodeCreateFlags::None) override;
};

MEDUSA_COCOS_END;
