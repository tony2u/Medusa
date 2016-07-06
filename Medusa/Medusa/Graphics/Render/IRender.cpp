// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "IRender.h"
#include "Core/Log/Log.h"
#include "Core/String/StringParser.h"
#include "Geometry/GeometryFactory.h"
#include "Resource/Effect/Shader/Parameter/ShaderAttribute.h"
#include "Core/Collection/Array.h"
#include "Graphics/State/SamplerRenderState.h"
#include "Core/String/Format/Format.h"

MEDUSA_BEGIN;

static HeapString ConvetFrontFace(int val)
{
	const static int paramSize = 2;
	

	const static GraphicsFrontFace paramNames[paramSize] =
	{
		GraphicsFrontFace::ClockWise,
		GraphicsFrontFace::CounterClockWise,
	};

	const static char* paramKeys[paramSize] =
	{
		"ClockWise",
		"CounterClockWise",
	};

	FOR_EACH_SIZE(i, paramSize)
	{
		if (val == (int)paramNames[i])
		{
			return HeapString(paramKeys[i]);
		}
	}
	return StringParser::ToString(val);
}


static HeapString ConvetFace(int val)
{
	const static int paramSize = 3;

	const static GraphicsFace paramNames[paramSize] =
	{
		GraphicsFace::Front,
		GraphicsFace::Back,
		GraphicsFace::FrontAndBack,
	};

	const static char* paramKeys[paramSize] =
	{
		"Front",
		"Back",
		"FrontAndBack",
	};

	FOR_EACH_SIZE(i, paramSize)
	{
		if (val == (int)paramNames[i])
		{
			return HeapString(paramKeys[i]);
		}
	}
	return StringParser::ToString(val);
}

static HeapString ConvetBlendEquation(int val)
{
	const static int paramSize = 3;

	const static GraphicsBlendEquation paramNames[paramSize] =
	{
		GraphicsBlendEquation::Add,
		GraphicsBlendEquation::Subtract,
		GraphicsBlendEquation::ReverserSubtract,
	};

	const static char* paramKeys[paramSize] =
	{
		"Add",
		"Subtract",
		"ReverserSubtract",
	};

	FOR_EACH_SIZE(i, paramSize)
	{
		if (val == (int)paramNames[i])
		{
			return HeapString(paramKeys[i]);
		}
	}
	return StringParser::ToString(val);
}


static HeapString ConvetHintMode(int val)
{
	const static int paramSize = 3;

	const static GraphicsHintMode paramNames[paramSize] =
	{
		GraphicsHintMode::Fastest,
		GraphicsHintMode::Nicest,
		GraphicsHintMode::DontCare,
	};

	const static char* paramKeys[paramSize] =
	{
		"Fastest",
		"Nicest",
		"DontCare",
	};

	FOR_EACH_SIZE(i, paramSize)
	{
		if (val == (int)paramNames[i])
		{
			return HeapString(paramKeys[i]);
		}
	}
	return StringParser::ToString(val);
}

static HeapString ConvetInternalFormat(int val)
{
	const static int paramSize=13;
	const static GraphicsInternalFormat paramNames[paramSize]=
	{
		GraphicsInternalFormat::Alpha,
		GraphicsInternalFormat::RGB,
		GraphicsInternalFormat::RGBA,
		GraphicsInternalFormat::Luminance,
		GraphicsInternalFormat::LuminanceAlpha,
		GraphicsInternalFormat::Compressed_RGB_PVRTC_4BPPV1_IMG,
		GraphicsInternalFormat::Compressed_RGB_PVRTC_2BPPV1_IMG,
		GraphicsInternalFormat::Compressed_RGBA_PVRTC_2BPPV1_IMG,
		GraphicsInternalFormat::Compressed_RGBA_PVRTC_4BPPV1_IMG,
		GraphicsInternalFormat::Compressed_RGBA_PVRTC_2BPPV2_IMG,
		GraphicsInternalFormat::Compressed_RGBA_PVRTC_4BPPV2_IMG,
		GraphicsInternalFormat::Compressed_ETC1_RGB8_OES,
		GraphicsInternalFormat::BGRA

	};
	const static char* paramKeys[paramSize]=
	{
		"Alpha",
		"RGB",
		"RGBA",
		"Luminance",
		"LuminanceAlpha",
		"Compressed_RGB_PVRTC_4BPPV1_IMG",
		"Compressed_RGB_PVRTC_2BPPV1_IMG",
		"Compressed_RGBA_PVRTC_2BPPV1_IMG",
		"Compressed_RGBA_PVRTC_4BPPV1_IMG",
		"Compressed_RGBA_PVRTC_2BPPV2_IMG",
		"Compressed_RGBA_PVRTC_4BPPV2_IMG",
		"Compressed_ETC1_RGB8_OES",
		"BGRA"
	};

	FOR_EACH_SIZE(i,paramSize)
	{
		if (val==(int)paramNames[i])
		{
			return HeapString(paramKeys[i]);
		}
	}
	return StringParser::ToString(val);
}


static HeapString ConvetStencilOperation(int val)
{
	const static int paramSize = 8;
	const static GraphicsStencilOperation paramNames[paramSize] =
	{
		GraphicsStencilOperation::Keep,
		GraphicsStencilOperation::Zero,
		GraphicsStencilOperation::ReplaceToRef,
		GraphicsStencilOperation::Increase,
		GraphicsStencilOperation::IncreaseWrap,
		GraphicsStencilOperation::Decrease,
		GraphicsStencilOperation::DecreaseWrap,
		GraphicsStencilOperation::Invert,

	};
	const static char* paramKeys[paramSize] =
	{
		"Keep",
		"Zero",
		"ReplaceToRef",
		"Increase",
		"IncreaseWrap",
		"Decrease",
		"DecreaseWrap",
		"Invert",
	};

	FOR_EACH_SIZE(i, paramSize)
	{
		if (val == (int)paramNames[i])
		{
			return HeapString(paramKeys[i]);
		}
	}
	return StringParser::ToString(val);
}



static HeapString ConvetFuncType(int val)
{
	const static int paramSize = 8;
	const static GraphicsFuncType paramNames[paramSize] =
	{
		GraphicsFuncType::Never,
		GraphicsFuncType::Less,
		GraphicsFuncType::Equal,
		GraphicsFuncType::LessOrEqual,
		GraphicsFuncType::Greater,
		GraphicsFuncType::NotEqual,
		GraphicsFuncType::GreaterOrEqual,
		GraphicsFuncType::Always,

	};
	const static char* paramKeys[paramSize] =
	{
		"Never",
		"Less",
		"Equal",
		"LessOrEqual",
		"Greater",
		"NotEqual",
		"GreaterOrEqual",
		"Always",
	};

	FOR_EACH_SIZE(i, paramSize)
	{
		if (val == (int)paramNames[i])
		{
			return HeapString(paramKeys[i]);
		}
	}
	return StringParser::ToString(val);
}




