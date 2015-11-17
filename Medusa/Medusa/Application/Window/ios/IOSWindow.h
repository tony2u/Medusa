// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "Application/Window/IWindow.h"
#ifdef MEDUSA_IOS

#include "Application/View/ios/IOSEGLView.h"

MEDUSA_BEGIN;

class IOSWindow:public IWindow
{
	MEDUSA_DECLARE_RTTI;

public:
	IOSWindow(MedusaWindowHandle parentWindow,StringRef name=StringRef::Empty);
	virtual ~IOSWindow(void);
	virtual bool Initialize()override;
	virtual void Show()override;
    virtual void MakeCenter()override{}

protected:
	intp mViewController;
};

MEDUSA_END;

#endif