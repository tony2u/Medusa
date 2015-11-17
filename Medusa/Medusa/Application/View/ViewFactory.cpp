// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Application/View/ViewFactory.h"

#include "Application/View/IView.h"
#ifdef MEDUSA_WINDOWS
#include "Application/View/win/WinGLView.h"
#include "Application/View/win/WinEGLView.h"
#endif

#ifdef MEDUSA_IOS
#include "Application/View/ios/IOSEGLView.h"
#endif

#ifdef MEDUSA_ANDROID
#include "Application/View/android/AndroidEGLView.h"
#endif

MEDUSA_BEGIN;




BaseRenderView* ViewFactory::CreateGLView(StringRef name /*= StringRef::Empty*/)
{
#ifdef MEDUSA_WINDOWS
#ifdef MEDUSA_GLES
	return new WinEGLView(name);
#endif
#ifdef MEDUSA_GLEW
	return new WinGLView(name);
#endif

#endif

#ifdef MEDUSA_IOS
	return new IOSEGLView(name);
#endif

#ifdef MEDUSA_ANDROID
	return new AndroidEGLView(name);
#endif
}

MEDUSA_END;

