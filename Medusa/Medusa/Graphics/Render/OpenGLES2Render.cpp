// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"


#include "OpenGLES2Render.h"
#include "Geometry/Rect2.h"
#include "Geometry/Color4.h"
#include "Core/Collection/Array.h"
#include "Geometry/Triangle.h"
#include "Geometry/Point3.h"
#include "Geometry/Point4.h"

#include "Core/Chrono/ProfileSample.h"
#include "Graphics/Render/RenderExtensionNames.h"
#include "Core/Log/Log.h"
#include "Graphics/State/SamplerRenderState.h"


#ifdef MEDUSA_IOS
// the extensions supported on the iPhone are treated as core functions of gl
// so use this macro to assign the function pointers in this class appropriately.
#define PRIVATE_GET_EXTENSION_PROC_ADRESS(x) ::x
#else
#ifdef MEDUSA_GLEW
#define PRIVATE_GET_EXTENSION_PROC_ADRESS(x) wglGetProcAddress(#x)
#elif defined(MEDUSA_GLES)
#define PRIVATE_GET_EXTENSION_PROC_ADRESS(x) eglGetProcAddress(#x)
#else
#error "Not defined GL version"
#endif
#endif


#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
#define RENDER_ASSIGN_IF_SUCCESS(x,y) if(AssertSuccess()){x=y;}
#define RENDER_RETURN_IF_EQUAL(x,y) RETURN_IF_EQUAL(x,y)
#else
#define RENDER_ASSIGN_IF_SUCCESS(x,y) AssertSuccess();
#define RENDER_RETURN_IF_EQUAL(x,y) 
#endif




MEDUSA_BEGIN;

OpenGLES2Render::OpenGLES2Render(void)
{
#ifdef MEUDSA_WINDOWS
#ifdef GL_EXT_multi_draw_arrays
	glMultiDrawArraysEXT = nullptr;
	glMultiDrawElementsEXT = nullptr;
#endif

#ifdef GL_OES_mapbuffer
	glMapBufferOES = nullptr;
	glUnmapBufferOES = nullptr;
	glGetBufferPointervOES = nullptr;
#endif

#ifdef GL_OES_vertex_array_object
	glBindVertexArrayOES = nullptr;
	glDeleteVertexArraysOES = nullptr;
	glGenVertexArraysOES = nullptr;
	glIsVertexArrayOES = nullptr;
#endif

#if defined(GL_EXT_discard_framebuffer)&&GL_EXT_discard_framebuffer==1
	glDiscardFramebufferEXT = nullptr;
#endif

#ifdef GL_IMG_multisampled_render_to_texture
	glRenderbufferStorageMultisampleIMG = nullptr;
	glFramebufferTexture2DMultisampleIMG = nullptr;
#endif
#endif
}


OpenGLES2Render::~OpenGLES2Render(void)
{
}

#pragma region Helpers

bool OpenGLES2Render::Initialize()
{
	RETURN_FALSE_IF_FALSE(IRender::Initialize());
	LoadExtensions();
	return true;
}


void OpenGLES2Render::Finish()
{
	glFinish();
	AssertSuccess();

}

void OpenGLES2Render::Flush()
{
	glFlush();
	AssertSuccess();
}


GraphicsErrorCode OpenGLES2Render::GetError() const
{
	return GraphicsErrorCode(glGetError());
}

void OpenGLES2Render::Clear(GraphicsBufferComponentMask clearMasks)const
{
	int mask = (int)clearMasks;
	glClear(mask);
	AssertSuccess();

}

#pragma endregion Helpers

#pragma region Set Values


void OpenGLES2Render::Hint(GraphicsHintMode mode)
{
	RENDER_RETURN_IF_EQUAL(mGenerateMipmapHint, mode);
	glHint(GL_GENERATE_MIPMAP_HINT, (uint)mode);
	RENDER_ASSIGN_IF_SUCCESS(mGenerateMipmapHint, mode);

}


void OpenGLES2Render::SetViewPort(const Rect2I& rect)
{
	RENDER_RETURN_IF_EQUAL(mViewport, rect);
	glViewport(rect.Origin.X, rect.Origin.Y, rect.Size.Width, rect.Size.Height);
	RENDER_ASSIGN_IF_SUCCESS(mViewport, rect);
}


void OpenGLES2Render::SetScissorBox(const Rect2I& rect)
{
	RENDER_RETURN_IF_EQUAL(mScissorBox, rect);
	glScissor(rect.Origin.X, rect.Origin.Y, rect.Size.Width, rect.Size.Height);
	RENDER_ASSIGN_IF_SUCCESS(mScissorBox, rect);
}

void OpenGLES2Render::SetClearColor(const Color4F& color)
{
	RENDER_RETURN_IF_EQUAL(mClearColor, color);
	glClearColor(color.R, color.G, color.B, color.A);
	RENDER_ASSIGN_IF_SUCCESS(mClearColor, color);
}

void OpenGLES2Render::SetBlendColor(const Color4F& color)
{
	RENDER_RETURN_IF_EQUAL(mBlendColor, color);
	glBlendColor(color.R, color.G, color.B, color.A);
	RENDER_ASSIGN_IF_SUCCESS(mBlendColor, color);
}


void OpenGLES2Render::SetLineWidth(float width)
{
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED

	if (Math::IsEqual(mLineWidth, width))
	{
		return;
	}
#endif

	glLineWidth(width);
	RENDER_ASSIGN_IF_SUCCESS(mLineWidth, width);


}

void OpenGLES2Render::SetBlendFunc(GraphicsBlendSrcFunc srcFactor, GraphicsBlendDestFunc destFactor)
{
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED

	if (mBlendSrcRGBFunc == srcFactor&&mBlendSrcAlphaFunc == srcFactor&&mBlendDestRGBFunc == destFactor&&mBlendDestAlphaFunc == destFactor)
	{
		return;
	}
#endif

	glBlendFunc((uint)srcFactor, (uint)destFactor);
	if (AssertSuccess())
	{
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
		mBlendSrcRGBFunc = mBlendSrcAlphaFunc = srcFactor;
		mBlendDestRGBFunc = mBlendDestAlphaFunc = destFactor;
#endif

	}

}

void OpenGLES2Render::SetBlendFuncSeparate(GraphicsBlendSrcFunc srcRGBFactor, GraphicsBlendSrcFunc srcAlphaFactor, GraphicsBlendDestFunc destRGBFactor, GraphicsBlendDestFunc destAlphaFactor)
{
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED

	if (mBlendSrcRGBFunc == srcRGBFactor&&mBlendSrcAlphaFunc == srcAlphaFactor&&mBlendDestRGBFunc == destRGBFactor&&mBlendDestAlphaFunc == destAlphaFactor)
	{
		return;
	}
#endif

	glBlendFuncSeparate((uint)srcRGBFactor, (uint)destRGBFactor, (uint)srcAlphaFactor, (uint)destAlphaFactor);
	if (AssertSuccess())
	{
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
		mBlendSrcRGBFunc = srcRGBFactor;
		mBlendSrcAlphaFunc = srcAlphaFactor;
		mBlendDestRGBFunc = destRGBFactor;
		mBlendDestAlphaFunc = destAlphaFactor;
#endif
	}
}

void OpenGLES2Render::SetBlendEquation(GraphicsBlendEquation equation)
{
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED

	if (mBlendRGBEquation == equation&&mBlendAlphaEquation == equation)
	{
		return;
	}
#endif


	glBlendEquation((uint)equation);
	if (AssertSuccess())
	{
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED

		mBlendRGBEquation = mBlendAlphaEquation = equation;
#endif

	}
}

void OpenGLES2Render::SetBlendEquationSeparate(GraphicsBlendEquation rgbEquation, GraphicsBlendEquation alphaEquation)
{
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	if (mBlendRGBEquation == rgbEquation&&mBlendAlphaEquation == alphaEquation)
	{
		return;
	}
#endif

	glBlendEquationSeparate((int)rgbEquation, (int)alphaEquation);
	if (AssertSuccess())
	{
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED

		mBlendRGBEquation = rgbEquation;
		mBlendAlphaEquation = alphaEquation;
#endif

	}
}



void OpenGLES2Render::SetPixelStore(GraphicsPixelStoreParameter parameter, int val)
{
	switch (parameter)
	{
	case GraphicsPixelStoreParameter::PackAlignment:
		RENDER_RETURN_IF_EQUAL(mPackAlignment, val);
		glPixelStorei((uint)parameter, val);
		RENDER_ASSIGN_IF_SUCCESS(mPackAlignment, val);

		break;
	case GraphicsPixelStoreParameter::UnpackAlignment:
		RENDER_RETURN_IF_EQUAL(mUnpackAlignment, val);
		glPixelStorei((uint)parameter, val);
		RENDER_ASSIGN_IF_SUCCESS(mUnpackAlignment, val);
		break;
	default:
		Log::AssertFailedFormat("Invalid GraphicsPixelStoreParameter:{}", parameter);
		break;
	}

}


void OpenGLES2Render::SetPolygonOffset(float scaleFactor, float unit)
{
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	if (mPolygonOffsetFactor == scaleFactor&&mPolygonOffsetUnit == unit)
	{
		return;
	}
#endif

	glPolygonOffset(scaleFactor, unit);
	if (AssertSuccess())
	{
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
		mPolygonOffsetFactor = scaleFactor;
		mPolygonOffsetUnit = unit;
#endif
	}

}

void OpenGLES2Render::SetSampleCoverage(float val, bool isInvert)
{
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED

	if (Math::IsEqual(mSampleCoverage, val))
	{
		if (isInvert)
		{
			RETURN_IF_TRUE(mSampleCoverageInvertEnabled);
		}
	}
#endif

	glSampleCoverage(val, isInvert);
	if (AssertSuccess())
	{
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED

		mSampleCoverage = val;
		if (isInvert)
		{
			mSampleCoverageInvertEnabled = true;
		}
		else
		{
			mSampleCoverageInvertEnabled = false;
		}
#endif

	}

}


