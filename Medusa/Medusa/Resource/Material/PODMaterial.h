// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Resource/Material/IMaterial.h"
#include "Core/String/HeapString.h"
#include "Core/Geometry/Color3.h"
#include "Core/Geometry/Color4.h"
#include "Core/Memory/MemoryData.h"


MEDUSA_BEGIN;

class PODMaterial:public IMaterial
{
public:
	PODMaterial(const FileIdRef& fileId=FileIdRef::Empty);
	virtual ~PODMaterial(void);
	using IMaterial::Initialize;
	bool Initialize(const List<HeapString>& textureNames);
private:
	bool TryAddTexture(const List<HeapString>& textureNames,GraphicsTextureUnits textureUnit,int index,StringRef samplerName=StringRef::Empty);
public:
	int		DiffuseTextureIndex=-1;			/*!< Idx into pTexture for the diffuse texture */
	int		AmbientTextureIndex = -1;			/*!< Idx into pTexture for the ambient texture */
	int		SpecularColorTextureIndex = -1;	/*!< Idx into pTexture for the specular Color texture */
	int		SpecularLevelTextureIndex = -1;	/*!< Idx into pTexture for the specular level texture */
	int		BumpMapTextureIndex = -1;			/*!< Idx into pTexture for the bump map */
	int		EmissiveTextureIndex = -1;		/*!< Idx into pTexture for the emissive texture */
	int		GlossinessTextureIndex = -1;		/*!< Idx into pTexture for the glossiness texture */
	int		OpacityTextureIndex = -1;			/*!< Idx into pTexture for the opacity texture */
	int		ReflectionTextureIndex = -1;		/*!< Idx into pTexture for the reflection texture */
	int		RefractionTextureIndex = -1;		/*!< Idx into pTexture for the refraction texture */
	float		Opacity=0;			/*!< Material opacity (used with vertex alpha ?) */\
	float		Shininess=0;			/*!< Material shininess */
	HeapString		EffectFile;			/*!< Name of effect file */
	HeapString		EffectName;			/*!< Name of effect in the effect file */

	GraphicsBlendSrcFunc	BlendSrcRGB= GraphicsBlendSrcFunc::One;		/*!< Blending RGB source value */
	GraphicsBlendSrcFunc	BlendSrcAlpha= GraphicsBlendSrcFunc::One;			/*!< Blending alpha source value */
	GraphicsBlendDestFunc	BlendDestRGB= GraphicsBlendDestFunc::Zero;		/*!< Blending RGB destination value */
	GraphicsBlendDestFunc	BlendDestAlpha= GraphicsBlendDestFunc::Zero;			/*!< Blending alpha destination value */
	GraphicsBlendEquation		BlendRGBEquation= GraphicsBlendEquation::Add;		/*!< Blending RGB operation */
	GraphicsBlendEquation		BlendAlphaEquation= GraphicsBlendEquation::Add;			/*!< Blending alpha operation */
	Color4F		BlendColor;	/*!< A RGBA Color to be used in blending */
	Color4F		BlendFactor;	/*!< An array of blend factors, one for each RGBA component */

	uint		Flags=0;				/*!< Stores information about the material e.g. Enable blending */

	Color3F mAmbientColor;
	Color3F mDiffuseColor;
	Color3F mSpecularColor;
	Color3F mEmissionColor;

	MemoryByteData UserData;
};

MEDUSA_END;