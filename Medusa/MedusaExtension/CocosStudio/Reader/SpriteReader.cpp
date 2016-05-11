#include "MedusaExtensionPreCompiled.h"
#include "SpriteReader.h"
#include "Core/String/StringRef.h"
#include "Core/IO/FileId.h"
#include "Node/Sprite/Sprite.h"
#include "Node/NodeFactory.h"
#include "ReaderFactory.h"
#include "CocosStudio/CSParseBinary_generated.h"
#include "Rendering/RenderingObjectFactory.h"
#include "Rendering/RenderingObject.h"
#include "Resource/Model/Mesh/IMesh.h"
#include "Core/IO/Path.h"

MEDUSA_COCOS_BEGIN;

INode* SpriteReader::CreateNodeWithFlatBuffers(INodeEditor& editor, const flatbuffers::Table* spriteOptions, const StringRef& className )
{
	auto options = (flatbuffers::SpriteOptions*)spriteOptions;
	StringRef name = options->fileNameData()->path()->c_str();
	name=Path::GetFileName(name);

	auto sprite = NodeFactory::Instance().CreateSprite(name);
	SetPropsWithFlatBuffers(sprite,(flatbuffers::Table*) options->nodeOptions());
	return sprite;
}

INode* SpriteReader::CreateNodeWithJson(INodeEditor& editor, const rapidjson::Value& nodeTree, const StringRef& className /*= StringRef::Empty*/)
{
	const rapidjson::Value& fileDataNode= nodeTree["FileData"];
	StringRef path= fileDataNode.GetString("Path", nullptr);
	path = Path::GetFileName(path);
	auto sprite = NodeFactory::Instance().CreateSprite(path);
	SetPropsWithJson(sprite, nodeTree);
	return sprite;
}



MEDUSA_IMPLEMENT_COCOS_READER(SpriteReader);
MEDUSA_COCOS_END;