void OpenGLES2Render::SetStencilFunc(GraphicsFuncType func, int refValue, uint readMask)
{
	/*
	GL_ALWAYS always pass
	GL_NEVER which causes the test to never pass.
	GL_LESS	    Passes if (	ref & mask )  < ( stencil & mask )
	GL_LEQUAL	Passes if (	ref & mask ) <= ( stencil & mask )
	GL_GREATER	Passes if (	ref & mask )  > ( stencil & mask )
	GL_GEQUAL	Passes if (	ref & mask ) >= ( stencil & mask )
	GL_EQUAL	Passes if (	ref & mask )  = ( stencil & mask )
	GL_NOTEQUAL	Passes if (	ref & mask ) != ( stencil & mask )
	*/

#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED

	if (mStencilFunc == func&&mStencilRefValue == refValue&&mStencilValueMask == readMask&&mStencilBackFunc == func&&mStencilBackRefValue == refValue&&mStencilBackValueMask == readMask)
	{
		return;
	}
#endif
	glStencilFunc((uint)func, refValue, readMask);

	if (AssertSuccess())
	{
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED

		mStencilFunc = func;
		mStencilRefValue = refValue;
		mStencilValueMask = readMask;

		mStencilBackFunc = func;
		mStencilBackRefValue = refValue;
		mStencilBackValueMask = readMask;
#endif

	}

}

void OpenGLES2Render::SetStencilFuncSeparate(GraphicsFace face, GraphicsFuncType func, int refValue, uint readMask)
{
	switch (face)
	{
	case GraphicsFace::Front:
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED

		if (mStencilFunc == func&&mStencilRefValue == refValue&&mStencilValueMask == readMask)
		{
			return;
		}
#endif

		glStencilFuncSeparate((uint)face, (uint)func, refValue, readMask);
		if (AssertSuccess())
		{
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED

			mStencilFunc = func;
			mStencilRefValue = refValue;
			mStencilValueMask = readMask;
#endif
		}
		break;
	case GraphicsFace::Back:
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED

		if (mStencilBackFunc == func&&mStencilBackRefValue == refValue&&mStencilBackValueMask == readMask)
		{
			return;
		}
#endif
		glStencilFuncSeparate((uint)face, (uint)func, refValue, readMask);
		if (AssertSuccess())
		{
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED

			mStencilBackFunc = func;
			mStencilBackRefValue = refValue;
			mStencilBackValueMask = readMask;
#endif
		}
		break;
	case GraphicsFace::FrontAndBack:
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED

		if (mStencilFunc == func&&mStencilRefValue == refValue&&mStencilValueMask == readMask&&mStencilBackFunc == func&&mStencilBackRefValue == refValue&&mStencilBackValueMask == readMask)
		{
			return;
		}
#endif
		glStencilFuncSeparate((uint)face, (uint)func, refValue, readMask);
		if (AssertSuccess())
		{
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED

			mStencilFunc = func;
			mStencilRefValue = refValue;
			mStencilValueMask = readMask;

			mStencilBackFunc = func;
			mStencilBackRefValue = refValue;
			mStencilBackValueMask = readMask;
#endif
		}
		break;
	default:
		Log::AssertFailedFormat("Invalid GraphicsFace:{}", (uint)face);
		break;

	}

}

void OpenGLES2Render::SetStencilWriteMask(uint mask)
{
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED

	if (mStencilWriteMask == mask&&mStencilBackWriteMask == mask)
	{
		return;
	}
#endif

	glStencilMask(mask);

	if (AssertSuccess())
	{
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED

		mStencilWriteMask = mask;
		mStencilBackWriteMask = mask;
#endif

	}
}

void OpenGLES2Render::SetStencilWriteMaskSeparate(GraphicsFace face, uint mask)
{
	switch (face)
	{
	case GraphicsFace::Front:
		RENDER_RETURN_IF_EQUAL(mStencilWriteMask, mask);
		glStencilMaskSeparate((uint)face, mask);
		RENDER_ASSIGN_IF_SUCCESS(mStencilWriteMask, mask);
		break;
	case GraphicsFace::Back:
		RENDER_RETURN_IF_EQUAL(mStencilBackWriteMask, mask);
		glStencilMaskSeparate((uint)face, mask);
		RENDER_ASSIGN_IF_SUCCESS(mStencilBackWriteMask, mask);
		break;
	case GraphicsFace::FrontAndBack:
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
		if (mStencilWriteMask == mask&&mStencilBackWriteMask == mask)
		{
			return;
		}
#endif
		glStencilMaskSeparate((uint)face, mask);

		if (AssertSuccess())
		{
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
			mStencilWriteMask = mask;
			mStencilBackWriteMask = mask;
#endif
		}
		break;
	default:
		Log::AssertFailedFormat("Invalid GraphicsFace:{}", (uint)face);
		break;

	}

}


void OpenGLES2Render::SetStencilOperation(GraphicsStencilOperation testFail, GraphicsStencilOperation testPassDepthFail, GraphicsStencilOperation testPassDepthPass)
{
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	if (mStencilFailOperation == testFail&&mStencilPassDepthFailOperation == testPassDepthFail&&mStencilPassDepthPassOperation == testPassDepthPass&&
		mStencilBackFailOperation == testFail&&mStencilBackPassDepthFailOperation == testPassDepthFail&&mStencilBackPassDepthPassOperation == testPassDepthPass)
	{
		return;
	}
#endif

	glStencilOp((uint)testFail, (uint)testPassDepthFail, (uint)testPassDepthPass);

	if (AssertSuccess())
	{
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
		mStencilFailOperation = testFail;
		mStencilPassDepthFailOperation = testPassDepthFail;
		mStencilPassDepthPassOperation = testPassDepthPass;

		mStencilBackFailOperation = testFail;
		mStencilBackPassDepthFailOperation = testPassDepthFail;
		mStencilBackPassDepthPassOperation = testPassDepthPass;
#endif
	}

}

void OpenGLES2Render::SetStencilOperationSeparate(GraphicsFace face, GraphicsStencilOperation testFail, GraphicsStencilOperation testPassDepthFail, GraphicsStencilOperation testPassDepthPass)
{
	switch (face)
	{
	case GraphicsFace::Front:
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
		if (mStencilFailOperation == testFail&&mStencilPassDepthFailOperation == testPassDepthFail&&mStencilPassDepthPassOperation == testPassDepthPass)
		{
			return;
		}
#endif
		glStencilOpSeparate((uint)face, (uint)testFail, (uint)testPassDepthFail, (uint)testPassDepthPass);

		if (AssertSuccess())
		{
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
			mStencilFailOperation = testFail;
			mStencilPassDepthFailOperation = testPassDepthFail;
			mStencilPassDepthPassOperation = testPassDepthPass;
#endif
		}
		break;
	case GraphicsFace::Back:
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
		if (mStencilBackFailOperation == testFail&&mStencilBackPassDepthFailOperation == testPassDepthFail&&mStencilBackPassDepthPassOperation == testPassDepthPass)
		{
			return;
		}
#endif
		glStencilOpSeparate((uint)face, (uint)testFail, (uint)testPassDepthFail, (uint)testPassDepthPass);

		if (AssertSuccess())
		{
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
			mStencilBackFailOperation = testFail;
			mStencilBackPassDepthFailOperation = testPassDepthFail;
			mStencilBackPassDepthPassOperation = testPassDepthPass;
#endif
		}
		break;
	case GraphicsFace::FrontAndBack:
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
		if (mStencilFailOperation == testFail&&mStencilPassDepthFailOperation == testPassDepthFail&&mStencilPassDepthPassOperation == testPassDepthPass&&
			mStencilBackFailOperation == testFail&&mStencilBackPassDepthFailOperation == testPassDepthFail&&mStencilBackPassDepthPassOperation == testPassDepthPass)
		{
			return;
		}
#endif
		glStencilOpSeparate((uint)face, (uint)testFail, (uint)testPassDepthFail, (uint)testPassDepthPass);

		if (AssertSuccess())
		{
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
			mStencilFailOperation = testFail;
			mStencilPassDepthFailOperation = testPassDepthFail;
			mStencilPassDepthPassOperation = testPassDepthPass;

			mStencilBackFailOperation = testFail;
			mStencilBackPassDepthFailOperation = testPassDepthFail;
			mStencilBackPassDepthPassOperation = testPassDepthPass;
#endif
		}
		break;
	default:
		Log::AssertFailedFormat("Invalid GraphicsFace:{}", (uint)face);
		break;

	}

}

void OpenGLES2Render::SetFrontFace(GraphicsFrontFace frontFace)
{
	RENDER_RETURN_IF_EQUAL(mFrontFace, frontFace);
	glFrontFace((uint)frontFace);
	RENDER_ASSIGN_IF_SUCCESS(mFrontFace, frontFace);
}

void OpenGLES2Render::SetDepthFunc(GraphicsFuncType func)
{
	RENDER_RETURN_IF_EQUAL(mDepthFunc, func);
	glDepthFunc((uint)func);
	RENDER_ASSIGN_IF_SUCCESS(mDepthFunc, func);

}

void OpenGLES2Render::SetDepthRange(const RangeF& depthRange)
{
	//default is 0-1
	RENDER_RETURN_IF_EQUAL(mDepthRange, depthRange);
	glDepthRangef(depthRange.Min, depthRange.Max);
	RENDER_ASSIGN_IF_SUCCESS(mDepthRange, depthRange);
}


void OpenGLES2Render::SetClearDepth(float depth)
{
	RENDER_RETURN_IF_EQUAL(mDepthClearValue, depth);

#ifdef MEDUSA_GLEW
	glClearDepth(depth);
#else
	glClearDepthf(depth);
#endif
	RENDER_ASSIGN_IF_SUCCESS(mDepthClearValue, depth);
}


void OpenGLES2Render::SetStencilClearValue(int val)
{
	RENDER_RETURN_IF_EQUAL(mStencilClearValue, val);
	glClearStencil(val);
	RENDER_ASSIGN_IF_SUCCESS(mStencilClearValue, val);

}


