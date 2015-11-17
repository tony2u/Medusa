// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "WinEGLView.h"
#include "Application/Window/win/WinWindow.h"
#include "Graphics/ResolutionAdapter.h"
#include "Core/Profile/ProfileSample.h"
#include "Graphics/Render/Render.h"
#include "Graphics/GraphicsContext.h"
#include "Rendering/RenderEngine.h"

#ifdef MEDUSA_WINDOWS
#ifdef MEDUSA_GLES
MEDUSA_BEGIN;

WinEGLView::WinEGLView(StringRef name/*=StringRef::Empty*/) :BaseRenderView(name)
{
	GraphicsAPI api = GraphicsContext::Instance().API();
	if (api == GraphicsAPI::OpenGLES2)
	{
		mGLESVersion = 2;
		mRenderableType = EGL_OPENGL_ES2_BIT;
	}
	else if (api == GraphicsAPI::OpenGLES3)
	{
		mGLESVersion = 3;
		mRenderableType = EGL_OPENGL_ES2_BIT;
	}

	mColorBufferSize = 0;	//0
	mRedColorBufferSize = 0;	//0
	mGreenColorBufferSize = 0;	//0
	mBlueColorBufferSize = 0;	//0
	mAlphaColorBufferSize = 0;	//0
	mConfigId = (uint)EGL_DONT_CARE;	//EGL_DONT_CARE
	//mDepthSize=24;	//0
	mLevel = 0;		//0
	mNativeRenderable = EGL_FALSE;	//EGL_DONT_CARE,EGL_TRUE,EGL_FALSE
	mSampleBuffers = 0;	//0,1
	mSamples = 0;	//0
	//mStencilSize=8;	//0
	mSurfaceType = EGL_WINDOW_BIT;	//EGL_WINDOW_BIT, EGL_PBUFFER_BIT, EGL_PIXMAP_BIT
	mTransparentType = EGL_NONE;	//EGL_NONE,EGL_TRANSPARENT_RGB
	mTransparentRedValue = 0;	//0
	mTransparentGreenValue = 0;	//0
	mTransparentBlueValue = 0;	//0

	mIsNeedPBuffer = false;
	mIsNeedPixmap = false;
}

WinEGLView::~WinEGLView(void)
{
	
}

bool WinEGLView::Initialize()
{
	RETURN_FALSE_IF_FALSE(BaseRenderView::Initialize());


	MEDUSA_ASSERT_TRUE(mParent->IsA<IWindow>(), "");
	WinWindow* window = (WinWindow*)(INode*)mParent;

	EGLNativeWindowType eglNativeWindow = window->WindowHandle();

	mEGLNativeWindow = eglNativeWindow;
	mEGLNativeDisplay = EGL_DEFAULT_DISPLAY;
	mEGLDisplay = EGL_NO_DISPLAY;
	mEGLConfig = 0;
	mEGLSurface = EGL_NO_SURFACE;
	mEGLContext = EGL_NO_CONTEXT;

	mPixmapDisplay = 0;
	mBitmapPixmap = 0;
	mBitmapPixmapOld = 0;

	/*
	Step 0 - Create a NativeWindowType that we can use for OpenGL ES output
	*/


	/*
	Step 1 - Get the default display.
	EGL uses the concept of a "display" which in most environments
	corresponds to a single physical screen. Since we usually want
	to draw to the main screen or only have a single screen to begin
	with, we let EGL pick the default display.
	Querying other displays is platform specific.
	*/
	mEGLNativeDisplay = GetDC(mEGLNativeWindow);

	mEGLDisplay = eglGetDisplay(mEGLNativeDisplay);
	if (mEGLDisplay == EGL_NO_DISPLAY)
	{
		mEGLDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
	}
	MEDUSA_ASSERT_NOT_EQUAL(mEGLDisplay, EGL_NO_DISPLAY, "");

	if (mIsNeedPixmap)
	{
		mPixmapDisplay = CreateCompatibleDC(mEGLNativeDisplay);
		Size2F screenSize = ResolutionAdapter::Instance().WinSize();
		mBitmapPixmap = CreateCompatibleBitmap(mEGLNativeDisplay, (uint)screenSize.Width, (uint)screenSize.Height);
	}

	/*
	Step 2 - Initialize EGL.
	EGL has to be initialized with the display obtained in the
	previous step. We cannot use other EGL functions except
	eglGetDisplay and eglGetError before eglInitialize has been
	called.
	If we're not interested in the EGL version number we can just
	pass nullptr for the second and third parameters.
	*/

	EGLint majorVersion, minorVersion;
	EGLBoolean result = eglInitialize(mEGLDisplay, &majorVersion, &minorVersion);
	MEDUSA_ASSERT_NOT_ZERO(result, "");

	//ASSERT_NOT_EQUAL(majorVersion,1);

	/*
	Step 3 - Specify the required configuration attributes.
	An EGL "configuration" describes the pixel format and type of
	surfaces that can be used for drawing.
	For now we just want to use a 16 bit RGB surface that is a
	Window surface, i.e. it will be visible on screen. The list
	has to contain key/value pairs, terminated with EGL_NONE.
	*/
	eglBindAPI(EGL_OPENGL_ES_API);
	MEDUSA_ASSERT_FALSE(GetEGLError(), "");

	/*
	Step 4 - Find a config that matches all requirements.
	eglChooseConfig provides a list of all available configurations
	that meet or exceed the requirements given as the second
	argument. In most cases we just want the first config that meets
	all criteria, so we can limit the number of configs returned to 1.
	*/

	mEGLConfig = ChooseConfig();

	/*
	Step 5 - Create a surface to draw to.
	Use the config picked in the previous step and the native window
	handle when available to create a window surface. A window surface
	is one that will be visible on screen inside the native display (or
	full screen if there is no windowing system).
	Pixmaps and pbuffers are surfaces which only exist in off-screen
	memory.
	*/
	CreateSurface();


	/*
	Step 6 - Create a context.
	EGL has to create a context for OpenGL ES. Our OpenGL ES resources
	like textures will only be valid inside this context
	(or shared contexts)
	*/
	CreateContext();


	/*
	Step 7 - Bind the context to the current thread and use our
	window surface for drawing and reading.
	Contexts are bound to a thread. This means you don't have to
	worry about other threads and processes interfering with your
	OpenGL ES application.
	We need to specify a surface that will be the target of all
	subsequent drawing operations, and one that will be the source
	of read operations. They can be the same surface.
	*/

	//ASSERT_NOT_EQUAL(eglSurface,EGL_NO_SURFACE,0);

	eglMakeCurrent(mEGLDisplay, mEGLSurface, mEGLSurface, mEGLContext);
	MEDUSA_ASSERT_FALSE(GetEGLError(), "");
	/*
	Step 8 - Draw something with OpenGL ES.
	At this point everything is initialized and we're ready to use
	OpenGL ES to draw something on the screen.
	*/
	if (mIsNeedPixmap)
	{
		mBitmapPixmapOld = (EGLNativePixmapType)SelectObject(mPixmapDisplay, mBitmapPixmap);
	}
	//SetForegroundWindow(mEGLNativeWindow);

	RenderEngine::Instance().Initialize();

	return true;

}

