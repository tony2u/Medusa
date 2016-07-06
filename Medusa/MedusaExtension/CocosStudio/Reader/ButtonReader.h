// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaExtensionPreDeclares.h"
#include "CocosStudio/CocosDefines.h"
//[PRE_DECLARE_NAMESPCAE] Cocos
#include "CocosStudio/Reader/INodeReader.h"
#include "Core/Pattern/Singleton.h"
MEDUSA_COCOS_BEGIN;

class ButtonReader : public INodeReader
{
	MEDUSA_RTTI(ButtonReader,INodeReader);
public:
	ButtonReader() {};
	virtual ~ButtonReader() {};
public:
	virtual INode* CreateNodeWithFlatBuffers(INodeEditor& editor, const flatbuffers::Table* nodeOptions, const StringRef& className= StringRef::Empty, NodeCreateFlags flags = NodeCreateFlags::None) override;
	virtual INode* CreateNodeWithJson(INodeEditor& editor, const rapidjson::Value& nodeTree, const StringRef& className = StringRef::Empty, NodeCreateFlags flags = NodeCreateFlags::None) override;
protected:
	static void SetButtonEvent(IButton* button, StringRef callbackType,StringRef callBackName);
};

MEDUSA_COCOS_END;