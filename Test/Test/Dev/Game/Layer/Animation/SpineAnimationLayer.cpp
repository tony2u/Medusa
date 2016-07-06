// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "TestPreCompiled.h"
#include "SpineAnimationLayer.h"


SpineAnimationLayer::SpineAnimationLayer(StringRef name/*=StringRef::Empty*/, const IEventArg& e/*=IEventArg::Empty*/) :BaseCaseLayer(name, e)
{

}

SpineAnimationLayer::~SpineAnimationLayer(void)
{
}

bool SpineAnimationLayer::Initialize()
{
	RETURN_FALSE_IF_FALSE(BaseCaseLayer::Initialize());


	FOR_EACH_SIZE(i, 1)
	{
		SpineSkeleton* skeleton = NodeFactory::Instance().CreateSkeleton("BladeMaster.json", "BladeMaster.atlas",true);
		skeleton->SetPosition(550.f+i, 200.f+i);
		AddChild(skeleton);
		skeleton->PlayAnimation("Idle", true);
	}
	

	//skeleton->StartAnimation("hit", true);
	//skeleton->StartAnimation("idle", true);
	//skeleton->StartAnimation("jump", true);
	//skeleton->StartAnimation("run", true);
	//skeleton->StartAnimation("shoot", true);
	//skeleton->StartAnimation("test", true);
	//skeleton->StartAnimation("walk", true);


	//skeleton->Start();

	//skeleton->SetBoneVisible(true);
	//skeleton->SetSlotVisible(false);
	/*Sprite* sprite = NodeFactory::Instance().CreateQuadSprite("TestSprite", "test2.png");
	skeleton->AddChild(sprite);*/
	/*SpineAnimation* ani = NodeFactory::Instance().CreateSpineAnimation("MyAni",1.f,"spineboy.json","spineboy.atlas");
	ani->SetDock(DockPoint::MiddleBottom);
	ani->SetAnchor(0.5f, 0.5f);
	AddChild(ani);

	ni->SetAnimation(0, "idle", true);
	ani->Start();*/

	return true;
}




MEDUSA_IMPLEMENT_NODE(SpineAnimationLayer);

