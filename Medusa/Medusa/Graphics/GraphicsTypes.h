// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"

MEDUSA_BEGIN;

#if MEDUSA_IS_OPENGL==1

#ifdef MEDUSA_IOS

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

#include <OpenGLES/ES3/gl.h>
#include <OpenGLES/ES3/glext.h>
#include <OpenGLES/gltypes.h>

#elif defined(MEDUSA_ANDROID)
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>
#include <EGL/egl.h>
//#include <KHR/khrplatform.h>
#elif defined(MEDUSA_WINDOWS)

#ifdef MEDUSA_GLEW
#define GLEW_STATIC
#include "Lib/win/GLEW/glew.h"

#endif

#ifdef MEDUSA_GLES
#include "Lib/win/OGLES/EGL/egl.h"
//#include "Lib/win/OGLES/KHR/khrplatform.h"

#include "Lib/win/OGLES/GLES3/gl3.h"
#include "Lib/win/OGLES/GLES3/gl3ext.h"
#include "Lib/win/OGLES/GLES3/gl3platform.h"

#endif

#endif


/* GL_IMG_texture_compression_pvrtc */
#ifndef GL_IMG_texture_compression_pvrtc
#define GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG			0x8C00
#define GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG			0x8C01
#define GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG			0x8C02
#define GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG			0x8C03
#endif

#ifndef GL_IMG_texture_compression_pvrtc2
#define GL_COMPRESSED_RGBA_PVRTC_2BPPV2_IMG			0x9137
#define GL_COMPRESSED_RGBA_PVRTC_4BPPV2_IMG			0x9138
#endif

#ifndef GL_OES_compressed_ETC1_RGB8_texture
#define GL_ETC1_RGB8_OES                                        0x8D64
#endif

#ifndef GL_OES_texture_half_float
#define GL_HALF_FLOAT_OES                                       0x8D61
#endif

#ifndef GL_IMG_shader_binary
#define GL_SGX_BINARY_IMG                                       0x8C0A
#endif

#ifndef GL_BGRA
#define GL_BGRA 0x80E1
#endif


enum class GraphicsFeatures
{
	Blend = GL_BLEND,
	CullFace = GL_CULL_FACE,
	DepthTest = GL_DEPTH_TEST,
	ScissorTest = GL_SCISSOR_TEST,
	StencilTest = GL_STENCIL_TEST,
	DepthWritable = GL_DEPTH_WRITEMASK,
	Dither = GL_DITHER,
	PolygonOffsetFill = GL_POLYGON_OFFSET_FILL,
	SampleAlphaToCoverage = GL_SAMPLE_ALPHA_TO_COVERAGE,
	SampleCoverage = GL_SAMPLE_COVERAGE,
};


enum class GraphicsFrameBufferType { FrameBuffer = GL_FRAMEBUFFER, RenderBuffer = GL_RENDERBUFFER, ReadFrameBuffer = GL_READ_FRAMEBUFFER, DrawFrameBuffer = GL_DRAW_FRAMEBUFFER };

enum class GraphicsFrameBufferAttachmentParameter
{
	ObjectType = GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE,
	ObjectName = GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME,
	TextureLevel = GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL,
	TextureCubeMapFace = GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE
};


enum class GraphicsRenderBufferParameter
{
	Width = GL_RENDERBUFFER_WIDTH,
	Height = GL_RENDERBUFFER_HEIGHT,
	InternalFormat = GL_RENDERBUFFER_INTERNAL_FORMAT,
	RedSize = GL_RENDERBUFFER_RED_SIZE,
	GreenSize = GL_RENDERBUFFER_GREEN_SIZE,
	BlueSize = GL_RENDERBUFFER_BLUE_SIZE,
	AlphaSize = GL_RENDERBUFFER_ALPHA_SIZE,
	DepthSize = GL_RENDERBUFFER_DEPTH_SIZE,
	StencilSize = GL_RENDERBUFFER_STENCIL_SIZE
};

enum class GraphicsBufferParameter { BufferSize = GL_BUFFER_SIZE, BufferUsage = GL_BUFFER_USAGE };