static HeapString ConvetPixelDataType(int val)
{
	const static int paramSize = 7;

	const static GraphicsPixelDataType paramNames[paramSize] =
	{
		GraphicsPixelDataType::Byte,
		GraphicsPixelDataType::UnsignedShort565,
		GraphicsPixelDataType::UnsignedShort4444,
		GraphicsPixelDataType::UnsignedShort5551,
		GraphicsPixelDataType::HalfFloatOES,
		GraphicsPixelDataType::FloatOES,
		GraphicsPixelDataType::UInt,
	};

	const static char* paramKeys[paramSize] =
	{
		"Byte",
		"UnsignedShort565",
		"UnsignedShort4444",
		"UnsignedShort5551",
		"HalfFloatOES",
		"FloatOES",
		"UInt"
	};

	FOR_EACH_SIZE(i, paramSize)
	{
		if (val == (int)paramNames[i])
		{
			return HeapString(paramKeys[i]);
		}
	}
	return StringParser::ToString(val);
}


static HeapString ConvetBlendSrcFunc(int val)
{
	const static int paramSize=15;
	const static GraphicsBlendSrcFunc paramNames[paramSize]=
	{
		GraphicsBlendSrcFunc::Zero,
		GraphicsBlendSrcFunc::One,
		GraphicsBlendSrcFunc::SrcColor,
		GraphicsBlendSrcFunc::OneMinusSrcColor,
		GraphicsBlendSrcFunc::DestColor,
		GraphicsBlendSrcFunc::OneMinusDestColor,
		GraphicsBlendSrcFunc::SrcAlpha,
		GraphicsBlendSrcFunc::OneMinusSrcAlpha,
		GraphicsBlendSrcFunc::DestAlpha,
		GraphicsBlendSrcFunc::OneMinusDestAlpha,
		GraphicsBlendSrcFunc::ConstantColor,
		GraphicsBlendSrcFunc::OneMinusConstantColor,
		GraphicsBlendSrcFunc::ConstantAlpha,
		GraphicsBlendSrcFunc::OneMinusConstantAlpha,
		GraphicsBlendSrcFunc::SrcAlphaSaturate,

	};
	const static char* paramKeys[paramSize]=
	{
		"Zero",
		"One",
		"SrcColor",
		"OneMinusSrcColor",
		"DestColor",
		"OneMinusDestColor",
		"SrcAlpha",
		"OneMinusSrcAlpha",
		"DestAlpha",
		"OneMinusDestAlpha",
		"ConstantColor",
		"OneMinusConstantColor",
		"ConstantAlpha",
		"OneMinusConstantAlpha",
		"SrcAlphaSaturate"
	};

	FOR_EACH_SIZE(i,paramSize)
	{
		if (val==(int)paramNames[i])
		{
			return HeapString(paramKeys[i]);
		}
	}
	return StringParser::ToString(val);
}

static HeapString ConvetBlendDestFunc(int val)
{
	const static int paramSize=14;
	const static GraphicsBlendDestFunc paramNames[paramSize]=
	{
		GraphicsBlendDestFunc::Zero,
		GraphicsBlendDestFunc::One,
		GraphicsBlendDestFunc::SrcColor,
		GraphicsBlendDestFunc::OneMinusSrcColor,
		GraphicsBlendDestFunc::DestColor,
		GraphicsBlendDestFunc::OneMinusDestColor,
		GraphicsBlendDestFunc::SrcAlpha,
		GraphicsBlendDestFunc::OneMinusSrcAlpha,
		GraphicsBlendDestFunc::DestAlpha,
		GraphicsBlendDestFunc::OneMinusDestAlpha,
		GraphicsBlendDestFunc::ConstantColor,
		GraphicsBlendDestFunc::OneMinusConstantColor,
		GraphicsBlendDestFunc::ConstantAlpha,
		GraphicsBlendDestFunc::OneMinusConstantAlpha
	};
	const static char* paramKeys[paramSize]=
	{
		"Zero",
		"One",
		"SrcColor",
		"OneMinusSrcColor",
		"DestColor",
		"OneMinusDestColor",
		"SrcAlpha",
		"OneMinusSrcAlpha",
		"DestAlpha",
		"OneMinusDestAlpha",
		"ConstantColor",
		"OneMinusConstantColor",
		"ConstantAlpha",
		"OneMinusConstantAlpha"
	};

	FOR_EACH_SIZE(i,paramSize)
	{
		if (val==(int)paramNames[i])
		{
			return HeapString(paramKeys[i]);
		}
	}
	return StringParser::ToString(val);
}
IRender::IRender(void)
{
}


IRender::~IRender(void)
{
#ifdef MEDUSA_RENDER_ASSERT_ENABLED
	mSamplerRenderStateDict.Clear();
#endif
}


bool IRender::IsSuccess() const
{
#ifdef MEDUSA_RENDER_ASSERT_ENABLED
	return GetError()==GraphicsErrorCode::Success;
#else
	return true;
#endif
}


bool IRender::AssertSuccess() const
{
#ifdef MEDUSA_RENDER_ASSERT_ENABLED
	GraphicsErrorCode errorCode = GetError();
	switch(errorCode)
	{
	case GraphicsErrorCode::Success:
		return true;
		break;
	case GraphicsErrorCode::InvalidEnum:
		Log::AssertFailed("GL:Invalid Enum.");
		break;
	case GraphicsErrorCode::InvalidValue:
		Log::AssertFailed("GL:Invalid Value.");
		break;
	case GraphicsErrorCode::InvalidOperation:
		Log::AssertFailed("GL:Invalid Operation.");
		break;
	case GraphicsErrorCode::InvalidFrameBufferOperation:
		Log::AssertFailed("GL:Invalid Frame Buffer Operation.");
		break;
	case GraphicsErrorCode::OutOfMemory:
		Log::AssertFailed("GL:Out of memory");
		break;
	}
	return false;
#else
	return true;
#endif // _DEBUG
}

