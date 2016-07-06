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
#include "Resource/Model/Mesh/Fixed/TextureNineGridMesh.h"
#include "Core/IO/FileSystem.h"
#include "Core/IO/Map/FileMapOrderItem.h"
#include "Resource/TextureAtlas/TextureAtlasRegion.h"
#include "Resource/Material/MaterialFactory.h"
#include "Resource/TextureAtlas/TextureAtlasFactory.h"

MEDUSA_COCOS_BEGIN;

INode* ImageViewReader::CreateNodeWithFlatBuffers(INodeEditor& editor, const flatbuffers::Table* imageOptions, const StringRef& className, NodeCreateFlags flags /*= NodeCreateFlags::None*/)
{
	auto options = (flatbuffers::ImageViewOptions*)imageOptions;
	StringRef fullName = options->fileNameData()->path()->c_str();
	auto fileId = FileId::ParseFrom(fullName);
	auto sprite = CreateNineGridSprite(options->scale9Enabled(), options->scale9Size(), options->widgetOptions()->size(), options->capInsets(), fileId);
	SetPropsWithFlatBuffers(sprite, (flatbuffers::Table*) options->widgetOptions(), flags);
	return sprite;
}

NineGridSprite* ImageViewReader::CreateNineGridSprite(uint8 enable, const flatbuffers::FlatSize* nineGridSize, const flatbuffers::FlatSize* widgetSize, const flatbuffers::CapInsets* capInset, const FileIdRef& fileId)
{
	bool isEnableNineGrid = enable != 0;
	Size2F size = Size2F::Zero;
	ThicknessF padding = ThicknessF::Zero;
	if (isEnableNineGrid)
	{
		size = Size2F(nineGridSize->width(), nineGridSize->height());
	}
	else
	{
		size = Size2F(widgetSize->width(), widgetSize->height());
	}
	padding = ThicknessF(capInset->x(), size.Width - capInset->width() - capInset->x(), size.Height - capInset->height() - capInset->y(), capInset->y());
	auto* sprite = NodeFactory::Instance().CreateNineGridSprite(size, fileId, padding);
	sprite->EnableNineGrid(isEnableNineGrid);
	return sprite;

	/*
	Share<IMaterial> material = nullptr;
	auto* orderItem = FileSystem::Instance().FindOrderItem(fileId);
	if (orderItem->Region() != nullptr)
	{
		TextureAtlasRegion* region = (TextureAtlasRegion*)orderItem->Region();
		if (region->IsPolygon())
		{
			Log::AssertFailedFormat("Not support polygon region mode on {} when CreateNineGridTexture", fileId.Name);
			return nullptr;
		}
		material = region->CreateMaterial();
	}
	else if (!orderItem->RegionName().IsEmpty())
	{
		auto regioFileId = FileId::ParseFrom(orderItem->GetFileEntry()->Path());
		auto region = TextureAtlasFactory::Instance().CreateAtlasRegion(orderItem->RegionName(), regioFileId);
		if (region == nullptr)
		{
			Log::AssertFailedFormat("Cannot find region:{} in {}", orderItem->RegionName(), regioFileId);
			return nullptr;
		}

		if (region->IsPolygon())
		{
			Log::AssertFailedFormat("Not support polygon region mode on {} when CreateNineGridTexture", regioFileId.Name);
			return nullptr;
		}

		material = region->CreateMaterial();
	}
	else 
	{
		material = MaterialFactory::Instance().CreateSingleTexture(fileId);
	}
	Size2F size = material->FirstTexture()->Size();
	ThicknessF padding = ThicknessF(capInset->x(), size.Width - capInset->width() - capInset->x(), size.Height - capInset->height() - capInset->y(), capInset->y());
	Share<TextureNineGridMesh> mesh = new TextureNineGridMesh();
	mesh->Initialize(Size2F(widgetSize->width(), widgetSize->height()), size,padding);
	auto renderObject = RenderingObject(mesh, material);

	NineGridSprite* sprite = new NineGridSprite();
	sprite->EnableLayout(false);	//suppress duplicate arrange after size changed
	sprite->SetRenderingObject(renderObject);
	sprite->SetTexturePadding(padding);
	sprite->SetSize(renderObject.Mesh()->Size());
	sprite->Initialize();
	sprite->EnableLayout(true);
	sprite->EnableNineGrid(enable != 0);

	return sprite;
	*/
}

INode* ImageViewReader::CreateNodeWithJson(INodeEditor& editor, const rapidjson::Value& nodeTree, const StringRef& className /*= StringRef::Empty*/, NodeCreateFlags flags /*= NodeCreateFlags::None*/)
{
	return nullptr;
}


MEDUSA_COCOS_END;
