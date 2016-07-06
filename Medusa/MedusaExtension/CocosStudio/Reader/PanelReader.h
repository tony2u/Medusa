// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaExtensionPreDeclares.h"
#include "CocosStudio/CocosDefines.h"
//[PRE_DECLARE_NAMESPCAE] Cocos
#include "CocosStudio/Reader/INodeReader.h"
MEDUSA_COCOS_BEGIN;

class PanelReader : public INodeReader
{
	MEDUSA_RTTI(PanelReader,INodeReader);
public:
	PanelReader() {};
	virtual ~PanelReader() {};
public:
	virtual INode* CreateNodeWithFlatBuffers(INodeEditor& editor, const flatbuffers::Table* nodeTree, const StringRef& className = StringRef::Empty, NodeCreateFlags flags = NodeCreateFlags::None) override;
	virtual INode* CreateNodeWithJson(INodeEditor& editor, const rapidjson::Value& nodeTree, const StringRef& className = StringRef::Empty, NodeCreateFlags flags = NodeCreateFlags::None) override;
public:
	static IShape* CreateSingleColorRect(byte opacity, const flatbuffers::Color& bgColor, const flatbuffers::FlatSize& flatSize);
	static IShape* CreateGradientRect(byte opacity, const flatbuffers::Color& bgColor, const flatbuffers::FlatSize& flatSize, const flatbuffers::Color& start, const flatbuffers::Color& end, const flatbuffers::ColorVector& vec);
private:
	static void SetGradientRectColor(IShape* rect,byte opacity, const flatbuffers::Color& start, const flatbuffers::Color& end, const flatbuffers::ColorVector& vec);
};

MEDUSA_COCOS_END;