void IRender::PrintAll() const
{
	HeapString str("Render status:\n");
	StringRef notSupportStr="NOT SUPPORTED!";

	{
		//string
		str+="*******************************String Values*****************************************\n";
		const static int paramSize=5;
		const static GraphicsStringName paramNames[paramSize]=
		{
			GraphicsStringName::Version,
			GraphicsStringName::Vendor,
			GraphicsStringName::ShaderLanguageVersion,
			GraphicsStringName::Renderer,
			GraphicsStringName::Extensions,
		};
		const static char* paramKeys[paramSize]=
		{
			"Version",
			"Vendor",
			"ShaderLanguageVersion",
			"Renderer",
			"Extensions",
		};
		StringRef outVal;
		FOR_EACH_SIZE(i,paramSize)
		{
			str+=paramKeys[i];
			str+=":\t\t";
			if(TryGetString(paramNames[i],outVal))
			{
				str+=outVal;
			}
			else
			{
				str+=notSupportStr;
			}
			str+='\n';

		}
	}


	{
		//bool 
		str+="*******************************Bool Values*****************************************\n";
		const static int paramSize=12;
		const static GraphicsBooleanName paramNames[paramSize]=
		{
			GraphicsBooleanName::Blend,
			GraphicsBooleanName::CullFace,
			GraphicsBooleanName::DepthTest,
			GraphicsBooleanName::ScissorTest,
			GraphicsBooleanName::StencilTest,
			GraphicsBooleanName::DepthWritable,
			GraphicsBooleanName::Dither,
			GraphicsBooleanName::PolygonOffsetFill,
			GraphicsBooleanName::SampleAlphaToCoverage,
			GraphicsBooleanName::SampleCoverage,
			GraphicsBooleanName::SampleCoverageInvert,
			GraphicsBooleanName::HasShaderCompiler
		};
		const static char* paramKeys[paramSize]=
		{
			"Blend",
			"CullFace",
			"DepthTest",
			"ScissorTest",
			"StencilTest",
			"DepthWritable",
			"Dither",
			"PolygonOffsetFill",
			"SampleAlphaToCoverage",
			"SampleCoverage",
			"SampleCoverageInvert",
			"HasShaderCompiler"
		};
		bool outVal;
		FOR_EACH_SIZE(i,paramSize)
		{
			str+=paramKeys[i];
			str+=":\t\t";
			if(TryGetBoolean(paramNames[i],outVal))
			{
				str+=StringParser::ToString(outVal);
			}
			else
			{
				str+=notSupportStr;
			}

			str+='\n';

		}
	}

	{
		//bool array 
		bool colorWriteMask[4];
		str+="ColorWriteMask";
		str+=":\t\t";
		if(TryGetBooleanArray(GraphicsBooleanArrayName::ColorWriteMask,(bool*)&colorWriteMask))
		{
			String::AppendFormat(str,"R:{} G:{},B:{} A:{}",StringParser::ToString(colorWriteMask[0]).c_str(),StringParser::ToString(colorWriteMask[1]).c_str(),StringParser::ToString(colorWriteMask[2]).c_str(),StringParser::ToString(colorWriteMask[3]).c_str());
		}
		else
		{
			str+=notSupportStr;
		}

		str+='\n';

	}

	{
		//int 
		str+="*******************************Int Values*****************************************\n";
		const static int paramSize=58;
		const static GraphicsIntegerName paramNames[paramSize]=
		{
			GraphicsIntegerName::ActiveTexture,
			GraphicsIntegerName::AlphaBits,
			GraphicsIntegerName::BlueBits,
			GraphicsIntegerName::GreenBits,
			GraphicsIntegerName::RedBits,
			GraphicsIntegerName::DepthBits,
			GraphicsIntegerName::StencilBits,
			GraphicsIntegerName::SubPixelBits,
			GraphicsIntegerName::ArrayBufferBinding,
			GraphicsIntegerName::ElementArrayBufferBinding,
			GraphicsIntegerName::FrameBufferBinding,
			GraphicsIntegerName::RenderBufferBinding,
			GraphicsIntegerName::BlendDestAlphaFunc,
			GraphicsIntegerName::BlendDestRGBFunc,
			GraphicsIntegerName::BlendAlphaEquation,
			GraphicsIntegerName::BlendRGBEquation,
			GraphicsIntegerName::BlendSrcAlphaFunc,
			GraphicsIntegerName::BlendSrcRGBFunc,
			GraphicsIntegerName::CullFaceMode,
			GraphicsIntegerName::CurrentProgram,
			GraphicsIntegerName::DepthFunc,
			GraphicsIntegerName::FrontFace,
			GraphicsIntegerName::GenerateMipmapHint,
			GraphicsIntegerName::ImplementionColorReadFormat,
			GraphicsIntegerName::ImplementionColorReadType,
			GraphicsIntegerName::MaxCombinedTextureUnitCount,
			GraphicsIntegerName::MaxTextureUnitCount,
			GraphicsIntegerName::MaxVertexTextureUnitCount,
			GraphicsIntegerName::MaxCubeMapTextureSize,
			GraphicsIntegerName::MaxFragmentUniformCount,
			GraphicsIntegerName::MaxVaryingCount,
			GraphicsIntegerName::MaxVetextAttributeCount,
			GraphicsIntegerName::MaxRenderBufferSize,
			GraphicsIntegerName::MaxTextureSize,
			GraphicsIntegerName::MaxVertexUnifromCount,
			GraphicsIntegerName::CompressedTextureFormatCount,
			GraphicsIntegerName::ShaderBinaryFormatCount,
			GraphicsIntegerName::PackAlignment,
			GraphicsIntegerName::UnpackAlignment,
			GraphicsIntegerName::SampleBufferCount,
			GraphicsIntegerName::SampleCoverageMaskSize,
			GraphicsIntegerName::StencilBackFailOperation,
			GraphicsIntegerName::StencilBackFunc,
			GraphicsIntegerName::StencilBackPassDepthFailOperation,
			GraphicsIntegerName::StencilBackPassDepthPassOperation,
			GraphicsIntegerName::StencilBackRefValue,
			GraphicsIntegerName::StencilBackValueMask,
			GraphicsIntegerName::StencilBackWriteMask,
			GraphicsIntegerName::StencilClearValue,
			GraphicsIntegerName::StencilFailOperation,
			GraphicsIntegerName::StencilFunc,
			GraphicsIntegerName::StencilPassDepthFailOperation,
			GraphicsIntegerName::StencilPassDepthPassOperation,
			GraphicsIntegerName::StencilRefValue,
			GraphicsIntegerName::StencilValueMask,
			GraphicsIntegerName::StencilWriteMask,
			GraphicsIntegerName::TextureBinding,
			GraphicsIntegerName::CubeMapTextureBinding
		};
		const static char* paramKeys[paramSize]=
		{
			"ActiveTexture",
			"AlphaBits",
			"BlueBits",
			"GreenBits",
			"RedBits",
			"DepthBits",
			"StencilBits",
			"SubPixelBits",
			"ArrayBufferBinding",
			"ElementArrayBufferBinding",
			"FrameBufferBinding",
			"RenderBufferBinding",
			"BlendDestAlphaFunc",
			"BlendDestRGBFunc",
			"BlendAlphaEquation",
			"BlendRGBEquation",
			"BlendSrcAlphaFunc",
			"BlendSrcRGBFunc",
			"CullFaceMode",
			"CurrentProgram",
			"DepthFunc",
			"FrontFace",
			"GenerateMipmapHint",
			"ImplementionColorReadFormat",
			"ImplementionColorReadType",
			"MaxCombinedTextureUnitCount",
			"MaxTextureUnitCount",
			"MaxVertexTextureUnitCount",
			"MaxCubeMapTextureSize",
			"MaxFragmentUniformCount",
			"MaxVaryingCount",
			"MaxVetextAttributeCount",
			"MaxRenderBufferSize",
			"MaxTextureSize",
			"MaxVertexUnifromCount",
			"CompressedTextureFormatCount",
			"ShaderBinaryFormatCount",
			"PackAlignment",
			"UnpackAlignment",
			"SampleBufferCount",
			"SampleCoverageMaskSize",
			"StencilBackFailOperation",
			"StencilBackFunc",
			"StencilBackPassDepthFailOperation",
			"StencilBackPassDepthPassOperation",
			"StencilBackRefValue",
			"StencilBackValueMask",
			"StencilBackWriteMask",
			"StencilClearValue",
			"StencilFailOperation",
			"StencilFunc",
			"StencilPassDepthFailOperation",
			"StencilPassDepthPassOperation",
			"StencilRefValue",
			"StencilValueMask",
			"StencilWriteMask",
			"TextureBinding",
			"CubeMapTextureBinding"
		};
		int outVal;
		FOR_EACH_SIZE(i,paramSize)
		{
			str+=paramKeys[i];
			str+=":\t\t";
			if(TryGetInteger(paramNames[i],outVal))
			{
				switch(paramNames[i])
				{
				case GraphicsIntegerName::ActiveTexture:
					String::AppendFormat(str, "Texture{}",outVal-(int)GraphicsTextureUnits::Texture0);
					break;
				case GraphicsIntegerName::BlendAlphaEquation:
				case GraphicsIntegerName::BlendRGBEquation:
					str+= ConvetBlendEquation(outVal);
					break;
				case GraphicsIntegerName::BlendSrcAlphaFunc:
				case GraphicsIntegerName::BlendSrcRGBFunc:
					str+=ConvetBlendSrcFunc(outVal);
					break;
				case GraphicsIntegerName::BlendDestAlphaFunc:
				case GraphicsIntegerName::BlendDestRGBFunc:
					str+=ConvetBlendDestFunc(outVal);
					break;
				case GraphicsIntegerName::CullFaceMode:
					str+= ConvetFace(outVal);
					break;
				case GraphicsIntegerName::FrontFace:
					str+= ConvetFrontFace(outVal);
					break;
				case GraphicsIntegerName::DepthFunc:
				case GraphicsIntegerName::StencilBackFunc:
				case GraphicsIntegerName::StencilFunc:
					str+= ConvetFuncType(outVal);
					break;
				case GraphicsIntegerName::StencilFailOperation:
				case GraphicsIntegerName::StencilPassDepthFailOperation:
				case GraphicsIntegerName::StencilPassDepthPassOperation:
				case GraphicsIntegerName::StencilBackFailOperation:
				case GraphicsIntegerName::StencilBackPassDepthFailOperation:
				case GraphicsIntegerName::StencilBackPassDepthPassOperation:
					str+= ConvetStencilOperation(outVal);
					break;
				case GraphicsIntegerName::GenerateMipmapHint:
					str += ConvetHintMode(outVal);
					break;
				case GraphicsIntegerName::ImplementionColorReadType:
					str += ConvetPixelDataType(outVal);
					break;
				case GraphicsIntegerName::ImplementionColorReadFormat:
					str+=ConvetInternalFormat(outVal);
					break;
				default:
					str+=StringParser::ToString(outVal);
					break;
				}

			}
			else
			{
				str+=notSupportStr;
			}

			str+='\n';
		}
	}


	{
		//int array 
		int vals[4];
		str+="AliasedLineWidthRange";
		str+=":\t\t";

		if(TryGetIntegerArray(GraphicsIntegerArrayName::AliasedLineWidthRange,(int*)&vals))
		{
			String::AppendFormat(str,"{},{}",vals[0],vals[1]);
		}
		else
		{
			str+=notSupportStr;
		}
		str+='\n';

		str+="AliasedPointSizeRange";
		str+=":\t\t";
		if(TryGetIntegerArray(GraphicsIntegerArrayName::AliasedPointSizeRange,(int*)&vals))
		{
			String::AppendFormat(str,"{},{}",vals[0],vals[1]);
		}
		else
		{
			str+=notSupportStr;
		}
		str+='\n';

		str+="AliasedPointSizeRange";
		str+=":\t\t";
		if(TryGetIntegerArray(GraphicsIntegerArrayName::AliasedPointSizeRange,(int*)&vals))
		{
			String::AppendFormat(str,"{},{}",vals[0],vals[1]);
		}
		else
		{
			str+=notSupportStr;
		}
		str+='\n';

		str+="CompressedTextureFormats";
		str+=":\t\t";
		int size;
		if (TryGetInteger(GraphicsIntegerName::CompressedTextureFormatCount,size))
		{
			int* tempVals=new int[size];
			if(TryGetIntegerArray(GraphicsIntegerArrayName::CompressedTextureFormats,tempVals))
			{
				FOR_EACH_SIZE(i,(uint)size)
				{
					str+=ConvetInternalFormat(tempVals[i]);
					if (i!=(uint)size-1)
					{
						str+=',';
					}
				}
			}
			else
			{
				str+=notSupportStr;
			}


			SAFE_DELETE_ARRAY(tempVals);
		}
		else
		{
			str+=notSupportStr;
		}
		str+='\n';


		str+="ShaderBinaryFormats";
		str+=":\t\t";
		if (TryGetInteger(GraphicsIntegerName::ShaderBinaryFormatCount,size))
		{
			int* tempVals=new int[size];
			if(TryGetIntegerArray(GraphicsIntegerArrayName::ShaderBinaryFormats,tempVals))
			{
				FOR_EACH_SIZE(i,(uint)size)
				{
					str+=StringParser::ToString(tempVals[i]);
					if (i!=(uint)size-1)
					{
						str+=',';
					}
				}
			}
			else
			{
				str+=notSupportStr;

			}
			SAFE_DELETE_ARRAY(tempVals);
		}
		else
		{
			str+=notSupportStr;
		}
		str+='\n';




		str+="MaxViewportDimensions";
		str+=":\t\t";
		if(TryGetIntegerArray(GraphicsIntegerArrayName::MaxViewportDimensions,(int*)&vals))
		{
			String::AppendFormat(str,"{},{}",vals[0],vals[1]);
		}
		else
		{
			str+=notSupportStr;
		}
		str+='\n';

		str+="ScissorBox";
		str+=":\t\t";
		if(TryGetIntegerArray(GraphicsIntegerArrayName::ScissorBox,(int*)&vals))
		{
			String::AppendFormat(str,"{},{},{},{}",vals[0],vals[1],vals[2],vals[3]);
		}
		else
		{
			str+=notSupportStr;
		}
		str+='\n';

		str+="Viewport";
		str+=":\t\t";
		if(TryGetIntegerArray(GraphicsIntegerArrayName::Viewport,(int*)&vals))
		{
			String::AppendFormat(str,"{},{},{},{}",vals[0],vals[1],vals[2],vals[3]);
		}
		else
		{
			str+=notSupportStr;
		}
		str+='\n';

	}

	{
		//float 
		str+="*******************************Float Values*****************************************\n";
		const static int paramSize=5;
		const static GraphicsFloatName paramNames[paramSize]=
		{
			GraphicsFloatName::DepthClearValue,
			GraphicsFloatName::LineWidth,
			GraphicsFloatName::PolygonOffsetFactor,
			GraphicsFloatName::PolygonOffsetUnit,
			GraphicsFloatName::SampleCoverage,
		};
		const static char* paramKeys[paramSize]=
		{
			"DepthClearValue",
			"LineWidth",
			"PolygonOffsetFactor",
			"PolygonOffsetUnit",
			"SampleCoverage",
		};
		float outVal;
		FOR_EACH_SIZE(i,paramSize)
		{
			str+=paramKeys[i];
			str+=":\t\t";
			if (TryGetFloat(paramNames[i],outVal))
			{
				str+=StringParser::ToString(outVal);
			}
			else
			{
				str+=notSupportStr;
			}
			str+='\n';

		}
	}

	{
		//float array
		float vals[4];
		str+="BlendColor";
		str+=":\t\t";
		if(TryGetFloatArray(GraphicsFloatArrayName::BlendColor,(float*)&vals))
		{
			String::AppendFormat(str,"%f,%f,%f,%f",vals[0],vals[1],vals[2],vals[3]);
		}
		else
		{
			str+=notSupportStr;
		}
		str+='\n';

		str+="ClearColor";
		str+=":\t\t";
		if(TryGetFloatArray(GraphicsFloatArrayName::ClearColor,(float*)&vals))
		{
			String::AppendFormat(str,"%f,%f,%f,%f",vals[0],vals[1],vals[2],vals[3]);
		}
		else
		{
			str+=notSupportStr;
		}
		str+='\n';

		str+="DepthRange";
		str+=":\t\t";
		if(TryGetFloatArray(GraphicsFloatArrayName::DepthRange,(float*)&vals))
		{
			String::AppendFormat(str,"%f,%f",vals[0],vals[1]);
		}
		else
		{
			str+=notSupportStr;
		}
		str+='\n';
	}

	Log::Info(str);

}



