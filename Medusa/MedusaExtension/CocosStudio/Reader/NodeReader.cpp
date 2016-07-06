#include "MedusaExtensionPreCompiled.h"
#include "NodeReader.h"
#include "Node/INode.h"
#include "Node/NodeFactory.h"
#include "CocosStudio/CSParseBinary_generated.h"
#include "Application/Settings/ApplicationSettings.h"
#include "Core/IO/Path.h"

MEDUSA_COCOS_BEGIN;

INode* NodeReader::CreateNodeWithFlatBuffers(INodeEditor& editor, const flatbuffers::Table* nodeOptions, const StringRef& className /*= StringRef::Empty*/, NodeCreateFlags flags /*= NodeCreateFlags::None*/)
{
	auto node = new INode();
 	SetPropsWithFlatBuffers(node, nodeOptions, flags);
	return node;
}



INode* NodeReader::CreateNodeWithJson(INodeEditor& editor, const rapidjson::Value& nodeTree, const StringRef& className /*= StringRef::Empty*/, NodeCreateFlags flags /*= NodeCreateFlags::None*/)
{
	return nullptr;
}

MEDUSA_COCOS_END;