enum class GraphicsBufferType
{
	Array = GL_ARRAY_BUFFER,
	Elements = GL_ELEMENT_ARRAY_BUFFER,
	CopyRead = GL_COPY_READ_BUFFER,
	CopyWrite = GL_COPY_WRITE_BUFFER,
	PixelPack = GL_PIXEL_PACK_BUFFER,
	PixelUnpack = GL_PIXEL_UNPACK_BUFFER,
	TransformFeedback = GL_TRANSFORM_FEEDBACK_BUFFER,
	Uniform = GL_UNIFORM_BUFFER
};


enum class GraphicsTextureType { Texture2D = GL_TEXTURE_2D, TextureCubeMap = GL_TEXTURE_CUBE_MAP };

enum class GraphicsTextureTarget
{
	Texture2D = GL_TEXTURE_2D,
	TextureCubeMapPositiveX = GL_TEXTURE_CUBE_MAP_POSITIVE_X,
	TextureCubeMapPositiveY = GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
	TextureCubeMapPositiveZ = GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
	TextureCubeMapNegativeX = GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
	TextureCubeMapNegativeY = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
	TextureCubeMapNegativeZ = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
};

enum class GraphicsBlendSrcFunc
{
	Zero = GL_ZERO,
	One = GL_ONE,
	SrcColor = GL_SRC_COLOR,
	OneMinusSrcColor = GL_ONE_MINUS_SRC_COLOR,
	DestColor = GL_DST_COLOR,
	OneMinusDestColor = GL_ONE_MINUS_DST_COLOR,
	SrcAlpha = GL_SRC_ALPHA,
	OneMinusSrcAlpha = GL_ONE_MINUS_SRC_ALPHA,
	DestAlpha = GL_DST_ALPHA,
	OneMinusDestAlpha = GL_ONE_MINUS_DST_ALPHA,
	ConstantColor = GL_CONSTANT_COLOR,
	OneMinusConstantColor = GL_ONE_MINUS_CONSTANT_COLOR,
	ConstantAlpha = GL_CONSTANT_ALPHA,
	OneMinusConstantAlpha = GL_ONE_MINUS_CONSTANT_ALPHA,
	SrcAlphaSaturate = GL_SRC_ALPHA_SATURATE
};

enum class GraphicsBlendDestFunc
{
	Zero = GL_ZERO,
	One = GL_ONE,
	SrcColor = GL_SRC_COLOR,
	OneMinusSrcColor = GL_ONE_MINUS_SRC_COLOR,
	DestColor = GL_DST_COLOR,
	OneMinusDestColor = GL_ONE_MINUS_DST_COLOR,
	SrcAlpha = GL_SRC_ALPHA,
	OneMinusSrcAlpha = GL_ONE_MINUS_SRC_ALPHA,
	DestAlpha = GL_DST_ALPHA,
	OneMinusDestAlpha = GL_ONE_MINUS_DST_ALPHA,
	ConstantColor = GL_CONSTANT_COLOR,
	OneMinusConstantColor = GL_ONE_MINUS_CONSTANT_COLOR,
	ConstantAlpha = GL_CONSTANT_ALPHA,
	OneMinusConstantAlpha = GL_ONE_MINUS_CONSTANT_ALPHA,
};



enum class GraphicsFrameBufferStatus
{
	Completed = GL_FRAMEBUFFER_COMPLETE,
	IncompleteAttachment = GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT,
	IncompleteDimensions = 0x8CD9,//GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT or //GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS
	IncompleteMissingAttachment = GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT,
	Unsupported = GL_FRAMEBUFFER_UNSUPPORTED
};



enum class GraphicsAttachment
{
	Color = GL_COLOR_ATTACHMENT0,
	Depth = GL_DEPTH_ATTACHMENT,
	Stencil = GL_STENCIL_ATTACHMENT,
	DepthStencil = GL_DEPTH_STENCIL_ATTACHMENT
};

enum class GraphicsTextureParameter
{
	MinFilter = GL_TEXTURE_MIN_FILTER,
	MagFilter = GL_TEXTURE_MAG_FILTER,
	WrapS = GL_TEXTURE_WRAP_S,
	WrapT = GL_TEXTURE_WRAP_T
};

