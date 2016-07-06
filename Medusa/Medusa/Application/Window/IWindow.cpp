// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "IWindow.h"
#include "Application/View/IView.h"

MEDUSA_BEGIN;

IWindow::IWindow(MedusaWindowHandle parentWindow,StringRef name/*=StringRef::Empty*/)
	:mName(name), mParentWindowHandle(parentWindow), mWindowHandle(0), mSize(Size2F::Zero)
{
}


IWindow::~IWindow(void)
{

	SAFE_DELETE_COLLECTION(mViews);
}

void IWindow::AddView(IView* view)
{
	mViews.Add(view);
	view->SetParent(this);
}
bool IWindow::Start()
{
	RETURN_FALSE_IF_FALSE(DefaultRunnable::Start());
	for (auto* view : mViews)
	{
		RETURN_FALSE_IF_FALSE(view->Start());
	}

	return true;
}


bool IWindow::Stop()
{
	RETURN_FALSE_IF_FALSE(DefaultRunnable::Stop());

	for (auto* view : mViews)
	{
		RETURN_FALSE_IF_FALSE(view->Stop());
	}

	return true;
}

bool IWindow::Pause()
{
	RETURN_FALSE_IF_FALSE(DefaultRunnable::Pause());

	for (auto* view : mViews)
	{
		RETURN_FALSE_IF_FALSE(view->Pause());
	}

	return true;
}


bool IWindow::Resume()
{
	RETURN_FALSE_IF_FALSE(DefaultRunnable::Resume());

	for (auto* view : mViews)
	{
		RETURN_FALSE_IF_FALSE(view->Resume());
	}

	return true;
}


MEDUSA_END;
