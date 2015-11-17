// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "IOSEGLView.h"
#import <UIKit/UIKit.h>

#import "MyEAGLView.h"
#include "Graphics/Render/Render.h"

MEDUSA_BEGIN;

IOSEGLView::IOSEGLView(StringRef name/*=StringRef::Empty*/):BaseRenderView(name)
{
}


IOSEGLView::~IOSEGLView(void)
{
    CFBridgingRelease(mViewHandle);
    mViewHandle=nullptr;
}

bool IOSEGLView::Initialize()
{
    CGRect frame=[[UIScreen mainScreen] bounds];
    MyEAGLView *view = [[MyEAGLView alloc] initWithFrame:frame];
	mViewHandle=(void*)CFBridgingRetain(view);
    
    return true;
}


void IOSEGLView::SwapBuffers()
{
	MyEAGLView *view=(__bridge MyEAGLView*)mViewHandle;
	return [view SwapBuffers];
}

void IOSEGLView::FinishDraw()
{
	Render::Instance().Finish();
}


bool IOSEGLView::Start()
{
	RETURN_FALSE_IF_FALSE(IView::Start());
	MyEAGLView *view=(__bridge MyEAGLView*)mViewHandle;
	return [view Start];
}

bool IOSEGLView::Stop()
{
	RETURN_FALSE_IF_FALSE(IView::Stop());
	MyEAGLView *view=(__bridge MyEAGLView*)mViewHandle;
	return [view Stop];
}

bool IOSEGLView::Pause()
{
	RETURN_FALSE_IF_FALSE(IView::Pause());
	MyEAGLView *view=(__bridge MyEAGLView*)mViewHandle;
	return [view Pause];
}

bool IOSEGLView::Resume()
{
	RETURN_FALSE_IF_FALSE(IView::Resume());
	MyEAGLView *view=(__bridge MyEAGLView*)mViewHandle;
	return [view Resume];
}


MEDUSA_IMPLEMENT_RTTI(IOSEGLView,BaseRenderView);

MEDUSA_END;
