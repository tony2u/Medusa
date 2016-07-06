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


INode* SpriteReader::CreateNodeWithFlatBuffers(INodeEditor& editor, const flatbuffers::Table* spriteOptions, const StringRef& className /*= StringRef::Empty*/, NodeCreateFlags flags /*= NodeCreateFlags::None*/)
{
	auto options = (flatbuffers::SpriteOptions*)spriteOptions;
	auto sprite = CreateSprite(options->fileNameData()->path()->c_str());
	SetPropsWithFlatBuffers(sprite, (flatbuffers::Table*) options->nodeOptions());
	return sprite;
}

INode* SpriteReader::CreateNodeWithJson(INodeEditor& editor, const rapidjson::Value& nodeTree, const StringRef& className /*= StringRef::Empty*/, NodeCreateFlags flags /*= NodeCreateFlags::None*/)
{
	const rapidjson::Value& fileDataNode = nodeTree["FileData"];
	StringRef path = fileDataNode.GetString("Path", nullptr);
	Sprite* sprite = CreateSprite(path);
	SetPropsWithJson(sprite, nodeTree);
	return sprite;
}

Sprite* SpriteReader::CreateSprite(StringRef fullName)
{
	Sprite* sprite = new Sprite();
	if (!fullName.IsEmpty())
	{
		auto fileId = FileId::ParseFrom(fullName);
		
		auto renderingObject = RenderingObjectFactory::Instance().CreateFromTexture(fileId);
		Log::Assert(renderingObject != nullptr, " sprite file path error");
		sprite->SetRenderingObject(renderingObject);
		sprite->SetSize(renderingObject.Mesh()->Size());
		sprite->Initialize();
	}
	return sprite;
}


MEDUSA_COCOS_END;