void OpenGLES2Render::SetColorMask(GraphicsColorMask colorMask)
{
	RENDER_RETURN_IF_EQUAL(mColorWriteMask, colorMask);
	glColorMask(MEDUSA_FLAG_HAS(colorMask,GraphicsColorMask::R), MEDUSA_FLAG_HAS(colorMask, GraphicsColorMask::G), MEDUSA_FLAG_HAS(colorMask, GraphicsColorMask::B), MEDUSA_FLAG_HAS(colorMask, GraphicsColorMask::A));
	RENDER_ASSIGN_IF_SUCCESS(mColorWriteMask, colorMask);
}

bool OpenGLES2Render::TryGetInteger(GraphicsIntegerName name, int& outVal) const
{
	outVal = 0;
	glGetIntegerv((uint)name, &outVal);
	return IsSuccess();
}

bool OpenGLES2Render::TryGetIntegerArray(GraphicsIntegerArrayName name, int* params) const
{
	glGetIntegerv((uint)name, params);
	return IsSuccess();
}


bool OpenGLES2Render::TryGetBoolean(GraphicsBooleanName name, bool& outVal) const
{
	outVal = false;
	glGetBooleanv((uint)name, (GLboolean*)&outVal);
	return IsSuccess();

}

bool OpenGLES2Render::TryGetBooleanArray(GraphicsBooleanArrayName name, bool* params) const
{
	glGetBooleanv((uint)name, (GLboolean*)params);
	return IsSuccess();
}

bool OpenGLES2Render::TryGetFloat(GraphicsFloatName name, float& outVal) const
{
	outVal = 0.f;
	glGetFloatv((uint)name, &outVal);
	return IsSuccess();
}


bool OpenGLES2Render::TryGetFloatArray(GraphicsFloatArrayName name, float* params) const
{
	glGetFloatv((uint)name, params);
	return IsSuccess();
}

bool OpenGLES2Render::TryGetString(GraphicsStringName name, StringRef& outVal) const
{
	const byte* str = glGetString((uint)name);
	outVal.ForceSetBuffer((const char*)str);
	outVal.ForceUpdateLength();

	return IsSuccess();
}

#pragma endregion Set Values

#pragma region Enable/Disable


void OpenGLES2Render::EnableDepthWrite(bool isEnable)
{
	RENDER_RETURN_IF_EQUAL(mDepthWritableEnabled, isEnable);
	glDepthMask(isEnable);
	RENDER_ASSIGN_IF_SUCCESS(mDepthWritableEnabled, isEnable);
}

void OpenGLES2Render::CullFace(GraphicsFace face)
{
	RENDER_RETURN_IF_EQUAL(mCullFaceMode, face);
	glCullFace((int)face);
	RENDER_ASSIGN_IF_SUCCESS(mCullFaceMode, face);
}


void OpenGLES2Render::EnableFeature(GraphicsFeatures feature, bool isEnable)
{
	switch (feature)
	{
	case GraphicsFeatures::Blend:
		RENDER_RETURN_IF_EQUAL(mBlendEnabled, isEnable);
		isEnable ? glEnable((uint)feature) : glDisable((uint)feature);
		RENDER_ASSIGN_IF_SUCCESS(mBlendEnabled, isEnable);
		break;
	case GraphicsFeatures::CullFace:
		RENDER_RETURN_IF_EQUAL(mCullFaceEnabled, isEnable);
		isEnable ? glEnable((uint)feature) : glDisable((uint)feature);
		RENDER_ASSIGN_IF_SUCCESS(mCullFaceEnabled, isEnable);
		break;
	case GraphicsFeatures::DepthTest:
		RENDER_RETURN_IF_EQUAL(mDepthTestEnabled, isEnable);
		isEnable ? glEnable((uint)feature) : glDisable((uint)feature);
		RENDER_ASSIGN_IF_SUCCESS(mDepthTestEnabled, isEnable);
		break;
	case GraphicsFeatures::ScissorTest:
		RENDER_RETURN_IF_EQUAL(mScissorTestEnabled, isEnable);
		isEnable ? glEnable((uint)feature) : glDisable((uint)feature);
		RENDER_ASSIGN_IF_SUCCESS(mScissorTestEnabled, isEnable);
		break;
	case GraphicsFeatures::StencilTest:
		RENDER_RETURN_IF_EQUAL(mStencilTestEnabled, isEnable);
		isEnable ? glEnable((uint)feature) : glDisable((uint)feature);
		RENDER_ASSIGN_IF_SUCCESS(mStencilTestEnabled, isEnable);
		break;
	case GraphicsFeatures::DepthWritable:
		RENDER_RETURN_IF_EQUAL(mDepthWritableEnabled, isEnable);
		isEnable ? glEnable((uint)feature) : glDisable((uint)feature);
		RENDER_ASSIGN_IF_SUCCESS(mDepthWritableEnabled, isEnable);
		break;
	case GraphicsFeatures::Dither:
		RENDER_RETURN_IF_EQUAL(mDitherEnabled, isEnable);
		isEnable ? glEnable((uint)feature) : glDisable((uint)feature);
		RENDER_ASSIGN_IF_SUCCESS(mDitherEnabled, isEnable);
		break;
	case GraphicsFeatures::PolygonOffsetFill:
		RENDER_RETURN_IF_EQUAL(mPolygonOffsetFillEnabled, isEnable);
		isEnable ? glEnable((uint)feature) : glDisable((uint)feature);
		RENDER_ASSIGN_IF_SUCCESS(mPolygonOffsetFillEnabled, isEnable);
		break;
	case GraphicsFeatures::SampleAlphaToCoverage:
		RENDER_RETURN_IF_EQUAL(mSampleAlphaToCoverageEnabled, isEnable);
		isEnable ? glEnable((uint)feature) : glDisable((uint)feature);
		RENDER_ASSIGN_IF_SUCCESS(mSampleAlphaToCoverageEnabled, isEnable);
		break;
	case GraphicsFeatures::SampleCoverage:
		RENDER_RETURN_IF_EQUAL(mSampleCoverageEnabled, isEnable);
		isEnable ? glEnable((uint)feature) : glDisable((uint)feature);
		RENDER_ASSIGN_IF_SUCCESS(mSampleCoverageEnabled, isEnable);
		break;
	default:
		Log::AssertFailedFormat("Invalid GraphicsFeatures:{}", feature);
		break;
	}

}
bool OpenGLES2Render::IsFeatureEnabled(GraphicsFeatures feature)
{
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	switch (feature)
	{
	case GraphicsFeatures::Blend:
		return mBlendEnabled;
	case GraphicsFeatures::CullFace:
		return mCullFaceEnabled;
	case GraphicsFeatures::DepthTest:
		return mDepthTestEnabled;
	case GraphicsFeatures::ScissorTest:
		return mScissorTestEnabled;
	case GraphicsFeatures::StencilTest:
		return mStencilTestEnabled;
	case GraphicsFeatures::DepthWritable:
		return mDepthWritableEnabled;
	case GraphicsFeatures::Dither:
		return mDitherEnabled;
	case GraphicsFeatures::PolygonOffsetFill:
		return mPolygonOffsetFillEnabled;
	case GraphicsFeatures::SampleAlphaToCoverage:
		return mSampleAlphaToCoverageEnabled;
	case GraphicsFeatures::SampleCoverage:
		return mSampleCoverageEnabled;
	default:
		Log::AssertFailedFormat("Invalid GraphicsFeatures:{}", feature);
		break;
	}

	return false;
#else
	return glIsEnabled((uint)feature) == GL_TRUE;
#endif
}

bool OpenGLES2Render::IsShaderBinaryFormatSupported(GraphicsShaderBinaryFormat binaryFormat) const
{
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	return mShaderBinaryFormats.Contains(binaryFormat);
#else
	List<GraphicsShaderBinaryFormat> shaderBinaryFormats;
	int shaderBinaryFormatCount = GetInteger(GraphicsIntegerName::ShaderBinaryFormatCount);
	shaderBinaryFormats.ReserveSize(shaderBinaryFormatCount);
	TryGetIntegerArray(GraphicsIntegerArrayName::ShaderBinaryFormats, (int*)shaderBinaryFormats.Items());
	shaderBinaryFormats.ForceSetCount(shaderBinaryFormatCount);
	return shaderBinaryFormats.Contains(binaryFormat);
#endif

}


#pragma endregion Enable/Disable




#pragma region Drawing 

void OpenGLES2Render::DrawArrays(GraphicsDrawMode mode, int first, uint count) const
{
	glDrawArrays((int)mode, first, count);
	AssertSuccess();
}

void OpenGLES2Render::DrawIndices(GraphicsDrawMode mode, uint count, GraphicsDataType type, const void* indices) const
{
	glDrawElements((int)mode, count, (int)type, indices);
	AssertSuccess();
}

void OpenGLES2Render::DrawIndices(GraphicsDrawMode mode, const ICollection<ushort>& indices) const
{
	if (indices.IsLinear())
	{
		DrawIndices(mode, static_cast<uint>(indices.Count()), GraphicsDataType::UShort, indices.Items());
	}
	else
	{
		List<ushort> temp = indices;
		DrawIndices(mode, static_cast<uint>(temp.Count()), GraphicsDataType::UShort, temp.Items());
	}
}

void OpenGLES2Render::DrawIndices(GraphicsDrawMode mode, const ICollection<byte>& indices) const
{
	if (indices.IsLinear())
	{
		DrawIndices(mode, static_cast<uint>(indices.Count()), GraphicsDataType::Byte, indices.Items());
	}
	else
	{
		List<byte> temp = indices;
		DrawIndices(mode, static_cast<uint>(temp.Count()), GraphicsDataType::Byte, temp.Items());
	}
}

void OpenGLES2Render::DrawIndices(GraphicsDrawMode mode, const ICollection<uint>& indices) const
{
	if (indices.IsLinear())
	{
		DrawIndices(mode, static_cast<uint>(indices.Count()), GraphicsDataType::UShort, indices.Items());
	}
	else
	{
		List<uint> temp = indices;
		DrawIndices(mode, static_cast<uint>(temp.Count()), GraphicsDataType::UShort, temp.Items());
	}
}


