// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "WinGLView.h"
#include "Application/Window/win/WinWindow.h"
#include "Graphics/ResolutionAdapter.h"
#include "Core/Profile/ProfileSample.h"
#include "Graphics/Render/Render.h"
#include "Core/Log/Log.h"
#include "Core/String/StringParser.h"
#include "Graphics/GraphicsContext.h"
#include "Rendering/RenderEngine.h"

#ifdef MEDUSA_WINDOWS
#ifdef MEDUSA_GLEW
#include "Lib/win/GLEW/glew.h"

MEDUSA_BEGIN;

WinGLView::WinGLView(StringRef name/*=StringRef::Empty*/) :BaseRenderView(name)
{
	mDC = nullptr;
	mRenderContext = nullptr;


}

WinGLView::~WinGLView(void)
{
	
}



bool WinGLView::Initialize()
{
	RETURN_FALSE_IF_FALSE(BaseRenderView::Initialize());

	WinWindow* window = (WinWindow*)mParent;
	mDC = GetDC(window->WindowHandle());
	if (!SetupPixelFormat())
	{
		Log::FormatError("Failed to SetPixelFormat,Error code:{}", GetLastError());

		return false;
	}

	mRenderContext = wglCreateContext(mDC);
	if (mRenderContext == nullptr)
	{
		Log::FormatError("Failed to wglCreateContext,Error:{}", GetLastError());
		return false;
	}

	if (!wglMakeCurrent(mDC, mRenderContext))
	{
		Log::FormatError("Failed to wglMakeCurrent,Error:{}", GetLastError());
		return false;
	}


	if (!SetupGLEW())
	{
		Log::FormatError("Failed to SetupGLEW.");
		return false;
	}

	RenderEngine::Instance().Initialize();
	return true;

}


bool WinGLView::Uninitialize()
{
	RETURN_TRUE_IF_NULL(mDC);
	if (mRenderContext != nullptr)
	{
		wglMakeCurrent(mDC, nullptr);
		wglDeleteContext(mRenderContext);
		mRenderContext = nullptr;
	}
	DeleteObject(mDC);
	mDC = nullptr;
	return true;
}

void WinGLView::SwapBuffers()
{
	::SwapBuffers(mDC);
}

void WinGLView::FinishDraw()
{
	Render::Instance().Finish();
}


void WinGLView::Resize(const Size2F& newSize)
{

}

bool WinGLView::SetupPixelFormat()
{
	int pixelFormat;

	byte depthBufferSize = GraphicsContext::Instance().NeedDepthBuffer() ? GraphicsContext::Instance().DepthBufferSize() : 0;
	byte stencilBufferSize = GraphicsContext::Instance().NeedStencilBuffer() ? GraphicsContext::Instance().StencilBufferSize() : 0;


	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),  // size
		1,                          // version
		PFD_SUPPORT_OPENGL |        // OpenGL window
		PFD_DRAW_TO_WINDOW |        // render to window
		PFD_DOUBLEBUFFER,           // support double-buffering
		PFD_TYPE_RGBA,              // color type
		32,                         // preferred color depth
		0, 0, 0, 0, 0, 0,           // color bits (ignored)
		0,                          // no alpha buffer
		0,                          // alpha bits (ignored)
		0,                          // no accumulation buffer
		0, 0, 0, 0,                 // accum bits (ignored)
		depthBufferSize,                         // depth buffer
		stencilBufferSize,                          // no stencil buffer
		0,                          // no auxiliary buffers
		PFD_MAIN_PLANE,             // main layer
		0,                          // reserved
		0, 0, 0,                    // no layer, visible, damage masks
	};

	pixelFormat = ChoosePixelFormat(mDC, &pfd);
	return SetPixelFormat(mDC, pixelFormat, &pfd) == TRUE;
}

