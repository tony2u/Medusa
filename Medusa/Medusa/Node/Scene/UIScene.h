// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "Node/Scene/IScene.h"
MEDUSA_BEGIN;


class UIScene :public IScene
{
	MEDUSA_NODE(UIScene,IScene);
public:
	UIScene(StringRef name = StringRef::Empty, const IEventArg& e = IEventArg::Empty);
	virtual ~UIScene(void);
	virtual bool Initialize() override;
	virtual bool Is2D()const override {return true;}
};

MEDUSA_END;