void OpenGLES2Render::DrawPoints(uint pointCount/*=1*/) const
{
	DrawArrays(GraphicsDrawMode::Points, 0, pointCount);
}


void OpenGLES2Render::DrawLines(uint pointCount, const ICollection<ushort>* indices/*=nullptr*/) const
{
	RETURN_IF(pointCount < 2);

	if (indices != nullptr)
	{
		RETURN_IF(indices->Count() < 2);
		MEDUSA_ASSERT(indices->Count() % 2 == 0, "");

		DrawIndices(GraphicsDrawMode::Lines, *indices);

	}
	else
	{
		MEDUSA_ASSERT(pointCount % 2 == 0, "");
		DrawArrays(GraphicsDrawMode::Lines, 0, pointCount);
	}
}

void OpenGLES2Render::DrawLinesStrip(uint pointCount, const ICollection<ushort>* indices/*=nullptr*/) const
{
	RETURN_IF(pointCount < 2);

	if (indices != nullptr)
	{
		RETURN_IF(indices->Count() < 2);

		DrawIndices(GraphicsDrawMode::LineStrip, *indices);
	}
	else
	{
		DrawArrays(GraphicsDrawMode::LineStrip, 0, pointCount);
	}
}


void OpenGLES2Render::DrawLinesLoop(uint pointCount, const ICollection<ushort>* indices) const
{
	RETURN_IF(pointCount < 2);

	if (indices != nullptr)
	{
		RETURN_IF(indices->Count() < 2);
		DrawIndices(GraphicsDrawMode::LineLoop, *indices);
	}
	else
	{
		DrawArrays(GraphicsDrawMode::LineLoop, 0, pointCount);
	}

}

void OpenGLES2Render::DrawTriangles(uint pointCount, const ICollection<ushort>* indices) const
{
	if (indices != nullptr)
	{
		DrawIndices(GraphicsDrawMode::Triangles, *indices);
	}
	else
	{
		DrawArrays(GraphicsDrawMode::Triangles, 0, pointCount);
	}

}

void OpenGLES2Render::DrawTriangleStrip(uint pointCount, const ICollection<ushort>* indices) const
{
	if (indices != nullptr)
	{
		DrawIndices(GraphicsDrawMode::TriangleStrip, *indices);
	}
	else
	{
		DrawArrays(GraphicsDrawMode::TriangleStrip, 0, pointCount);
	}
}


void OpenGLES2Render::DrawTrianglesFan(uint pointCount, const ICollection<ushort>* indices) const
{
	MEDUSA_PROFILE("DrawTrianglesFan");
	if (indices != nullptr)
	{
		DrawIndices(GraphicsDrawMode::TriangleFan, *indices);
	}
	else
	{
		DrawArrays(GraphicsDrawMode::TriangleFan, 0, pointCount);
	}

}


#pragma endregion Drawing Primitives

#pragma region Texture Objects


void OpenGLES2Render::GenTextures(uint count, uint* outBuffers)
{
	glGenTextures(count, outBuffers);
	if (AssertSuccess())
	{
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
		FOR_EACH_SIZE(i, count)
		{
			uint texture = outBuffers[i];
			Share<SamplerRenderState> state = new SamplerRenderState(mDefaultTextureMinFilter, mDefaultTextureMagFilter, mDefaultTextureWrapS, mDefaultTextureWrapT);
			state->SetTexture(texture);
			mSamplerRenderStateDict.Add(texture, state);
		}
#endif
	}
}


void OpenGLES2Render::DeleteTextures(uint count, uint* textures)
{
	glDeleteTextures(count, textures);
	if (AssertSuccess())
	{
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
		int activeTexture = (int)mActiveTexture - (int)GraphicsTextureUnits::Texture0;
		int binding = 0;
		TryGetInteger(GraphicsIntegerName::TextureBinding, binding);
		mTextureBindings[activeTexture] = binding;

		TryGetInteger(GraphicsIntegerName::CubeMapTextureBinding, binding);
		mCubeMapTextureBindings[activeTexture] = binding;

		FOR_EACH_SIZE(i, count)
		{
			uint texture = textures[i];
			mSamplerRenderStateDict.RemoveKey(texture);
			
		}
#endif
	}

}

void OpenGLES2Render::BindTexture(GraphicsTextureType textureType, uint texture)
{
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	int activeTexture = (int)mActiveTexture - (int)GraphicsTextureUnits::Texture0;
#endif
	switch (textureType)
	{
	case GraphicsTextureType::Texture2D:
		RENDER_RETURN_IF_EQUAL(mTextureBindings[activeTexture], texture);
		glBindTexture((int)textureType, texture);
		RENDER_ASSIGN_IF_SUCCESS(mTextureBindings[activeTexture], texture);
		break;
	case GraphicsTextureType::TextureCubeMap:
		RENDER_RETURN_IF_EQUAL(mCubeMapTextureBindings[activeTexture], texture);
		glBindTexture((int)textureType, texture);
		RENDER_ASSIGN_IF_SUCCESS(mCubeMapTextureBindings[activeTexture], texture);
		break;
	default:
		Log::AssertFailedFormat("Invalid GraphicsTextureType:{}", textureType);
		break;
	}
}


void OpenGLES2Render::ActivateTexture(GraphicsTextureUnits textureUnit)
{
	RENDER_RETURN_IF_EQUAL(mActiveTexture, textureUnit);
	glActiveTexture((uint)textureUnit);
	RENDER_ASSIGN_IF_SUCCESS(mActiveTexture, textureUnit);
}

void OpenGLES2Render::GenerateTextureMipmap(GraphicsTextureType textureType) const
{
	glGenerateMipmap((uint)textureType);
	AssertSuccess();
}

bool OpenGLES2Render::IsTexture(uint texture) const
{
	bool result = glIsTexture(texture) == GL_TRUE;
	AssertSuccess();

	return result;
}

void OpenGLES2Render::LoadTexture(GraphicsTextureTarget textureTarget, int level, PixelType pixelType, const Size2U& size, int border,  const void *pixels) const
{
	glTexImage2D((uint)textureTarget, level, (uint)pixelType.InternalFormat(), size.Width, size.Height, border, (uint)pixelType.Format(), (uint)pixelType.DataType(), pixels);
	AssertSuccess();
}

void OpenGLES2Render::LoadSubTexture(GraphicsTextureTarget textureTarget, int level, const Rect2I& rect, PixelType pixelType, const void *pixels) const
{
	glTexSubImage2D((uint)textureTarget, level, rect.Origin.X, rect.Origin.Y, rect.Size.Width, rect.Size.Height, (uint)pixelType.Format(), (uint)pixelType.DataType(), pixels);
	AssertSuccess();
}


void OpenGLES2Render::LoadCompressedTexture(GraphicsTextureTarget textureTarget, int level, PixelType pixelType, const Size2U& size, int border, uint imageSize, const void *pixels) const
{
	glCompressedTexImage2D((uint)textureTarget, level, (uint)pixelType.InternalFormat(), size.Width, size.Width, border, imageSize, pixels);
	AssertSuccess();
}

void OpenGLES2Render::LoadCompressedSubTexture(GraphicsTextureTarget textureTarget, int level, PixelType pixelType, const Rect2I& rect, uint imageSize, const void *pixels) const
{
	glCompressedTexSubImage2D((uint)textureTarget, level, rect.Origin.X, rect.Origin.Y, rect.Size.Width, rect.Size.Height, (uint)pixelType.InternalFormat(), imageSize, pixels);
	AssertSuccess();
}


void OpenGLES2Render::CopyTexture(GraphicsTextureTarget textureTarget, int level, PixelType pixelType, const Rect2I& rect, int border) const
{
	glCopyTexImage2D((uint)textureTarget, level, (uint)pixelType.InternalFormat(), rect.Origin.X, rect.Origin.Y, rect.Size.Width, rect.Size.Height, border);
	AssertSuccess();
}

void OpenGLES2Render::CopySubTexture(GraphicsTextureTarget textureTarget, int level, const Point2I& offset, const Rect2I& rect) const
{
	glCopyTexSubImage2D((uint)textureTarget, level, offset.X, offset.Y, rect.Origin.X, rect.Origin.Y, rect.Size.Width, rect.Size.Height);
	AssertSuccess();

}

void OpenGLES2Render::SetTextureMinFilter(GraphicsTextureType textureType, GraphicsTextureMinFilter minFilter)
{
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	int texture = 0;
	switch (textureType)
	{
	case GraphicsTextureType::Texture2D:
		texture = mTextureBindings[(int)mActiveTexture - (int)GraphicsTextureUnits::Texture0];
		break;
	case GraphicsTextureType::TextureCubeMap:
		texture = mCubeMapTextureBindings[(int)mActiveTexture - (int)GraphicsTextureUnits::Texture0];
		break;
	default:
		Log::AssertFailedFormat("Invalid GraphicsTextureType:{}", textureType);
		return;
	}

	auto state = mSamplerRenderStateDict.Get(texture);
	RENDER_RETURN_IF_EQUAL(state->MinFilter(), minFilter);
#endif
	glTexParameteri((uint)textureType, (int)GraphicsTextureParameter::MinFilter, (uint)minFilter);
	if (AssertSuccess())
	{
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
		state->SetMinFilter(minFilter);
#endif
	}

}

void OpenGLES2Render::SetTextureMagFilter(GraphicsTextureType textureType, GraphicsTextureMagFilter magFilter)
{
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	int texture = 0;
	switch (textureType)
	{
	case GraphicsTextureType::Texture2D:
		texture = mTextureBindings[(int)mActiveTexture - (int)GraphicsTextureUnits::Texture0];
		break;
	case GraphicsTextureType::TextureCubeMap:
		texture = mCubeMapTextureBindings[(int)mActiveTexture - (int)GraphicsTextureUnits::Texture0];
		break;
	default:
		Log::AssertFailedFormat("Invalid GraphicsTextureType:{}", textureType);
		return;
	}

	auto state = mSamplerRenderStateDict.Get(texture);
	RENDER_RETURN_IF_EQUAL(state->MagFilter(), magFilter);
#endif
	glTexParameteri((uint)textureType, (uint)GraphicsTextureParameter::MagFilter, (uint)magFilter);
	if (AssertSuccess())
	{
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
		state->SetMagFilter(magFilter);
#endif
	}
}

