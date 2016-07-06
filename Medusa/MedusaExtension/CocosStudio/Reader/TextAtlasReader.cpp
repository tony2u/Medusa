#include "MedusaExtensionPreCompiled.h"
#include "TextAtlasReader.h"
#include "Core/String/StringRef.h"
#include "Core/IO/FileId.h"
#include "Node/Control/Label/ILabel.h"
#include "Resource/Font/FontId.h"
#include "Resource/Font/BMPFont.h"
#include "Node/Control/Label/FntLabel.h"
#include "Node/NodeFactory.h"
#include "Core/IO/FileSystem.h"
#include "ReaderFactory.h"
#include "Node/Control/Label/FntLabel.h"
#include "Node/NodeFactory.h"
#include "CocosStudio/CSParseBinary_generated.h"
#include "Core/IO/Path.h"
#include "Resource/Font/FontFactory.h"
MEDUSA_COCOS_BEGIN;

INode* TextAtlasReader::CreateNodeWithFlatBuffers(INodeEditor& editor, const flatbuffers::Table* textOptions, const StringRef& className, NodeCreateFlags flags /*= NodeCreateFlags::None*/)
{
	auto options = (flatbuffers::TextAtlasOptions*)textOptions;
	StringRef path = options->charMapFileData()->path()->c_str();
	auto fileId = FileId::ParseFrom(path);
	Log::Assert(FileSystem::Instance().Exists(fileId), " TextAtlasReader image file path error");
	StringRef text = options->stringValue()->c_str();
	int itemWidth = options->itemWidth();
	char firstChar = *(options->startCharMap()->c_str());
	FontId fontId(fileId);
	fontId.SetSize(itemWidth);
	auto label = NodeFactory::Instance().CreateSingleLineBMPNumberLabel(fontId, text, firstChar);
	SetPropsWithFlatBuffers(label, (flatbuffers::Table*) options->widgetOptions(), flags);
	return label;
}


INode* TextAtlasReader::CreateNodeWithJson(INodeEditor& editor, const rapidjson::Value& nodeTree, const StringRef& className /*= StringRef::Empty*/, NodeCreateFlags flags /*= NodeCreateFlags::None*/)
{
	return nullptr;
}


MEDUSA_COCOS_END;
