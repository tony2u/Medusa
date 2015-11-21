// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "MeshFactory.h"
#include "Resource/Font/FontFactory.h"
#include "Resource/Material/MaterialFactory.h"
#include "Resource/ResourceNames.h"
#include "Resource/Effect/EffectFactory.h"
#include "Resource/Model/Mesh/Fixed/ShapeQuadMesh.h"
#include "Resource/Model/Mesh/Fixed/ShapeTriangleMesh.h"
#include "Resource/Model/Mesh/General/ShapeGeneralMesh.h"
#include "Resource/Model/Mesh/Fixed/TextureQuadMesh.h"
#include "Resource/Model/Mesh/Fixed/TextureNineGridMesh.h"
#include "Resource/Model/Mesh/General/TextureGeneralMesh.h"
#include "Resource/TextureAtlas/TextureAtlasFactory.h"
#include "Core/Log/Log.h"
#include "Resource/TextureAtlas/TextureAtlasRegion.h"
#include "Resource/TextureAtlas/TextureAtlasPage.h"
#include "Resource/Texture/ITexture.h"
#include "Core/IO/FileSystem.h"
#include "Core/IO/Map/FileMapOrderItem.h"


MEDUSA_BEGIN;

MeshFactory::MeshFactory()
{

}

MeshFactory::~MeshFactory()
{

}

bool MeshFactory::Initialize()
{
	return true;
}

bool MeshFactory::Uninitialize()
{
	return true;
}


ShapeQuadMesh* MeshFactory::CreateShapeQuadMesh(const Size2F& rectSize, const Color4F& color)
{
	IMaterial* material = MaterialFactory::Instance().CreateEmpty(MEDUSA_PREFIX(Shape));
	RETURN_NULL_IF_NULL(material);
	IEffect* effect = EffectFactory::Instance().CreateSinglePassDefault(RenderPassNames::Shape);
	RETURN_NULL_IF_NULL(effect);

	ShapeQuadMesh* mesh = new ShapeQuadMesh(effect, material);
	mesh->Initialize(rectSize, color);
	return mesh;
}

ShapeQuadMesh* MeshFactory::CreateShapeQuadMesh(const Rect2F& rect, const Color4F& color)
{
	IMaterial* material = MaterialFactory::Instance().CreateEmpty(MEDUSA_PREFIX(Shape));
	RETURN_NULL_IF_NULL(material);
	IEffect* effect = EffectFactory::Instance().CreateSinglePassDefault(RenderPassNames::Shape);
	RETURN_NULL_IF_NULL(effect);
	ShapeQuadMesh* mesh = new ShapeQuadMesh(effect, material);
	mesh->Initialize(rect, color);
	return mesh;
}


ShapeTriangleMesh* MeshFactory::CreateShapeTriangleMesh(const Point3F& p1, const Point3F& p2, const Point3F& p3, const Color4F& color)
{
	IMaterial* material = MaterialFactory::Instance().CreateEmpty(MEDUSA_PREFIX(Shape));
	RETURN_NULL_IF_NULL(material);
	IEffect* effect = EffectFactory::Instance().CreateSinglePassDefault(RenderPassNames::Shape);
	RETURN_NULL_IF_NULL(effect);
	ShapeTriangleMesh* mesh = new ShapeTriangleMesh(effect, material);
	mesh->Initialize(p1, p2, p3, color);
	return mesh;
}

ShapeTriangleMesh* MeshFactory::CreateShapeTriangleMesh(float width, float height, const Color4F& color)
{
	IMaterial* material = MaterialFactory::Instance().CreateEmpty(MEDUSA_PREFIX(Shape));
	RETURN_NULL_IF_NULL(material);
	IEffect* effect = EffectFactory::Instance().CreateSinglePassDefault(RenderPassNames::Shape);
	RETURN_NULL_IF_NULL(effect);
	ShapeTriangleMesh* mesh = new ShapeTriangleMesh(effect, material);
	mesh->Initialize(width, height, color);
	return mesh;
}

ShapeGeneralMesh* MeshFactory::CreateShapeQuadBorderMesh(const Size2F& rectSize, const Color4F& color)
{
	IMaterial* material = MaterialFactory::Instance().CreateEmpty(MEDUSA_PREFIX(Shape));
	RETURN_NULL_IF_NULL(material);
	IEffect* effect = EffectFactory::Instance().CreateSinglePassDefault(RenderPassNames::Shape);
	RETURN_NULL_IF_NULL(effect);
	ShapeGeneralMesh* mesh = new ShapeGeneralMesh(effect, material);
	mesh->Initialize(rectSize, color, true);
	return mesh;
}

