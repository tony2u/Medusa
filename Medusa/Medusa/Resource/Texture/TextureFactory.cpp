// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "TextureFactory.h"
#include "Resource/Texture/GPUTexture.h"
#include "Resource/Texture/ImageTexture.h"
#include "Resource/Image/ImageFactory.h"

MEDUSA_BEGIN;

TextureFactory::TextureFactory()
{

}

TextureFactory::~TextureFactory()
{

}

bool TextureFactory::Initialize()
{
	return true;
}

bool TextureFactory::Uninitialize()
{
	Clear();
	return true;
}


Share<ImageTexture> TextureFactory::CreateFromFile(const FileIdRef& fileId, StringRef samplerName/*=ShaderSamplerNames::Texture*/,
	GraphicsTextureUnits unit/*=GraphicsTextureUnits::Texture0*/, ResourceShareType shareType /*= ResourceShareType::Share*/)
{

	if (shareType != ResourceShareType::None)
	{
		Share<ImageTexture> result = Find(fileId).CastPtr<ImageTexture>();
		RETURN_SELF_IF_NOT_NULL(result);
	}


	auto image = ImageFactory::Instance().CreateFromFile(fileId);
	RETURN_NULL_IF_NULL(image);
	return CreateFromImage(fileId, image, samplerName, unit, shareType);
}

Share<ImageTexture> TextureFactory::CreateFromOrderItem(const FileIdRef& fileId, const FileMapOrderItem& orderItem, StringRef samplerName /*= ShaderSamplerNames::Texture*/, GraphicsTextureUnits unit /*= GraphicsTextureUnits::Texture0*/, ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	if (shareType != ResourceShareType::None)
	{
		Share<ImageTexture> result = Find(fileId).CastPtr<ImageTexture>();
		RETURN_SELF_IF_NOT_NULL(result);
	}

	auto image = ImageFactory::Instance().CreateFromOrderItem(fileId, orderItem);
	RETURN_NULL_IF_NULL(image);
	return CreateFromImage(fileId, image, samplerName, unit, shareType);
}

Share<ImageTexture> TextureFactory::CreateFromImage(const FileIdRef& fileId, const Share<IImage>& image, StringRef samplerName/*=ShaderSamplerNames::Texture*/,
	GraphicsTextureUnits unit/*=GraphicsTextureUnits::Texture0*/, ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	Share<ImageTexture> result;
	if (shareType != ResourceShareType::None)
	{
		result = Find(fileId).CastPtr<ImageTexture>();
		RETURN_SELF_IF_NOT_NULL(result);
	}

	result = new ImageTexture(fileId, image, samplerName, unit);
	result->ResetDefaultParameters();
	Add(result, shareType);

	return result;
}


Share<GPUTexture> TextureFactory::CreateGPUTexture(const FileIdRef& fileId, const Size2U& size, GraphicsTextureType textureType/*=GraphicsTextureType::Texture2D*/,
	GraphicsTextureTarget textureTarget/*=GraphicsTextureTarget::Texture2D*/,
	PixelType pixelType /*= PixelType::RGB888*/,
	int level/*=0*/, int border/*=0*/,
	StringRef samplerName/*=StringRef::Empty*/,
	GraphicsTextureUnits unit/*=GraphicsTextureUnits::Texture0*/, ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	Share<GPUTexture> result = nullptr;
	if (shareType != ResourceShareType::None)
	{
		result = Find(fileId).CastPtr<GPUTexture>();
		RETURN_SELF_IF_NOT_NULL(result);
	}


	result = new GPUTexture(fileId, size, textureType, textureTarget, pixelType, level, border,samplerName, unit);
	result->ResetDefaultParameters();
	Add(result, shareType);

	return result;
}



MEDUSA_END;