bool WinEGLView::Uninitialize()
{
	RETURN_TRUE_IF_NULL(mEGLDisplay);

	/*
	Step 9 - Terminate OpenGL ES and destroy the window (if present).
	eglTerminate takes care of destroying any context or surface created
	with this display, so we don't need to call eglDestroySurface or
	eglDestroyContext here.
	*/
	if (mEGLDisplay != nullptr)
	{
		eglMakeCurrent(mEGLDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
		eglTerminate(mEGLDisplay);
		mEGLDisplay = EGL_NO_DISPLAY;
	}

	if (mIsNeedPixmap)
	{
		SelectObject(mPixmapDisplay, mBitmapPixmapOld);
		DeleteDC(mPixmapDisplay);
		DeleteObject(mBitmapPixmap);
	}

	/*
	Step 10 - Destroy the eglWindow.
	Again, this is platform specific and delegated to a separate function.
	*/
	if (mEGLNativeDisplay != nullptr)
	{
		ReleaseDC(mEGLNativeWindow, mEGLNativeDisplay);
		mEGLNativeWindow = nullptr;
		mEGLNativeDisplay = EGL_DEFAULT_DISPLAY;
	}

	//mEGLNativeWindow will be destroyed outside


	mEGLConfig = 0;
	mEGLSurface = EGL_NO_SURFACE;
	mEGLContext = EGL_NO_CONTEXT;

	return true;
}



void WinEGLView::SwapBuffers()
{
	eglSwapBuffers(mEGLDisplay, mEGLSurface);
}

void WinEGLView::FinishDraw()
{
	Render::Instance().Finish();
}

bool WinEGLView::GetEGLError()
{
	EGLint error = eglGetError();
	if (error != EGL_SUCCESS)
	{
		return true;
	}

	return false;
}


void WinEGLView::Resize(const Size2F& newSize)
{
	if (!mEGLNativeWindow || EGL_NO_DISPLAY == mEGLDisplay)
	{
		return;
	}


	if (mIsNeedPixmap)
	{
		//delete old pixmap
		SelectObject(mPixmapDisplay, mBitmapPixmapOld);
		DeleteObject(mBitmapPixmap);
		//create new pixmap
		Size2F screenSize = ResolutionAdapter::Instance().WinSize();
		mBitmapPixmap = CreateCompatibleBitmap(mEGLNativeDisplay, (uint)screenSize.Width, (uint)screenSize.Height);
		SelectObject(mPixmapDisplay, mBitmapPixmapOld);
	}

	// release old surface
	if (EGL_NO_SURFACE != mEGLSurface)
	{
		eglDestroySurface(mEGLDisplay, mEGLSurface);
		mEGLSurface = EGL_NO_SURFACE;
	}

	// create new surface and make current
	mEGLSurface = eglCreateWindowSurface(mEGLDisplay, mEGLConfig, mEGLNativeWindow, nullptr);
	eglMakeCurrent(mEGLDisplay, mEGLSurface, mEGLSurface, mEGLContext);
}

EGLConfig WinEGLView::ChooseConfig() const
{
	EGLint configAttribures[32];
	EGLConfig config = (EGLConfig)0;
	uint i = 0;

	if (mConfigId != EGL_DONT_CARE)
	{
		configAttribures[i++] = EGL_CONFIG_ID;
		configAttribures[i++] = mConfigId;
	}
	else
	{
		configAttribures[i++] = EGL_LEVEL;
		configAttribures[i++] = 0;

		configAttribures[i++] = EGL_RENDERABLE_TYPE;
		configAttribures[i++] = mRenderableType;

		/*configAttribures[i++]=EGL_BUFFER_SIZE;
		configAttribures[i++]=mColorBufferSize;*/

		if (mNativeRenderable != EGL_DONT_CARE)
		{
			configAttribures[i++] = EGL_NATIVE_RENDERABLE;
			configAttribures[i++] = mNativeRenderable;
		}

		if (GraphicsContext::Instance().NeedDepthBuffer())
		{
			configAttribures[i++] = EGL_DEPTH_SIZE;
			configAttribures[i++] = GraphicsContext::Instance().DepthBufferSize();
		}

		if (GraphicsContext::Instance().NeedStencilBuffer())
		{
			configAttribures[i++] = EGL_STENCIL_SIZE;
			configAttribures[i++] = GraphicsContext::Instance().StencilBufferSize();
		}

		configAttribures[i++] = EGL_SURFACE_TYPE;
		configAttribures[i] = EGL_WINDOW_BIT;
		if (mIsNeedPBuffer)
		{
			configAttribures[i] |= EGL_PBUFFER_BIT;
		}
		if (mIsNeedPixmap)
		{
			configAttribures[i] |= EGL_PIXMAP_BIT;
		}
		i++;

		if (GraphicsContext::Instance().NeedMultipleSampling())
		{
			configAttribures[i++] = EGL_SAMPLE_BUFFERS;
			configAttribures[i++] = 1;

			configAttribures[i++] = EGL_SAMPLES;
			configAttribures[i++] = GraphicsContext::Instance().SampleCount();
		}
		else
		{
			configAttribures[i++] = EGL_SAMPLE_BUFFERS;
			configAttribures[i++] = 0;
		}

	}
	//configAttribures[i++]=EGL_DEPTH_SIZE;
	//configAttribures[i++]=EGL_DONT_CARE;

	configAttribures[i++] = EGL_NONE;
	EGLint configCount;
	EGLint result = eglChooseConfig(mEGLDisplay, configAttribures, &config, 1, &configCount);
	MEDUSA_ASSERT_TRUE(result&&configCount == 1, "");
	return config;
}

bool WinEGLView::IsEGLExtensionSupported(StringRef extension)
{
	StringRef extensions = eglQueryString(mEGLDisplay, EGL_EXTENSIONS);
	return extensions.Contains(extension);
}

void WinEGLView::CreateContext()
{
	EGLint contextAttributes[32];
	uint i = 0;
	switch (mGLESVersion)
	{
	case 2:
		contextAttributes[i++] = EGL_CONTEXT_CLIENT_VERSION;
		contextAttributes[i++] = 2;
		break;
	case 3:
		contextAttributes[i++] = EGL_CONTEXT_CLIENT_VERSION;
		contextAttributes[i++] = 3;
		break;
	case 1:
	default:
		contextAttributes[i++] = EGL_CONTEXT_CLIENT_VERSION;
		contextAttributes[i++] = 1;
		break;
	}

	contextAttributes[i] = EGL_NONE;


	mEGLContext = eglCreateContext(mEGLDisplay, mEGLConfig, nullptr, contextAttributes);
	MEDUSA_ASSERT_NOT_EQUAL(mEGLContext, EGL_NO_CONTEXT, "");
	MEDUSA_ASSERT_FALSE(GetEGLError(), "");
}

void WinEGLView::CreateSurface()
{
	EGLint	surfaceAttributes[16];
	uint i = 0;

	surfaceAttributes[i++] = EGL_NONE;

	if (mIsNeedPixmap)
	{
		mEGLSurface = eglCreatePixmapSurface(mEGLDisplay, mEGLConfig, mBitmapPixmap, surfaceAttributes);
	}
	else
	{
		mEGLSurface = eglCreateWindowSurface(mEGLDisplay, mEGLConfig, mEGLNativeWindow, surfaceAttributes);
		if (mEGLSurface == EGL_NO_SURFACE)
		{
			eglGetError(); // Clear error
			mEGLSurface = eglCreateWindowSurface(mEGLDisplay, mEGLConfig, nullptr, surfaceAttributes);
		}
	}

	MEDUSA_ASSERT_NOT_EQUAL(mEGLSurface, EGL_NO_SURFACE, "");
	MEDUSA_ASSERT_FALSE(GetEGLError(), "");
}

MEDUSA_IMPLEMENT_RTTI(WinEGLView, BaseRenderView);

MEDUSA_END;

#endif
#endif