ShapeGeneralMesh* MeshFactory::CreateShapeQuadBorderMesh(const Rect2F& rect, const Color4F& color)
{
	IMaterial* material = MaterialFactory::Instance().CreateEmpty(MEDUSA_PREFIX(Shape));
	RETURN_NULL_IF_NULL(material);
	IEffect* effect = EffectFactory::Instance().CreateSinglePassDefault(RenderPassNames::Shape);
	RETURN_NULL_IF_NULL(effect);
	ShapeGeneralMesh* mesh = new ShapeGeneralMesh(effect, material);
	mesh->Initialize(rect, color, true);
	return mesh;
}

ShapeGeneralMesh* MeshFactory::CreateShapeTriangleBorderMesh(const Point3F& p1, const Point3F& p2, const Point3F& p3, const Color4F& color)
{
	IMaterial* material = MaterialFactory::Instance().CreateEmpty(MEDUSA_PREFIX(Shape));
	RETURN_NULL_IF_NULL(material);
	IEffect* effect = EffectFactory::Instance().CreateSinglePassDefault(RenderPassNames::Shape);
	RETURN_NULL_IF_NULL(effect);
	ShapeGeneralMesh* mesh = new ShapeGeneralMesh(effect, material);
	mesh->Initialize(p1, p2, p3, color, true);
	return mesh;
}

ShapeGeneralMesh* MeshFactory::CreateShapeTriangleBorderMesh(float width, float height, const Color4F& color)
{
	IMaterial* material = MaterialFactory::Instance().CreateEmpty(MEDUSA_PREFIX(Shape));
	RETURN_NULL_IF_NULL(material);
	IEffect* effect = EffectFactory::Instance().CreateSinglePassDefault(RenderPassNames::Shape);
	RETURN_NULL_IF_NULL(effect);
	ShapeGeneralMesh* mesh = new ShapeGeneralMesh(effect, material);
	mesh->Initialize(width, height, color, true);
	return mesh;
}

ShapeGeneralMesh* MeshFactory::CreateShapeCircleMesh(float radius, float precision, const Color4F& color)
{
	IMaterial* material = MaterialFactory::Instance().CreateEmpty(MEDUSA_PREFIX(Shape));
	RETURN_NULL_IF_NULL(material);
	IEffect* effect = EffectFactory::Instance().CreateSinglePassDefault(RenderPassNames::Shape);
	RETURN_NULL_IF_NULL(effect);
	ShapeGeneralMesh* mesh = new ShapeGeneralMesh(effect, material);
	uint count = Math::Ceil(Math::PI2 / precision);
	mesh->SetDrawMode(GraphicsDrawMode::TriangleFan);
	Point3F center(radius, radius);
	mesh->AppendVertex(center);
	mesh->AppendIndex(0);
	mesh->SetSize(msize3(2 * radius, 2 * radius, 0.f));
	
	FOR_EACH_SIZE(i, count)
	{
		float a = i*precision;
		Point3F pos(radius+radius*Math::Cos(a), radius+radius*Math::Sin(a));
		mesh->AppendVertex(pos);
		mesh->AppendIndex(i+1);
	}
	mesh->AppendIndex(1);

	mesh->SetColorAll(color);
	
	return mesh;
}

ShapeGeneralMesh* MeshFactory::CreateShapeCircleBorderMesh(float radius, float precision, const Color4F& color)
{
	IMaterial* material = MaterialFactory::Instance().CreateEmpty(MEDUSA_PREFIX(Shape));
	RETURN_NULL_IF_NULL(material);
	IEffect* effect = EffectFactory::Instance().CreateSinglePassDefault(RenderPassNames::Shape);
	RETURN_NULL_IF_NULL(effect);
	ShapeGeneralMesh* mesh = new ShapeGeneralMesh(effect, material);
	uint count = Math::Ceil(Math::PI2 / precision);
	mesh->SetDrawMode(GraphicsDrawMode::LineLoop);
	mesh->SetSize(msize3(2 * radius, 2 * radius, 0.f));

	FOR_EACH_SIZE(i, count)
	{
		float a = i*precision;
		Point3F pos(radius + radius*Math::Cos(a), radius + radius*Math::Sin(a));
		mesh->AppendVertex(pos);
		mesh->AppendIndex(i);
	}
	mesh->SetColorAll(color);

	return mesh;
}

