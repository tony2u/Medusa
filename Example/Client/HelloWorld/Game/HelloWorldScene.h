// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Medusa.h"

USING_MEDUSA;

class HelloWorldScene:public UIScene
{
	MEDUSA_DECLARE_SCENE(HelloWorldScene);
public:
	HelloWorldScene(StringRef name=StringRef::Empty, const IEventArg& e = IEventArg::Empty);
	virtual ~HelloWorldScene(void);
	virtual bool Initialize();
	virtual bool OnEnter();

};

