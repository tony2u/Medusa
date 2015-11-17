// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "TestPreCompiled.h"
#include "TestLayer.h"
#include "Game/Layer/Sprite/SpriteFeatureLayer.h"
#include "Game/Layer/Shape/ShapeFeatureLayer.h"

#include "Game/Layer/Control/ControlFeatureLayer.h"
#include "Game/Layer/Action/ActionFeatureLayer.h"
#include "Game/Layer/Animation/AnimationFeatureLayer.h"
#include "Game/Layer/Font/FontFeatureLayer.h"
#include "Game/Layer/Particle/ParticleFeatureLayer.h"
#include "Game/Layer/Shader/ShaderFeatureLayer.h"
#include "Game/Layer/Performance/PerformanceFeatureLayer.h"
#include "Game/Layer/Audio/AudioFeatureLayer.h"
#include "Game/Layer/Component/ComponentFeatureLayer.h"
#include "Game/Layer/Graphics/GraphicsFeatureLayer.h"

enum class TestItem
{
	Sprite,
	Shape,
	Control,
	Action,
	Animation,
	Font,
	Particle,
	Shader,
	Performance,
	Audio,
	Component,
	Graphics,

};

TestLayer::TestLayer(StringRef name/*=StringRef::Empty*/,const IEventArg& e/*=IEventArg::Empty*/):ILayer(name,e)
{
	mItems.Emplace(L"Sprite");
	mItems.Emplace(L"Shape");
	mItems.Emplace(L"Control");
	mItems.Emplace(L"Action");
	mItems.Emplace(L"Animation");
	mItems.Emplace(L"Font");
	mItems.Emplace(L"Particle");
	mItems.Emplace(L"Shader");
	mItems.Emplace(L"Performance");
	mItems.Emplace(L"Audio");
	mItems.Emplace(L"Component");
	mItems.Emplace(L"Graphics");


}

TestLayer::~TestLayer(void)
{
}

bool TestLayer::Initialize()
{
	RETURN_FALSE_IF_FALSE(ILayer::Initialize());

	ListBox* listBox=NodeFactory::Instance().CreateStringListBox(mItems,true);
	listBox->SetStretch(Medusa::Stretch::Fill);
	StringListDataSource* dataSource=(StringListDataSource*)listBox->DataSource();
	LabelItemTemplate* labelItemTemplate=(LabelItemTemplate*)dataSource->ItemTemplate();
	labelItemTemplate->SetAlignment(Alignment::MiddleCenter);
	labelItemTemplate->MutableFontId().SetSize(44);
	labelItemTemplate->MutableFontId().Name="arial88.fnt";

	AddChild(listBox);
	listBox->OnItemClicked+=Bind(&TestLayer::OnItemClicked,this);

	return true;
}


void TestLayer::OnItemClicked(ListBox& sender,const ListBoxItem& item)
{
	TestItem testItem=(TestItem)item.Index;
	switch (testItem)
	{
	case TestItem::Sprite:
		SceneManager::Instance().RunningScene()->PushLayer<SpriteFeatureLayer>();
		break;
	case TestItem::Shape:
		SceneManager::Instance().RunningScene()->PushLayer<ShapeFeatureLayer>();
		break;
	case TestItem::Control:
		SceneManager::Instance().RunningScene()->PushLayer<ControlFeatureLayer>();
		break;
	case TestItem::Action:
		SceneManager::Instance().RunningScene()->PushLayer<ActionFeatureLayer>();
		break;
	case TestItem::Animation:
		SceneManager::Instance().RunningScene()->PushLayer<AnimationFeatureLayer>();
		break;
	case TestItem::Font:
		SceneManager::Instance().RunningScene()->PushLayer<FontFeatureLayer>();
		break;
	case TestItem::Particle:
		SceneManager::Instance().RunningScene()->PushLayer<ParticleFeatureLayer>();
		break;
	case TestItem::Shader:
		SceneManager::Instance().RunningScene()->PushLayer<ShaderFeatureLayer>();
		break;
	case TestItem::Performance:
		SceneManager::Instance().RunningScene()->PushLayer<PerformanceFeatureLayer>();
		break;
	case TestItem::Audio:
		SceneManager::Instance().RunningScene()->PushLayer<AudioFeatureLayer>();
		break;
	case TestItem::Component:
		SceneManager::Instance().RunningScene()->PushLayer<ComponentFeatureLayer>();
		break;
	case TestItem::Graphics:
		SceneManager::Instance().RunningScene()->PushLayer<GraphicsFeatureLayer>();
		break;
	default:
		break;
	}
	

}



MEDUSA_IMPLEMENT_LAYER(TestLayer, ILayer, StringRef::Empty);

