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
#include "Game/Layer/3D/ThreeDFeatureLayer.h"
#include "Game/Layer/Map/MapFeatureLayer.h"
#include "Game/Layer/Cocos/CocosFeatureLayer.h"
#include "Game/Layer/Game/GameFeatureLayer.h"
#include "CocosStudio/BinaryEditor.h"


enum class TestItem
{
	Cocos,
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
	ThreeD,
	Map,
	Game,

};

TestLayer::TestLayer(StringRef name/*=StringRef::Empty*/,const IEventArg& e/*=IEventArg::Empty*/):ILayer(name,e)
{

	mItems.Emplace(L"Cocos");
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
	mItems.Emplace(L"3D");
	mItems.Emplace(L"Map");
	mItems.Emplace(L"Game");





}

TestLayer::~TestLayer(void)
{
}

bool TestLayer::Initialize()
{
	RETURN_FALSE_IF_FALSE(ILayer::Initialize());

	auto dataSource = DataSourceFactory::Instance().CreateWStringList("MainList", mItems, true);


	ListBox* listBox = NodeFactory::Instance().CreateListBox();
	listBox->SetStretch(Medusa::Stretch::Fill);
	auto binding = listBox->BindTo<LabelTemplate>(dataSource,true);
	auto nodeTemplate = (LabelTemplate*)binding->GetTemplate(0);
	nodeTemplate->MutableFontId().Name="arial88.fnt";
	nodeTemplate->SetAlignment(Alignment::LeftBottom);
	nodeTemplate->SetDock(DockPoint::MiddleBottom);
	nodeTemplate->SetAnchor(AnchorPoint::MiddleBottom);

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
		SceneManager::Instance().Current()->PushLayer<SpriteFeatureLayer>();
		break;
	case TestItem::Shape:
		SceneManager::Instance().Current()->PushLayer<ShapeFeatureLayer>();
		break;
	case TestItem::Control:
		SceneManager::Instance().Current()->PushLayer<ControlFeatureLayer>();
		break;
	case TestItem::Action:
		SceneManager::Instance().Current()->PushLayer<ActionFeatureLayer>();
		break;
	case TestItem::Animation:
		SceneManager::Instance().Current()->PushLayer<AnimationFeatureLayer>();
		break;
	case TestItem::Font:
		SceneManager::Instance().Current()->PushLayer<FontFeatureLayer>();
		break;
	case TestItem::Particle:
		SceneManager::Instance().Current()->PushLayer<ParticleFeatureLayer>();
		break;
	case TestItem::Shader:
		SceneManager::Instance().Current()->PushLayer<ShaderFeatureLayer>();
		break;
	case TestItem::Performance:
		SceneManager::Instance().Current()->PushLayer<PerformanceFeatureLayer>();
		break;
	case TestItem::Audio:
		SceneManager::Instance().Current()->PushLayer<AudioFeatureLayer>();
		break;
	case TestItem::Component:
		SceneManager::Instance().Current()->PushLayer<ComponentFeatureLayer>();
		break;
	case TestItem::Graphics:
		SceneManager::Instance().Current()->PushLayer<GraphicsFeatureLayer>();
		break;
	case TestItem::ThreeD:
		SceneManager::Instance().Current()->PushLayer<ThreeDFeatureLayer>();
		break;
	case TestItem::Map:
		SceneManager::Instance().Current()->PushLayer<MapFeatureLayer>();
		break;
	case TestItem::Cocos:
		SceneManager::Instance().Current()->PushLayer<CocosFeatureLayer>();
		break;
	case TestItem::Game:
		SceneManager::Instance().Current()->PushLayer<GameFeatureLayer>();
		break;
	default:
		break;
	}
	

}



MEDUSA_IMPLEMENT_NODE(TestLayer);