enum class GraphicsTextureMagFilter { Nearest = GL_NEAREST, Linear = GL_LINEAR };

enum class GraphicsTextureMinFilter
{
	Nearest = GL_NEAREST,
	Linear = GL_LINEAR,
	NearestMipMapNearest = GL_NEAREST_MIPMAP_NEAREST,
	LinearMipMapNearest = GL_LINEAR_MIPMAP_NEAREST,
	NearestMipMapLinear = GL_NEAREST_MIPMAP_LINEAR,
	LinearMipMapLinear = GL_LINEAR_MIPMAP_LINEAR
};

enum class GraphicsTextureWrapMode
{
	Repeat = GL_REPEAT,
	ClampToEdge = GL_CLAMP_TO_EDGE,
	MirroedRepeat = GL_MIRRORED_REPEAT
};


enum class GraphicsRenderBufferInternalFormat
{
	None=0,
	//color
	RGBA8 = 0x8058,	//GL_RGBA8 or GL_RGBA8_OES
	RGBA4 = GL_RGBA4,
	RGB565 = GL_RGB565,
	RGB5_A1 = GL_RGB5_A1,

	//depth
	DepthComponent16 = GL_DEPTH_COMPONENT16,
	DepthComponent24 = GL_DEPTH_COMPONENT24,
	DepthComponent32 = GL_DEPTH_COMPONENT32F,

	//stencil
	StencilIndex8 = GL_STENCIL_INDEX8,

	//depth combine stencil
	Depth24AndStencil8 = GL_DEPTH24_STENCIL8,	//will alloc depth and stencil too
	Depth32AndStencil8 = GL_DEPTH32F_STENCIL8,	//will alloc depth and stencil too

};


/*
Specifies the number of color components in the texture.
*/
enum class GraphicsInternalFormat
{
	Alpha = GL_ALPHA,
	RGB = GL_RGB,
	RGBA = GL_RGBA,
	Luminance = GL_LUMINANCE,
	LuminanceAlpha = GL_LUMINANCE_ALPHA,
	Compressed_RGB_PVRTC_4BPPV1_IMG = GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG,
	Compressed_RGB_PVRTC_2BPPV1_IMG = GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG,
	Compressed_RGBA_PVRTC_2BPPV1_IMG = GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG,
	Compressed_RGBA_PVRTC_4BPPV1_IMG = GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG,
	Compressed_RGBA_PVRTC_2BPPV2_IMG = GL_COMPRESSED_RGBA_PVRTC_2BPPV2_IMG,
	Compressed_RGBA_PVRTC_4BPPV2_IMG = GL_COMPRESSED_RGBA_PVRTC_4BPPV2_IMG,
	Compressed_ETC1_RGB8_OES = GL_ETC1_RGB8_OES,	//for iphone
	BGRA = GL_BGRA,
	DepthComponent = GL_DEPTH_COMPONENT,
};


//Specifies the format of the pixel data.
//enum class GraphicsPixelFormat
//{
//	RGB=GL_RGB,
//	RGBA=GL_RGBA,
//	Alpha=GL_ALPHA,
//	Luminance=GL_LUMINANCE,
//	LuminanceAlpha=GL_LUMINANCE_ALPHA,
//	BGRA=GL_BGRA,
//	DepthComponent=GL_DEPTH_COMPONENT
//};

enum class GraphicsPixelFormat
{
	RGB = GL_RGB,
	RGBA = GL_RGBA,
	Alpha = GL_ALPHA,
	Luminance = GL_LUMINANCE,
	LuminanceAlpha = GL_LUMINANCE_ALPHA,
	BGRA = GL_BGRA,
	DepthComponent = GL_DEPTH_COMPONENT
};


enum class GraphicsBufferUsage
{
	DynamicDraw = GL_DYNAMIC_DRAW,
	StaticDraw = GL_STATIC_DRAW,
	StreamDraw = GL_STREAM_DRAW
};

enum class GraphicsDrawMode
{
	Points = GL_POINTS,
	Lines = GL_LINES,
	LineLoop = GL_LINE_LOOP,
	LineStrip = GL_LINE_STRIP,
	Triangles = GL_TRIANGLES,
	TriangleStrip = GL_TRIANGLE_STRIP,
	TriangleFan = GL_TRIANGLE_FAN,
	Count = 7
};

