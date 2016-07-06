#include "MedusaExtensionPreCompiled.h"
#include "ButtonReader.h"
#include "Core/String/StringRef.h"
#include "Core/IO/FileId.h"
#include "Node/Sprite/Sprite.h"
#include "Node/NodeFactory.h"
#include "Core/IO/FileSystem.h"
#include "Node/Control/Button/IButton.h"
#include "Node/Control/Button/LabelButton.h"
#include "Node/Control/Button/TextureButton.h"
#include "Resource/Font/FontId.h"
#include "Node/Control/Label/FntLabel.h"
#include "ReaderFactory.h"
#include "CocosStudio/CSParseBinary_generated.h"
#include "Core/IO/Path.h"
#include "Node/Input/InputDispatcher.h"
#include "Resource/Font/FontFactory.h"

MEDUSA_COCOS_BEGIN;

INode* ButtonReader::CreateNodeWithFlatBuffers(INodeEditor& editor, const flatbuffers::Table* nodeOptions, const StringRef& className, NodeCreateFlags flags /*= NodeCreateFlags::None*/)
{
	auto options = (flatbuffers::ButtonOptions*)nodeOptions;
	ILabel* label = nullptr;
	StringRef titleText = options->text()->c_str();
	if (!titleText.IsEmpty())
	{
		int fontSize = options->fontSize();
		FileIdRef fontName(options->fontName()->c_str());
		fontName = FontFactory::Instance().ExistsOrDefault(fontName);
		FontId fontId(fontName);
		fontId.SetSize(fontSize);
		label = NodeFactory::Instance().CreateSingleLineLabel(fontId, titleText, Alignment::MiddleCenter);
		auto textColor = options->textColor();
		Color4F color(textColor->r(), textColor->g(), textColor->b(), textColor->a());
		label->SetColor(color);
		label->SetAnchorPoint(AnchorPoint::MiddleCenter);
		label->DockToParent(DockPoint::MiddleCenter);
	}
	
	StringRef normalImage = StringRef(options->normalData()->path()->c_str());
	StringRef pressedImage = StringRef(options->pressedData()->path()->c_str());
	StringRef disabledImage = StringRef(options->disabledData()->path()->c_str());
	if (normalImage=="Default/Button_Normal.png")
	{
		normalImage = StringRef::Empty;
	}
	if (pressedImage == "Default/Button_Press.png")
	{
		pressedImage = StringRef::Empty;
	}
	if (disabledImage == "Default/Button_Disable.png")
	{
		disabledImage = StringRef::Empty;
	}

	auto normalImageFileId = FileId::ParseFrom(normalImage);
	auto pressedImageFileId = FileId::ParseFrom(pressedImage);
	auto disabledImageFileId = FileId::ParseFrom(disabledImage);


	IButton* button = nullptr;
	if (!normalImageFileId.IsEmpty() || !pressedImageFileId.IsEmpty() || !disabledImageFileId.IsEmpty())
	{
		bool isEnableNineGrid = options->scale9Enabled() != 0;
		Size2F size = Size2F::Zero;
		ThicknessF padding = ThicknessF::Zero;
		if (isEnableNineGrid)
		{
			auto flatbufferSize = options->scale9Size();
			size = Size2F(flatbufferSize->width(), flatbufferSize->height());
			auto capInset = options->capInsets();
			padding = ThicknessF(capInset->x(), size.Width - capInset->width() - capInset->x(), size.Height - capInset->height() - capInset->y(), capInset->y());
		}
		auto* textureButton = NodeFactory::Instance().CreateTextureButton(normalImageFileId, pressedImageFileId, disabledImageFileId);
		textureButton->SetSize(size);
		textureButton->EnableNineGrid(isEnableNineGrid);
		textureButton->SetTexturePadding(padding);

		button = textureButton;
		if (label)
			button->AddChild(label);
	}
	else if (label)
	{
		button = new LabelButton(label);
		button->Initialize();
	}
	else
	{
		Log::Error("NO button");
	}

	auto widgetOptions= options->widgetOptions();
	button->EnableInput(widgetOptions->touchEnabled() != 0);

	StringRef callBackName = widgetOptions->callBackName()->c_str();
	StringRef callbackType = widgetOptions->callBackType()->c_str();
	SetButtonEvent(button, callbackType, callBackName);

	SetPropsWithFlatBuffers(button, (flatbuffers::Table*) options->widgetOptions(), flags);

	return button;
}

