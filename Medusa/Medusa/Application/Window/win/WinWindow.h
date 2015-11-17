// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#ifdef MEDUSA_WINDOWS
#include "Application/Window/IWindow.h"
#include "Application/View/win/WinGLView.h"
#include "Node/Input/Touch.h"
#include "Core/Profile/PerformanceCounter.h"


MEDUSA_BEGIN;

class WinWindow:public IWindow
{
	MEDUSA_DECLARE_RTTI;

public:
	WinWindow(MedusaWindowHandle parentWindow,StringRef name=StringRef::Empty);
	virtual ~WinWindow(void);
	virtual bool Initialize();
	virtual bool Uninitialize();

	virtual bool OnEvent(IEventArg& eventArg)override;
	virtual void Show()override;

	virtual void MakeCenter()override;
	virtual void Resize(const Size2F& newSize)override;

	virtual bool Start()override;
	virtual bool Stop()override;
	virtual bool Pause()override;
	virtual bool Resume()override;


	LRESULT WndProc(UINT message, WPARAM wParam, LPARAM lParam);
protected:
	virtual void OnResize(const Size2F& newSize)override;
	Touch mPrevMouseTouch;
	ProfileTimeType mPrev;
	ProfileTimeType mNow;

};

MEDUSA_END;

#endif