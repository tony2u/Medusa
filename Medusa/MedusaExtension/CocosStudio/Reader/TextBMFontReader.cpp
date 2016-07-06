#include "MedusaExtensionPreCompiled.h"
#include "TextBMFontReader.h"
#include "Core/String/StringRef.h"
#include "Core/IO/FileId.h"
#include "Node/Control/Label/ILabel.h"
#include "Resource/Font/FontId.h"
#include "Node/Control/Label/FntLabel.h"
#include "Node/NodeFactory.h"
#include "Core/IO/FileSystem.h"
#include "ReaderFactory.h"
#include "CocosStudio/CSParseBinary_generated.h"
#include "Core/IO/Path.h"
#include "Resource/Font/FontFactory.h"

MEDUSA_COCOS_BEGIN;

INode* TextBMFontReader::CreateNodeWithFlatBuffers(INodeEditor& editor, const flatbuffers::Table* textOptions, const StringRef& className, NodeCreateFlags flags /*= NodeCreateFlags::None*/)
{
	auto options = (flatbuffers::TextBMFontOptions*)textOptions;
	auto fileId = FileId::ParseFrom(options->fileNameData()->path()->c_str());
	FontId fontId;
	fontId = FontFactory::Instance().ExistsOrDefault(fileId);
	ILabel* label = NodeFactory::Instance().CreateSingleLineLabel(fontId, options->text()->c_str());
	label->SetColor(Color4F::White);
	SetPropsWithFlatBuffers(label, (flatbuffers::Table*) options->widgetOptions(), flags);
	return label;
}


INode* TextBMFontReader::CreateNodeWithJson(INodeEditor& editor, const rapidjson::Value& nodeTree, const StringRef& className /*= StringRef::Empty*/, NodeCreateFlags flags /*= NodeCreateFlags::None*/)
{
	return nullptr;
}


MEDUSA_COCOS_END;
