#include "MedusaExtensionPreCompiled.h"
#include "LayerReader.h"
#include "Node/Layer/LayerFactory.h"
#include "Node/Layer/NormalLayer.h"
#include "ReaderFactory.h"
#include "CocosStudio/CSParseBinary_generated.h"
MEDUSA_COCOS_BEGIN;

INode* LayerReader::CreateNodeWithFlatBuffers(INodeEditor& editor, const flatbuffers::Table *nodeOptions, const StringRef& className)
{
	ILayer* node = nullptr;
	if (className.IsEmpty())
	{
		node = LayerFactory::Instance().Create<NormalLayer>();
	}
	else
	{
		node = LayerFactory::Instance().Create(className, FileIdRef::Empty);
	}

	SetPropsWithFlatBuffers(node, nodeOptions);

	return node;
}

INode* LayerReader::CreateNodeWithJson(INodeEditor& editor, const rapidjson::Value& nodeTree, const StringRef& className /*= StringRef::Empty*/)
{
	ILayer* node = nullptr;
	if (className.IsEmpty())
	{
		node = LayerFactory::Instance().Create<NormalLayer>();
	}
	else
	{
		node = LayerFactory::Instance().Create(className, FileIdRef::Empty);
	}

	SetPropsWithJson(node, nodeTree);

	return node;
}

MEDUSA_IMPLEMENT_COCOS_READER(LayerReader);
MEDUSA_COCOS_END;
