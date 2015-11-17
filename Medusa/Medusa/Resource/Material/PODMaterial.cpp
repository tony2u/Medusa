// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "PODMaterial.h"
#include "Resource/ResourceNames.h"
#include "Resource/Texture/ImageTexture.h"
#include "Resource/Texture/TextureFactory.h"

MEDUSA_BEGIN;


PODMaterial::PODMaterial(const FileIdRef& fileId/*=FileId::Empty*/):IMaterial(fileId)
	,BlendColor(Color4F::Black),BlendFactor(Color4F::Black),
	mAmbientColor(Color3F::Black),
	mDiffuseColor(Color3F::Black),
	mSpecularColor(Color3F::Black),
	mEmissionColor(Color3F::Black)
{
}


PODMaterial::~PODMaterial(void)
{
	
}


bool PODMaterial::Initialize( const List<HeapString>& textureNames )
{
	bool hasTexture=false;
	hasTexture|=TryAddTexture(textureNames,GraphicsTextureUnits::Texture0,DiffuseTextureIndex,ShaderSamplerNames::Texture);
	hasTexture|=TryAddTexture(textureNames,GraphicsTextureUnits::Texture1,AmbientTextureIndex);
	hasTexture|=TryAddTexture(textureNames,GraphicsTextureUnits::Texture2,SpecularColorTextureIndex);
	hasTexture|=TryAddTexture(textureNames,GraphicsTextureUnits::Texture3,SpecularLevelTextureIndex);
	hasTexture|=TryAddTexture(textureNames,GraphicsTextureUnits::Texture4,BumpMapTextureIndex,ShaderSamplerNames::NormalMap);
	hasTexture|=TryAddTexture(textureNames,GraphicsTextureUnits::Texture5,EmissiveTextureIndex);
	hasTexture|=TryAddTexture(textureNames,GraphicsTextureUnits::Texture6,GlossinessTextureIndex);
	hasTexture|=TryAddTexture(textureNames,GraphicsTextureUnits::Texture7,OpacityTextureIndex);
	hasTexture|=TryAddTexture(textureNames,GraphicsTextureUnits::Texture8,ReflectionTextureIndex);
	hasTexture|=TryAddTexture(textureNames,GraphicsTextureUnits::Texture9,RefractionTextureIndex);



	//if(!EffectFile.IsEmpty())
	//{
	//	mEffect=ResourceManager::Instance().CreateEffectFromFile(EffectFile);
	//}
	//else
	//{
	//	//load default effect
	//	if (hasTexture)
	//	{
	//		mEffect=ResourceManager::Instance().CreateEffectSinglePassDefault(RenderPassNames::Texture);
	//	}
	//	else
	//	{
	//		mEffect=ResourceManager::Instance().CreateEffectSinglePassDefault(RenderPassNames::PositionColor);
	//	}
	//}

	//SAFE_RETAIN(mEffect);
	return true;
}

bool PODMaterial::TryAddTexture(const List<HeapString>& textureNames,GraphicsTextureUnits textureUnit,int index ,StringRef samplerName/*=StringRef::Empty*/)
{
	RETURN_FALSE_IF(index<0);
	if ((uint)index>=textureNames.Count())
	{
		MEDUSA_ASSERT_FAILED("Index out of range");
		return false;
	}
	ITexture* texture=TextureFactory::Instance().CreateFromFile(textureNames[index],samplerName);
	RETURN_FALSE_IF_NULL(texture);
	texture->SetUnit(textureUnit);
	AddTexture(texture);
	return true;
}

MEDUSA_END;