// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Application/View/BaseRenderView.h"
#ifdef MEDUSA_WINDOWS

#ifdef MEDUSA_GLES
#include "Lib/win/OGLES/EGL/egl.h"
MEDUSA_BEGIN;

class WinEGLView :public BaseRenderView
{
	MEDUSA_RTTI(WinEGLView,BaseRenderView);

public:
	WinEGLView(StringRef name=StringRef::Empty);
	virtual ~WinEGLView(void);
	virtual bool Initialize();
	virtual bool Uninitialize();

public:
	virtual void SwapBuffers();
	virtual void FinishDraw();

	virtual void Resize(const Size2F& newSize)override;
private:
	bool GetEGLError();
	EGLConfig ChooseConfig()const;
	void CreateContext();
	void CreateSurface();

	bool IsEGLExtensionSupported(StringRef extension);

	bool IsNeedPBuffer() const { return mIsNeedPBuffer; }
	void SetIsNeedPBuffer(bool val) { mIsNeedPBuffer = val; }
	bool IsNeedPixmap() const { return mIsNeedPixmap; }
	void SetIsNeedPixmap(bool val) { mIsNeedPixmap = val; }
private:
	uint mGLESVersion;
	EGLNativeWindowType     mEGLNativeWindow;
	EGLNativeDisplayType    mEGLNativeDisplay;
	EGLDisplay              mEGLDisplay;
	EGLConfig               mEGLConfig;
	EGLSurface              mEGLSurface;
	EGLContext              mEGLContext;

	//pixmap support
	EGLNativePixmapType mBitmapPixmap;
	EGLNativePixmapType mBitmapPixmapOld;
	EGLNativeDisplayType mPixmapDisplay;


	//refer to http://www.khronos.org/opengles/documentation/opengles1_0/html/eglChooseConfig.html
	uint mColorBufferSize;	//EGL_BUFFER_SIZE:0	
	uint mRedColorBufferSize;	//EGL_RED_SIZE:0
	uint mGreenColorBufferSize;	//EGL_GREEN_SIZE:0
	uint mBlueColorBufferSize;	//EGL_BLUE_SIZE:0
	uint mAlphaColorBufferSize;	//EGL_ALPHA_SIZE:0
	uint mConfigId;	//EGL_CONFIG_ID:EGL_DONT_CARE
	//uint mDepthSize;	//EGL_DEPTH_SIZE:0
	int mLevel;		//EGL_LEVEL:0
	int mNativeRenderable;	//EGL_NATIVE_RENDERABLE:EGL_DONT_CARE,EGL_TRUE,EGL_FALSE
	uint mSampleBuffers;	//EGL_SAMPLE_BUFFERS:0,1
	uint mSamples;	//EGL_SAMPLES:0
	//uint mStencilSize;	//EGL_STENCIL_SIZE:0
	uint mSurfaceType;	//EGL_SURFACE_TYPE:EGL_WINDOW_BIT, EGL_PBUFFER_BIT, EGL_PIXMAP_BIT
	uint mTransparentType;	//EGL_TRANSPARENT_TYPE:EGL_NONE,EGL_TRANSPARENT_RGB
	uint mTransparentRedValue;	//EGL_TRANSPARENT_RED_VALUE:0
	uint mTransparentGreenValue;	//EGL_TRANSPARENT_GREEN_VALUE:0
	uint mTransparentBlueValue;	//EGL_TRANSPARENT_BLUE_VALUE:0
	uint mRenderableType;	//EGL_OPENGL_ES_BIT,EGL_OPENVG_BIT,EGL_OPENGL_ES2_BIT,EGL_OPENGL_BIT

	bool mIsNeedPBuffer;	//off screen rendering
	bool mIsNeedPixmap;	//off screen rendering,but local API can access it too
};


MEDUSA_END;
#endif
#endif
