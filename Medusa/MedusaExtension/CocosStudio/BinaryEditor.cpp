#include "MedusaExtensionPreCompiled.h"
#include "CocosStudio/BinaryEditor.h"
#include "Core/IO/FileSystem.h"
#include "Core/String/StringRef.h"
#include "Core/IO/FileId.h"
#include "Node/Layer/LayerFactory.h"
#include "CocosStudio/Reader/ReaderFactory.h"
#include "Node/Scene/IScene.h"
#include "Node/Layer/ILayer.h"


MEDUSA_COCOS_BEGIN;

BinaryEditor::BinaryEditor()
{

}

BinaryEditor::~BinaryEditor()
{

}

INode* BinaryEditor::Create(const StringRef& className, const FileIdRef& editorFile, const IEventArg& e /*= IEventArg::Empty*/, NodeCreateFlags flags /*= NodeCreateFlags::None*/)
{
	auto data = FileSystem::Instance().ReadAllData(editorFile);
	RETURN_NULL_IF_EMPTY(data);
	auto csParsebinary = flatbuffers::GetCSParseBinary(data.Data());
	return NodeWithFlatBuffers(className, csParsebinary->nodeTree(), flags);
}

INode* BinaryEditor::NodeWithFlatBuffers(const StringRef& className, const flatbuffers::NodeTree *nodeTree, NodeCreateFlags flags /*= NodeCreateFlags::None*/)
{
	RETURN_NULL_IF_FALSE(nodeTree);
	auto options = nodeTree->options();

	StringRef className2 = nodeTree->classname()->c_str();
	StringRef customClassName = nodeTree->customClassName()->c_str();
	if (customClassName != "")
	{
		className2 = customClassName;
	}
	StringRef readerName = GetReaderName(className2, options);

	auto reader = ReaderFactory::Instance().Create(readerName);
	RETURN_NULL_IF_NULL(reader);

	INode* node = reader->CreateNodeWithFlatBuffers(*this, options->data(), className, flags);
	RETURN_NULL_IF_NULL(node);

	flags = GetChildrenCreateFlags(flags);

	auto children = nodeTree->children();
	int size = children->size();
	for (int i = 0; i < size; ++i)
	{
		auto subNodeTree = children->Get(i);
		auto child = NodeWithFlatBuffers(StringRef::Empty, subNodeTree, flags);
		if (node->IsA<IScene>() && child->IsA<ILayer>())
		{
			((IScene*)node)->PushLayer((ILayer*)child);
		}
		else
		{
			node->AddChild(child);
		}
	}

	return node;
}


StringRef BinaryEditor::GetReaderName(const StringRef& name, const flatbuffers::Options* options)
{
	if (name == "Node")
	{
		auto widetOptions = (flatbuffers::WidgetOptions*) options->data();
		StringRef widgetName = widetOptions->name()->c_str();
		if (widgetName == "Scene")
		{
			return "SceneReader";
		}
		else if (widgetName == "Layer")
		{
			return "LayerReader";
		}
	}
	if (name == "Panel")
	{
		return "LayoutReader";
	}
	else if (name == "TextArea")
	{
		return "TextReader";
	}
	else if (name == "TextButton" || name == "Button")
	{
		return "ButtonReader";
	}
	else if (name == "Label")
	{
		return "TextReader";
	}
	else if (name == "LabelAtlas")
	{
		return  "TextAtlasReader";
	}
	else if (name == "LabelBMFont")
	{
		return  "TextBMFontReader";
	}
	else if (name == "ProjectNode")
	{
		return  "ProjectNodeReader";
	}
	else if (name == "Sprite")
	{
		return "SpriteReader";
	}
	else if (name == "ImageView")
	{
		return "ImageViewReader";
	}
	else if (name == "Text")
	{
		return "TextReader";
	}

	Log::AssertFailedFormat("Invalid name:{}", name);

	return StringRef::Empty;
}

MEDUSA_COCOS_END;
