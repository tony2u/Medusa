// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "Node/Scene/IScene.h"
MEDUSA_BEGIN;


class Base3DScene :public IScene
{
	MEDUSA_NODE(Base3DScene,IScene);
public:
	Base3DScene(StringRef name = StringRef::Empty, const IEventArg& e = IEventArg::Empty);
	virtual ~Base3DScene(void);
	virtual bool Initialize()override;
	virtual bool Is2D()const override {return false;}
};
MEDUSA_ENABLE_STATIC_CONSTRUCTOR(Base3DScene);

MEDUSA_END;