enum class GraphicsDataType
{
	Char = GL_BYTE,
	Byte = GL_UNSIGNED_BYTE,
	Short = GL_SHORT,
	UShort = GL_UNSIGNED_SHORT,
	Int = GL_INT,
	UInt = GL_UNSIGNED_INT,
	Float = GL_FLOAT,
	Fixed = GL_FIXED
};

enum class GraphicsIntegerDataType
{
	Char = GL_BYTE,
	Byte = GL_UNSIGNED_BYTE,
	Short = GL_SHORT,
	UShort = GL_UNSIGNED_SHORT,
	Int = GL_INT,
	UInt = GL_UNSIGNED_INT
};



enum class GraphicsErrorCode
{
	Success = GL_NO_ERROR,
	InvalidEnum = GL_INVALID_ENUM,
	InvalidValue = GL_INVALID_VALUE,
	InvalidOperation = GL_INVALID_OPERATION,
	InvalidFrameBufferOperation = GL_INVALID_FRAMEBUFFER_OPERATION,
	OutOfMemory = GL_OUT_OF_MEMORY
};




enum class GraphicsShaderType { VertexShader = GL_VERTEX_SHADER, PixelShader = GL_FRAGMENT_SHADER };

enum class GraphicsShaderPrecisionType
{
	LowFloat = GL_LOW_FLOAT,
	MediumFloat = GL_MEDIUM_FLOAT,
	HighFloat = GL_HIGH_FLOAT,
	LowInt = GL_LOW_INT,
	MediumInt = GL_MEDIUM_INT,
	HighInt = GL_HIGH_INT
};


enum class GraphicsProgramStatus
{
	DeleteStatus = GL_DELETE_STATUS,
	CompileStatus = GL_COMPILE_STATUS,
	InfoLogLength = GL_INFO_LOG_LENGTH,
	LinkStatus = GL_LINK_STATUS,
	ValidateStatus = GL_VALIDATE_STATUS,
	AttachedShaderCount = GL_ATTACHED_SHADERS,
	ActiveAttributeCount = GL_ACTIVE_ATTRIBUTES,
	MaxActiveAttributeNameLength = GL_ACTIVE_ATTRIBUTE_MAX_LENGTH,
	ActiveUniformCount = GL_ACTIVE_UNIFORMS,
	MaxActiveUniformNameLength = GL_ACTIVE_UNIFORM_MAX_LENGTH
};


enum class GraphicsShaderStatus
{
	ShaderType = GL_SHADER_TYPE,
	DeleteStatus = GL_DELETE_STATUS,
	CompileStatus = GL_COMPILE_STATUS,
	InfoLogLength = GL_INFO_LOG_LENGTH,
	LinkStatus = GL_LINK_STATUS,
	ValidateStatus = GL_SHADER_SOURCE_LENGTH
};




enum class GraphicsVertexAttributeParameter
{
	ArrayBufferBinding = GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING,
	ArrayEnabled = GL_VERTEX_ATTRIB_ARRAY_ENABLED,
	ArraySize = GL_VERTEX_ATTRIB_ARRAY_SIZE,
	ArrayStride = GL_VERTEX_ATTRIB_ARRAY_STRIDE,
	ArrayDataType = GL_VERTEX_ATTRIB_ARRAY_TYPE,
	NormalizeEnabled = GL_VERTEX_ATTRIB_ARRAY_NORMALIZED,
	Integer = GL_VERTEX_ATTRIB_ARRAY_INTEGER,
	Divisor = GL_VERTEX_ATTRIB_ARRAY_DIVISOR,
	CurrentValue = GL_CURRENT_VERTEX_ATTRIB	//return 4 values
};


enum class GraphicsShaderBinaryFormat { SGX = GL_SGX_BINARY_IMG };



enum class GraphicsPixelStoreParameter
{
	PackAlignment = GL_PACK_ALIGNMENT,
	UnpackAlignment = GL_UNPACK_ALIGNMENT
};


