// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Graphics/State/SamplerRenderState.h"
#include "Graphics/Render/Render.h"
#include "Rendering/RenderingContext.h"
#include "Core/Log/Log.h"

MEDUSA_BEGIN;
SamplerRenderState::SamplerRenderState(GraphicsTextureType textureType/*=GraphicsTextureType::Texture2D*/, GraphicsTextureUnits unit/*=GraphicsTextureUnits::Texture0*/)
	:mTextureType(textureType),
	mTextureUnit(unit)
{

}

SamplerRenderState::SamplerRenderState(GraphicsTextureMinFilter minFilter, GraphicsTextureMagFilter magFilter, GraphicsTextureWrapMode wrapS, GraphicsTextureWrapMode wrapT)
	:mMinFilter(minFilter),
	mMagFilter(magFilter),
	mWrapS(wrapS),
	mWrapT(wrapT)
{

}

SamplerRenderState::~SamplerRenderState()
{

}

void SamplerRenderState::Apply()const
{
	Render::Instance().ActivateTexture(mTextureUnit);

	Render::Instance().BindTexture(mTextureType, mTexture);
	//Parameters set with glTexParameter affects the currently bound texture object, and stays with the texture object until changed.

	Render::Instance().SetTextureMinFilter(mTextureType, mMinFilter);
	Render::Instance().SetTextureMagFilter(mTextureType, mMagFilter);
	Render::Instance().SetTextureWrapS(mTextureType, mWrapS);
	Render::Instance().SetTextureWrapT(mTextureType, mWrapT);

}

SamplerRenderState* SamplerRenderState::Clone() const
{
	SamplerRenderState* state = new SamplerRenderState();
	state->SetTextureType(mTextureType);
	state->SetTextureUnit(mTextureUnit);
	state->SetTexture(mTexture);
	state->SetMagFilter(mMagFilter);
	state->SetMinFilter(mMinFilter);
	state->SetWrapS(mWrapS);
	state->SetWrapT(mWrapT);
	return state;
}

bool SamplerRenderState::Equals(const IRenderState& state) const
{
	RETURN_FALSE_IF_FALSE(IRenderState::Equals(state));
	const SamplerRenderState& val = (const SamplerRenderState&)state;
	return mTextureType == val.TextureType() &&
		mTextureUnit == val.TextureUnit() &&
		mTexture == val.Texture() &&
		mMagFilter == val.MagFilter() &&
		mMinFilter == val.MinFilter() &&
		mWrapS == val.WrapS() &&
		mWrapT == val.WrapT();

}

SamplerRenderState* SamplerRenderState::Current()
{
	IRender& render = Render::Instance();
	GraphicsTextureUnits activeTexture = (GraphicsTextureUnits)render.GetInteger(GraphicsIntegerName::ActiveTexture);
	SamplerRenderState* samplerState = new SamplerRenderState();
	samplerState->SetTextureUnit(activeTexture);

	uint cubeMapTexture = render.GetInteger(GraphicsIntegerName::CubeMapTextureBinding);
	uint texture2D = render.GetInteger(GraphicsIntegerName::TextureBinding);
	//uint texture = 0;
	GraphicsTextureType textureType = GraphicsTextureType::Texture2D;
	if (cubeMapTexture != 0)
	{
		if (texture2D != 0)
		{
			Log::Error("Error texture binding");
			MEDUSA_ASSERT_FAILED("Error texture binding");
		}
		else
		{
			textureType = GraphicsTextureType::TextureCubeMap;
			samplerState->SetTexture(cubeMapTexture);
			//texture = cubeMapTexture;
		}
	}
	else
	{
		textureType = GraphicsTextureType::Texture2D;
		samplerState->SetTexture(texture2D);
		//texture = texture2D;
	}

	samplerState->SetTextureUnit((GraphicsTextureUnits)render.GetInteger(GraphicsIntegerName::ActiveTexture));
	samplerState->SetMagFilter(GraphicsTextureMagFilter(render.GetTextureParamter(textureType, GraphicsTextureParameter::MagFilter)));
	samplerState->SetMinFilter(GraphicsTextureMinFilter(render.GetTextureParamter(textureType, GraphicsTextureParameter::MinFilter)));
	samplerState->SetWrapS(GraphicsTextureWrapMode(render.GetTextureParamter(textureType, GraphicsTextureParameter::WrapS)));
	samplerState->SetWrapT(GraphicsTextureWrapMode(render.GetTextureParamter(textureType, GraphicsTextureParameter::WrapT)));

	return samplerState;
}


MEDUSA_IMPLEMENT_RTTI(SamplerRenderState, IRenderState);

MEDUSA_END;