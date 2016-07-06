// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "TestPreDeclares.h"
#include "Node/Scene/UIScene.h"
#include "Core/String/StringRef.h"

class TestScene:public UIScene
{
	MEDUSA_NODE(TestScene,UIScene);
public:
	TestScene(StringRef name=StringRef::Empty, const IEventArg& e = IEventArg::Empty);
	virtual ~TestScene(void);
	virtual bool Initialize()override;

};