void OpenGLES2Render::SetTextureWrapS(GraphicsTextureType textureType, GraphicsTextureWrapMode wrapS)
{
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	int texture = 0;
	switch (textureType)
	{
	case GraphicsTextureType::Texture2D:
		texture = mTextureBindings[(int)mActiveTexture - (int)GraphicsTextureUnits::Texture0];
		break;
	case GraphicsTextureType::TextureCubeMap:
		texture = mCubeMapTextureBindings[(int)mActiveTexture - (int)GraphicsTextureUnits::Texture0];
		break;
	default:
		Log::AssertFailedFormat("Invalid GraphicsTextureType:{}", textureType);
		return;
	}

	auto state = mSamplerRenderStateDict.Get(texture);
	RENDER_RETURN_IF_EQUAL(state->WrapS(), wrapS);
#endif
	glTexParameteri((uint)textureType, (uint)GraphicsTextureParameter::WrapS, (uint)wrapS);
	if (AssertSuccess())
	{
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
		state->SetWrapS(wrapS);
#endif
	}

}

void OpenGLES2Render::SetTextureWrapT(GraphicsTextureType textureType, GraphicsTextureWrapMode wrapT)
{
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	int texture = 0;
	switch (textureType)
	{
	case GraphicsTextureType::Texture2D:
		texture = mTextureBindings[(int)mActiveTexture - (int)GraphicsTextureUnits::Texture0];
		break;
	case GraphicsTextureType::TextureCubeMap:
		texture = mCubeMapTextureBindings[(int)mActiveTexture - (int)GraphicsTextureUnits::Texture0];
		break;
	default:
		Log::AssertFailedFormat("Invalid GraphicsTextureType:{}", textureType);
		return;
	}

	auto state = mSamplerRenderStateDict.Get(texture);
	RENDER_RETURN_IF_EQUAL(state->WrapT(), wrapT);
#endif
	glTexParameteri((uint)textureType, (uint)GraphicsTextureParameter::WrapT, (uint)wrapT);
	if (AssertSuccess())
	{
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
		state->SetWrapT(wrapT);
#endif
	}
}


int OpenGLES2Render::GetTextureParamter(GraphicsTextureType textureType, GraphicsTextureParameter parameter)
{
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	int texture = 0;
	switch (textureType)
	{
	case GraphicsTextureType::Texture2D:
		texture = mTextureBindings[(int)mActiveTexture - (int)GraphicsTextureUnits::Texture0];
		break;
	case GraphicsTextureType::TextureCubeMap:
		texture = mCubeMapTextureBindings[(int)mActiveTexture - (int)GraphicsTextureUnits::Texture0];
		break;
	default:
		Log::AssertFailedFormat("Invalid GraphicsTextureType:{}", textureType);
		return 0;
	}

	auto state = mSamplerRenderStateDict.Get(texture);
	switch (parameter)
	{
	case GraphicsTextureParameter::MinFilter:return (int)state->MinFilter();
	case GraphicsTextureParameter::MagFilter:return (int)state->MagFilter();
	case GraphicsTextureParameter::WrapS:return (int)state->WrapS();
	case GraphicsTextureParameter::WrapT:return (int)state->WrapT();
	default:
		Log::AssertFailedFormat("Invalid GraphicsTextureParameter:{}", parameter);
		break;
	}

	return 0;
#else
	int outVal;
	TryGetTextureParamter(textureType, parameter, outVal);
	return outVal;
#endif

}


bool OpenGLES2Render::TryGetTextureParamter(GraphicsTextureType textureType, GraphicsTextureParameter parameter, int& outVal)
{
	glGetTexParameteriv((uint)textureType, (uint)parameter, &outVal);
	return AssertSuccess();
}

#pragma endregion Texture Objects

#pragma region Buffer Objects

bool OpenGLES2Render::IsBuffer(uint bufferObject) const
{
	bool result = glIsBuffer(bufferObject) == GL_TRUE;
	AssertSuccess();
	return result;
}
bool OpenGLES2Render::IsFrameBuffer(uint bufferObject) const
{
	bool result = glIsFramebuffer(bufferObject) == GL_TRUE;
	AssertSuccess();
	return result;
}

bool OpenGLES2Render::IsRenderBuffer(uint bufferObject) const
{
	bool result = glIsRenderbuffer(bufferObject) == GL_TRUE;
	AssertSuccess();
	return result;
}


void OpenGLES2Render::GenBuffers(uint count, uint* outBuffers) const
{
	glGenBuffers(count, outBuffers);
	AssertSuccess();
}


void OpenGLES2Render::DeleteBuffers(uint count, uint* buffers) const
{
	glDeleteBuffers(count, buffers);
	AssertSuccess();

}


void OpenGLES2Render::GenFrameBuffers(uint count, uint* outBuffers) const
{
	glGenFramebuffers(count, outBuffers);
	AssertSuccess();
}


void OpenGLES2Render::GenRenderBuffers(uint count, uint* outBuffers) const
{
	glGenRenderbuffers(count, outBuffers);
	AssertSuccess();
}

void OpenGLES2Render::DeleteFrameBuffers(uint count, uint* buffers)
{
	glDeleteFramebuffers(count, buffers);
	AssertSuccess();
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	TryGetInteger(GraphicsIntegerName::FrameBufferBinding, (int&)mFrameBufferBinding);
#endif

}


void OpenGLES2Render::DeleteRenderBuffers(uint count, uint* buffers)
{
	glDeleteRenderbuffers(count, buffers);
	AssertSuccess();
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	TryGetInteger(GraphicsIntegerName::RenderBufferBinding, (int&)mRenderBufferBinding);
#endif
}


void OpenGLES2Render::BindBuffer(GraphicsBufferType bufferType, uint bufferObject)
{
	switch (bufferType)
	{
	case GraphicsBufferType::Array:
		RENDER_RETURN_IF_EQUAL(mArrayBufferBinding, bufferObject);
		glBindBuffer((uint)bufferType, bufferObject);
		RENDER_ASSIGN_IF_SUCCESS(mArrayBufferBinding, bufferObject);
		break;
	case GraphicsBufferType::Elements:
		RENDER_RETURN_IF_EQUAL(mElementArrayBufferBinding, bufferObject);
		glBindBuffer((uint)bufferType, bufferObject);
		RENDER_ASSIGN_IF_SUCCESS(mElementArrayBufferBinding, bufferObject);
		break;
	default:
		Log::AssertFailedFormat("Invalid GraphicsBufferType:{}", bufferType);
		break;
	}
}


void OpenGLES2Render::LoadBufferData(GraphicsBufferType bufferType, uint byteSize, void* data, GraphicsBufferUsage usageType) const
{
#ifdef MEDUSA_SAFE_CHECK
	if (byteSize==0)
	{
		Log::AssertFailed("LoadBufferData apply 0 data");
	}
#endif
	glBufferData((uint)bufferType, byteSize, data, (uint)usageType);
	AssertSuccess();

}


void OpenGLES2Render::ModifyBufferSubData(GraphicsBufferType bufferType, int byteOffset, uint byteSize, const void* data) const
{
#ifdef MEDUSA_SAFE_CHECK
	if (byteSize == 0)
	{
		Log::AssertFailed("ModifyBufferSubData apply 0 data");
	}
#endif

	glBufferSubData((uint)bufferType, byteOffset, byteSize, data);
	AssertSuccess();

}


void OpenGLES2Render::BindFrameBuffer(uint frameBufferObject)
{
	RENDER_RETURN_IF_EQUAL(mFrameBufferBinding, frameBufferObject);
	glBindFramebuffer((uint)GraphicsFrameBufferType::FrameBuffer, frameBufferObject);
	RENDER_ASSIGN_IF_SUCCESS(mFrameBufferBinding, frameBufferObject);
}


void OpenGLES2Render::BindRenderBuffer(uint frameBufferObject)
{
	RENDER_RETURN_IF_EQUAL(mRenderBufferBinding, frameBufferObject);
	glBindRenderbuffer((uint)GraphicsFrameBufferType::RenderBuffer, frameBufferObject);
	RENDER_ASSIGN_IF_SUCCESS(mRenderBufferBinding, frameBufferObject);

}


void OpenGLES2Render::AttachRenderBufferToFrameBuffer(GraphicsAttachment attachment, uint renderBufferObject) const
{
	glFramebufferRenderbuffer((uint)GraphicsFrameBufferType::FrameBuffer, (uint)attachment, (uint)GraphicsFrameBufferType::RenderBuffer, renderBufferObject);
	AssertSuccess();

}

void OpenGLES2Render::AttachTextureToFrameBuffer(GraphicsAttachment attachment, GraphicsTextureTarget textureTarget, uint texture, int level) const
{
	glFramebufferTexture2D((uint)GraphicsFrameBufferType::FrameBuffer, (uint)attachment, (uint)textureTarget, texture, level);
	AssertSuccess();
}


int OpenGLES2Render::GetBufferParameter(GraphicsBufferType bufferType, GraphicsBufferParameter parameter) const
{
	int outVal;
	glGetBufferParameteriv((uint)bufferType, (uint)parameter, &outVal);
	AssertSuccess();
	return outVal;
}

int OpenGLES2Render::GetFrameBufferAttachmentParameter(GraphicsAttachment attachment, GraphicsFrameBufferAttachmentParameter parameter) const
{
	int outVal;
	glGetFramebufferAttachmentParameteriv((uint)GraphicsFrameBufferType::FrameBuffer, (uint)attachment, (uint)parameter, &outVal);
	AssertSuccess();
	return outVal;
}


int OpenGLES2Render::GetRenderBufferParameter(GraphicsRenderBufferParameter parameter) const
{
	int outVal;
	glGetRenderbufferParameteriv((uint)GraphicsFrameBufferType::RenderBuffer, (uint)parameter, &outVal);
	AssertSuccess();
	return outVal;
}