enum class GraphicsTextureUnits
{
	Texture0 = GL_TEXTURE0,
	Texture1 = GL_TEXTURE1,
	Texture2 = GL_TEXTURE2,
	Texture3 = GL_TEXTURE3,
	Texture4 = GL_TEXTURE4,
	Texture5 = GL_TEXTURE5,
	Texture6 = GL_TEXTURE6,
	Texture7 = GL_TEXTURE7,
	Texture8 = GL_TEXTURE8,
	Texture9 = GL_TEXTURE9,
	Texture10 = GL_TEXTURE10,
	Texture11 = GL_TEXTURE11,
	Texture12 = GL_TEXTURE12,
	Texture13 = GL_TEXTURE13,
	Texture14 = GL_TEXTURE14,
	Texture15 = GL_TEXTURE15,
	Texture16 = GL_TEXTURE16,
	Texture17 = GL_TEXTURE17,
	Texture18 = GL_TEXTURE18,
	Texture19 = GL_TEXTURE19,
	Texture20 = GL_TEXTURE20,
	Texture21 = GL_TEXTURE21,
	Texture22 = GL_TEXTURE22,
	Texture23 = GL_TEXTURE23,
	Texture24 = GL_TEXTURE24,
	Texture25 = GL_TEXTURE25,
	Texture26 = GL_TEXTURE26,
	Texture27 = GL_TEXTURE27,
	Texture28 = GL_TEXTURE28,
	Texture29 = GL_TEXTURE29,
	Texture30 = GL_TEXTURE30,
	Texture31 = GL_TEXTURE31,
	Size = GL_TEXTURE31 - GL_TEXTURE0 + 1,
};

enum class GraphicsUniformDataType
{
	Float = GL_FLOAT,
	FloatVec2 = GL_FLOAT_VEC2,
	FloatVec3 = GL_FLOAT_VEC3,
	FloatVec4 = GL_FLOAT_VEC4,
	Int = GL_INT,
	IntVec2 = GL_INT_VEC2,
	IntVec3 = GL_INT_VEC3,
	IntVec4 = GL_INT_VEC4,
	Bool = GL_BOOL,
	BoolVec2 = GL_BOOL_VEC2,
	BoolVec3 = GL_BOOL_VEC3,
	BoolVec4 = GL_BOOL_VEC4,
	FloatMat2 = GL_FLOAT_MAT2,
	FloatMat3 = GL_FLOAT_MAT3,
	FloatMat4 = GL_FLOAT_MAT4,
	Sampler2D = GL_SAMPLER_2D,
	SamplerCube = GL_SAMPLER_CUBE,
};

enum class GraphicsAttributeDataType
{
	Float = GL_FLOAT,
	FloatVec2 = GL_FLOAT_VEC2,
	FloatVec3 = GL_FLOAT_VEC3,
	FloatVec4 = GL_FLOAT_VEC4,
	FloatMat2 = GL_FLOAT_MAT2,
	FloatMat3 = GL_FLOAT_MAT3,
	FloatMat4 = GL_FLOAT_MAT4,
};


enum class GraphicsBooleanName
{
	Blend = GL_BLEND,
	CullFace = GL_CULL_FACE,
	DepthTest = GL_DEPTH_TEST,
	ScissorTest = GL_SCISSOR_TEST,
	StencilTest = GL_STENCIL_TEST,
	DepthWritable = GL_DEPTH_WRITEMASK,
	Dither = GL_DITHER,
	PolygonOffsetFill = GL_POLYGON_OFFSET_FILL,
	SampleAlphaToCoverage = GL_SAMPLE_ALPHA_TO_COVERAGE,
	SampleCoverage = GL_SAMPLE_COVERAGE,
	SampleCoverageInvert = GL_SAMPLE_COVERAGE_INVERT,
	HasShaderCompiler = GL_SHADER_COMPILER,
};

enum class GraphicsBooleanArrayName
{
	ColorWriteMask = GL_COLOR_WRITEMASK,
};

