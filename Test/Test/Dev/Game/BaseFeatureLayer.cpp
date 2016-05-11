// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "TestPreCompiled.h"
#include "BaseFeatureLayer.h"
#include "BaseCaseLayer.h"

BaseFeatureLayer::BaseFeatureLayer(StringRef name/*=StringRef::Empty*/, const IEventArg& e/*=IEventArg::Empty*/)
	:ILayer(name, e), mIndex(0)
{
	mCurrentLayer = nullptr;
	mIndex = 0;

}

BaseFeatureLayer::~BaseFeatureLayer(void)
{
}

bool BaseFeatureLayer::Initialize()
{
	RETURN_FALSE_IF_FALSE(ILayer::Initialize());

	TextureButton* returnButton = NodeFactory::Instance().CreateTextureButton("Close.png", "CloseSelected.png");
	returnButton->OnTap += Bind(&BaseFeatureLayer::OnReturn,this);
	returnButton->SetDock(DockPoint::LeftTop);
	returnButton->SetAnchor(0.f, 1.f);
	AddChild(returnButton);

	TextureButton* refreshButton = NodeFactory::Instance().CreateTextureButton("Refresh.png", "RefreshSelected.png");
	refreshButton->OnTap += Bind(&BaseFeatureLayer::OnRefresh, this);
	refreshButton->SetDock(DockPoint::MiddleBottom);
	refreshButton->SetAnchor(0.5f, 0.f);
	AddChild(refreshButton);


	float xPadding = refreshButton->Size().Width*0.5f + 100.f;

	TextureButton* leftButton = NodeFactory::Instance().CreateTextureButton("Left.png", "LeftSelected.png");
	leftButton->OnTap += Bind(&BaseFeatureLayer::OnLeft, this);
	leftButton->SetDock(DockPoint::MiddleBottom);
	leftButton->SetAnchor(0.5f, 0.f);
	leftButton->SetRelativePosition(Point2F(-xPadding, 0.f));
	AddChild(leftButton);


	TextureButton* rightButton = NodeFactory::Instance().CreateTextureButton("Left.png", "LeftSelected.png");
	rightButton->OnTap += Bind(&BaseFeatureLayer::OnRight, this);
	rightButton->SetDock(DockPoint::MiddleBottom);
	rightButton->SetAnchor(0.5f, 0.f);
	rightButton->SetRelativePosition(Point2F(xPadding, 0.f));
	rightButton->SetFlipX(true);
	AddChild(rightButton);


	return true;
}


bool BaseFeatureLayer::OnEnter()
{
	RETURN_TRUE_IF_EMPTY(mLayers);

	mIndex = 0;
	StringRef layerName = mLayers[mIndex];
	FileIdRef editorFile = mLayerEditorFiles[mIndex];
	mCurrentLayer = (BaseCaseLayer*)LayerFactory::Instance().Create(layerName, editorFile, IEventArg::Empty, LayerCreateFlags::AlwaysCreate);
	mCurrentLayer->SetDepth(-1);
	AddChild(mCurrentLayer);
	mCurrentLayer->OnEnter();

	return true;
}

void BaseFeatureLayer::OnReturn(INode* sender, TapGestureEventArg& e)
{
	mCurrentLayer->OnExit();
	DeleteChild(mCurrentLayer);
	mCurrentLayer = nullptr;
	SceneManager::Instance().Current()->PopLayer(LayerPopFlags::DeleteCurrentLayerAsync);


}

void BaseFeatureLayer::OnLeft(INode* sender, TapGestureEventArg& e)
{
	RETURN_IF(mLayers.Count() <= 1);
	if (mIndex == 0)
	{
		mIndex = mLayers.Count() - 1;
	}
	else
	{
		--mIndex;
	}
	StringRef layerName = mLayers[mIndex];
	FileIdRef editorFile = mLayerEditorFiles[mIndex];

	DeleteChild(mCurrentLayer);
	mCurrentLayer = nullptr;
	mCurrentLayer = (BaseCaseLayer*)LayerFactory::Instance().Create(layerName, editorFile, IEventArg::Empty, LayerCreateFlags::AlwaysCreate);
	mCurrentLayer->SetDepth(-1);
	AddChild(mCurrentLayer);
}

void BaseFeatureLayer::OnRight(INode* sender, TapGestureEventArg& e)
{
	RETURN_IF(mLayers.Count() <= 1);


	++mIndex;
	mIndex %= mLayers.Count();

	StringRef layerName = mLayers[mIndex];
	FileIdRef editorFile = mLayerEditorFiles[mIndex];

	DeleteChild(mCurrentLayer);
	mCurrentLayer = nullptr;
	mCurrentLayer = (BaseCaseLayer*)LayerFactory::Instance().Create(layerName, editorFile, IEventArg::Empty, LayerCreateFlags::AlwaysCreate);
	mCurrentLayer->SetDepth(-1);
	AddChild(mCurrentLayer);
}

void BaseFeatureLayer::OnRefresh(INode* sender, TapGestureEventArg& e)
{
	RETURN_IF_EMPTY(mLayers);

	OnRestart();
}

void BaseFeatureLayer::OnRestart()
{
	mCurrentLayer->OnRestart();

}



MEDUSA_IMPLEMENT_LAYER(BaseFeatureLayer, ILayer, StringRef::Empty, StringRef::Empty);

