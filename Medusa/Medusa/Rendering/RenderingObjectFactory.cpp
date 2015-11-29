// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "RenderingObjectFactory.h"
#include "Resource/TextureAtlas/TextureAtlasFactory.h"
#include "Resource/TextureAtlas/TextureAtlasRegion.h"
#include "Resource/TextureAtlas/TextureAtlasPage.h"
#include "Core/Log/Log.h"
#include "Resource/Material/MaterialFactory.h"
#include "RenderingObject.h"
#include "Resource/Model/Mesh/MeshFactory.h"
#include "Resource/Model/Mesh/Fixed/TextureQuadMesh.h"
#include "Resource/Model/Mesh/Fixed/TextureNineGridMesh.h"


MEDUSA_BEGIN;

RenderingObjectFactory::RenderingObjectFactory()
{

}

RenderingObjectFactory::~RenderingObjectFactory()
{

}

bool RenderingObjectFactory::Initialize()
{
	return true;
}

bool RenderingObjectFactory::Uninitialize()
{
	return true;
}


RenderingObject RenderingObjectFactory::CreateFromTexture(const FileIdRef& textureName, const Rect2F& textureRect /*= Rect2F::Zero*/, const Color4F& color /*= Color4F::White*/)
{
	IMaterial* material = MaterialFactory::Instance().CreateSingleTexture(textureName);
	RETURN_OBJECT_IF_NULL(material, RenderingObject::Empty);
	auto* mesh= MeshFactory::Instance().CreateTextureQuadMesh(material->FirstTexture()->Size(), textureRect, color);
	RETURN_OBJECT_IF_NULL(mesh, RenderingObject::Empty);

	return RenderingObject(mesh, material);
}

RenderingObject RenderingObjectFactory::CreateNineGridTexture(const Size2F& targetSize, const FileIdRef& textureName, const ThicknessF& padding, const Rect2F& textureRect /*= Rect2F::Zero*/)
{
	IMaterial* material = MaterialFactory::Instance().CreateSingleTexture(textureName);
	RETURN_NULL_IF_NULL(material);
	TextureNineGridMesh* mesh = MeshFactory::Instance().CreateTextureNineGridMesh(targetSize, material->FirstTexture()->Size(), padding, textureRect);
	RETURN_NULL_IF_NULL(mesh);

	return RenderingObject(mesh, material);

}

RenderingObject RenderingObjectFactory::CreateFromTextureAtlasRegion(TextureAtlasRegion* region, const Color4F& color /*= Color4F::White*/)
{
	TextureQuadMesh* mesh = MeshFactory::Instance().CreateTextureQuadMeshFromAtlasRegion(region);
	RETURN_NULL_IF_NULL(mesh);

	return RenderingObject(mesh, region->GetMaterial());
}

RenderingObject RenderingObjectFactory::CreateFromTextureAtlasRegion(StringRef regionName, const FileIdRef& atlasFileId, TextureAtlasFileFormat fileFormat /*= TextureAtlasFileFormat::Spine*/, uint atlasPageCount /*= 1*/)
{
	TextureAtlasRegion* region = TextureAtlasFactory::Instance().CreateAtlasRegion(regionName, atlasFileId, fileFormat, atlasPageCount);
	return CreateFromTextureAtlasRegion(region);
}

RenderingObject RenderingObjectFactory::CreateFromSingleTextureMaterial(IMaterial* material, const Rect2F& textureRect /*= Rect2F::Zero*/, const Color4F& color /*= Color4F::White*/)
{
	auto* mesh = MeshFactory::Instance().CreateTextureQuadMesh(material->FirstTexture()->Size(), textureRect, color);
	RETURN_OBJECT_IF_NULL(mesh, RenderingObject::Empty);

	return RenderingObject(mesh, material);
}

bool RenderingObjectFactory::CreateFromTextureAtlas(SortedDictionary<uint, RenderingObject>& outObjects, const StringRef& regionPattern, const FileIdRef& atlasFileId, TextureAtlasFileFormat fileFormat /*= TextureAtlasFileFormat::Spine*/, uint atlasPageCount /*= 1*/, const Color4F& color /*= Color4F::White*/)
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
			IMaterial* material = MaterialFactory::Instance().CreateSingleTexture(page->LoadTexture());
			const List<TextureAtlasRegion*>& regions = page->Regions();
			FOR_EACH_COLLECTION(j, regions)
			{
				TextureAtlasRegion* region = *j;
				StringRef regionName = region->Name();
				uint outOrder = 0;
				StringParser::TryExtractUInt(regionName, outOrder);
				auto* mesh=MeshFactory::Instance().CreateTextureQuadMeshFromAtlasRegion(region,color);
			
				outObjects.Add(outOrder, RenderingObject(mesh, material));
			}
		}
	}
	else
	{
		const List<TextureAtlasPage*>& pages = atlas->Pages();
		FOR_EACH_COLLECTION(i, pages)
		{
			TextureAtlasPage* page = *i;
			IMaterial* material = MaterialFactory::Instance().CreateSingleTexture(page->LoadTexture());

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
					auto* mesh = MeshFactory::Instance().CreateTextureQuadMeshFromAtlasRegion(region, color);
					outObjects.Add(outOrder, RenderingObject(mesh, material));

				}

			}
		}
	}



	return true;

}



MEDUSA_END;