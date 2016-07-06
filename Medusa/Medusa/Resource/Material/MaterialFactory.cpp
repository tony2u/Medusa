// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "MaterialFactory.h"
#include "Resource/Material/IMaterial.h"
#include "Resource/Texture/TextureFactory.h"
#include "Resource/Texture/ImageTexture.h"
#include "Resource/Effect/EffectFactory.h"
#include "Core/IO/FileSystem.h"
#include "Core/IO/Map/FileMapOrderItem.h"

MEDUSA_BEGIN;

MaterialFactory::MaterialFactory()
{

}

MaterialFactory::~MaterialFactory()
{

}

bool MaterialFactory::Initialize()
{
	return true;
}

bool MaterialFactory::Uninitialize()
{
	Clear();
	return true;
}

Share<IMaterial> MaterialFactory::CreateSingleTexture(const FileIdRef& textureFileId, ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	RETURN_NULL_IF_FALSE(textureFileId.IsValid());
	Share<IMaterial> result = nullptr;
	if (shareType!=ResourceShareType::None)
	{
		result = Find(textureFileId);
		RETURN_SELF_IF_NOT_NULL(result);
	}
	
	auto texture = TextureFactory::Instance().CreateFromFile(textureFileId, ShaderSamplerNames::Texture);
	auto effect = EffectFactory::Instance().CreateSinglePassDefault(RenderPassNames::Texture);
	result = new IMaterial(texture, effect, GraphicsDrawMode::Triangles, textureFileId);

	Add(result, shareType);
	return result;
}

Share<IMaterial> MaterialFactory::CreateSingleTexture(const Share<ITexture>& texture, ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	RETURN_NULL_IF_NULL(texture);
	Share<IMaterial> result = nullptr;
	if (shareType != ResourceShareType::None)
	{
		result = Find(texture->GetFileId());
		RETURN_SELF_IF_NOT_NULL(result);
	}

	auto effect = EffectFactory::Instance().CreateSinglePassDefault(RenderPassNames::Texture);
	result = new IMaterial(texture, effect, GraphicsDrawMode::Triangles, texture->GetFileId());

	Add(result, shareType);
	return result;
}


Share<IMaterial> MaterialFactory::CreateCustom(const FileIdRef& fileId, const Share<ITexture>& texture, const Share<IEffect>& effect, GraphicsDrawMode drawMode, ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	Share<IMaterial> result = nullptr;
	if (shareType != ResourceShareType::None)
	{
		result = Find(fileId);
		RETURN_SELF_IF_NOT_NULL(result);
	}
	result = new IMaterial(texture,effect,drawMode,fileId);

	Add(result, shareType);
	return result;
}


Share<IMaterial> MaterialFactory::CreateEmpty(const FileIdRef& fileId, ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	Share<IMaterial> result = nullptr;
	if (shareType != ResourceShareType::None)
	{
		result = Find(fileId);
		RETURN_SELF_IF_NOT_NULL(result);
	}

	result = new IMaterial(nullptr,nullptr,GraphicsDrawMode::Triangles,fileId);
	Add(result, shareType);
	return result;
}

Share<IMaterial> MaterialFactory::CreateShape(const FileIdRef& fileId, ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	Share<IMaterial> result = nullptr;
	if (shareType != ResourceShareType::None)
	{
		result = Find(fileId);
		RETURN_SELF_IF_NOT_NULL(result);
	}

	auto effect = EffectFactory::Instance().CreateSinglePassDefault(RenderPassNames::Shape);
	result = new IMaterial(nullptr, effect, GraphicsDrawMode::Triangles, fileId);

	Add(result, shareType);
	return result;
}


bool MaterialFactory::CreateTextures(SortedDictionary<uint, Share<IMaterial>>& outMaterials, const StringRef& textureNamePattern)
{
	List<const FileMapOrderItem*> outOrderItems;
	if (!FileSystem::Instance().TryGetOrderItems(textureNamePattern, outOrderItems))
	{
		return false;
	}

	for (const FileMapOrderItem* orderItem : outOrderItems)
	{
		auto texture = TextureFactory::Instance().CreateFromOrderItem(FileIdRef(textureNamePattern, orderItem->Order()), *orderItem, ShaderSamplerNames::Texture);
		auto material = CreateSingleTexture(texture);
		outMaterials.Add(orderItem->Order(),material);
	}

	return true;
}

MEDUSA_END;