void OpenGLES2Render::ReadPixels(GraphicsPixelFormat format, GraphicsPixelDataType dataType, const Rect2I& rect, void* outData)
{
	glReadPixels(rect.Origin.X, rect.Origin.Y, rect.Size.Width, rect.Size.Height, (uint)format, (uint)dataType, outData);
	AssertSuccess();
}


void OpenGLES2Render::SetRenderBufferStorage(GraphicsRenderBufferInternalFormat format, const Size2U& size)
{
	glRenderbufferStorage((uint)GraphicsFrameBufferType::RenderBuffer, (uint)format, size.Width, size.Height);
	AssertSuccess();

}

GraphicsFrameBufferStatus OpenGLES2Render::CheckFrameBufferStatus() const
{
	GraphicsFrameBufferStatus status = (GraphicsFrameBufferStatus)glCheckFramebufferStatus((uint)GraphicsFrameBufferType::FrameBuffer);
	AssertSuccess();

	return status;
}


#pragma endregion Buffer Objects

#pragma region Shader
uint OpenGLES2Render::CreateShader(GraphicsShaderType type)
{
	return glCreateShader((uint)type);
}

void OpenGLES2Render::DeleteShader(uint shader)
{
	glDeleteShader(shader);
	AssertSuccess();
}

void OpenGLES2Render::SetShaderSource(uint shader, StringRef source)
{
	const char* buffer = source.Buffer();
	glShaderSource(shader, 1, &buffer, nullptr);
	AssertSuccess();
}


void OpenGLES2Render::GetShaderSource(uint shader, HeapString& outSource)
{
	int outLength;
	glGetShaderSource(shader, static_cast<uint32>(outSource.Size()), &outLength, outSource.MutableBuffer());
	outSource.ForceSetLength(outLength);
	AssertSuccess();
}


void OpenGLES2Render::SetShadersBinary(uint count, const uint* shaders, GraphicsShaderBinaryFormat binaryFormat, const void* data, uint length)
{
	glShaderBinary(count, shaders, (uint)binaryFormat, data, length);
	AssertSuccess();
}

void OpenGLES2Render::SetShaderBinary(uint shader, GraphicsShaderBinaryFormat binaryFormat, const void* data, uint length)
{
	glShaderBinary(1, &shader, (uint)binaryFormat, data, length);
	AssertSuccess();
}

void OpenGLES2Render::CompileShader(uint shader)
{
	glCompileShader(shader);
	AssertSuccess();
}

void OpenGLES2Render::GetShadderInfoLog(uint shader, HeapString& outInfoLog)
{
	int outLength;
	glGetShaderInfoLog(shader, static_cast<uint32>(outInfoLog.Size()), &outLength, outInfoLog.MutableBuffer());
	outInfoLog.ForceSetLength(outLength);
	AssertSuccess();
}

bool OpenGLES2Render::IsShader(uint shader)
{
	return glIsShader(shader) != 0;
}


int OpenGLES2Render::GetShaderStatus(uint shader, GraphicsShaderStatus name)
{
	int outVal;
	glGetShaderiv(shader, (uint)name, &outVal);
	AssertSuccess();
	return outVal;
}

uint OpenGLES2Render::CreateProgram()
{
	uint result = glCreateProgram();
	AssertSuccess();
	return result;
}

void OpenGLES2Render::DeleteProgram(uint program)
{
	glDeleteProgram(program);
	AssertSuccess();
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	TryGetInteger(GraphicsIntegerName::CurrentProgram, (int&)mCurrentProgram);
#endif
}

void OpenGLES2Render::AttachShader(uint program, uint shader)
{
	glAttachShader(program, shader);
	AssertSuccess();
}

void OpenGLES2Render::DetachShader(uint program, uint shader)
{
	glDetachShader(program, shader);
	AssertSuccess();
}

void OpenGLES2Render::LinkProgram(uint program)
{
	glLinkProgram(program);
	AssertSuccess();
}

void OpenGLES2Render::GetProgramInfoLog(uint program, HeapString& outInfoLog)
{
	int outLength;
	glGetProgramInfoLog(program, static_cast<uint32>(outInfoLog.Size()), &outLength, outInfoLog.MutableBuffer());
	outInfoLog.ForceSetLength(outLength);
	AssertSuccess();
}

void OpenGLES2Render::UseProgram(uint program)
{
	RENDER_RETURN_IF_EQUAL(mCurrentProgram, program);
	glUseProgram(program);
	RENDER_ASSIGN_IF_SUCCESS(mCurrentProgram, program);
}

bool OpenGLES2Render::IsProgram(uint program)
{
	return glIsProgram(program) != 0;
}

void OpenGLES2Render::ValidateProgram(uint program)
{
	glValidateProgram(program);
	AssertSuccess();
}

int OpenGLES2Render::GetProgramStatus(uint program, GraphicsProgramStatus name)
{
	int outVal;
	glGetProgramiv(program, (uint)name, &outVal);
	AssertSuccess();
	return outVal;
}


void OpenGLES2Render::BindUniformLocation(uint program, int index, StringRef name)
{
	glBindAttribLocation(program, index, name.Buffer());
	AssertSuccess();
}

int OpenGLES2Render::GetUniformLocation(uint program, StringRef name)
{
	int result = glGetUniformLocation(program, name.Buffer());
	AssertSuccess();
	return result;
}
void OpenGLES2Render::SetUniform(int location, int x)
{
	glUniform1i(location, x);
	AssertSuccess();
}

void OpenGLES2Render::SetUniform(int location, int x, int y)
{
	glUniform2i(location, x, y);
	AssertSuccess();
}

void OpenGLES2Render::SetUniform(int location, int x, int y, int z)
{
	glUniform3i(location, x, y, z);
	AssertSuccess();
}

void OpenGLES2Render::SetUniform(int location, int x, int y, int z, int w)
{
	glUniform4i(location, x, y, z, w);
	AssertSuccess();
}

void OpenGLES2Render::SetUniform(int location, float x)
{
	glUniform1f(location, x);
	AssertSuccess();
}

void OpenGLES2Render::SetUniform(int location, float x, float y)
{
	glUniform2f(location, x, y);
	AssertSuccess();
}

void OpenGLES2Render::SetUniform(int location, float x, float y, float z)
{
	glUniform3f(location, x, y, z);
	AssertSuccess();
}

void OpenGLES2Render::SetUniform(int location, float x, float y, float z, float w)
{
	glUniform4f(location, x, y, z, w);
	AssertSuccess();
}


void OpenGLES2Render::SetUniformArray1(int location, uint count, const float* data)
{
	glUniform1fv(location, count, data);
	AssertSuccess();
}

void OpenGLES2Render::SetUniformArray1(int location, uint count, const int* data)
{
	glUniform1iv(location, count, data);
	AssertSuccess();
}

void OpenGLES2Render::SetUniformArray2(int location, uint count, const float* data)
{
	glUniform2fv(location, count, data);
	AssertSuccess();
}

void OpenGLES2Render::SetUniformArray2(int location, uint count, const int* data)
{
	glUniform2iv(location, count, data);
	AssertSuccess();
}

void OpenGLES2Render::SetUniformArray3(int location, uint count, const float* data)
{
	glUniform3fv(location, count, data);
	AssertSuccess();
}

void OpenGLES2Render::SetUniformArray3(int location, uint count, const int* data)
{
	glUniform3iv(location, count, data);
	AssertSuccess();
}

void OpenGLES2Render::SetUniformArray4(int location, uint count, const float* data)
{
	glUniform4fv(location, count, data);
	AssertSuccess();
}

void OpenGLES2Render::SetUniformArray4(int location, uint count, const int* data)
{
	glUniform4iv(location, count, data);
	AssertSuccess();
}

void OpenGLES2Render::SetUniformMatrix2(int location, uint count, const float* data, bool isTransposed/*=false*/)
{
	glUniformMatrix2fv(location, count, isTransposed, data);
	AssertSuccess();
}

void OpenGLES2Render::SetUniformMatrix3(int location, uint count, const float* data, bool isTransposed/*=false*/)
{
	glUniformMatrix3fv(location, count, isTransposed, data);
	AssertSuccess();
}

void OpenGLES2Render::SetUniformMatrix4(int location, uint count, const float* data, bool isTransposed/*=false*/)
{
	glUniformMatrix4fv(location, count, isTransposed, data);
	AssertSuccess();
}

void OpenGLES2Render::GetUniformArray(uint program, int location, float* outData)
{
	glGetUniformfv(program, location, outData);
	AssertSuccess();
}

void OpenGLES2Render::GetUniformArray(uint program, int location, int* outData)
{
	glGetUniformiv(program, location, outData);
	AssertSuccess();
}


void OpenGLES2Render::SetVertexAttribute(uint index, float x)
{
	glVertexAttrib1f(index, x);
	AssertSuccess();
}

void OpenGLES2Render::SetVertexAttribute(uint index, const Point2F& pos)
{
	glVertexAttrib2f(index, pos.X, pos.Y);
	AssertSuccess();
}

void OpenGLES2Render::SetVertexAttribute(uint index, const Point3F& pos)
{
	glVertexAttrib3f(index, pos.X, pos.Y, pos.Z);
	AssertSuccess();
}

void OpenGLES2Render::SetVertexAttribute(uint index, const Point4F& pos)
{
	glVertexAttrib4f(index, pos.X, pos.Y, pos.Z, pos.W);
	AssertSuccess();
}

void OpenGLES2Render::SetVertexAttributeArray1(uint index, const float* data)
{
	glVertexAttrib1fv(index, data);
	AssertSuccess();
}

void OpenGLES2Render::SetVertexAttributeArray2(uint index, const float* data)
{
	glVertexAttrib2fv(index, data);
	AssertSuccess();
}

void OpenGLES2Render::SetVertexAttributeArray3(uint index, const float* data)
{
	glVertexAttrib3fv(index, data);
	AssertSuccess();
}

void OpenGLES2Render::SetVertexAttributeArray4(uint index, const float* data)
{
	glVertexAttrib4fv(index, data);
	AssertSuccess();
}

void OpenGLES2Render::SetVertexAttributePointer(uint index, uint componentCount, GraphicsDataType type, bool isNormalized, uint stride, const void* data)
{
	glVertexAttribPointer(index, componentCount, (uint)type, isNormalized, stride, data);
	AssertSuccess();
}

