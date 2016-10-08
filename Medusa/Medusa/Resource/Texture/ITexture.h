// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/String/StringRef.h"
#include "Geometry/Size2.h"
#include "Graphics/GraphicsTypes.h"
#include "Graphics/State/SamplerRenderState.h"
#include "Graphics/State/PixelStoreRenderState.h"
#include "Resource/IResource.h"
#include "Resource/ResourceNames.h"
#include "Resource/Image/IImage.h"
#include "Core/Pattern/Share.h"

MEDUSA_BEGIN;

class ITexture :public IResource
{
public:
	ITexture(const FileIdRef& fileId, GraphicsTextureType textureType, StringRef samplerName = ShaderSamplerNames::Texture, GraphicsTextureUnits unit = GraphicsTextureUnits::Texture0);
	virtual ~ITexture(void);
public:
	virtual ResourceType Type()const { return ResourceType::Texture; }
	static ResourceType ClassGetResourceType() { return ResourceType::Texture; }

	bool IsAvailable()const;

	uint Texture() const { return mSamplerState->Texture(); }
	GraphicsTextureUnits Unit() const { return mSamplerState->TextureUnit(); }
	void SetUnit(GraphicsTextureUnits val) { mSamplerState->SetTextureUnit(val); }

	virtual void Apply();
	virtual void Restore();

	virtual Share<IImage> Image() const = 0;
	virtual bool IsBlend()const = 0;
	virtual Size2U Size() const = 0;
	virtual void ResetDefaultParameters() = 0;

	StringRef SamplerName() const { return mSamplerName; }
	void SetSamplerName(StringRef val) { mSamplerName = val; }

	GraphicsTextureMinFilter MinFilter() const { return mSamplerState->MinFilter(); }
	void SetMinFilter(GraphicsTextureMinFilter val) { mSamplerState->SetMinFilter(val); }

	GraphicsTextureMagFilter MagFilter() const { return mSamplerState->MagFilter(); }
	void SetMagFilter(GraphicsTextureMagFilter val) { mSamplerState->SetMagFilter(val); }

	GraphicsTextureWrapMode WrapS() const { return mSamplerState->WrapS(); }
	void SetWrapS(GraphicsTextureWrapMode val) { mSamplerState->SetWrapS(val); }

	GraphicsTextureWrapMode WrapT() const { return mSamplerState->WrapT(); }
	void SetWrapT(GraphicsTextureWrapMode val) { mSamplerState->SetWrapT(val); }

	bool IsLoaded() const { return mIsLoaded; }
	void SetLoaded(bool val) { mIsLoaded = val; }
protected:
	virtual void Upload() = 0;
protected:
	HeapString mSamplerName;

	Share<SamplerRenderState> mSamplerState;
	Share<PixelStoreRenderState> mPixelStoreState;
	bool mIsLoaded;
};

MEDUSA_END;