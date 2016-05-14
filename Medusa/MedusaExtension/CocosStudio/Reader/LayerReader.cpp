#include "MedusaExtensionPreCompiled.h"
#include "LayerReader.h"
#include "Node/Layer/LayerFactory.h"
#include "Node/Layer/NormalLayer.h"
#include "ReaderFactory.h"
#include "CocosStudio/CSParseBinary_generated.h"
#include "Application/Settings/ApplicationSettings.h"

MEDUSA_COCOS_BEGIN;

INode* LayerReader::CreateNodeWithFlatBuffers(INodeEditor& editor, const flatbuffers::Table *nodeOptions, const StringRef& className, NodeCreateFlags flags /*= NodeCreateFlags::None*/)
{
	ILayer* node = nullptr;
	if (className.IsEmpty())
	{
		node = LayerFactory::Instance().Create<NormalLayer>(IEventArg::Empty,flags);
	}
	else
	{
		node = LayerFactory::Instance().Create(className, FileIdRef::Empty, IEventArg::Empty, flags);
	}

	SetPropsWithFlatBuffers(node, nodeOptions,flags);


	return node;
}

INode* LayerReader::CreateNodeWithJson(INodeEditor& editor, const rapidjson::Value& nodeTree, const StringRef& className /*= StringRef::Empty*/, NodeCreateFlags flags /*= NodeCreateFlags::None*/)
{
	ILayer* node = nullptr;
	if (className.IsEmpty())
	{
		node = LayerFactory::Instance().Create<NormalLayer>(IEventArg::Empty, flags);
	}
	else
	{
		node = LayerFactory::Instance().Create(className, FileIdRef::Empty, IEventArg::Empty, flags);
	}

	SetPropsWithJson(node, nodeTree,flags);

#ifdef MEDUSA_SCRIPT
	if (ApplicationSettings::Instance().HasScriptBinding())
	{
		node->TryAttachScriptObject();
	}
#endif
	return node;
}

MEDUSA_IMPLEMENT_COCOS_READER(LayerReader);
MEDUSA_COCOS_END;
