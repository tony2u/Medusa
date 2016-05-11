#include "MedusaExtensionPreCompiled.h"
#include "TextReader.h"
#include "Core/String/StringRef.h"
#include "Core/IO/FileId.h"
#include "Node/Control/Label/ILabel.h"
#include "Resource/Font/FontId.h"
#include "Node/Control/Label/FntLabel.h"
#include "Node/NodeFactory.h"
#include "Core/IO/FileSystem.h"
#include "ReaderFactory.h"
#include "CocosStudio/CSParseBinary_generated.h"
MEDUSA_COCOS_BEGIN;

INode* TextReader::CreateNodeWithFlatBuffers(INodeEditor& editor, const flatbuffers::Table* projectNodeOptions, const StringRef& className)
{
	auto options = (flatbuffers::TextOptions*)projectNodeOptions;
	FontId fontId;
	fontId.Name = FileSystem::Instance().ExistsOr(StringRef(options->fontName()->c_str()), StringRef("arial.ttf"));	//如果没有字体则切换为默认字体
	fontId.SetSize(options->fontSize());
	Color4F fontColor(options->widgetOptions()->color()->r(), options->widgetOptions()->color()->g(), options->widgetOptions()->color()->b(), options->widgetOptions()->alpha());
	fontId.SetColor(fontColor);

	if (options->outlineEnabled())
	{
		fontId.SetOutlineThickness(options->outlineSize());

		auto outlineColor = options->outlineColor();
		Color4F color(outlineColor->r(), outlineColor->g(), outlineColor->b(), outlineColor->a());
		fontId.SetOutlineColor(color);
		fontId.SetOutlineType(FontOutlineType::Outer);
	}

	ILabel* label = NodeFactory::Instance().CreateSingleLineLabel(fontId, options->text()->c_str());
	label->SetAlignment((Alignment)(options->vAlignment() * 3 + options->hAlignment()));

	SetPropsWithFlatBuffers(label, (flatbuffers::Table*) options->widgetOptions());
	label->SetColor(Color4F::White);	//reset default,use node color as font color
	return label;
}


INode* TextReader::CreateNodeWithJson(INodeEditor& editor, const rapidjson::Value& nodeTree, const StringRef& className /*= StringRef::Empty*/)
{
	const rapidjson::Value& fileDataNode = nodeTree["FontResource"];
	StringRef path = fileDataNode.GetString("Path", nullptr);
	FontId fontId;
	fontId.Name = FileSystem::Instance().ExistsOr(path, StringRef("arial.ttf"));	//如果没有字体则切换为默认字体
	fontId.SetSize(nodeTree.Get("FontSize", 0));
	StringRef hAlignment = nodeTree.GetString("HorizontalAlignmentType", "");
	StringRef vAlignment = nodeTree.GetString("VerticalAlignmentType", "");
	Alignment align= GetAlignment(hAlignment, vAlignment);
	
	Color4F color = ToColor(nodeTree.GetMember("CColor"));
	fontId.SetColor(color);

	bool outlineEnabled = nodeTree.Get("OutlineEnabled", false);
	if (outlineEnabled)
	{
		fontId.SetOutlineType(FontOutlineType::Outer);
		fontId.SetOutlineThickness(nodeTree.Get("OutlineSize", 0));

		Color4F outlineColor = ToColor(nodeTree.GetMember("OutlineColor"));
		fontId.SetOutlineColor(outlineColor);
	}

	/*
	//Not support yet
	bool shadowEnabled = nodeTree.Get("ShadowEnabled", false);
	if (shadowEnabled)
	{
		Color4F shadowColor = ToColor(nodeTree.GetMember("ShadowColor"));
		fontId.SetShadowColor(shadowColor);

		float shadowOffsetX = nodeTree.Get("ShadowOffsetX", 0.f);
		float shadowOffsetY = nodeTree.Get("ShadowOffsetY", 0.f);
	}
	*/

	StringRef text = nodeTree.GetString("LabelText", "");

	ILabel* label = NodeFactory::Instance().CreateSingleLineLabel(fontId, text);
	label->SetAlignment(align);
	SetPropsWithJson(label, nodeTree);
	label->SetColor(Color4F::White);	//reset default,use node color as font color
	return label;

}

Alignment TextReader::GetAlignment(StringRef hAlignmentStr, StringRef vAlignmentStr)
{
	int hAlignment = 0;
	if (hAlignmentStr == "HT_Left")
	{
		hAlignment = 0;
	}
	else if (hAlignmentStr == "HT_Center")
	{
		hAlignment = 1;
	}
	else if (hAlignmentStr == "HT_Right")
	{
		hAlignment = 2;
	}

	int vAlignment = 0;
	if (vAlignmentStr == "HT_Bottom")
	{
		vAlignment = 0;
	}
	else if (vAlignmentStr == "HT_Center")
	{
		vAlignment = 1;
	}
	else if (vAlignmentStr == "HT_Top")
	{
		vAlignment = 2;
	}

	return (Alignment)(hAlignment * 3 + vAlignment);
}

MEDUSA_IMPLEMENT_COCOS_READER(TextReader);

MEDUSA_COCOS_END;