TextureQuadMesh* MeshFactory::CreateTextureQuadMesh(const FileIdRef& textureName, const Rect2F& textureRect/*=Rect2F::Zero*/, const Color4F& color/*=Color4F::White*/)
{
	IMaterial* material = MaterialFactory::Instance().Create(textureName, ShaderSamplerNames::Texture);
	RETURN_NULL_IF_NULL(material);
	IEffect* effect = EffectFactory::Instance().CreateSinglePassDefault(RenderPassNames::Texture);
	RETURN_NULL_IF_NULL(effect);

	const Size2U& textureSize = material->FirstTexture()->Size();
	TextureQuadMesh* mesh = new TextureQuadMesh(effect, material);

	mesh->Initialize(textureSize, textureRect, color);

	return mesh;
}


TextureQuadMesh* MeshFactory::CreateTextureQuadMesh(const FileIdRef& textureName, const FileMapOrderItem& orderItem, const Rect2F& textureRect /*= Rect2F::Zero*/, const Color4F& color /*= Color4F::White*/)
{
	IMaterial* material = MaterialFactory::Instance().Create(textureName, orderItem, ShaderSamplerNames::Texture);
	RETURN_NULL_IF_NULL(material);
	IEffect* effect = EffectFactory::Instance().CreateSinglePassDefault(RenderPassNames::Texture);
	RETURN_NULL_IF_NULL(effect);

	const Size2U& textureSize = material->FirstTexture()->Size();
	TextureQuadMesh* mesh = new TextureQuadMesh(effect, material);

	mesh->Initialize(textureSize, textureRect, color);

	return mesh;
}

TextureNineGridMesh* MeshFactory::CreateTextureNineGridMesh(const Size2F& targetSize, const FileIdRef& textureName, const ThicknessF& padding, const Rect2F& textureRect/*=Rect2F::Zero*/, const Color4F& color/*=Color4F::White*/)
{
	IMaterial* material = MaterialFactory::Instance().Create(textureName, ShaderSamplerNames::Texture);
	RETURN_NULL_IF_NULL(material);
	IEffect* effect = EffectFactory::Instance().CreateSinglePassDefault(RenderPassNames::Texture);
	RETURN_NULL_IF_NULL(effect);

	TextureNineGridMesh* mesh = new TextureNineGridMesh(effect, material);
	mesh->Initialize(targetSize, padding, textureRect, color);
	return mesh;
}

TextureGeneralMesh* MeshFactory::CreateTextureGeneralMesh(ITexture* texture, bool isStatic/*=false*/)
{
	RETURN_NULL_IF_NULL(texture);
	IMaterial* material = MaterialFactory::Instance().Create(texture->GetFileId(), texture);
	RETURN_NULL_IF_NULL(material);

	IEffect* effect = EffectFactory::Instance().CreateSinglePassDefault(RenderPassNames::Texture);
	RETURN_NULL_IF_NULL(effect);

	TextureGeneralMesh* mesh = new TextureGeneralMesh(effect, material, isStatic);
	return mesh;
}

TextureQuadMesh* MeshFactory::CreateTextureQuadMeshFromAtlasRegion(const StringRef& regionName, const FileIdRef& atlasFileId, TextureAtlasFileFormat fileFormat /*= TextureAtlasFileFormat::Spine*/, uint atlasPageCount /*= 1*/, const Color4F& color/*=Color4F::White*/)
{
	TextureAtlasRegion* region = TextureAtlasFactory::Instance().CreateAtlasRegion(regionName, atlasFileId, fileFormat, atlasPageCount);
	if (region == nullptr)
	{
		Log::AssertFailedFormat("Cannot find region:{}", regionName.c_str());
		return nullptr;
	}
	return CreateTextureQuadMeshFromAtlasRegion(region, color);
}