INode* ButtonReader::CreateNodeWithJson(INodeEditor& editor, const rapidjson::Value& nodeTree, const StringRef& className /*= StringRef::Empty*/, NodeCreateFlags flags /*= NodeCreateFlags::None*/)
{
	const rapidjson::Value& normalFileDataNode = nodeTree["NormalFileData"];
	StringRef normalPath = StringRef(normalFileDataNode.GetString("Path", nullptr));
	const rapidjson::Value& selectedFileDataNode = nodeTree["PressedFileData"];
	StringRef selectedPath = StringRef( selectedFileDataNode.GetString("Path", nullptr));
	const rapidjson::Value& disabledFileDataNode = nodeTree["DisabledFileData"];
	StringRef disabledPath = StringRef( disabledFileDataNode.GetString("Path", nullptr));
	if (normalPath == "Default/Button_Normal.png")
	{
		normalPath = StringRef::Empty;
	}
	if (selectedPath == "Default/Button_Press.png")
	{
		selectedPath = StringRef::Empty;
	}
	if (disabledPath == "Default/Button_Disable.png")
	{
		disabledPath = StringRef::Empty;
	}

	auto normalPathFileId = FileId::ParseFrom(normalPath);
	auto selectedPathFileId = FileId::ParseFrom(selectedPath);
	auto disabledPathFileId = FileId::ParseFrom(disabledPath);


	ILabel* label = nullptr;
	StringRef buttonText = nodeTree.GetString("ButtonText", nullptr);
	if (!buttonText.IsEmpty())
	{
		int fontSize = nodeTree.Get("FontSize", 0);
	
		const rapidjson::Value* fontResourceNode = nodeTree.GetMember("FontResource");
		StringRef fontName = fontResourceNode != nullptr ? fontResourceNode->GetString("Path", nullptr) : StringRef::Empty;
		fontName = FontFactory::Instance().ExistsOrDefault(fontName);
		FontId fontId(fontName);
		fontId.SetSize(fontSize);

		Color4F textColor = ToColor(nodeTree.GetMember("TextColor"));

		label = NodeFactory::Instance().CreateSingleLineLabel(fontId, StringParser::ToW(buttonText), Alignment::MiddleCenter);
		label->SetColor(textColor);
		label->SetAnchorPoint(AnchorPoint::MiddleCenter);
		label->SetDock(DockPoint::MiddleCenter);
		//outline color...
	}

	IButton* button = nullptr;
	if (!normalPathFileId.IsEmpty() || !selectedPathFileId.IsEmpty() || !disabledPathFileId.IsEmpty())
	{
		bool isEnableNineGrid = nodeTree.Get("Scale9Enable", false);
		Size2F size = Size2F::Zero;
		ThicknessF padding = ThicknessF::Zero;
		if (isEnableNineGrid)
		{
			const rapidjson::Value& jsonSize = nodeTree["Size"];
			size = Size2F(jsonSize.Get("X",0.f), jsonSize.Get("Y", 0.f));
			auto originX = nodeTree.Get("Scale9OriginX", 0);
			auto originY = nodeTree.Get("Scale9OriginY", 0);
			auto nineWidth = nodeTree.Get("Scale9Width", 0);
			auto nineHeight = nodeTree.Get("Scale9Height", 0);
			padding = ThicknessF(originX,  size.Width -  nineWidth - originX, size.Height -  nineHeight - originY, originY);
		}
		auto textureButton = NodeFactory::Instance().CreateTextureButton(normalPathFileId, selectedPathFileId, disabledPathFileId);
		textureButton->SetSize(size);
		textureButton->EnableNineGrid(isEnableNineGrid);
		textureButton->SetTexturePadding(padding);
		button = textureButton;
		if (label)
			button->AddChild(label);
	}
	else if (label)
	{
		button = new LabelButton(label);
		button->Initialize();
	}
	else
	{
		Log::Error("NO button");
	}

	bool inputEnabled = nodeTree.Get("TouchEnable", true);
	button->EnableInput(inputEnabled);

	bool isButtonEnabled = nodeTree.Get("DisplayState", true);
	button->SetButtonState(isButtonEnabled ? ButtonState::Normal : ButtonState::Disabled);

	StringRef callBackName = nodeTree.GetString("CallBackName", nullptr);
	StringRef callbackType = nodeTree.GetString("CallBackType", nullptr);
	SetButtonEvent(button, callbackType, callBackName);
	
	SetPropsWithJson(button, nodeTree,flags);
	return button;
}

void ButtonReader::SetButtonEvent(IButton* button, StringRef callbackType, StringRef callBackName)
{
	if (!callBackName.IsEmpty())
	{
		if (callbackType == "Touch")
		{
			//from touch began to end
			button->MutableInput().Monitor(InputEventType::TouchBegan, callBackName);
			button->MutableInput().Monitor(InputEventType::TouchMoved, callBackName);
			button->MutableInput().Monitor(InputEventType::TouchEnded, callBackName);
			button->MutableInput().Monitor(InputEventType::TouchCancelled, callBackName);

		}
		else if (callbackType == "Click")
		{
			button->MutableInput().Monitor(InputEventType::Tap, callBackName);
		}
		else
		{

		}

	}

}


MEDUSA_COCOS_END;