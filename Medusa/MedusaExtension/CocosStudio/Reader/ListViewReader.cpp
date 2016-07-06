#include "MedusaExtensionPreCompiled.h"
#include "ImageViewReader.h"
#include "PanelReader.h"
#include "ListViewReader.h"
#include "Core/String/StringRef.h"
#include "Core/IO/FileId.h"
#include "Node/Panel/CanvasPanel.h"
#include "Node/NodeFactory.h"
#include "ReaderFactory.h"
#include "CocosStudio/CSParseBinary_generated.h"
#include "Rendering/RenderingObjectFactory.h"
#include "Rendering/RenderingObject.h"
#include "Resource/Model/Mesh/IMesh.h"
#include "Resource/Model/Mesh/Fixed/ShapeQuadMesh.h"
#include "Node/Shape/IShape.h"
#include "Core/IO/Path.h"
#include "Node/Sprite/NineGridSprite.h"

MEDUSA_COCOS_BEGIN;


INode* ListViewReader::CreateNodeWithFlatBuffers(INodeEditor& editor, const flatbuffers::Table* nodeTree, const StringRef& className /*= StringRef::Empty*/, NodeCreateFlags flags /*= NodeCreateFlags::None*/)
{
	auto options = (flatbuffers::ListViewOptions*)nodeTree;
	auto panel = (NodeFactory::Instance().CreatePanel(PanelType::Stack));
	bool clipEnabled = options->clipEnabled() != 0;
	panel->EnableClipToBound(clipEnabled);

	StringRef fullName = options->backGroundImageData()->path()->c_str();
	auto fileId = FileId::ParseFrom(fullName);
	if (fileId.IsValid())
	{
		auto sprite = ImageViewReader::CreateNineGridSprite(options->backGroundScale9Enabled(), options->scale9Size(), options->widgetOptions()->size(), options->capInsets(), fileId);
		sprite->EnableManaged(true);
		panel->AddChild(sprite);
	}

	switch (options->colorType())
	{
	case 0:
		break;
	case 1:
	{
		INode* rect = PanelReader::CreateSingleColorRect(options->bgColorOpacity(), *options->bgColor(), *options->widgetOptions()->size());
		rect->EnableManaged(true);
		panel->AddChild(rect);
	}
		break; 
	case 2:
	{
		INode* rect = PanelReader::CreateGradientRect(options->bgColorOpacity(), *options->bgColor(), *options->widgetOptions()->size(), *options->bgStartColor(), *options->bgEndColor(),*options->colorVector());
		rect->EnableManaged(true);
		panel->AddChild(rect);
	}
	break;
	default:
		Log::AssertFailed("ListViewReader PanelBackGroundColorType  Error");
		break;
	}




	SetPropsWithFlatBuffers(panel, (flatbuffers::Table*) options->widgetOptions());
	return panel;
}


INode* ListViewReader::CreateNodeWithJson(INodeEditor& editor, const rapidjson::Value& nodeTree, const StringRef& className /*= StringRef::Empty*/, NodeCreateFlags flags /*= NodeCreateFlags::None*/)
{
	return nullptr;
}


MEDUSA_COCOS_END;
