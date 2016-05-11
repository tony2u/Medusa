#include "MedusaExtensionPreCompiled.h"
#include "SceneReader.h"
#include "Node/Scene/SceneFactory.h"
#include "Node/Scene/UIScene.h"
#include "ReaderFactory.h"
#include "CocosStudio/CSParseBinary_generated.h"
MEDUSA_COCOS_BEGIN;


INode* SceneReader::CreateNodeWithFlatBuffers(INodeEditor& editor, const flatbuffers::Table* nodeOptions, const StringRef& className /*= StringRef::Empty*/)
{
	IScene* node = nullptr;
	if (className.IsEmpty())
	{
		node = SceneFactory::Instance().Create<UIScene>();
	}
	else
	{
		node = SceneFactory::Instance().Create(className, FileIdRef::Empty);
	}

	SetPropsWithFlatBuffers(node, nodeOptions);

	return node;
}

INode* SceneReader::CreateNodeWithJson(INodeEditor& editor, const rapidjson::Value& nodeTree, const StringRef& className /*= StringRef::Empty*/)
{
	IScene* node = nullptr;
	if (className.IsEmpty())
	{
		node = SceneFactory::Instance().Create<UIScene>();
	}
	else
	{
		node = SceneFactory::Instance().Create(className, FileIdRef::Empty);
	}

	SetPropsWithJson(node, nodeTree);
	return node;
}

MEDUSA_IMPLEMENT_COCOS_READER(SceneReader);
MEDUSA_COCOS_END;

