// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "TestPreCompiled.h"
#include "BlendTestLayer.h"






BlendTestLayer::BlendTestLayer(StringRef name/*=StringRef::Empty*/, const IEventArg& e/*=IEventArg::Empty*/) :BaseCaseLayer(name, e)
{
}

BlendTestLayer::~BlendTestLayer(void)
{
}

bool BlendTestLayer::Initialize()
{
	RETURN_FALSE_IF_FALSE(BaseCaseLayer::Initialize());

	mBackSrite = NodeFactory::Instance().CreateSprite("Background.jpg");
	mBackSrite->SetDock(DockPoint::MiddleCenter);
	mBackSrite->SetAnchor(0.5f, 0.5f);
	AddChild(mBackSrite);

	IShape* rectShape = NodeFactory::Instance().CreateRect(msize(100, 100), Color4F(0,0,0,0.9f));
	rectShape->SetDock(DockPoint::MiddleCenter);
	rectShape->SetAnchor(0.5f, 0.5f);
	rectShape->SetStretch(Stretch::Fill);
	AddChild(rectShape);

	mFrontSprite = NodeFactory::Instance().CreateSprite("WarriorAttack.png");
	mFrontSprite->SetDock(DockPoint::MiddleCenter);
	mFrontSprite->SetAnchor(0.5f, 0.5f);
	AddChild(mFrontSprite);

	mSrcFunc = GraphicsBlendSrcFuncHelper::SrcAlpha;   
	ILabel* srcLabel = NodeFactory::Instance().CreateSingleLineLabel(FontId("arial22.fnt"), mSrcFunc.ToString(), Alignment::LeftBottom, Size2U::Zero, true);
	mSrcFuncButton = new LabelButton(srcLabel);
	mSrcFuncButton->Initialize();
	mSrcFuncButton->SetAnchorPoint(AnchorPoint::LeftCenter);
	mSrcFuncButton->SetDock(DockPoint::LeftCenter);
	mSrcFuncButton->OnTap += Bind(&BlendTestLayer::OnSrcChanged, this);
	AddChild(mSrcFuncButton);

	mDestFunc = GraphicsBlendDestFuncHelper::OneMinusSrcAlpha;
	ILabel* destLabel = NodeFactory::Instance().CreateSingleLineLabel(FontId("arial22.fnt"), mDestFunc.ToString(), Alignment::LeftBottom, Size2U::Zero, true);
	mDestFuncButton = new LabelButton(destLabel);
	mDestFuncButton->Initialize();
	mDestFuncButton->SetAnchorPoint(AnchorPoint::RightCenter);
	mDestFuncButton->SetDock(DockPoint::RightCenter);
	mDestFuncButton->OnTap += Bind(&BlendTestLayer::OnDestChanged, this);
	AddChild(mDestFuncButton);
	 
	mFrontSprite->MutableRenderState().SetBlendFunc(GraphicsBlendSrcFunc::SrcAlpha, GraphicsBlendDestFunc::OneMinusSrcAlpha);
	return true;
}


void BlendTestLayer::OnSrcChanged(INode* sender, TapGestureEventArg& e)
{
	uint index=mSrcFunc.ToIndex();
	index = (++index) % GraphicsBlendSrcFuncHelper::Size;
	mSrcFunc.ForceSet(GraphicsBlendSrcFuncHelper::Values[index]);
	
	mFrontSprite->MutableRenderState().SetBlendFunc((GraphicsBlendSrcFunc)mSrcFunc.ToUInt(), (GraphicsBlendDestFunc)mDestFunc.ToUInt());
	mSrcFuncButton->Label()->SetString(mSrcFunc.ToString());
}

void BlendTestLayer::OnDestChanged(INode* sender, TapGestureEventArg& e)
{
	uint index = mDestFunc.ToIndex();
	index = (++index) % GraphicsBlendDestFuncHelper::Size;
	mDestFunc.ForceSet(GraphicsBlendDestFuncHelper::Values[index]);

	mFrontSprite->MutableRenderState().SetBlendFunc((GraphicsBlendSrcFunc)mSrcFunc.ToUInt(), (GraphicsBlendDestFunc)mDestFunc.ToUInt());
	mDestFuncButton->Label()->SetString(mDestFunc.ToString());
}

MEDUSA_IMPLEMENT_LAYER(BlendTestLayer, BaseCaseLayer, StringRef::Empty, StringRef::Empty);

