// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#ifdef MEDUSA_IOS
#include "IOSWindow.h"
#include "IOSEGLView.h"
#import "MyRootViewController.h"

#import <UIKit/UIKit.h>
#import <GLKit/GLKit.h>

MEDUSA_BEGIN;

IOSWindow::IOSWindow(MedusaWindowHandle parentWindow,StringRef name/*=StringRef::Empty*/):IWindow(parentWindow,name)
{
}


IOSWindow::~IOSWindow(void)
{
    void* window=(void*)mWindowHandle;
    CFBridgingRelease(window);
    mWindowHandle=0;
}

bool IOSWindow::Initialize()
{
	UIWindow* window = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];
    CFBridgingRetain(window);
	mWindowHandle=(MedusaWindowHandle)window;
    return true;
}

void IOSWindow::Show()
{
	IOSEGLView* glView=(IOSEGLView*)FirstView();

	UIView* uiView=(__bridge UIView*)glView->GetViewHandle();

    MyRootViewController* viewController = [[MyRootViewController alloc] initWithNibName:nil bundle:nil];
    //viewController.wantsFullScreenLayout = YES;
    viewController.view = uiView;

    UIWindow* window=(__bridge UIWindow*)(void*)mWindowHandle;
    // Set RootViewController to window
    if ( [[UIDevice currentDevice].systemVersion floatValue] < 6.0)
    {
        // warning: addSubView doesn't work on iOS6
        [window addSubview: viewController.view];
    }
    else
    {
        // use this method on ios6
        [window setRootViewController:viewController];
    }
    

    [window makeKeyAndVisible];

    //[[UIApplication sharedApplication] setStatusBarHidden: YES];
    [viewController prefersStatusBarHidden];
}


MEDUSA_IMPLEMENT_RTTI(IOSWindow, IWindow);
MEDUSA_END;

#endif