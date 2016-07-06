// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "Application/View/IView.h"


MEDUSA_BEGIN;

class BaseRenderView :public IView
{
	MEDUSA_RTTI(BaseRenderView,IView);

public:
	BaseRenderView(StringRef name=StringRef::Empty);
	virtual ~BaseRenderView(void);
	virtual void SwapBuffers()=0;
	virtual void FinishDraw()=0;

};

MEDUSA_END;