bool IRender::Initialize()
{
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	//bool values
	TryGetBoolean(GraphicsBooleanName::Blend,mBlendEnabled);
	TryGetBoolean(GraphicsBooleanName::CullFace,mCullFaceEnabled);
	TryGetBoolean(GraphicsBooleanName::DepthTest,mDepthTestEnabled);
	TryGetBoolean(GraphicsBooleanName::ScissorTest,mScissorTestEnabled);
	TryGetBoolean(GraphicsBooleanName::StencilTest,mStencilTestEnabled);
	TryGetBoolean(GraphicsBooleanName::DepthWritable,mDepthWritableEnabled);
	TryGetBoolean(GraphicsBooleanName::Dither,mDitherEnabled);
	TryGetBoolean(GraphicsBooleanName::PolygonOffsetFill,mPolygonOffsetFillEnabled);
	TryGetBoolean(GraphicsBooleanName::SampleAlphaToCoverage,mSampleAlphaToCoverageEnabled);
	TryGetBoolean(GraphicsBooleanName::SampleCoverage,mSampleCoverageEnabled);
	TryGetBoolean(GraphicsBooleanName::SampleCoverageInvert,mSampleCoverageInvertEnabled);
	TryGetBoolean(GraphicsBooleanName::HasShaderCompiler,mHasShaderCompilerEnabled);

	bool outColorMask[4];//RGBA
	TryGetBooleanArray(GraphicsBooleanArrayName::ColorWriteMask,outColorMask);
	if (outColorMask[0])
	{
		MEDUSA_FLAG_ADD(mColorWriteMask, GraphicsColorMask::R);
	}
	if (outColorMask[1])
	{
		MEDUSA_FLAG_ADD(mColorWriteMask, GraphicsColorMask::G);
	}
	if (outColorMask[2])
	{
		MEDUSA_FLAG_ADD(mColorWriteMask, GraphicsColorMask::B);
	}
	if (outColorMask[3])
	{
		MEDUSA_FLAG_ADD(mColorWriteMask, GraphicsColorMask::A);
	}

	//int values
	TryGetInteger(GraphicsIntegerName::ActiveTexture,(int&)mActiveTexture);
	TryGetInteger(GraphicsIntegerName::AlphaBits,mAlphaBits);
	TryGetInteger(GraphicsIntegerName::BlueBits,mBlueBits);
	TryGetInteger(GraphicsIntegerName::GreenBits,mGreenBits);
	TryGetInteger(GraphicsIntegerName::RedBits,mRedBits);
	TryGetInteger(GraphicsIntegerName::DepthBits,mDepthBits);
	TryGetInteger(GraphicsIntegerName::StencilBits,mStencilBits);
	TryGetInteger(GraphicsIntegerName::SubPixelBits,mSubPixelBits);
	TryGetInteger(GraphicsIntegerName::ArrayBufferBinding,(int&)mArrayBufferBinding);
	TryGetInteger(GraphicsIntegerName::ElementArrayBufferBinding, (int&)mElementArrayBufferBinding);
	TryGetInteger(GraphicsIntegerName::FrameBufferBinding, (int&)mFrameBufferBinding);
	TryGetInteger(GraphicsIntegerName::RenderBufferBinding, (int&)mRenderBufferBinding);
	TryGetInteger(GraphicsIntegerName::BlendDestAlphaFunc,(int&)mBlendDestAlphaFunc);
	TryGetInteger(GraphicsIntegerName::BlendDestRGBFunc,(int&)mBlendDestRGBFunc);
	TryGetInteger(GraphicsIntegerName::BlendAlphaEquation,(int&)mBlendAlphaEquation);
	TryGetInteger(GraphicsIntegerName::BlendRGBEquation, (int&)mBlendRGBEquation);
	TryGetInteger(GraphicsIntegerName::BlendSrcAlphaFunc,(int&)mBlendSrcAlphaFunc);
	TryGetInteger(GraphicsIntegerName::BlendSrcRGBFunc,(int&)mBlendSrcRGBFunc);
	TryGetInteger(GraphicsIntegerName::CullFaceMode, (int&)mCullFaceMode);
	TryGetInteger(GraphicsIntegerName::CurrentProgram, (int&)mCurrentProgram);
	TryGetInteger(GraphicsIntegerName::DepthFunc, (int&)mDepthFunc);
	TryGetInteger(GraphicsIntegerName::FrontFace, (int&)mFrontFace);
	TryGetInteger(GraphicsIntegerName::GenerateMipmapHint, (int&)mGenerateMipmapHint);
	TryGetInteger(GraphicsIntegerName::ImplementionColorReadFormat,(int&)mImplementionColorReadFormat);
	TryGetInteger(GraphicsIntegerName::ImplementionColorReadType, (int&)mImplementionColorReadType);
	TryGetInteger(GraphicsIntegerName::MaxCombinedTextureUnitCount,mMaxCombinedTextureUnitCount);
	TryGetInteger(GraphicsIntegerName::MaxTextureUnitCount,mMaxFragmentTextureUnitCount);
	TryGetInteger(GraphicsIntegerName::MaxVertexTextureUnitCount,mMaxVertexTextureUnitCount);
	TryGetInteger(GraphicsIntegerName::MaxCubeMapTextureSize,mMaxCubeMapTextureSize);
	TryGetInteger(GraphicsIntegerName::MaxFragmentUniformCount,mMaxFragmentUniformCount);
	TryGetInteger(GraphicsIntegerName::MaxVaryingCount,mMaxVaryingCount);
	TryGetInteger(GraphicsIntegerName::MaxVetextAttributeCount,mMaxVetextAttributeCount);
	TryGetInteger(GraphicsIntegerName::MaxRenderBufferSize,mMaxRenderBufferSize);
	TryGetInteger(GraphicsIntegerName::MaxTextureSize,mMaxTextureSize);
	TryGetInteger(GraphicsIntegerName::MaxVertexUnifromCount,mMaxVertexUnifromCount);
	TryGetInteger(GraphicsIntegerName::CompressedTextureFormatCount,mCompressedTextureFormatCount);
	TryGetInteger(GraphicsIntegerName::ShaderBinaryFormatCount,mShaderBinaryFormatCount);
	TryGetInteger(GraphicsIntegerName::PackAlignment,mPackAlignment);
	TryGetInteger(GraphicsIntegerName::UnpackAlignment,mUnpackAlignment);
	TryGetInteger(GraphicsIntegerName::SampleBufferCount,mSampleBufferCount);
	TryGetInteger(GraphicsIntegerName::SampleCoverageMaskSize,mSampleCoverageMaskSize);
	TryGetInteger(GraphicsIntegerName::StencilBackFailOperation, (int&)mStencilBackFailOperation);
	TryGetInteger(GraphicsIntegerName::StencilBackFunc, (int&)mStencilBackFunc);
	TryGetInteger(GraphicsIntegerName::StencilBackPassDepthFailOperation, (int&)mStencilBackPassDepthFailOperation);
	TryGetInteger(GraphicsIntegerName::StencilBackPassDepthPassOperation, (int&)mStencilBackPassDepthPassOperation);
	TryGetInteger(GraphicsIntegerName::StencilBackRefValue,mStencilBackRefValue);
	TryGetInteger(GraphicsIntegerName::StencilBackValueMask, (int&)mStencilBackValueMask);
	TryGetInteger(GraphicsIntegerName::StencilBackWriteMask, (int&)mStencilBackWriteMask);
	TryGetInteger(GraphicsIntegerName::StencilClearValue,mStencilClearValue);
	TryGetInteger(GraphicsIntegerName::StencilFailOperation, (int&)mStencilFailOperation);
	TryGetInteger(GraphicsIntegerName::StencilFunc, (int&)mStencilFunc);
	TryGetInteger(GraphicsIntegerName::StencilPassDepthFailOperation, (int&)mStencilPassDepthFailOperation);
	TryGetInteger(GraphicsIntegerName::StencilPassDepthPassOperation, (int&)mStencilPassDepthPassOperation);
	TryGetInteger(GraphicsIntegerName::StencilRefValue,mStencilRefValue);
	TryGetInteger(GraphicsIntegerName::StencilValueMask, (int&)mStencilValueMask);
	TryGetInteger(GraphicsIntegerName::StencilWriteMask, (int&)mStencilWriteMask);

	mTextureBindings.ReserveSize(mMaxVertexTextureUnitCount);
	mTextureBindings.ForceSetCount(mMaxVertexTextureUnitCount);
	mTextureBindings.SetAll(0);
	TryGetInteger(GraphicsIntegerName::TextureBinding, (int&)*mTextureBindings.Items());

	mCubeMapTextureBindings.ReserveSize(mMaxVertexTextureUnitCount);
	mCubeMapTextureBindings.ForceSetCount(mMaxVertexTextureUnitCount);
	mCubeMapTextureBindings.SetAll(0);
	TryGetInteger(GraphicsIntegerName::CubeMapTextureBinding, (int&)*mCubeMapTextureBindings.Items());


	
	TryGetIntegerArray(GraphicsIntegerArrayName::AliasedLineWidthRange,mAliasedLineWidthRange.Buffer);
	TryGetIntegerArray(GraphicsIntegerArrayName::AliasedPointSizeRange,mAliasedPointSizeRange.Buffer);

	mCompressedTextureFormats.ReserveSize(mCompressedTextureFormatCount);
	TryGetIntegerArray(GraphicsIntegerArrayName::CompressedTextureFormats,(int*)mCompressedTextureFormats.Items());
	mCompressedTextureFormats.ForceSetCount(mCompressedTextureFormatCount);

	if (mShaderBinaryFormatCount==0)
	{
		//Some device not support ShaderBinaryFormatCount so that we use the extension
		//The problem is the GL_ARB_ES2_compatibility extension is not properly supported on your system.
		TryGetInteger(GraphicsIntegerName::ProgramBinaryFormatCount, mShaderBinaryFormatCount);
		if (mShaderBinaryFormatCount!=0)
		{
			mShaderBinaryFormats.ReserveSize(mShaderBinaryFormatCount);
			TryGetIntegerArray(GraphicsIntegerArrayName::ProgramBinaryFormats, (int*)mShaderBinaryFormats.Items());
			mShaderBinaryFormats.ForceSetCount(mShaderBinaryFormatCount);
		}
		else
		{
			//still failed
		}
	}
	else
	{
		mShaderBinaryFormats.ReserveSize(mShaderBinaryFormatCount);
		TryGetIntegerArray(GraphicsIntegerArrayName::ShaderBinaryFormats, (int*)mShaderBinaryFormats.Items());
		mShaderBinaryFormats.ForceSetCount(mShaderBinaryFormatCount);
	}
	

	TryGetIntegerArray(GraphicsIntegerArrayName::MaxViewportDimensions,(int*)mMaxViewportDimensions.Buffer);
	TryGetIntegerArray(GraphicsIntegerArrayName::ScissorBox,(int*)mScissorBox.GetBuffer());
	TryGetIntegerArray(GraphicsIntegerArrayName::Viewport,(int*)mViewport.GetBuffer());

	//float values
	TryGetFloat(GraphicsFloatName::DepthClearValue,mDepthClearValue);
	TryGetFloat(GraphicsFloatName::LineWidth,mLineWidth);
	TryGetFloat(GraphicsFloatName::PolygonOffsetFactor,mPolygonOffsetFactor);
	TryGetFloat(GraphicsFloatName::PolygonOffsetUnit,mPolygonOffsetUnit);
	TryGetFloat(GraphicsFloatName::SampleCoverage,mSampleCoverage);

	TryGetFloatArray(GraphicsFloatArrayName::BlendColor,mBlendColor.Buffer);
	TryGetFloatArray(GraphicsFloatArrayName::ClearColor,mClearColor.Buffer);
	TryGetFloatArray(GraphicsFloatArrayName::DepthRange,mDepthRange.Buffer);

	//string values
	TryGetString(GraphicsStringName::Vendor,mVendor);
	TryGetString(GraphicsStringName::Renderer,mRenderer);
	TryGetString(GraphicsStringName::Version,mVersion);
	TryGetString(GraphicsStringName::ShaderLanguageVersion,mShaderLanguageVersion);
	TryGetString(GraphicsStringName::Extensions,mExtensions);

	//texture values
	TryGetTextureParamter(GraphicsTextureType::Texture2D,GraphicsTextureParameter::MinFilter,(int&)mDefaultTextureMinFilter);
	TryGetTextureParamter(GraphicsTextureType::Texture2D, GraphicsTextureParameter::MagFilter, (int&)mDefaultTextureMagFilter);
	TryGetTextureParamter(GraphicsTextureType::Texture2D, GraphicsTextureParameter::WrapS, (int&)mDefaultTextureWrapS);
	TryGetTextureParamter(GraphicsTextureType::Texture2D, GraphicsTextureParameter::WrapT, (int&)mDefaultTextureWrapT);

	TryGetTextureParamter(GraphicsTextureType::TextureCubeMap, GraphicsTextureParameter::MinFilter, (int&)mDefaultCubeMapMinFilter);
	TryGetTextureParamter(GraphicsTextureType::TextureCubeMap, GraphicsTextureParameter::MagFilter, (int&)mDefaultCubeMapMagFilter);
	TryGetTextureParamter(GraphicsTextureType::TextureCubeMap, GraphicsTextureParameter::WrapS, (int&)mDefaultCubeMapWrapS);
	TryGetTextureParamter(GraphicsTextureType::TextureCubeMap, GraphicsTextureParameter::WrapT, (int&)mDefaultCubeMapWrapT);


	Share<SamplerRenderState> state=new SamplerRenderState(mDefaultTextureMinFilter,mDefaultTextureMagFilter,mDefaultTextureWrapS,mDefaultTextureWrapT);
	state->SetTexture(0);
	mSamplerRenderStateDict.Add(0,state);

#endif
	return true;
}

