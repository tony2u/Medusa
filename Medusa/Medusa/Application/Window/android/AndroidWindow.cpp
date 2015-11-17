// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"

#ifdef MEDUSA_ANDROID

#include "AndroidWindow.h"
#include "Graphics/ResolutionAdapter.h"
#include "Node/Input/InputManager.h"
#include "Node/Input/Touch.h"
#include "Node/Input/EventArg/TouchEventArg.h"
#include "Node/Input/EventArg/KeyDownEventArg.h"
#include "Node/Input/EventArg/KeyUpEventArg.h"
#include "Node/Input/EventArg/ScrollEventArg.h"
#include "Node/Input/EventArg/CharInputEventArg.h"
#include "Application/Application.h"
#include "Application/ApplicationStatics.h"

MEDUSA_BEGIN;


AndroidWindow::AndroidWindow(MedusaWindowHandle parentWindow, StringRef name/*=StringRef::Empty*/) :IWindow(parentWindow, name)
{

}

AndroidWindow::~AndroidWindow()
{
	
}

bool AndroidWindow::Initialize()
{
	RETURN_FALSE_IF_FALSE(IWindow::Initialize());

	
	return true;
}


bool AndroidWindow::Uninitialize()
{
	
	return true;
}

void AndroidWindow::Show()
{

}


bool AndroidWindow::OnEvent(IEventArg& eventArg)
{
	return true;
}

bool AndroidWindow::Start()
{
	return true;
}

bool AndroidWindow::Stop()
{
	return true;
}

void AndroidWindow::MakeCenter()
{
	
}

void AndroidWindow::Resize(const Size2F& newSize)
{
	
}


MEDUSA_IMPLEMENT_RTTI(AndroidWindow, IWindow);

MEDUSA_END;

#endif
