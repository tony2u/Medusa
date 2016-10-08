#include "MedusaExtensionPreCompiled.h"
#include "CocosStudio/JsonEditor.h"
#include "Core/IO/FileSystem.h"
#include "CocosStudio/Reader/ReaderFactory.h"
#include "CocosStudio/Reader/SceneReader.h"
#include "Node/Scene/IScene.h"
#include "Node/Layer/ILayer.h"

MEDUSA_COCOS_BEGIN;

JsonEditor::JsonEditor()
{

}

JsonEditor::~JsonEditor()
{

}

INode* JsonEditor::Create(const StringRef& className, const FileIdRef& editorFile, const FileIdRef& scriptFile, const IEventArg& e /*= IEventArg::Empty*/, NodeCreateFlags flags /*= NodeCreateFlags::None*/)
{
	auto data = FileSystem::Instance().ReadAllData(editorFile);
	RETURN_NULL_IF_EMPTY(data);
	rapidjson::Document root;
	const char* beginDoc = (const char*)data.Data();
	root.Parse<rapidjson::kParseStopWhenDoneFlag>(beginDoc);
	if (root.HasParseError())
	{
		rapidjson::ParseErrorCode errorCode = root.GetParseError();
		Log::AssertFailedFormat("Invalid json format:{}. ErrorCode:{}", editorFile.Name, errorCode);
		return nullptr;
	}
	return NodeWithJsonRoot(className, root, flags);
}

INode* JsonEditor::NodeWithJsonRoot(const StringRef& className, const rapidjson::Value& root, NodeCreateFlags flags/* = NodeCreateFlags::None*/)
{
	StringRef type = root.GetMember("Type", nullptr);
	StringRef readerName = GetReaderName(type, root);
	auto reader = ReaderFactory::Instance().Create(readerName);
	RETURN_NULL_IF_NULL(reader);

	INode* node = reader->CreateNodeWithJson(*this, root, className, flags);
	RETURN_NULL_IF_NULL(node);
	flags = GetChildrenCreateFlags(flags);

	const rapidjson::Value& nodeCentent = root["Content"]["Content"];
	//const rapidjson::Value& nodeAnimation = nodeCentent["Animation"];
	//const rapidjson::Value& nodeAnimationList = nodeCentent["AnimationList"];
	const rapidjson::Value& nodeObjectData = nodeCentent["ObjectData"];
	const rapidjson::Value& nodeSizeNode = nodeObjectData["Size"];
	Size2F nodeSize;
	nodeSize.Width = nodeSizeNode.GetMember("X", 0.f);
	nodeSize.Height = nodeSizeNode.GetMember("Y", 0.f);
	node->SetSize(nodeSize);

	const rapidjson::Value* childrenArray = nodeObjectData.GetMemberValue("Children");
	if (childrenArray != nullptr)
	{
		for (auto& subNodeTree : *childrenArray)
		{
			auto child = NodeWithJson(subNodeTree, flags);
			if (node->IsA<IScene>() && child->IsA<ILayer>())
			{
				((IScene*)node)->PushLayer((ILayer*)child, NodePushFlags::ShowPrev);
			}
			else
			{
				node->AddChild(child);
			}
		}
	}


	return node;
}


INode* JsonEditor::NodeWithJson(const rapidjson::Value& jsonNode, NodeCreateFlags flags /*= NodeCreateFlags::None*/)
{
	StringRef type = jsonNode.GetMember("ctype", nullptr);
	StringRef readerName = GetReaderName(type, jsonNode);
	auto reader = ReaderFactory::Instance().Create(readerName);
	if (reader == nullptr)
	{
		Log::AssertFailedFormat("Cannot find reader:{}", readerName);
		return nullptr;
	}

	INode* node = reader->CreateNodeWithJson(*this, jsonNode, StringRef::Empty, flags);
	RETURN_NULL_IF_NULL(node);

	flags = GetChildrenCreateFlags(flags);

	const rapidjson::Value* childrenArray = jsonNode.GetMemberValue("Children");
	if (childrenArray != nullptr)
	{
		for (auto& subNodeTree : *childrenArray)
		{
			auto child = NodeWithJson(subNodeTree, flags);
			node->AddChild(child);
		}
	}

	return node;
}

StringRef JsonEditor::GetReaderName(const StringRef& name, const rapidjson::Value& nodeTree)
{
	if (name == "Scene")
	{
		return "SceneReader";
	}
	else if (name == "Layer")
	{
		return "LayerReader";
	}
	else if (name == "SpriteObjectData")
	{
		return "SpriteReader";
	}
	else if (name == "ProjectNodeObjectData")
	{
		return "ProjectNodeReader";
	}
	else if (name == "TextObjectData")
	{
		return "TextReader";
	}
	else if (name == "ButtonObjectData")
	{
		return "ButtonReader";
	}
	else if (name == "GameMapObjectData")
	{
		return "TiledMapReader";
	}


	Log::AssertFailedFormat("Invalid name:{}", name);

	return StringRef::Empty;
}

MEDUSA_COCOS_END;
