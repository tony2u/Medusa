// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/String/StringRef.h"
#include "Core/Pattern/Singleton.h"
#include "Graphics/GraphicsTypes.h"
#include "Resource/BaseResourceFactory.h"
#include "Resource/ResourceNames.h"
#include "ITexture.h"
#include "Graphics/PixelType.h"

MEDUSA_BEGIN;

class TextureFactory:public Singleton<TextureFactory>,public BaseResourceFactory<ITexture>
{
	friend class Singleton<TextureFactory>;
public:
	TextureFactory();
	~TextureFactory();
public:
	virtual StringRef Name()const override { return "TextureFactory"; }

	virtual bool Initialize();
	virtual bool Uninitialize();
public:
	Share<ImageTexture> CreateFromFile(const FileIdRef& fileId, StringRef samplerName = ShaderSamplerNames::Texture, GraphicsTextureUnits unit = GraphicsTextureUnits::Texture0, ResourceShareType shareType = ResourceShareType::Share);
	Share<ImageTexture> CreateFromOrderItem(const FileIdRef& fileId, const FileMapOrderItem& orderItem, StringRef samplerName = ShaderSamplerNames::Texture, GraphicsTextureUnits unit = GraphicsTextureUnits::Texture0, ResourceShareType shareType = ResourceShareType::Share);

	Share<ImageTexture> CreateFromImage(const FileIdRef& fileId, const Share<IImage>& image, StringRef samplerName = ShaderSamplerNames::Texture, GraphicsTextureUnits unit = GraphicsTextureUnits::Texture0, ResourceShareType shareType = ResourceShareType::Share);
	Share<GPUTexture> CreateGPUTexture(const FileIdRef& fileId,
		const Size2U& size,
		GraphicsTextureType textureType=GraphicsTextureType::Texture2D,
		GraphicsTextureTarget textureTarget=GraphicsTextureTarget::Texture2D,
		PixelType pixelType = PixelType::RGB888,
		int level=0,
		int border=0,
		StringRef samplerName=StringRef::Empty,GraphicsTextureUnits unit=GraphicsTextureUnits::Texture0,ResourceShareType shareType = ResourceShareType::Share);
};

MEDUSA_END;