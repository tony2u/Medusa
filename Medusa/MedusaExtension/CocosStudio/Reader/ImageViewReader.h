// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaExtensionPreDeclares.h"
#include "CocosStudio/CocosDefines.h"
//[PRE_DECLARE_NAMESPCAE] Cocos
#include "CocosStudio/Reader/INodeReader.h"
#include "Node/Sprite/NineGridSprite.h"
#include "CocosStudio/CSParseBinary_generated.h"
MEDUSA_COCOS_BEGIN;

class ImageViewReader : public INodeReader
{
	MEDUSA_RTTI(ImageViewReader,INodeReader);
public:
	ImageViewReader() {};
	virtual ~ImageViewReader() {};
public:
	virtual INode* CreateNodeWithFlatBuffers(INodeEditor& editor, const flatbuffers::Table* imageOptions, const StringRef& className = StringRef::Empty, NodeCreateFlags flags = NodeCreateFlags::None) override;
	virtual INode* CreateNodeWithJson(INodeEditor& editor, const rapidjson::Value& nodeTree, const StringRef& className = StringRef::Empty, NodeCreateFlags flags = NodeCreateFlags::None) override;
public:
	static NineGridSprite* CreateNineGridSprite(uint8 enable, const flatbuffers::FlatSize* nineGridSize, const flatbuffers::FlatSize* widgetSize, const flatbuffers::CapInsets* capInset, const FileIdRef& fileId);
};

MEDUSA_COCOS_END;
