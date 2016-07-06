// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Graphics/Render/Render.h"
#include "Resource/Texture/ITexture.h"
#include "Graphics/GraphicsTypes.h"
#include "Core/Collection/Dictionary.h"
#include "Core/Pattern/RTTI/RTTIClass.h"
#include "Graphics/State/RenderStateSet.h"
#include "Resource/IResource.h"
#include "Rendering/RenderingTypes.h"


MEDUSA_BEGIN;
class IMaterial :public RenderStateSet, public IResource
{
public:
	typedef Dictionary<GraphicsTextureUnits, Share<ITexture>, SafeEnumHashCoder > TextureDict;
	IMaterial(const Share<ITexture>& texture = nullptr, const Share<IEffect>& effect = nullptr, GraphicsDrawMode drawMode = GraphicsDrawMode::Triangles, const FileIdRef& fileId = FileIdRef::Empty);

	virtual ~IMaterial(void);
	Event<void(RenderableChangedFlags)> OnMaterialChanged;

	MEDUSA_VIRTUAL int Retain() const
	{
		return ++mRefCount;
	}
	MEDUSA_VIRTUAL bool Release()const
	{
		if (--mRefCount <= 0)
		{
			delete this;
			return false;
		}
		return true;
	}
public:
	virtual ResourceType Type()const { return ResourceType::Material; }
	static ResourceType ClassGetResourceType() { return ResourceType::Material; }

	virtual void Apply()const;
	virtual void Restore()const;

	const TextureDict& Textures() const { return mTextures; }
	size_t TextureCount()const { return mTextures.Count(); }

	void AddTexture(const Share<ITexture>& texture);
	Share<ITexture> FirstTexture()const;
	Share<ITexture> FindTextureBySampler(StringRef smaplerName);

	virtual bool Equals(const IMaterial& material)const;

	const Share<IEffect>& Effect() const { return mEffect; }
	void SetEffect(const Share<IEffect>& val);

	GraphicsDrawMode DrawMode() const { return mDrawMode; }
	void SetDrawMode(GraphicsDrawMode val);
protected:
	TextureDict mTextures;
	Dictionary<HeapString, Share<ITexture>> mTextureSamplerDict;
	Share<ITexture> mFirstTexture;

	Share<IEffect> mEffect = nullptr;	//batch
	GraphicsDrawMode mDrawMode = GraphicsDrawMode::Triangles;//batch

};

MEDUSA_END;