#pragma region Easy


int IRender::GetInteger( GraphicsIntegerName name ) const
{
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED


	switch (name)
	{
	case GraphicsIntegerName::ActiveTexture:return (int)mActiveTexture;
	case GraphicsIntegerName::AlphaBits:return mAlphaBits;
	case GraphicsIntegerName::BlueBits:return mBlueBits;
	case GraphicsIntegerName::GreenBits:return mGreenBits;
	case GraphicsIntegerName::RedBits:return mRedBits;
	case GraphicsIntegerName::DepthBits:return mDepthBits;
	case GraphicsIntegerName::StencilBits:return mStencilBits;
	case GraphicsIntegerName::SubPixelBits:return mSubPixelBits;
	case GraphicsIntegerName::ArrayBufferBinding:return mArrayBufferBinding;
	case GraphicsIntegerName::ElementArrayBufferBinding:return mElementArrayBufferBinding;
	case GraphicsIntegerName::FrameBufferBinding:return mFrameBufferBinding;
	case GraphicsIntegerName::RenderBufferBinding:return mRenderBufferBinding;
	case GraphicsIntegerName::BlendDestAlphaFunc:return (int)mBlendDestAlphaFunc;
	case GraphicsIntegerName::BlendDestRGBFunc:return (int)mBlendDestRGBFunc;
	case GraphicsIntegerName::BlendAlphaEquation:return (int)mBlendAlphaEquation;
	case GraphicsIntegerName::BlendRGBEquation:return (int)mBlendRGBEquation;
	case GraphicsIntegerName::BlendSrcAlphaFunc:return (int)mBlendSrcAlphaFunc;
	case GraphicsIntegerName::BlendSrcRGBFunc:return (int)mBlendSrcRGBFunc;
	case GraphicsIntegerName::CullFaceMode:return (int)mCullFaceMode;
	case GraphicsIntegerName::CurrentProgram:return mCurrentProgram;
	case GraphicsIntegerName::DepthFunc:return (int)mDepthFunc;
	case GraphicsIntegerName::FrontFace:return (int)mFrontFace;
	case GraphicsIntegerName::GenerateMipmapHint:return (int)mGenerateMipmapHint;
	case GraphicsIntegerName::ImplementionColorReadFormat:return (int)mImplementionColorReadFormat;
	case GraphicsIntegerName::ImplementionColorReadType:return (int)mImplementionColorReadType;
	case GraphicsIntegerName::MaxCombinedTextureUnitCount:return mMaxCombinedTextureUnitCount;
	case GraphicsIntegerName::MaxTextureUnitCount:return mMaxFragmentTextureUnitCount;
	case GraphicsIntegerName::MaxVertexTextureUnitCount:return mMaxVertexTextureUnitCount;
	case GraphicsIntegerName::MaxCubeMapTextureSize:return mMaxCubeMapTextureSize;
	case GraphicsIntegerName::MaxFragmentUniformCount:return mMaxFragmentUniformCount;
	case GraphicsIntegerName::MaxVaryingCount:return mMaxVaryingCount;
	case GraphicsIntegerName::MaxVetextAttributeCount:return mMaxVetextAttributeCount;
	case GraphicsIntegerName::MaxRenderBufferSize:return mMaxRenderBufferSize;
	case GraphicsIntegerName::MaxTextureSize:return mMaxTextureSize;
	case GraphicsIntegerName::MaxVertexUnifromCount:return mMaxVertexUnifromCount;
	case GraphicsIntegerName::CompressedTextureFormatCount:return mCompressedTextureFormatCount;
	case GraphicsIntegerName::ShaderBinaryFormatCount:return mShaderBinaryFormatCount;
	case GraphicsIntegerName::PackAlignment:return mPackAlignment;
	case GraphicsIntegerName::UnpackAlignment:return mUnpackAlignment;
	case GraphicsIntegerName::SampleBufferCount:return mSampleBufferCount;
	case GraphicsIntegerName::SampleCoverageMaskSize:return mSampleCoverageMaskSize;
	case GraphicsIntegerName::StencilBackFailOperation:return (int)mStencilBackFailOperation;
	case GraphicsIntegerName::StencilBackFunc:return (int)mStencilBackFunc;
	case GraphicsIntegerName::StencilBackPassDepthFailOperation:return (int)mStencilBackPassDepthFailOperation;
	case GraphicsIntegerName::StencilBackPassDepthPassOperation:return (int)mStencilBackPassDepthPassOperation;
	case GraphicsIntegerName::StencilBackRefValue:return mStencilBackRefValue;
	case GraphicsIntegerName::StencilBackValueMask:return mStencilBackValueMask;
	case GraphicsIntegerName::StencilBackWriteMask:return mStencilBackWriteMask;
	case GraphicsIntegerName::StencilClearValue:return mStencilClearValue;
	case GraphicsIntegerName::StencilFailOperation:return (int)mStencilFailOperation;
	case GraphicsIntegerName::StencilFunc:return (int)mStencilFunc;
	case GraphicsIntegerName::StencilPassDepthFailOperation:return (int)mStencilPassDepthFailOperation;
	case GraphicsIntegerName::StencilPassDepthPassOperation:return (int)mStencilPassDepthPassOperation;
	case GraphicsIntegerName::StencilRefValue:return mStencilRefValue;
	case GraphicsIntegerName::StencilValueMask:return mStencilValueMask;
	case GraphicsIntegerName::StencilWriteMask:return mStencilWriteMask;
	case GraphicsIntegerName::TextureBinding:return mTextureBindings[(int)mActiveTexture-(int)GraphicsTextureUnits::Texture0];
	case GraphicsIntegerName::CubeMapTextureBinding:return mCubeMapTextureBindings[(int)mActiveTexture-(int)GraphicsTextureUnits::Texture0];
	default:
		Log::AssertFailedFormat("Invalid GraphicsIntegerName:{}",name);
		break;
	}
	
	return 0;
#else
	int outVal=0;
	TryGetInteger(name,outVal);
	return outVal;
#endif
}


