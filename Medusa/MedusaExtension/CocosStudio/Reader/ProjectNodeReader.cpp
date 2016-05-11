#include "MedusaExtensionPreCompiled.h"
#include "ProjectNodeReader.h"
#include "Core/String/StringRef.h"
#include "Core/IO/FileId.h"
#include "Node/Sprite/Sprite.h"
#include "Node/NodeFactory.h"
#include "ReaderFactory.h"
#include "Core/IO/FileSystem.h"
#include "Node/Editor/INodeEditor.h"
#include "CocosStudio/CSParseBinary_generated.h"
#include "Core/IO/Path.h"

MEDUSA_COCOS_BEGIN;

INode* ProjectNodeReader::CreateNodeWithFlatBuffers(INodeEditor& editor, const flatbuffers::Table* nodeOptions, const StringRef& className )
{
	auto projectNodeOptions = (flatbuffers::ProjectNodeOptions*)nodeOptions;
	StringRef filePath = projectNodeOptions->fileName()->c_str();
	filePath = Path::GetFileName(filePath);
	RETURN_NULL_IF_FALSE(FileSystem::Instance().AssertExists(filePath));
	INode* node = editor.Create("", filePath);
	SetPropsWithFlatBuffers(node, (flatbuffers::Table*)(projectNodeOptions->nodeOptions()));
	return node;
}

INode* ProjectNodeReader::CreateNodeWithJson(INodeEditor& editor, const rapidjson::Value& nodeTree, const StringRef& className /*= StringRef::Empty*/)
{
	const rapidjson::Value& fileDataNode = nodeTree["FileData"];
	StringRef filePath = fileDataNode.GetString("Path", nullptr);
	filePath = Path::GetFileName(filePath);
	RETURN_NULL_IF_FALSE(FileSystem::Instance().AssertExists(filePath));
	INode* node = editor.Create("", filePath);
	SetPropsWithJson(node, nodeTree);
	return node;
}

MEDUSA_IMPLEMENT_COCOS_READER(ProjectNodeReader);
MEDUSA_COCOS_END;
