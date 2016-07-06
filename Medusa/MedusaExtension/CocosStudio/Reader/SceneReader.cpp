#include "MedusaExtensionPreCompiled.h"
#include "SceneReader.h"
#include "Node/Scene/UIScene.h"
#include "ReaderFactory.h"
#include "CocosStudio/CSParseBinary_generated.h"
#include "Node/NodeFactory.h"

MEDUSA_COCOS_BEGIN;


INode* SceneReader::CreateNodeWithFlatBuffers(INodeEditor& editor, const flatbuffers::Table* nodeOptions, const StringRef& className /*= StringRef::Empty*/, NodeCreateFlags flags /*= NodeCreateFlags::None*/)
{
	IScene* node = nullptr;
	if (className.IsEmpty())
	{
		node = NodeFactory::Instance().Create<UIScene>(IEventArg::Empty,flags);
	}
	else
	{
		node = (IScene*)NodeFactory::Instance().Create(className, FileIdRef::Empty, FileIdRef::Empty,IEventArg::Empty,flags);
	}

	SetPropsWithFlatBuffers(node, nodeOptions, flags);

	return node;
}

INode* SceneReader::CreateNodeWithJson(INodeEditor& editor, const rapidjson::Value& nodeTree, const StringRef& className /*= StringRef::Empty*/, NodeCreateFlags flags /*= NodeCreateFlags::None*/)
{
	IScene* node = nullptr;
	if (className.IsEmpty())
	{
		node = NodeFactory::Instance().Create<UIScene>(IEventArg::Empty,flags);
	}
	else
	{
		node = (IScene*)NodeFactory::Instance().Create(className, FileIdRef::Empty, FileIdRef::Empty,IEventArg::Empty,flags);
	}

	/*const rapidjson::Value* contentNode = nodeTree.GetMember("Content")->GetMember("Content");
	const rapidjson::Value* animationNode = contentNode->GetMember("Animation");
	const rapidjson::Value* animationListNode = contentNode->GetMember("AnimationList");
	const rapidjson::Value* objectDataNode = contentNode->GetMember("ObjectData");*/

	SetPropsWithJson(node, nodeTree, flags);


	return node;
}

MEDUSA_COCOS_END;

