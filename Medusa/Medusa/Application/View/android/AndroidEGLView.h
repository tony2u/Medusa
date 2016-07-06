// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Application/View/BaseRenderView.h"
#ifdef MEDUSA_ANDROID

#ifdef MEDUSA_GLES

MEDUSA_BEGIN;

class AndroidEGLView :public BaseRenderView
{
	MEDUSA_RTTI(AndroidEGLView,BaseRenderView);

public:
	AndroidEGLView(StringRef name=StringRef::Empty);
	virtual ~AndroidEGLView(void);
	virtual bool Initialize()override;
	virtual bool Uninitialize()override;

public:
	virtual void SwapBuffers() override;
	virtual void FinishDraw() override;

	virtual void Resize(const Size2F& newSize)override;

};


MEDUSA_END;
#endif
#endif
