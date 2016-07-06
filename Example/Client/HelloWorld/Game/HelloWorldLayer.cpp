// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "HelloWorldLayer.h"
#include "Core/Chrono/ProfileSample.h"
#include "Node/Panel/PanelFactory.h"


HelloWorldLayer::HelloWorldLayer(StringRef name/*=StringRef::Empty*/,const IEventArg& e/*=IEventArg::Empty*/):ILayer(name,e)
{

	

}

HelloWorldLayer::~HelloWorldLayer(void)
{
}

bool HelloWorldLayer::Initialize()
{
	RETURN_FALSE_IF_FALSE(ILayer::Initialize());
	/*auto* sprite=NodeFactory::Instance().CreateQuadSprite("HelloWorld.png");
	sprite->SetAnchorPoint(AnchorPoint::MiddleCenter);
	sprite->SetDock(DockPoint::MiddleCenter);
	AddChild(sprite);*/
	
	/*auto state=this->MutableRenderState().AllocState<RasterizerRenderState>();
	state->SetCullMode(GraphicsFace::Back);
	state->Enable(true);

	auto depthState = this->MutableRenderState().AllocState<DepthStencilRenderState>();
	depthState->EnableDepthTest(true);*/
	

	//auto* shape1 = NodeFactory::Instance().CreatePODSprite("Scene.pod");
	////shape1->SetAnchor(0.5f, 0.5f);
	////shape1->SetDock(DockPoint::MiddleCenter);
	//AddChild(shape1);

	return true;
}


bool HelloWorldLayer::OnEnter()
{
	/*auto winSize = ResolutionAdapter::Instance().WinSize();
	auto camera = CameraFactory::Instance().CreateFromModel("Camera01", "Scene.pod", winSize, false);
	IScene* scene = (IScene*)mParent;
	scene->SetCamera(camera);*/
	return true;
}

MEDUSA_IMPLEMENT_NODE(HelloWorldLayer);
