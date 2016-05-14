#include "MedusaExtensionPreCompiled.h"
#include "ImageViewReader.h"
#include "SpriteReader.h"
#include "Core/String/StringRef.h"
#include "Core/IO/FileId.h"
#include "Node/Sprite/Sprite.h"
#include "Node/NodeFactory.h"
#include "ReaderFactory.h"
#include "Rendering/RenderingObjectFactory.h"
#include "Rendering/RenderingObject.h"
#include "Resource/Model/Mesh/IMesh.h"
#include "CocosStudio/CSParseBinary_generated.h"
#include "Core/IO/Path.h"
MEDUSA_COCOS_BEGIN;

INode* ImageViewReader::CreateNodeWithFlatBuffers(INodeEditor& editor, const flatbuffers::Table* imageOptions, const StringRef& className, NodeCreateFlags flags /*= NodeCreateFlags::None*/)
{
	auto options = (flatbuffers::ImageViewOptions*)imageOptions;
	bool isEnableNineGrid = options->scale9Enabled() != 0;
	StringRef fullName = options->fileNameData()->path()->c_str();
	fullName = Path::GetFileName(fullName);

	auto flatbufferSize = options->scale9Size();
	Size2F size = Size2F::Zero;
	ThicknessF padding = ThicknessF::Zero;

	if (isEnableNineGrid)
	{
		size = Size2F(flatbufferSize->width(), flatbufferSize->height());
	}
	else
	{
		Size2F contentSize(options->widgetOptions()->size()->width(), options->widgetOptions()->size()->height());
		size = contentSize;
	}

	auto capInset = options->capInsets();
	padding = ThicknessF(capInset->x(), size.Width - capInset->width() - capInset->x(), size.Height - capInset->height() - capInset->y(), capInset->y());

	auto* sprite = NodeFactory::Instance().CreateNineGridSprite(size, fullName, padding);
	sprite->EnableNineGrid(isEnableNineGrid);

	SetPropsWithFlatBuffers(sprite, (flatbuffers::Table*) options->widgetOptions(), flags);
	return sprite;
}

INode* ImageViewReader::CreateNodeWithJson(INodeEditor& editor, const rapidjson::Value& nodeTree, const StringRef& className /*= StringRef::Empty*/, NodeCreateFlags flags /*= NodeCreateFlags::None*/)
{
	return nullptr;
}


MEDUSA_IMPLEMENT_COCOS_READER(ImageViewReader);
MEDUSA_COCOS_END;
