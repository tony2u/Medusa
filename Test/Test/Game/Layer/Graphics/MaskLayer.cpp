// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "TestPreCompiled.h"
#include "MaskLayer.h"

MaskLayer::MaskLayer(StringRef name/*=StringRef::Empty*/, const IEventArg& e/*=IEventArg::Empty*/) :BaseCaseLayer(name, e)
{
}

MaskLayer::~MaskLayer(void)
{
}

bool MaskLayer::Initialize()
{
	RETURN_FALSE_IF_FALSE(BaseCaseLayer::Initialize());

	mBackSrite = NodeFactory::Instance().CreateQuadSprite("Background.jpg");
	mBackSrite->SetDock(DockPoint::MiddleCenter);
	mBackSrite->SetAnchor(0.5f, 0.5f);
	AddChild(mBackSrite);

	mFrontSprite = NodeFactory::Instance().CreateQuadSprite("WarriorAttack.png");
	mFrontSprite->SetDock(DockPoint::MiddleCenter);
	mFrontSprite->SetAnchor(0.5f, 0.5f);
	AddChild(mFrontSprite);


	IShape* rectShape = NodeFactory::Instance().CreateRect(msize(100, 100), Color4F(0,0,0,1.f));
	rectShape->SetDock(DockPoint::MiddleCenter);
	rectShape->SetAnchor(0.5f, 0.5f);
	rectShape->SetStretch(Stretch::Fill);
	AddChild(rectShape);

	
	mFrontSprite->EnableScissor(true);

	//BlendRenderState* state= mFrontSprite->MutableRenderState().BlendState(); 

	//alpha = dest -src
	//state->SetDestAlphaFunc(GraphicsBlendDestFunc::DestAlpha);
	//state->SetSrcAlphaFunc(GraphicsBlendSrcFunc::SrcAlpha);
	//state->SetBlendAlphaEquation(GraphicsBlendEquation::Subtract);
	//mFrontSprite->MutableRenderState().SetBlendFunc(GraphicsBlendSrcFunc::SrcAlpha, GraphicsBlendDestFunc::OneMinusSrcAlpha);

	//state->SetDestRGBFunc(GraphicsBlendDestFunc::One);
	//state->SetSrcRGBFunc(GraphicsBlendSrcFunc::Zero);
	//state->SetBlendRGBEquation(GraphicsBlendEquation::Add);


	//IRenderPass* maskPass= RenderPassFactory::Instance().CreateRenderPass("MaskPass", VertexShaderFiles::Texture, "MaskTexture.fsh");
	//IEffect* maskEffect=EffectFactory::Instance().CreateEffectSinglePass("MaskEffect", maskPass);
	//mFrontSprite->Mesh()->SetEffect(maskEffect);
	//mFrontSprite->Mesh()->SetEffect()
	return true;
}


MEDUSA_IMPLEMENT_LAYER(MaskLayer, BaseCaseLayer, StringRef::Empty);

