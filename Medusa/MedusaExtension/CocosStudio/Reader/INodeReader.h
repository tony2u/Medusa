// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaExtensionPreDeclares.h"
#include "CocosStudio/CocosDefines.h"
//[PRE_DECLARE_NAMESPCAE] Cocos

#include "ExtensionLib/Common/flatbuffers.h"
#include "CoreLib/Common/rapidjson.h"
#include "Core/String/StringRef.h"
#include "Geometry/GeometryDefines.h"

MEDUSA_COCOS_BEGIN;

class INodeReader
{
public:
	INodeReader() {};
	virtual ~INodeReader() {};
public:
	virtual INode* CreateNodeWithFlatBuffers(INodeEditor& editor, const flatbuffers::Table* nodeOptions, const StringRef& className = StringRef::Empty) = 0;
	static void SetPropsWithFlatBuffers(INode* node, const flatbuffers::Table* nodeOptions);

	virtual INode* CreateNodeWithJson(INodeEditor& editor, const rapidjson::Value& nodeTree, const StringRef& className = StringRef::Empty) = 0;
	static void SetPropsWithJson(INode* node, const rapidjson::Value& jsonNode);

public:
	static MarginEdges GetHorizontalMarginEdge(StringRef val);
	static MarginEdges GetVerticalMarginEdge(StringRef val);

	static void  SetRotatioSkewXY(INode* node, float x, float y);
	static Color4F ToColor( const rapidjson::Value* jsonNode);

};

MEDUSA_COCOS_END;
