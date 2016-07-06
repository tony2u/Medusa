#include "MedusaExtensionPreCompiled.h"
#include "LoadingBarReader.h"
#include "Core/IO/FileId.h"
#include "Node/Control/ProgressBar/TextureProgressBar.h"
#include "Node/NodeFactory.h"
#include "ReaderFactory.h"
#include "CocosStudio/CSParseBinary_generated.h"
#include "Rendering/RenderingObjectFactory.h"
#include "Rendering/RenderingObject.h"
#include "Resource/Model/Mesh/IMesh.h"
#include "Core/IO/Path.h"

MEDUSA_COCOS_BEGIN;


INode* LoadingBarReader::CreateNodeWithFlatBuffers(INodeEditor& editor, const flatbuffers::Table* loadingBarOptions, const StringRef& className /*= StringRef::Empty*/, NodeCreateFlags flags /*= NodeCreateFlags::None*/)
{
	auto options = (flatbuffers::LoadingBarOptions*)loadingBarOptions;
	auto fileId = FileId::ParseFrom(options->textureData()->path()->c_str());
	auto loadingBar = NodeFactory::Instance().CreateTextureProgressBar((ProgressType)(options->direction()), fileId, options->percent()/100.f);
	SetPropsWithFlatBuffers(loadingBar, (flatbuffers::Table*) options->widgetOptions());
	return loadingBar;
}

INode* LoadingBarReader::CreateNodeWithJson(INodeEditor& editor, const rapidjson::Value& nodeTree, const StringRef& className /*= StringRef::Empty*/, NodeCreateFlags flags /*= NodeCreateFlags::None*/)
{
	return nullptr;
}


MEDUSA_COCOS_END;