void OpenGLES2Render::GetVertexAttributePointer(uint index, void** outData)
{
	glGetVertexAttribPointerv(index, GL_VERTEX_ATTRIB_ARRAY_POINTER, outData);
	AssertSuccess();
}

void OpenGLES2Render::EnableVertexAttributeArray(uint index, bool isEnabled)
{
	if (isEnabled)
	{
		glEnableVertexAttribArray(index);
	}
	else
	{
		glDisableVertexAttribArray(index);
	}
	AssertSuccess();
}

int OpenGLES2Render::GetVertexAttributeLocation(uint program, StringRef name)
{
	int result;
	result = glGetAttribLocation(program, name.Buffer());
	AssertSuccess();
	return result;

}

void OpenGLES2Render::GetActiveAttributeName(uint program, uint index, int& outSize, uint& outDataType, HeapString& outName)
{
	int outLength;
	glGetActiveAttrib(program, index, static_cast<uint32>(outName.Size()), &outLength, &outSize, &outDataType, outName.MutableBuffer());
	outName.ForceSetLength(outLength);
	AssertSuccess();
}

void OpenGLES2Render::GetActiveUniformName(uint program, uint index, int& outSize, uint& outDataType, HeapString& outName)
{
	int outLength;
	glGetActiveUniform(program, index, static_cast<uint32>(outName.Size()), &outLength, &outSize, &outDataType, outName.MutableBuffer());
	outName.ForceSetLength(outLength);
	AssertSuccess();
}

void OpenGLES2Render::GetAttachedShaders(uint program, uint maxCount, int& outCount, uint* outShaders)
{
	glGetAttachedShaders(program, maxCount, &outCount, outShaders);
	AssertSuccess();
}

void OpenGLES2Render::GetShaderPrecisionFormat(GraphicsShaderType shaderType, GraphicsShaderPrecisionType precesionType, int* outRange, int* outPrecision)
{
	glGetShaderPrecisionFormat((uint)shaderType, (uint)precesionType, outRange, outPrecision);
	AssertSuccess();
}

void OpenGLES2Render::GetVertexAttributeValue(uint index, GraphicsVertexAttributeParameter parameter, float* outParams)
{
	glGetVertexAttribfv(index, (uint)parameter, outParams);
	AssertSuccess();
}

void OpenGLES2Render::GetVertexAttributeValue(uint index, GraphicsVertexAttributeParameter parameter, int* outParams)
{
	glGetVertexAttribiv(index, (uint)parameter, outParams);
	AssertSuccess();
}

void OpenGLES2Render::ReleaseShaderCompiler() const
{
	glReleaseShaderCompiler();
	AssertSuccess();
}

#pragma endregion Shader

#pragma region Extension
bool OpenGLES2Render::IsExtensionSupported(StringRef extension) const
{
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	RETURN_FALSE_IF_EMPTY(extension);
	return mExtensions.Contains(extension);
#else
	StringRef extensions = GetString(GraphicsStringName::Extensions);
	return extensions.Contains(extension);
#endif
}

void OpenGLES2Render::LoadExtensions()
{
#ifdef MEDUSA_WINDOWS

#ifdef GLEW
	if (IsExtensionSupported(RenderExtensionNames::EXT_multi_draw_arrays))
	{
		glMultiDrawArraysEXT = (PFNGLMULTIDRAWARRAYSEXTPROC)PRIVATE_GET_EXTENSION_PROC_ADRESS(glMultiDrawArraysEXT);
		glMultiDrawElementsEXT = (PFNGLMULTIDRAWELEMENTSEXTPROC)PRIVATE_GET_EXTENSION_PROC_ADRESS(glMultiDrawElementsEXT);
	}
#endif

#ifdef GL_OES_mapbuffer
	if (IsExtensionSupported(RenderExtensionNames::OES_mapbuffer))
	{
		glMapBufferOES = (PFNGLMAPBUFFEROESPROC)PRIVATE_GET_EXTENSION_PROC_ADRESS(glMapBufferOES);
		glUnmapBufferOES = (PFNGLUNMAPBUFFEROESPROC)PRIVATE_GET_EXTENSION_PROC_ADRESS(glUnmapBufferOES);
		glGetBufferPointervOES = (PFNGLGETBUFFERPOINTERVOESPROC)PRIVATE_GET_EXTENSION_PROC_ADRESS(glGetBufferPointervOES);
	}
#endif

#ifdef GL_OES_vertex_array_object
	if (IsExtensionSupported(RenderExtensionNames::OES_vertex_array_object))
	{
		glBindVertexArrayOES = (PFNGLBINDVERTEXARRAYOESPROC)PRIVATE_GET_EXTENSION_PROC_ADRESS(glBindVertexArrayOES);
		glDeleteVertexArraysOES = (PFNGLDELETEVERTEXARRAYSOESPROC)PRIVATE_GET_EXTENSION_PROC_ADRESS(glDeleteVertexArraysOES);
		glGenVertexArraysOES = (PFNGLGENVERTEXARRAYSOESPROC)PRIVATE_GET_EXTENSION_PROC_ADRESS(glGenVertexArraysOES);
		glIsVertexArrayOES = (PFNGLISVERTEXARRAYOESPROC)PRIVATE_GET_EXTENSION_PROC_ADRESS(glIsVertexArrayOES);
	}
#endif

#ifdef GL_IMG_multisampled_render_to_texture
	if (IsExtensionSupported(RenderExtensionNames::IMG_multisampled_render_to_texture))
	{
		glRenderbufferStorageMultisampleIMG = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLEIMGPROC)PRIVATE_GET_EXTENSION_PROC_ADRESS(glRenderbufferStorageMultisampleIMG);
		glFramebufferTexture2DMultisampleIMG = (PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEIMGPROC)PRIVATE_GET_EXTENSION_PROC_ADRESS(glFramebufferTexture2DMultisampleIMG);
	}
#endif


#if defined(GL_EXT_discard_framebuffer)&&GL_EXT_discard_framebuffer==1
	if (IsExtensionSupported(RenderExtensionNames::EXT_discard_framebuffer))
	{
		glDiscardFramebufferEXT = (PFNGLDISCARDFRAMEBUFFEREXTPROC)PRIVATE_GET_EXTENSION_PROC_ADRESS(glDiscardFramebufferEXT);
	}
#endif

#endif
}



#pragma endregion Extension



#pragma region OpenGL ES 3.0

#pragma region Frame buffer

void OpenGLES2Render::ReadBuffer(GraphicsColorBuffers buffer)const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}

void OpenGLES2Render::SetDrawBufferTargets(uint count, const GraphicsColorBuffers* buffers) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}


void OpenGLES2Render::BlitFrameBuffer(const Rect2I& srcRect, const Rect2I& destRect, GraphicsBufferComponentMask mask, GraphicsTextureMagFilter filter) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}

void OpenGLES2Render::SetRenderBufferMultipleSampleStorage(GraphicsRenderBufferInternalFormat format, uint sampleCount, const Size2U& size) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}

void OpenGLES2Render::AttachTextureLayerToFrameBuffer(GraphicsFrameBufferType frameBuffer, GraphicsAttachment attachment, uint texture, int level, int layer) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();

}

void OpenGLES2Render::InvalidateFramebuffer(uint numAttachments, const GraphicsAttachment* attachments) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();

}

void OpenGLES2Render::InvalidateSubFramebuffer(uint numAttachments, const GraphicsAttachment* attachments, const Rect2U& rect) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}

void OpenGLES2Render::GetInternalFormatParameter(GraphicsInternalFormat internalFormat, GraphicsInternalFormatParameterName name, uint bufferSize, int* outParam) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}

#pragma endregion Frame buffer

#pragma region Texture
void OpenGLES2Render::LoadTexture3D(GraphicsTextureTarget textureTarget, int level, PixelType pixelType, const Size3U& size, int border,  const void *pixels) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}

void OpenGLES2Render::LoadSubTexture3D(GraphicsTextureTarget textureTarget, int level, const CubeI& rect, PixelType pixelType, const void *pixels) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}

void OpenGLES2Render::CopySubTexture3D(GraphicsTextureTarget textureTarget, int level, const Point3I& offset, const Rect2I& rect) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}

void OpenGLES2Render::LoadCompressedTexture3D(GraphicsTextureTarget textureTarget, int level, PixelType pixelType, const Size3U& size, int border, uint imageSize, const void *pixels) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}

void OpenGLES2Render::LoadCompressedSubTexture3D(GraphicsTextureTarget textureTarget, int level, PixelType pixelType, const CubeI& rect, uint imageSize, const void *pixels) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}

void OpenGLES2Render::SetTextureStorage2D(GraphicsTextureTarget textureTarget, uint level, PixelType pixelType, const Size2U& size) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}

void OpenGLES2Render::SetTextureStorage3D(GraphicsTextureTarget textureTarget, uint level, PixelType pixelType, const Size3U& size) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}
#pragma endregion Texture

#pragma region Query
void OpenGLES2Render::GenQueries(uint count, uint* outQueries) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}

void OpenGLES2Render::DeleteQueries(uint count, uint* queries) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}

bool OpenGLES2Render::IsQuery(uint id) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
	return false;
}

void OpenGLES2Render::BeginQuery(GraphicsQueryTarget target, uint query) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}

void OpenGLES2Render::EndQuery(uint query) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}

int OpenGLES2Render::GetQueryParameter(GraphicsQueryTarget target, GraphicsQueryParameter parameter) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
	return -1;
}

uint OpenGLES2Render::GetQueryObjectParameter(uint query, GraphicsQueryObjectParameter parameter) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
	return 0;
}

#pragma endregion Query

#pragma region Buffer

void* OpenGLES2Render::MapBufferRange(GraphicsBufferType bufferType, int offset, uint length, GraphicsMapBufferMask mask) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
	return nullptr;
}

bool OpenGLES2Render::UnmapBuffer(GraphicsBufferType bufferType)const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
	return false;
}


void OpenGLES2Render::GetBufferPointer(GraphicsBufferType bufferType, GraphicsBufferPointerName name, void** outResult) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}


