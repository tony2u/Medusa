// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "Graphics/State/IRenderState.h"
#include "Graphics/GraphicsTypes.h"
MEDUSA_BEGIN;

class SamplerRenderState:public IRenderState
{
	MEDUSA_RTTI(SamplerRenderState,IRenderState);

public:
	SamplerRenderState(GraphicsTextureType textureType = GraphicsTextureType::Texture2D,GraphicsTextureUnits unit = GraphicsTextureUnits::Texture0);
	SamplerRenderState(GraphicsTextureMinFilter minFilter,GraphicsTextureMagFilter magFilter,GraphicsTextureWrapMode wrapS,GraphicsTextureWrapMode wrapT);

	virtual ~SamplerRenderState();
	virtual void Apply()const override;

	Share<SamplerRenderState> Clone()const;
	virtual void CopyFrom(const IRenderState& other)override;

	virtual bool Equals(const IRenderState& state)const override;

	virtual RenderStateType Type()const override {return RenderStateType::Sampler;}
	static RenderStateType GetTypeIdStatic() { return RenderStateType::Sampler; }


	GraphicsTextureType TextureType() const { return mTextureType; }
	void SetTextureType(GraphicsTextureType val) {RETURN_IF_EQUAL(mTextureType, val); mTextureType = val; OnStateChanged();}

	GraphicsTextureUnits TextureUnit() const { return mTextureUnit; }
	void SetTextureUnit(GraphicsTextureUnits val) {RETURN_IF_EQUAL(mTextureUnit, val); mTextureUnit = val; OnStateChanged();}

	uint Texture() const { return mTexture; }
	void SetTexture(uint val) {RETURN_IF_EQUAL(mTexture, val); mTexture = val; OnStateChanged();}

	GraphicsTextureMinFilter MinFilter() const { return mMinFilter; }
	void SetMinFilter(GraphicsTextureMinFilter val) {RETURN_IF_EQUAL(mMinFilter, val); mMinFilter = val; OnStateChanged();}

	GraphicsTextureMagFilter MagFilter() const { return mMagFilter; }
	void SetMagFilter(GraphicsTextureMagFilter val) {RETURN_IF_EQUAL(mMagFilter, val); mMagFilter = val; OnStateChanged();}

	GraphicsTextureWrapMode WrapS() const { return mWrapS; }
	void SetWrapS(GraphicsTextureWrapMode val) {RETURN_IF_EQUAL(mWrapS, val); mWrapS = val; OnStateChanged();}

	GraphicsTextureWrapMode WrapT() const { return mWrapT; }
	void SetWrapT(GraphicsTextureWrapMode val) {RETURN_IF_EQUAL(mWrapT, val); mWrapT = val; OnStateChanged();}
	
	static Share<SamplerRenderState> Current();
protected:
	GraphicsTextureType mTextureType = GraphicsTextureType::Texture2D;
	GraphicsTextureUnits mTextureUnit= GraphicsTextureUnits::Texture0;
	uint mTexture=0;

	GraphicsTextureMinFilter mMinFilter= GraphicsTextureMinFilter::Linear;
	GraphicsTextureMagFilter mMagFilter= GraphicsTextureMagFilter::Linear;
	GraphicsTextureWrapMode mWrapS = GraphicsTextureWrapMode::Repeat;
	GraphicsTextureWrapMode mWrapT = GraphicsTextureWrapMode::Repeat;
};


MEDUSA_END;