enum class GraphicsIntegerName
{
	ActiveTexture = GL_ACTIVE_TEXTURE,
	AlphaBits = GL_ALPHA_BITS,
	BlueBits = GL_BLUE_BITS,
	GreenBits = GL_GREEN_BITS,
	RedBits = GL_RED_BITS,
	DepthBits = GL_DEPTH_BITS,
	StencilBits = GL_STENCIL_BITS,
	SubPixelBits = GL_SUBPIXEL_BITS,
	ArrayBufferBinding = GL_ARRAY_BUFFER_BINDING,
	ElementArrayBufferBinding = GL_ELEMENT_ARRAY_BUFFER_BINDING,
	FrameBufferBinding = GL_FRAMEBUFFER_BINDING,
	RenderBufferBinding = GL_RENDERBUFFER_BINDING,
	BlendDestAlphaFunc = GL_BLEND_DST_ALPHA,
	BlendDestRGBFunc = GL_BLEND_DST_RGB,
	BlendAlphaEquation = GL_BLEND_EQUATION_ALPHA,
	BlendRGBEquation = GL_BLEND_EQUATION_RGB,
	BlendSrcAlphaFunc = GL_BLEND_SRC_ALPHA,
	BlendSrcRGBFunc = GL_BLEND_SRC_RGB,
	CullFaceMode = GL_CULL_FACE_MODE,
	CurrentProgram = GL_CURRENT_PROGRAM,
	DepthFunc = GL_DEPTH_FUNC,
	FrontFace = GL_FRONT_FACE,
	GenerateMipmapHint = GL_GENERATE_MIPMAP_HINT,
	ImplementionColorReadFormat = GL_IMPLEMENTATION_COLOR_READ_FORMAT,
	ImplementionColorReadType = GL_IMPLEMENTATION_COLOR_READ_TYPE,
	MaxCombinedTextureUnitCount = GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,	//>=8,glActiveTexture
	MaxTextureUnitCount = GL_MAX_TEXTURE_IMAGE_UNITS,	//>=8,glActiveTexture
	MaxVertexTextureUnitCount = GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS,	//>=8,glActiveTexture
	MaxCubeMapTextureSize = GL_MAX_CUBE_MAP_TEXTURE_SIZE,
	MaxFragmentUniformCount = GL_MAX_FRAGMENT_UNIFORM_VECTORS,	//>=16
	MaxVaryingCount = GL_MAX_VARYING_VECTORS,	//>=8
	MaxVetextAttributeCount = GL_MAX_VERTEX_ATTRIBS,	//>=8
	MaxRenderBufferSize = GL_MAX_RENDERBUFFER_SIZE,
	MaxTextureSize = GL_MAX_TEXTURE_SIZE,	//>=64
	MaxVertexUnifromCount = GL_MAX_VERTEX_UNIFORM_VECTORS,	//>=128
	CompressedTextureFormatCount = GL_NUM_COMPRESSED_TEXTURE_FORMATS,
	ShaderBinaryFormatCount = GL_NUM_SHADER_BINARY_FORMATS,
	ProgramBinaryFormatCount = GL_NUM_PROGRAM_BINARY_FORMATS,	//GL_ARB_get_program_binary 
	PackAlignment = GL_PACK_ALIGNMENT,
	UnpackAlignment = GL_UNPACK_ALIGNMENT,
	SampleBufferCount = GL_SAMPLE_BUFFERS,
	SampleCoverageMaskSize = GL_SAMPLES,
	StencilBackFailOperation = GL_STENCIL_BACK_FAIL,
	StencilBackFunc = GL_STENCIL_BACK_FUNC,
	StencilBackPassDepthFailOperation = GL_STENCIL_BACK_PASS_DEPTH_FAIL,
	StencilBackPassDepthPassOperation = GL_STENCIL_BACK_PASS_DEPTH_PASS,
	StencilBackRefValue = GL_STENCIL_BACK_REF,
	StencilBackValueMask = GL_STENCIL_BACK_VALUE_MASK,
	StencilBackWriteMask = GL_STENCIL_BACK_WRITEMASK,
	StencilClearValue = GL_STENCIL_CLEAR_VALUE,
	StencilFailOperation = GL_STENCIL_FAIL,
	StencilFunc = GL_STENCIL_FUNC,
	StencilPassDepthFailOperation = GL_STENCIL_PASS_DEPTH_FAIL,
	StencilPassDepthPassOperation = GL_STENCIL_PASS_DEPTH_PASS,
	StencilRefValue = GL_STENCIL_REF,
	StencilValueMask = GL_STENCIL_VALUE_MASK,
	StencilWriteMask = GL_STENCIL_WRITEMASK,
	TextureBinding = GL_TEXTURE_BINDING_2D,
	CubeMapTextureBinding = GL_TEXTURE_BINDING_CUBE_MAP,

};

