// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#ifdef MEDUSA_ANDROID
#include "Application/Window/IWindow.h"
#include "Node/Input/Touch.h"


MEDUSA_BEGIN;

class AndroidWindow:public IWindow
{
	MEDUSA_RTTI(AndroidWindow,IWindow);

public:
	AndroidWindow(MedusaWindowHandle parentWindow,StringRef name=StringRef::Empty);
	virtual ~AndroidWindow(void);
	virtual bool Initialize()override;
	virtual bool Uninitialize()override;

	virtual bool OnEvent(IEventArg& eventArg)override;
	virtual void Show()override;

	virtual void MakeCenter()override;
	virtual void Resize(const Size2F& newSize)override;

	virtual bool Start()override;
	virtual bool Stop()override;
protected:
	Touch mPrevMouseTouch;
};

MEDUSA_END;

#endif