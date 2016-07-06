#include "MedusaExtensionPreCompiled.h"
#include "TmxMapReader.h"
#include "ReaderFactory.h"
#include "CocosStudio/CSParseBinary_generated.h"
#include "Core/IO/Path.h"
#include "Node/NodeFactory.h"
#include "Core/IO/FileId.h"

MEDUSA_COCOS_BEGIN;

INode* TmxMapReader::CreateNodeWithFlatBuffers(INodeEditor& editor, const flatbuffers::Table *nodeOptions, const StringRef& className, NodeCreateFlags flags /*= NodeCreateFlags::None*/)
{
	return nullptr;
}

INode* TmxMapReader::CreateNodeWithJson(INodeEditor& editor, const rapidjson::Value& nodeTree, const StringRef& className /*= StringRef::Empty*/, NodeCreateFlags flags /*= NodeCreateFlags::None*/)
{
	const rapidjson::Value* fileData = nodeTree.GetMember("FileData");
	RETURN_NULL_IF_NULL(fileData);
	StringRef path = fileData->Get("Path", nullptr);
	auto fileId = FileId::ParseFrom(path);
	auto node = NodeFactory::Instance().Create(fileId);
	SetPropsWithJson(node, nodeTree, flags);

	return node;
}

MEDUSA_COCOS_END;
