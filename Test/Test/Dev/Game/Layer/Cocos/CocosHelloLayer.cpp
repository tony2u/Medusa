// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "TestPreCompiled.h"
#include "CocosHelloLayer.h"
#include "Node/Sprite/NineGridSprite.h"
#include "Node/Input/IInputHandler.h"

CocosHelloLayer::CocosHelloLayer(StringRef name/*=StringRef::Empty*/, const IEventArg& e/*=IEventArg::Empty*/) :BaseCaseLayer(name, e)
{
}

CocosHelloLayer::~CocosHelloLayer(void)
{
}

bool CocosHelloLayer::Initialize()
{
	RETURN_FALSE_IF_FALSE(BaseCaseLayer::Initialize());

	MEDUSA_INPUT_BIND(CocosHelloLayer,OnStart);

	return true;
}

bool CocosHelloLayer::OnEnter()
{
	auto child = (NineGridSprite*)FindChild("Image_1");
	child->EnableNineGrid(true);
	return true;
}

bool CocosHelloLayer::OnStart(INode* sender, IEventArg* e)
{
	auto userData= sender->Properties().Get("UserData");
	Log::FormatInfo("Invoke {}", userData);
	return true;
}

MEDUSA_IMPLEMENT_LAYER(CocosHelloLayer, BaseCaseLayer, "MainLayer.csb", StringRef::Empty);

