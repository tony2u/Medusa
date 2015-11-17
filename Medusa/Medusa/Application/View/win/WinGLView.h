// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Application/View/BaseRenderView.h"
#ifdef MEDUSA_WINDOWS
#ifdef MEDUSA_GLEW
MEDUSA_BEGIN;

class WinGLView :public BaseRenderView
{
	MEDUSA_DECLARE_RTTI;

public:
	WinGLView(StringRef name=StringRef::Empty);
	virtual ~WinGLView(void);
	virtual bool Initialize();
	virtual bool Uninitialize();

public:
	virtual void SwapBuffers();
	virtual void FinishDraw();

	virtual void Resize(const Size2F& newSize)override;

	bool SetupPixelFormat();
	bool SetupGLEW();
private:
	HDC mDC;
	HGLRC mRenderContext;
};

MEDUSA_END;
#endif
#endif