void OpenGLES2Render::FlushMappedBufferRange(GraphicsBufferType bufferType, int offset, uint length) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}

void OpenGLES2Render::BindBufferToBuffer(GraphicsBindBufferTarget target, uint index, uint buffer) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();

}

void OpenGLES2Render::BindBufferRangeToBuffer(GraphicsBindBufferTarget target, uint index, uint buffer, int offset, uint length) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}


void OpenGLES2Render::ClearBuffer(GraphicsBufferClearMask clearMask, int drawBuffer, const int* val) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}

void OpenGLES2Render::ClearBuffer(GraphicsBufferClearMask clearMask, int drawBuffer, const uint* val) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}

void OpenGLES2Render::ClearBuffer(GraphicsBufferClearMask clearMask, int drawBuffer, const float* val) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}

void OpenGLES2Render::ClearBuffer(GraphicsBufferClearMask clearMask, int drawBuffer, float depth, int stencil) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}


void OpenGLES2Render::CopyBufferSubData(GraphicsBufferType fromTarget, uint fromOffset, GraphicsBufferType toTarget, uint toOffset, uint size) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}


int64 OpenGLES2Render::GetBufferParameter64(GraphicsBufferType bufferType, GraphicsBufferParameter parameter) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
	return -1;
}

#pragma endregion Buffer

#pragma region Uniform

void OpenGLES2Render::SetUniformMatrix23(int location, uint count, const float* data, bool isTransposed /*= false*/) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}

void OpenGLES2Render::SetUniformMatrix32(int location, uint count, const float* data, bool isTransposed /*= false*/) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}

void OpenGLES2Render::SetUniformMatrix24(int location, uint count, const float* data, bool isTransposed /*= false*/) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}

void OpenGLES2Render::SetUniformMatrix42(int location, uint count, const float* data, bool isTransposed /*= false*/) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}

void OpenGLES2Render::SetUniformMatrix34(int location, uint count, const float* data, bool isTransposed /*= false*/) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}

void OpenGLES2Render::SetUniformMatrix43(int location, uint count, const float* data, bool isTransposed /*= false*/) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}


void OpenGLES2Render::GetUniformIndices(uint program, uint uniformCount, const char* const* uniformNames, uint* outUniformIndices) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}

void OpenGLES2Render::GetActiveUniformParameter(uint program, uint uniformCount, const uint* uniformIndices, GraphicsUniformParameterName name, int* outParam) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();

}

uint OpenGLES2Render::GetUniformBlockIndex(uint program, const char* uniformBlockName) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
	return 0;
}

void OpenGLES2Render::GetActiveUniformBlockParameter(uint program, uint uniformBlockIndex, GraphicsUniformBlockParameterName name, int* outParam) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}

void OpenGLES2Render::GetActiveUniformBlockName(uint program, uint uniformBlockIndex, uint outNameBufferSize, uint& outLength, char* outName) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}

void OpenGLES2Render::SetUniformBlockBinding(uint program, uint uniformBlockIndex, uint uniformBlockBinding) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}
void OpenGLES2Render::GetUniformArray(uint program, int location, uint* outData) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}

void OpenGLES2Render::SetUniform(int location, uint x)const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}

void OpenGLES2Render::SetUniform(int location, uint x, uint y)const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}

void OpenGLES2Render::SetUniform(int location, uint x, uint y, uint z)const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}

void OpenGLES2Render::SetUniform(int location, uint x, uint y, uint z, uint w)const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}

void OpenGLES2Render::SetUniformArray1(int location, uint count, const uint* data)const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}

void OpenGLES2Render::SetUniformArray2(int location, uint count, const uint* data)const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}

void OpenGLES2Render::SetUniformArray3(int location, uint count, const uint* data)const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}

void OpenGLES2Render::SetUniformArray4(int location, uint count, const uint* data)const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}

#pragma endregion Uniform

#pragma region VertexArray

void OpenGLES2Render::BindVertexArray(uint id) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}

void OpenGLES2Render::DeleteVertexArrays(uint count, uint* arrays) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();

}

void OpenGLES2Render::GenVertexArrays(uint count, uint* outArrays) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();

}

bool OpenGLES2Render::IsVertexArray(uint id) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
	return false;
}


void OpenGLES2Render::SetVertexAttributeIntegerPointer(uint index, uint componentCount, GraphicsIntegerDataType type, uint stride, const void* data)const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}

void OpenGLES2Render::GetVertexAttributeValueInt(uint index, GraphicsVertexAttributeParameter parameter, int* outParams) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}

void OpenGLES2Render::GetVertexAttributeValueUInt(uint index, GraphicsVertexAttributeParameter parameter, uint* outParams) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}

void OpenGLES2Render::SetVertexAttribute(uint index, const Point4I& pos) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}

void OpenGLES2Render::SetVertexAttribute(uint index, const Point4U& pos) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}

void OpenGLES2Render::SetVertexAttributeArray4(uint index, const int* data) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}

void OpenGLES2Render::SetVertexAttributeArray4(uint index, const uint* data) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}


void OpenGLES2Render::SetVertexAttributeDivisor(uint index, uint divisor) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}
#pragma endregion VertexArray

#pragma region Transform feedback

void OpenGLES2Render::BeginTransformFeedback(GraphicsTransformFeedbackPrimitiveMode mode) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}

void OpenGLES2Render::EndTransformFeedback() const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}

void OpenGLES2Render::SetTransformFeedbackVaryings(uint program, uint count, const char* const* varyings, GraphicsTransformFeedbackBufferMode bufferMode) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}

void OpenGLES2Render::GetTransformFeedbackVaryings(uint program, uint index, uint outVaryingNameBufferSize, char* outVaryingName, uint& outVaryingNameLength, uint& outVaryingType, uint& outVaryingSize) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}

void OpenGLES2Render::BindTransformFeedback(uint id) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();;
}

void OpenGLES2Render::DeleteTransformFeedbacks(uint count, const uint* ids) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}

void OpenGLES2Render::GenTransformFeedbacks(uint count, uint* outIds)const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}

bool OpenGLES2Render::IsTransformFeedback(uint id) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
	return false;
}

void OpenGLES2Render::PauseTransformFeedback() const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();

}

void OpenGLES2Render::ResumeTransformFeedback() const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();

}

#pragma endregion Transform feedback

#pragma region Program


int OpenGLES2Render::GetFragDataLocation(uint program, const char* name) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
	return -1;
}

void OpenGLES2Render::GetProgramBinary(uint program, uint outBufferSize, uint& outLength, uint& outBinaryFormat, void* outBinary) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}

void OpenGLES2Render::LoadProgramBinary(uint program, uint outbinaryFormat, const void* binary, uint length) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}

void OpenGLES2Render::SetProgramParamter(uint program, GraphicsProgramParameterName name, int val) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();

}

#pragma endregion Program

#pragma region Draw

void OpenGLES2Render::DrawIndicesRange(GraphicsDrawMode mode, uint start, uint end, uint count, GraphicsDataType type, const void* indices) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}

void OpenGLES2Render::DrawArraysInstanced(GraphicsDrawMode mode, int first, uint count, uint instanceCount) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}

void OpenGLES2Render::DrawIndicesInstanced(GraphicsDrawMode mode, uint count, GraphicsDataType type, const void* indices, uint instanceCount) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}


#pragma endregion Draw

#pragma region Sync


intp OpenGLES2Render::CreateSync(GraphicsSyncCondition condition) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
	return -1;
}

bool OpenGLES2Render::IsSync(intp sync) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
	return false;
}

void OpenGLES2Render::DeleteSync(intp sync) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}

void OpenGLES2Render::ClientWaitSync(intp sync, GraphicsSyncMask mask, uint64 timeout) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}

void OpenGLES2Render::WaitSync(intp sync, GraphicsSyncMask mask, uint64 timeout) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}

void OpenGLES2Render::GetSyncParameter(intp sync, GraphicsSyncParameterName name, uint outBufferSize, uint& outLength, int* outValues) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}


#pragma endregion Sync

#pragma region Sampler


void OpenGLES2Render::GenSamplers(uint count, uint* outSamplers) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}

void OpenGLES2Render::DeleteSamplers(uint count, const uint* samplers) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}

bool OpenGLES2Render::IsSampler(uint sampler) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
	return false;
}

void OpenGLES2Render::BindSampler(GraphicsTextureUnits unit, uint sampler) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();

}

void OpenGLES2Render::SetSamplerParameter(uint sampler, GraphicsSamplerParameterName name, int val) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();

}

void OpenGLES2Render::SetSamplerParameter(uint sampler, GraphicsSamplerParameterName name, float val) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}

void OpenGLES2Render::SetSamplerParameterArray(uint sampler, GraphicsSamplerParameterName name, const int* values) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}

void OpenGLES2Render::SetSamplerParameterArray(uint sampler, GraphicsSamplerParameterName name, const float* values) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}

void OpenGLES2Render::GetSamplerParameter(uint sampler, GraphicsSamplerParameterName name, int* outParam) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}

void OpenGLES2Render::GetSamplerParameter(uint sampler, GraphicsSamplerParameterName name, float* outParam) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
}


#pragma endregion Sampler

#pragma region Get


bool OpenGLES2Render::TryGetIntegerWithIndex(GraphicsIntegerName name, uint index, int& outVal) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
	return false;
}

bool OpenGLES2Render::TryGetInteger64(GraphicsIntegerName name, int64& outVal) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
	return false;
}

bool OpenGLES2Render::TryGetInteger64WithIndex(GraphicsIntegerName name, uint index, int64& outVal) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
	return false;
}


bool OpenGLES2Render::TryGetStringWithIndex(GraphicsStringName name, uint index, StringRef& outVal) const
{
	MEDUSA_ASSERT_NOT_IMPLEMENT();
	return false;
}

#pragma endregion Get

#pragma endregion OpenGL ES 3.0



MEDUSA_END;

#undef PRIVATE_GET_EXTENSION_PROC_ADRESS
#undef RENDER_ASSIGN_IF_SUCCESS
#undef RENDER_RETURN_IF_EQUAL