enum class GraphicsIntegerArrayName
{
	AliasedLineWidthRange = GL_ALIASED_LINE_WIDTH_RANGE,
	AliasedPointSizeRange = GL_ALIASED_POINT_SIZE_RANGE,
	CompressedTextureFormats = GL_COMPRESSED_TEXTURE_FORMATS,

	ShaderBinaryFormats = GL_SHADER_BINARY_FORMATS,

	ProgramBinaryFormats = GL_PROGRAM_BINARY_FORMATS,	//GL_ARB_get_program_binary

	MaxViewportDimensions = GL_MAX_VIEWPORT_DIMS,
	ScissorBox = GL_SCISSOR_BOX,
	Viewport = GL_VIEWPORT,
};

enum class GraphicsFloatName :uint
{
	DepthClearValue = GL_DEPTH_CLEAR_VALUE,
	LineWidth = GL_LINE_WIDTH,
	PolygonOffsetFactor = GL_POLYGON_OFFSET_FACTOR,
	PolygonOffsetUnit = GL_POLYGON_OFFSET_UNITS,
	SampleCoverage = GL_SAMPLE_COVERAGE_VALUE,
};

enum class GraphicsFloatArrayName :uint
{
	BlendColor = GL_BLEND_COLOR,
	ClearColor = GL_COLOR_CLEAR_VALUE,
	DepthRange = GL_DEPTH_RANGE,

};

enum class GraphicsStringName :uint
{
	Vendor = GL_VENDOR,
	Renderer = GL_RENDERER,
	Version = GL_VERSION,
	ShaderLanguageVersion = GL_SHADING_LANGUAGE_VERSION,
	Extensions = GL_EXTENSIONS,
};



enum class GraphicsLightType { Point, Directional, Spot };

#pragma region OpenGL ES 3.0

enum class GraphicsColorBuffers :uint
{
	None = GL_NONE,
	Back = GL_BACK,
	Color = GL_COLOR_ATTACHMENT0,
};


enum class GraphicsQueryTarget :uint
{
	AnySamplesPassed = GL_ANY_SAMPLES_PASSED,
	AnySamplesPassedConservative = GL_ANY_SAMPLES_PASSED_CONSERVATIVE,
	TransformFeedbackPrimitivesWritten = GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN,
};

enum class GraphicsQueryParameter { CurrentQuery = GL_CURRENT_QUERY };

enum class GraphicsQueryObjectParameter { QueryResult = GL_QUERY_RESULT, IsQueryResultAvailable = GL_QUERY_RESULT_AVAILABLE };



enum class GraphicsBufferPointerName { MapPointer = GL_BUFFER_MAP_POINTER };


enum class GraphicsTransformFeedbackPrimitiveMode
{
	Points = GL_POINTS,
	Lines = GL_LINES,
	Triangles = GL_TRIANGLES
};

enum class GraphicsBindBufferTarget { TransformFeedback = GL_TRANSFORM_FEEDBACK_BUFFER, Uniform = GL_UNIFORM_BUFFER };

enum class GraphicsTransformFeedbackBufferMode { Interleaved = GL_INTERLEAVED_ATTRIBS, Separate = GL_SEPARATE_ATTRIBS };

enum class GraphicsBufferClearMask
{
	Color = GL_COLOR,
	Depth = GL_DEPTH,
	Stencil = GL_STENCIL,
	DepthStencil = GL_DEPTH_STENCIL
};

enum class GraphicsUniformParameterName
{
	Type = GL_UNIFORM_TYPE,
	UniformSize = GL_UNIFORM_SIZE,
	NameLength = GL_UNIFORM_NAME_LENGTH,
	BlockIndex = GL_UNIFORM_BLOCK_INDEX,
	Offset = GL_UNIFORM_OFFSET,
	ArrayStride = GL_UNIFORM_ARRAY_STRIDE,
	MatrixStride = GL_UNIFORM_MATRIX_STRIDE,
	IsRowMajor = GL_UNIFORM_IS_ROW_MAJOR
};

