// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "TestPreDeclares.h"
#include "Game/BaseCaseLayer.h"

class TextureButtonLayer :public BaseCaseLayer
{
	MEDUSA_NODE(TextureButtonLayer, BaseCaseLayer);
public:
	TextureButtonLayer(StringRef name=StringRef::Empty,const IEventArg& e=IEventArg::Empty);
	virtual ~TextureButtonLayer(void);
	virtual bool Initialize()override;
private:
	void OnTap(INode* sender,TapGestureEventArg& e);

};

MEDUSA_ENABLE_STATIC_CONSTRUCTOR(TextureButtonLayer);