void IRender::GetIntegerArray( GraphicsIntegerArrayName name,int* params ) const
{
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED

	switch (name)
	{
	case GraphicsIntegerArrayName::AliasedLineWidthRange:
		*(params)=mAliasedLineWidthRange.Min;
		*(params+1)=mAliasedLineWidthRange.Max;
		break;
	case GraphicsIntegerArrayName::AliasedPointSizeRange:
		*(params)=mAliasedPointSizeRange.Min;
		*(params+1)=mAliasedPointSizeRange.Max;
		break;
	case GraphicsIntegerArrayName::CompressedTextureFormats:
		mCompressedTextureFormats.CopyTo((GraphicsInternalFormat*)params,mCompressedTextureFormats.Count());
		break;
	case GraphicsIntegerArrayName::ShaderBinaryFormats:
		mShaderBinaryFormats.CopyTo((GraphicsShaderBinaryFormat*)params,mShaderBinaryFormats.Count());
		break;
	case GraphicsIntegerArrayName::MaxViewportDimensions:
		*(params)=mMaxViewportDimensions.Width;
		*(params+1)=mMaxViewportDimensions.Height;
		break;
	case GraphicsIntegerArrayName::ScissorBox:
		*(params)=mScissorBox.Origin.X;
		*(params+1)=mScissorBox.Origin.Y;
		*(params+2)=mScissorBox.Size.Width;
		*(params+3)=mScissorBox.Size.Height;
		break;
	case GraphicsIntegerArrayName::Viewport:
		*(params)=mViewport.Origin.X;
		*(params+1)=mViewport.Origin.Y;
		*(params+2)=mViewport.Size.Width;
		*(params+3)=mViewport.Size.Height;
		break;
	default:
		Log::AssertFailedFormat("Invalid GraphicsIntegerArrayName:{}",name);
		break;
	}


#else
	TryGetIntegerArray(name,params);
#endif
}

