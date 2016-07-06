// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaExtensionPreDeclares.h"
#include "CocosStudio/CocosDefines.h"
//[PRE_DECLARE_NAMESPCAE] Cocos
#include "CocosStudio/Reader/INodeReader.h"
MEDUSA_COCOS_BEGIN;

class ScrollViewReader : public INodeReader
{
	MEDUSA_RTTI(ScrollViewReader,INodeReader);
public:
	ScrollViewReader() {};
	virtual ~ScrollViewReader() {};
public:
	virtual INode* CreateNodeWithFlatBuffers(INodeEditor& editor, const flatbuffers::Table* nodeTree, const StringRef& className = StringRef::Empty, NodeCreateFlags flags = NodeCreateFlags::None) override;
	virtual INode* CreateNodeWithJson(INodeEditor& editor, const rapidjson::Value& nodeTree, const StringRef& className = StringRef::Empty, NodeCreateFlags flags = NodeCreateFlags::None) override;
};

MEDUSA_COCOS_END;
