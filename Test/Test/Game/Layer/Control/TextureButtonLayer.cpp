// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "TestPreCompiled.h"
#include "TextureButtonLayer.h"


TextureButtonLayer::TextureButtonLayer(StringRef name/*=StringRef::Empty*/, const IEventArg& e/*=IEventArg::Empty*/) :BaseCaseLayer(name, e)
{



}

TextureButtonLayer::~TextureButtonLayer(void)
{
}

bool TextureButtonLayer::Initialize()
{
	RETURN_FALSE_IF_FALSE(BaseCaseLayer::Initialize());

	TextureButton* button=NodeFactory::Instance().CreateTextureButton("Close.png","CloseSelected.png");
	button->SetDock(DockPoint::MiddleCenter);
	button->SetAnchor(0.5f,0.5f);
	AddChild(button);
	button->OnTap+=Bind(&TextureButtonLayer::OnTap,this);

	return true;
}


void TextureButtonLayer::OnTap(INode* sender,TapGestureEventArg& e)
{
	Log::FormatInfo("Tap");
}



MEDUSA_IMPLEMENT_LAYER(TextureButtonLayer, BaseCaseLayer, StringRef::Empty);