bool IRender::GetBoolean( GraphicsBooleanName name ) const
{
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	switch (name)
	{
	case GraphicsBooleanName::Blend:return mBlendEnabled;
	case GraphicsBooleanName::CullFace:return mCullFaceEnabled;
	case GraphicsBooleanName::DepthTest:return mDepthTestEnabled;
	case GraphicsBooleanName::ScissorTest:return mScissorTestEnabled;
	case GraphicsBooleanName::StencilTest:return mStencilTestEnabled;
	case GraphicsBooleanName::DepthWritable:return mDepthWritableEnabled;
	case GraphicsBooleanName::Dither:return mDitherEnabled;
	case GraphicsBooleanName::PolygonOffsetFill:return mPolygonOffsetFillEnabled;
	case GraphicsBooleanName::SampleAlphaToCoverage:return mSampleAlphaToCoverageEnabled;
	case GraphicsBooleanName::SampleCoverage:return mSampleCoverageEnabled;
	case GraphicsBooleanName::SampleCoverageInvert:return mSampleCoverageInvertEnabled;
	case GraphicsBooleanName::HasShaderCompiler:return mHasShaderCompilerEnabled;
	default:
		Log::AssertFailedFormat("Invalid GraphicsBooleanName:{}",name);
		break;
	}

	return false;
#else
	bool outVal;
	TryGetBoolean(name,outVal);
	return outVal;
#endif

}

