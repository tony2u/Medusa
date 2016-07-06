// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "AndroidEGLView.h"
#include "Application/Window/android/AndroidWindow.h"
#include "Graphics/ResolutionAdapter.h"
#include "Graphics/Render/Render.h"
#include "Graphics/GraphicsContext.h"

#ifdef MEDUSA_ANDROID
#ifdef MEDUSA_GLES
MEDUSA_BEGIN;

AndroidEGLView::AndroidEGLView(StringRef name/*=StringRef::Empty*/) :BaseRenderView(name)
{
	
}

AndroidEGLView::~AndroidEGLView(void)
{
	
}

bool AndroidEGLView::Initialize()
{
	RETURN_FALSE_IF_FALSE(BaseRenderView::Initialize());


	return true;

}

bool AndroidEGLView::Uninitialize()
{
	return true;
}



void AndroidEGLView::SwapBuffers()
{
}

void AndroidEGLView::FinishDraw()
{
	Render::Instance().Finish();
}

void AndroidEGLView::Resize(const Size2F& newSize)
{
	
}


MEDUSA_END;

#endif
#endif