bool WinGLView::SetupGLEW()
{
	GLenum initResult = glewInit();
	if (GLEW_OK != initResult)
	{
		char* str = (char*)glewGetErrorString(initResult);
		Log::FormatError("Failed to glewInit,Error:{}", str);
		return false;
	}

	if (!GLEW_ARB_vertex_shader)
	{
		Log::Error("GLEW_ARB_vertex_shader isn't supported!");
		return false;
	}

	if (!GLEW_ARB_fragment_shader)
	{
		Log::Error("GLEW_ARB_vertex_shader isn't supported!");
		return false;
	}

	
	StringRef extensionStr = (const char*)glGetString(GL_EXTENSIONS);
	if (glGenFramebuffers == nullptr)
	{
		Log::Info("OpenGL: glGenFramebuffers is nullptr, try to detect an extension");
		if (extensionStr.Contains("ARB_framebuffer_object"))
		{
			Log::Info("OpenGL: ARB_framebuffer_object is supported");
			glIsRenderbuffer = (PFNGLISRENDERBUFFERPROC)wglGetProcAddress("glIsRenderbuffer");
			glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC)wglGetProcAddress("glBindRenderbuffer");
			glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC)wglGetProcAddress("glDeleteRenderbuffers");
			glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC)wglGetProcAddress("glGenRenderbuffers");
			glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC)wglGetProcAddress("glRenderbufferStorage");
			glGetRenderbufferParameteriv = (PFNGLGETRENDERBUFFERPARAMETERIVPROC)wglGetProcAddress("glGetRenderbufferParameteriv");
			glIsFramebuffer = (PFNGLISFRAMEBUFFERPROC)wglGetProcAddress("glIsFramebuffer");
			glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC)wglGetProcAddress("glBindFramebuffer");
			glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC)wglGetProcAddress("glDeleteFramebuffers");
			glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC)wglGetProcAddress("glGenFramebuffers");
			glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC)wglGetProcAddress("glCheckFramebufferStatus");
			glFramebufferTexture1D = (PFNGLFRAMEBUFFERTEXTURE1DPROC)wglGetProcAddress("glFramebufferTexture1D");
			glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC)wglGetProcAddress("glFramebufferTexture2D");
			glFramebufferTexture3D = (PFNGLFRAMEBUFFERTEXTURE3DPROC)wglGetProcAddress("glFramebufferTexture3D");
			glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC)wglGetProcAddress("glFramebufferRenderbuffer");
			glGetFramebufferAttachmentParameteriv = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)wglGetProcAddress("glGetFramebufferAttachmentParameteriv");
			glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)wglGetProcAddress("glGenerateMipmap");
		}
		else if (extensionStr.Contains("EXT_framebuffer_object"))
		{
			Log::Info("OpenGL: EXT_framebuffer_object is supported");
			glIsRenderbuffer = (PFNGLISRENDERBUFFERPROC)wglGetProcAddress("glIsRenderbufferEXT");
			glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC)wglGetProcAddress("glBindRenderbufferEXT");
			glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC)wglGetProcAddress("glDeleteRenderbuffersEXT");
			glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC)wglGetProcAddress("glGenRenderbuffersEXT");
			glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC)wglGetProcAddress("glRenderbufferStorageEXT");
			glGetRenderbufferParameteriv = (PFNGLGETRENDERBUFFERPARAMETERIVPROC)wglGetProcAddress("glGetRenderbufferParameterivEXT");
			glIsFramebuffer = (PFNGLISFRAMEBUFFERPROC)wglGetProcAddress("glIsFramebufferEXT");
			glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC)wglGetProcAddress("glBindFramebufferEXT");
			glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC)wglGetProcAddress("glDeleteFramebuffersEXT");
			glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC)wglGetProcAddress("glGenFramebuffersEXT");
			glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC)wglGetProcAddress("glCheckFramebufferStatusEXT");
			glFramebufferTexture1D = (PFNGLFRAMEBUFFERTEXTURE1DPROC)wglGetProcAddress("glFramebufferTexture1DEXT");
			glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC)wglGetProcAddress("glFramebufferTexture2DEXT");
			glFramebufferTexture3D = (PFNGLFRAMEBUFFERTEXTURE3DPROC)wglGetProcAddress("glFramebufferTexture3DEXT");
			glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC)wglGetProcAddress("glFramebufferRenderbufferEXT");
			glGetFramebufferAttachmentParameteriv = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)wglGetProcAddress("glGetFramebufferAttachmentParameterivEXT");
			glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)wglGetProcAddress("glGenerateMipmapEXT");
		}
		else
		{
			Log::Error("No frame buffers extension is supported.Any call to FBO will crash!");
			return false;
		}
	}


	return true;
}


MEDUSA_IMPLEMENT_RTTI(WinGLView, BaseRenderView);

MEDUSA_END;
#endif
#endif