TextureQuadMesh* MeshFactory::CreateTextureQuadMeshFromAtlasRegion(TextureAtlasRegion* region, const Color4F& color/*=Color4F::White*/)
{
	RETURN_NULL_IF_NULL(region);

	region->AssertMeshLoaded();
	TextureAtlasPage* page = region->Page();
	ITexture* texture = page->GetTexture();

	IMaterial* material = MaterialFactory::Instance().Create(texture->GetFileId(), texture);
	RETURN_NULL_IF_NULL(material);

	IEffect* effect = EffectFactory::Instance().CreateSinglePassDefault(RenderPassNames::Texture);
	RETURN_NULL_IF_NULL(effect);

	TextureQuadMesh* mesh = new TextureQuadMesh(effect, material);
	mesh->Initialize(region->Vertices(), region->Texcoords(), color);

	return mesh;
}




bool MeshFactory::CreateTextureQuadMeshesFromAtlas(SortedDictionary<uint, TextureQuadMesh*>& outMeshes, const StringRef& regionPattern, const FileIdRef& atlasFileId, TextureAtlasFileFormat fileFormat /*= TextureAtlasFileFormat::Spine*/, uint atlasPageCount /*= 1*/, const Color4F& color /*= Color4F::White*/)
{
	TextureAtlas* atlas = TextureAtlasFactory::Instance().Create(atlasFileId, fileFormat, atlasPageCount);
	if (atlas == nullptr)
	{
		Log::AssertFailedFormat("Cannot find texture atlas:{}", atlasFileId.Name.c_str());
		return false;
	}

	if (regionPattern.IsEmpty())
	{
		const List<TextureAtlasPage*>& pages = atlas->Pages();
		FOR_EACH_COLLECTION(i, pages)
		{
			TextureAtlasPage* page = *i;
			ITexture* texture = page->LoadTexture();
			IMaterial* material = MaterialFactory::Instance().Create(texture->GetFileId(), texture);
			IEffect* effect = EffectFactory::Instance().CreateSinglePassDefault(RenderPassNames::Texture);

			const List<TextureAtlasRegion*>& regions = page->Regions();
			FOR_EACH_COLLECTION(j, regions)
			{
				TextureAtlasRegion* region = *j;
				StringRef regionName = region->Name();
				uint outOrder = 0;
				StringParser::TryExtractUInt(regionName, outOrder);
				TextureQuadMesh* mesh = new TextureQuadMesh(effect, material);
				mesh->Initialize(region->Vertices(), region->Texcoords(), color);
				mesh->SetSize(region->OriginalSize());
				outMeshes.Add(outOrder, mesh);
			}
		}
	}
	else
	{
		const List<TextureAtlasPage*>& pages = atlas->Pages();
		FOR_EACH_COLLECTION(i, pages)
		{
			TextureAtlasPage* page = *i;
			ITexture* texture = page->LoadTexture();
			IMaterial* material = MaterialFactory::Instance().Create(texture->GetFileId(), texture);
			IEffect* effect = EffectFactory::Instance().CreateSinglePassDefault(RenderPassNames::Texture);

			const List<TextureAtlasRegion*>& regions = page->Regions();
			FOR_EACH_COLLECTION(j, regions)
			{
				TextureAtlasRegion* region = *j;
				StringRef regionName = region->Name();
				if (regionName.BeginWith(regionPattern))
				{
					regionName.ForceSetBuffer(regionName.Buffer() + regionPattern.Length());	//skip start
					regionName.ForceSetLength(regionName.Length() - regionPattern.Length());
					uint outOrder = 0;
					StringParser::TryExtractUInt(regionName, outOrder);
					TextureQuadMesh* mesh = new TextureQuadMesh(effect, material);
					mesh->Initialize(region->Vertices(), region->Texcoords(), color);
					mesh->SetSize(region->OriginalSize());
					outMeshes.Add(outOrder, mesh);
				}

			}
		}
	}



	return true;

}

bool MeshFactory::CreateTextureQuadMeshesFromTextures(SortedDictionary<uint, TextureQuadMesh*>& outMeshes, const StringRef& textureNamePattern, const Color4F& color /*= Color4F::White*/)
{
	List<const FileMapOrderItem*> outOrderItems;
	if (!FileSystem::Instance().TryGetOrderItems(textureNamePattern, outOrderItems))
	{
		return false;
	}

	for (const FileMapOrderItem* orderItem : outOrderItems)
	{
		TextureQuadMesh* mesh=CreateTextureQuadMesh(FileIdRef(textureNamePattern, orderItem->Order()), *orderItem);
		outMeshes.Add(orderItem->Order(), mesh);
	}

	return true;
}


MEDUSA_END;