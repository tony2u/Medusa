#include "MedusaExtensionPreCompiled.h"
#include "TextFieldReader.h"
#include "Core/IO/FileId.h"
#include "Resource/Font/FontId.h"
#include "Node/Control/EditBox/SingleLineEditBox.h"
#include "Node/NodeFactory.h"
#include "ReaderFactory.h"
#include "CocosStudio/CSParseBinary_generated.h"
#include "Rendering/RenderingObjectFactory.h"
#include "Rendering/RenderingObject.h"
#include "Resource/Model/Mesh/IMesh.h"
#include "Core/IO/Path.h"
#include "Resource/Font/FontFactory.h"

MEDUSA_COCOS_BEGIN;


INode* TextFieldReader::CreateNodeWithFlatBuffers(INodeEditor& editor, const flatbuffers::Table* textFieldOptions, const StringRef& className /*= StringRef::Empty*/, NodeCreateFlags flags /*= NodeCreateFlags::None*/)
{
	auto options = (flatbuffers::TextFieldOptions*)textFieldOptions;

	WHeapString placeholder = StringParser::ToW(options->placeHolder()->c_str());
	WHeapString text = StringParser::ToW(options->text()->c_str());

	FontId fontId;
	fontId.Name = FontFactory::Instance().ExistsOrDefault(StringRef(options->fontName()->c_str()));	//如果没有字体则切换为默认字体
	fontId.SetSize(options->fontSize());

	auto editbox = new SingleLineEditBox();
	editbox->SetFontId(fontId);
	editbox->SetPlaceHolderText(placeholder);
	editbox->SetText(text);	

	//密文和限长功能未做

	bool maxLengthEnabled = options->maxLengthEnabled() != 0;
	if (maxLengthEnabled)
	{
		//int maxLength = options->maxLength();
	}

	bool passwordEnabled = options->passwordEnabled() != 0;
	if (passwordEnabled)
	{
		std::string passwordStyleText = options->passwordStyleText()->c_str();
	}

	SetPropsWithFlatBuffers(editbox, (flatbuffers::Table*) options->widgetOptions());
	editbox->Initialize();

	return editbox;
}

INode* TextFieldReader::CreateNodeWithJson(INodeEditor& editor, const rapidjson::Value& nodeTree, const StringRef& className /*= StringRef::Empty*/, NodeCreateFlags flags /*= NodeCreateFlags::None*/)
{
	return nullptr;
}


MEDUSA_COCOS_END;