void IRender::GetBooleanArray( GraphicsBooleanArrayName name,bool* params ) const
{
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	switch (name)
	{
	case GraphicsBooleanArrayName::ColorWriteMask:
		*(params)=  MEDUSA_FLAG_HAS(mColorWriteMask,GraphicsColorMask::R);
		*(params+1)=MEDUSA_FLAG_HAS(mColorWriteMask,GraphicsColorMask::G);
		*(params+2)=MEDUSA_FLAG_HAS(mColorWriteMask,GraphicsColorMask::B);
		*(params+3)=MEDUSA_FLAG_HAS(mColorWriteMask,GraphicsColorMask::A);
		break;
	default:
		Log::AssertFailedFormat("Invalid GraphicsBooleanArrayName:{}",name);
		break;
	}

#else
	TryGetBooleanArray(name,params);
#endif
	
}

float IRender::GetFloat( GraphicsFloatName name ) const
{
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	switch (name)
	{
	case GraphicsFloatName::DepthClearValue:return mDepthClearValue;
	case GraphicsFloatName::LineWidth:return mLineWidth;
	case GraphicsFloatName::PolygonOffsetFactor:return mPolygonOffsetFactor;
	case GraphicsFloatName::PolygonOffsetUnit:return mPolygonOffsetUnit;
	case GraphicsFloatName::SampleCoverage:return mSampleCoverage;
	default:
		Log::AssertFailedFormat("Invalid GraphicsFloatName:{}",name);
		break;
	}

	return 0.f;
#else
	float outVal=0.f;
	TryGetFloat(name,outVal);
	return outVal;
#endif

	
}

void IRender::GetFloatArray( GraphicsFloatArrayName name,float* params ) const
{
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED

	switch (name)
	{
	case GraphicsFloatArrayName::BlendColor:
		*(params)=mBlendColor.R;
		*(params+1)=mBlendColor.G;
		*(params+2)=mBlendColor.B;
		*(params+3)=mBlendColor.A;
		break;
	case GraphicsFloatArrayName::ClearColor:
		*(params)=mClearColor.R;
		*(params+1)=mClearColor.G;
		*(params+2)=mClearColor.B;
		*(params+3)=mClearColor.A;
		break;
	case GraphicsFloatArrayName::DepthRange:
		*(params)=mDepthRange.Min;
		*(params+1)=mDepthRange.Max;
		break;
	default:
		Log::AssertFailedFormat("Invalid GraphicsFloatArrayName:{}",name);
		break;
	}

#else
	TryGetFloatArray(name,params);
#endif
}


StringRef IRender::GetString( GraphicsStringName name )const
{
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	switch (name)
	{
	case GraphicsStringName::Vendor:return mVendor;
	case GraphicsStringName::Renderer:return mRenderer;
	case GraphicsStringName::Version:return mVersion;
	case GraphicsStringName::ShaderLanguageVersion:return mShaderLanguageVersion;
	case GraphicsStringName::Extensions:return mExtensions;
	default:
		Log::AssertFailedFormat("Invalid GraphicsStringName:{}",name);
		break;
	}

	return StringRef::Empty;
#else
	StringRef outVal;
	TryGetString(name,outVal);
	return outVal;
#endif

	
}


void IRender::DrawRect( const Rect2F& rect,ShaderAttribute* vertexArray )
{
	Array<Point2F,4> points;
	GeometryFactory::CreateRect(rect,points);

	vertexArray->SetPointer(Point2F::Size,GraphicsDataType::Float,false,0,points.Items());
	DrawTrianglesFan(static_cast<uint32>(points.Count()));
	vertexArray->Invalidate();

}

void IRender::DrawTextureRect( const Rect2F& rect,const Rect2F& textureRect,ShaderAttribute* vertexArray,ShaderAttribute* texCoordArray )
{

	Array<Point2F,4>  points;
	GeometryFactory::CreateRect(rect,points);
	vertexArray->SetPointer(Point2F::Size,GraphicsDataType::Float,false,0,points.Items());

	Array<Point2F,4>  points2;
	GeometryFactory::CreateRect(textureRect,points2);
	texCoordArray->SetPointer(Point2F::Size,GraphicsDataType::Float,false,0,points2.Items());

	DrawTrianglesFan(static_cast<uint32>(points.Count()));

	vertexArray->Invalidate();
	texCoordArray->Invalidate();

}

uint IRender::GenBuffer() const
{
	uint result;
	GenBuffers(1,&result);
	AssertSuccess();
	return result;
}

uint IRender::GenTexture()
{
	uint result;
    BindTexture(GraphicsTextureType::Texture2D, 0);
	GenTextures(1,&result);
    BindTexture(GraphicsTextureType::Texture2D, result);
    BindTexture(GraphicsTextureType::Texture2D, 0);
	AssertSuccess();
	return result;
}

uint IRender::GenFrameBuffer() const
{
	uint result;
	GenFrameBuffers(1,&result);
	AssertSuccess();
	return result;
}

uint IRender::GenRenderBuffer() const
{
	uint result;
	GenRenderBuffers(1,&result);
	AssertSuccess();
	return result;
}

void IRender::DeleteBuffer(uint bufferObject) const
{
	DeleteBuffers(1,&bufferObject);
}

void IRender::DeleteFrameBuffer(uint frameBufferObject)
{
	DeleteFrameBuffers(1,&frameBufferObject);
}

void IRender::DeleteRenderBuffer(uint renderBufferObject)
{
	DeleteRenderBuffers(1,&renderBufferObject);
}

void IRender::DeleteTexture(uint texture)
{
	DeleteTextures(1,&texture);
}


#pragma endregion Easy

MEDUSA_END;
