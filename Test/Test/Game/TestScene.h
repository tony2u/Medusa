// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "TestPreDeclares.h"
#include "Node/Scene/Base2DScene.h"
#include "Core/String/StringRef.h"

class TestScene:public Base2DScene
{
	MEDUSA_DECLARE_RTTI;
public:
	TestScene(StringRef name=StringRef::Empty);
	virtual ~TestScene(void);
	virtual bool Initialize()override;

};

