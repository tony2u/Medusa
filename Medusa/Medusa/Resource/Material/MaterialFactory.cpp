// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "MaterialFactory.h"
#include "Resource/Material/IMaterial.h"
#include "Resource/Texture/TextureFactory.h"
#include "Resource/Texture/ImageTexture.h"

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



IMaterial* MaterialFactory::Create(const FileIdRef& fileId, ITexture* texture, ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	IMaterial* result = Find(fileId);
	RETURN_SELF_IF_NOT_NULL(result);
	result = new IMaterial(texture, fileId);
	Add(result, shareType);
	return result;
}

IMaterial* MaterialFactory::Create(const FileIdRef& fileId, StringRef samplerName/*=StringRef::Empty*/, ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	IMaterial* result = Find(fileId);
	RETURN_SELF_IF_NOT_NULL(result);

	ITexture* texture = nullptr;
	texture = TextureFactory::Instance().CreateFromFile(fileId, samplerName);
	RETURN_NULL_IF_NULL(texture);

	return Create(fileId, texture, shareType);
}

IMaterial* MaterialFactory::Create(const FileIdRef& fileId, IImage* image, StringRef samplerName/*=StringRef::Empty*/, GraphicsTextureUnits unit/*=GraphicsTextureUnits::Texture0*/, ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	ITexture* texture = TextureFactory::Instance().CreateFromImage(fileId, image, samplerName, unit, shareType);
	return Create(fileId, texture, shareType);
}

IMaterial* MaterialFactory::Create(const FileIdRef& fileId, const FileMapOrderItem& orderItem, StringRef samplerName /*= StringRef::Empty*/, ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	IMaterial* result = Find(fileId);
	RETURN_SELF_IF_NOT_NULL(result);

	ITexture* texture = nullptr;
	texture = TextureFactory::Instance().CreateFromOrderItem(fileId, orderItem, samplerName);
	RETURN_NULL_IF_NULL(texture);

	return Create(fileId, texture, shareType);
}

IMaterial* MaterialFactory::CreateEmpty(const FileIdRef& fileId, ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	IMaterial* result = Find(fileId);
	RETURN_SELF_IF_NOT_NULL(result);

	result = new IMaterial(fileId);
	Add(result, shareType);
	return result;
}


MEDUSA_END;