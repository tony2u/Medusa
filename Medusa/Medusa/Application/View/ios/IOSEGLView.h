// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "Application/View/BaseRenderView.h"
#ifdef MEDUSA_IOS

MEDUSA_BEGIN;

class IOSEGLView :public BaseRenderView
{
	MEDUSA_DECLARE_RTTI;
public:
	IOSEGLView(StringRef name=StringRef::Empty);
	virtual ~IOSEGLView(void);
	virtual bool Initialize()override;
	void* GetViewHandle()const{return mViewHandle;}
public:
	virtual void SwapBuffers()override;
	virtual void FinishDraw()override;

	virtual bool Start()override;
	virtual bool Stop()override;
	virtual bool Pause()override;
	virtual bool Resume()override;
protected:
	void* mViewHandle;
};

MEDUSA_END;

#endif
