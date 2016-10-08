// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Medusa.h"

USING_MEDUSA;

class HelloWorldLayer:public ILayer
{
	MEDUSA_NODE(HelloWorldLayer,ILayer);
public:
	HelloWorldLayer(StringRef name=StringRef::Empty,const IEventArg& e=IEventArg::Empty);
	virtual ~HelloWorldLayer(void);
	virtual bool Initialize();
	virtual bool OnEnter();
private:
};

MEDUSA_ENABLE_STATIC_CONSTRUCTOR(HelloWorldLayer);