enum class GraphicsUniformBlockParameterName
{
	Binding = GL_UNIFORM_BLOCK_BINDING,
	DataSize = GL_UNIFORM_BLOCK_DATA_SIZE,
	NameLength = GL_UNIFORM_BLOCK_NAME_LENGTH,
	ActiveUniforms = GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS,
	ActiveIndices = GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES,
	ReferencedByVertexShader = GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER,
	ReferencedByPixelShader = GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER
};

enum class GraphicsSyncCondition { GPUCommandsComplete = GL_SYNC_GPU_COMMANDS_COMPLETE };



enum class GraphicsSyncParameterName
{
	ObjectType = GL_OBJECT_TYPE,
	Status = GL_SYNC_STATUS,
	Condition = GL_SYNC_CONDITION,
	Flags = GL_SYNC_FLAGS
};

enum class GraphicsSamplerParameterName
{
	MagFilter = GL_TEXTURE_MAG_FILTER,
	MinFilter = GL_TEXTURE_MIN_FILTER,
	MinLOD = GL_TEXTURE_MIN_LOD,
	MaxLOD = GL_TEXTURE_MAX_LOD,
	WrapS = GL_TEXTURE_WRAP_S,
	WrapT = GL_TEXTURE_WRAP_T,
	WrapR = GL_TEXTURE_WRAP_R,
	CompareMode = GL_TEXTURE_COMPARE_MODE,
	CompareFunc = GL_TEXTURE_COMPARE_FUNC
};

enum class GraphicsProgramParameterName { RetrievableHint = GL_PROGRAM_BINARY_RETRIEVABLE_HINT };

enum class GraphicsInternalFormatParameterName { SampleCount = GL_NUM_SAMPLE_COUNTS, Samples = GL_SAMPLES };


#pragma endregion OpenGL ES 3.0
#else
#endif

enum class GraphicsAPI
{
	DirectX,
	OpenGLES2,
	OpenGLES3,

#if defined(MEDUSA_WINDOWS)&&defined(MEDUSA_DIRECTX)
	Default = DirectX,
#elif defined(MEDUSA_GLES)
	Default = OpenGLES3,
#endif


};

struct GraphicsSupportAPI
{
#if defined(MEDUSA_WINDOWS)&&defined(MEDUSA_DIRECTX)
	const static bool DirectX = true;
#else
	const static bool DirectX = false;
#endif

#if defined(MEDUSA_ANDROID)||defined(MEDUSA_IOS)||(defined(MEDUSA_WINDOWS)&&!defined(MEDUSA_DIRECTX))
	const static bool OpenGLES2 = true;
	const static bool OpenGLES3 = true;
#else
	const static bool OpenGLES2 = false;
	const static bool OpenGLES3 = false;
#endif

	static bool Support(GraphicsAPI api)
	{
		switch (api)
		{
		case GraphicsAPI::OpenGLES2:
			return OpenGLES2;
		case GraphicsAPI::OpenGLES3:
			return OpenGLES3;
		case GraphicsAPI::DirectX:
			return DirectX;
		default:
			return false;
		}
	}

};

enum class GraphicsContextPixelFormat
{
	RGBA8,
#if defined(MEDUSA_IOS)
	RGB565,
	SRGBA8,
#endif
};

enum class GraphicsPixelConvertMode
{
	Normal = 0,
	Real = 1,
	Alpha = 2,

};


enum class MeshFixType
{
	None = 0,
	ForceToQuad = 1,	//If some vertical or horizontal coordinate turns to not "vertical" or "horizontal"  after rotation because of float precision, this option could fix this
};
//enum class Visibility
//{
//	Visible = 0,	//Display the element.
//	Hidden = 1,		//Do not display the element, but reserve space for the element in layout.
//	Collapsed = 2,	//Do not display the element, and do not reserve space for it in layout.
//};

MEDUSA_END;