// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Graphics/Render/IRender.h"

MEDUSA_BEGIN;
class OpenGLES2Render :public IRender
{
public:
	OpenGLES2Render(void);
	virtual ~OpenGLES2Render(void);

#pragma region Helpers
public:
	virtual bool Initialize()override;
	virtual void Finish()override;
	virtual void Flush()override;
	virtual GraphicsErrorCode GetError()const override;

	virtual void Clear(GraphicsBufferComponentMask clearMasks)const override;

#pragma endregion Helpers


#pragma region Set Values
	virtual void Hint(GraphicsHintMode mode) override;
	virtual void SetClearColor(const Color4F& color) override;
	virtual void SetBlendColor(const Color4F& color) override;

	virtual void SetLineWidth(float width) override;

	virtual void SetViewPort(const Rect2I& rect) override;
	virtual void SetScissorBox(const Rect2I& rect) override;


	virtual void SetBlendFunc(GraphicsBlendSrcFunc srcFactor, GraphicsBlendDestFunc destFactor) override;
	virtual void SetBlendFuncSeparate(GraphicsBlendSrcFunc srcRGBFactor,GraphicsBlendSrcFunc srcAlphaFactor,GraphicsBlendDestFunc destRGBFactor,GraphicsBlendDestFunc destAlphaFactor) override;


	virtual void SetBlendEquation(GraphicsBlendEquation equation) override;
	virtual void SetBlendEquationSeparate(GraphicsBlendEquation rgbEquation,GraphicsBlendEquation alphaEquation) override;

	virtual void SetFrontFace(GraphicsFrontFace frontFace) override;
	virtual void SetDepthRange(const RangeF& depthRange) override;
	virtual void SetDepthFunc(GraphicsFuncType func) override;
	virtual void SetClearDepth(float depth) override;
	virtual void SetStencilClearValue(int val) override;
	virtual void SetColorMask(GraphicsColorMask colorMask) override;

	virtual GraphicsFrameBufferStatus CheckFrameBufferStatus()const override;

	virtual void SetPixelStore(GraphicsPixelStoreParameter parameter,int val) override;
	virtual void SetPolygonOffset(float scaleFactor,float unit) override;
	virtual void SetSampleCoverage(float val,bool isInvert) override;	//0-1
	virtual void SetStencilFunc(GraphicsFuncType func,int refValue,uint readMask) override;
	virtual void SetStencilFuncSeparate(GraphicsFace face,GraphicsFuncType func,int refValue,uint readMask) override;
	virtual void SetStencilWriteMask(uint mask) override;
	virtual void SetStencilWriteMaskSeparate(GraphicsFace face,uint mask) override;
	virtual void SetStencilOperation(GraphicsStencilOperation testFail,GraphicsStencilOperation testPassDepthFail,GraphicsStencilOperation testPassDepthPass) override;
	virtual void SetStencilOperationSeparate(GraphicsFace face,GraphicsStencilOperation testFail,GraphicsStencilOperation testPassDepthFail,GraphicsStencilOperation testPassDepthPass) override;
protected:
	virtual bool TryGetInteger(GraphicsIntegerName name,int& outVal)const override;
	virtual bool TryGetIntegerArray(GraphicsIntegerArrayName name,int* params)const override;
	virtual bool TryGetBoolean(GraphicsBooleanName name,bool& outVal)const override;
	virtual bool TryGetBooleanArray(GraphicsBooleanArrayName name,bool* params)const override;
	virtual bool TryGetFloat(GraphicsFloatName name,float& outVal)const override;
	virtual bool TryGetFloatArray(GraphicsFloatArrayName name,float* params)const override;
	virtual bool TryGetString(GraphicsStringName name,StringRef& outVal)const override;
#pragma endregion Set Values

#pragma region Enable/Disable
public:
	virtual void EnableDepthWrite(bool isEnable) override;
	virtual void CullFace(GraphicsFace face) override;


	virtual void EnableFeature(GraphicsFeatures feature,bool isEnable) override;
	virtual bool IsFeatureEnabled(GraphicsFeatures feature) override;


#pragma endregion Enable/Disable


#pragma region Drawing Primitives
public:
	virtual void DrawArrays(GraphicsDrawMode mode, int first, uint count)const override;
	virtual void DrawIndices(GraphicsDrawMode mode, uint count, GraphicsDataType type, const void* indices)const override;
	virtual void DrawIndices(GraphicsDrawMode mode, const ICollection<ushort>& indices)const override;
	virtual void DrawIndices(GraphicsDrawMode mode, const ICollection<byte>& indices)const override;
	virtual void DrawIndices(GraphicsDrawMode mode, const ICollection<uint>& indices)const override;


	//GL_POINTS
	virtual void DrawPoints(uint pointCount=1)const override;

	//GL_LINES
	virtual void DrawLines(uint pointCount,const ICollection<ushort>* indices=nullptr)const override;

	//GL_LINE_STRIP
	virtual void DrawLinesStrip(uint pointCount,const ICollection<ushort>* indices=nullptr)const override;

	//GL_LINE_LOOP 
	virtual void DrawLinesLoop(uint pointCount,const ICollection<ushort>* indices=nullptr)const override;

	//GL_TRIANGLES
	virtual void DrawTriangles(uint pointCount,const ICollection<ushort>* indices=nullptr)const override;

	//GL_TRIANGLE_STRIP
	virtual void DrawTriangleStrip(uint pointCount,const ICollection<ushort>* indices=nullptr)const override;

	//GL_TRIANGLE_FAN
	virtual void DrawTrianglesFan(uint pointCount,const ICollection<ushort>* indices=nullptr)const override;


#pragma endregion Drawing Primitives

#pragma region Texture Objects
public:
	virtual void GenTextures(uint count,uint* outBuffers) override;

	virtual void DeleteTextures(uint count,uint* textures) override;

	virtual void BindTexture(GraphicsTextureType textureType,uint texture) override;

	virtual void ActivateTexture(GraphicsTextureUnits textureUnit) override;

	virtual void GenerateTextureMipmap(GraphicsTextureType textureType)const override;

	virtual bool IsTexture(uint texture)const override;
	virtual void LoadTexture(GraphicsTextureTarget textureTarget,int level,GraphicsInternalFormat internalformat,const Size2U& size, int border, GraphicsPixelFormat format, GraphicsPixelDataType type, const void *pixels)const override;
	virtual void LoadSubTexture(GraphicsTextureTarget textureTarget,int level,const Rect2I& rect, GraphicsPixelFormat format, GraphicsPixelDataType type, const void *pixels)const override;

	virtual void LoadCompressedTexture(GraphicsTextureTarget textureTarget,int level,GraphicsInternalFormat internalformat, const Size2U& size, int border, uint imageSize, const void *pixels)const override;
	virtual void LoadCompressedSubTexture(GraphicsTextureTarget textureTarget,int level,GraphicsInternalFormat internalformat, const Rect2I& rect,uint imageSize, const void *pixels)const override;
	virtual void CopyTexture(GraphicsTextureTarget textureTarget,int level,GraphicsInternalFormat internalformat, const Rect2I& rect,int border)const override;
	virtual void CopySubTexture(GraphicsTextureTarget textureTarget,int level,const Point2I& offset,const Rect2I& rect)const override;

	virtual void SetTextureMinFilter(GraphicsTextureType textureType,GraphicsTextureMinFilter minFilter) override;
	virtual void SetTextureMagFilter(GraphicsTextureType textureType,GraphicsTextureMagFilter magFilter) override;
	virtual void SetTextureWrapS(GraphicsTextureType textureType,GraphicsTextureWrapMode wrapS) override;
	virtual void SetTextureWrapT(GraphicsTextureType textureType,GraphicsTextureWrapMode wrapT) override;

	virtual int GetTextureParamter(GraphicsTextureType textureType,GraphicsTextureParameter parameter) override;

	protected:
		virtual bool TryGetTextureParamter(GraphicsTextureType textureType,GraphicsTextureParameter parameter,int& outVal) override;
#pragma endregion Texture Objects

#pragma region Buffer Objects
public:
	virtual bool IsBuffer(uint bufferObject)const override;
	virtual bool IsFrameBuffer(uint bufferObject)const override;
	virtual bool IsRenderBuffer(uint bufferObject)const override;

	virtual void GenBuffers(uint count,uint* outBuffers)const override;

	virtual void DeleteBuffers(uint count,uint* buffers)const override;

	virtual void BindBuffer(GraphicsBufferType bufferType,uint bufferObject) override;

	virtual void LoadBufferData(GraphicsBufferType bufferType,uint byteSize,void* data,GraphicsBufferUsage usageType)const override;
	virtual void ModifyBufferSubData(GraphicsBufferType bufferType,int byteOffset, uint byteSize, const void* data)const override;

	virtual void GenFrameBuffers(uint count,uint* outBuffers)const override;
	virtual void GenRenderBuffers(uint count,uint* outBuffers)const override;

	virtual void BindFrameBuffer(uint frameBufferObject) override;
	virtual void BindRenderBuffer(uint frameBufferObject) override;

	virtual void DeleteFrameBuffers(uint count,uint* buffers) override;
	virtual void DeleteRenderBuffers(uint count,uint* buffers) override;

	virtual void AttachRenderBufferToFrameBuffer(GraphicsAttachment attachment,uint renderBufferObject)const override;
	virtual void AttachTextureToFrameBuffer(GraphicsAttachment attachment,GraphicsTextureTarget textureTarget,uint texture,int level)const override;

	virtual int GetBufferParameter(GraphicsBufferType bufferType,GraphicsBufferParameter parameter)const override;
	virtual int GetFrameBufferAttachmentParameter(GraphicsAttachment attachment,GraphicsFrameBufferAttachmentParameter parameter)const override;
	virtual int GetRenderBufferParameter(GraphicsRenderBufferParameter parameter)const override;
	virtual void ReadPixels(GraphicsPixelFormat format,GraphicsPixelDataType dataType,const Rect2I& rect,void* outData) override;
	virtual void SetRenderBufferStorage(GraphicsRenderBufferInternalFormat format,const Size2U& size) override;
#pragma endregion Buffer Objects

#pragma region Shader
public:
	virtual bool IsShaderBinaryFormatSupported(GraphicsShaderBinaryFormat binaryFormat)const override;
	virtual void EnableVertexAttributeArray(uint index,bool isEnabled) override;

	virtual uint CreateShader(GraphicsShaderType type) override;
	virtual void DeleteShader(uint shader) override;
	virtual void SetShaderSource(uint shader,StringRef source) override;
	virtual void GetShaderSource(uint shader,HeapString& outSource) override;

	virtual void SetShadersBinary(uint count,const uint* shaders,GraphicsShaderBinaryFormat binaryFormat,const void* data,uint length) override;
	virtual void SetShaderBinary(uint shader,GraphicsShaderBinaryFormat binaryFormat,const void* data,uint length) override;


	virtual void CompileShader(uint shader) override;
	virtual void GetShadderInfoLog(uint shader,HeapString& outInfoLog) override;
	virtual bool IsShader(uint shader) override;
	virtual int GetShaderStatus(uint shader,GraphicsShaderStatus name) override;

	virtual uint CreateProgram() override;
	virtual void DeleteProgram(uint program) override;
	virtual void AttachShader(uint program,uint shader) override;
	virtual void DetachShader(uint program,uint shader) override;
	virtual void LinkProgram(uint program) override;
	virtual void GetProgramInfoLog(uint program,HeapString& outInfoLog) override;
	virtual void UseProgram(uint program) override;
	virtual bool IsProgram(uint program) override;
	virtual void ValidateProgram(uint program) override;
	virtual int GetProgramStatus(uint program,GraphicsProgramStatus name) override;

	virtual void BindUniformLocation(uint program,int index,StringRef name) override;	//called before link
	virtual int GetUniformLocation(uint program,StringRef name) override;


	virtual void SetUniform(int location,int x) override;
	virtual void SetUniform(int location,int x,int y) override;
	virtual void SetUniform(int location,int x,int y,int z) override;
	virtual void SetUniform(int location,int x,int y,int z,int w) override;

	virtual void SetUniform(int location,float x) override;
	virtual void SetUniform(int location,float x,float y) override;
	virtual void SetUniform(int location,float x,float y,float z) override;
	virtual void SetUniform(int location,float x,float y,float z,float w) override;

	virtual void SetUniformArray1(int location,uint count,const float* data) override;
	virtual void SetUniformArray2(int location,uint count,const float* data) override;
	virtual void SetUniformArray3(int location,uint count,const float* data) override;
	virtual void SetUniformArray4(int location,uint count,const float* data) override;

	virtual void SetUniformArray1(int location,uint count,const int* data) override;
	virtual void SetUniformArray2(int location,uint count,const int* data) override;
	virtual void SetUniformArray3(int location,uint count,const int* data) override;
	virtual void SetUniformArray4(int location,uint count,const int* data) override;

	virtual void SetUniformMatrix2(int location,uint count,const float* data,bool isTransposed=false) override;
	virtual void SetUniformMatrix3(int location,uint count,const float* data,bool isTransposed=false) override;
	virtual void SetUniformMatrix4(int location,uint count,const float* data,bool isTransposed=false) override;

	virtual void GetUniformArray(uint program,int location,float* outData) override;
	virtual void GetUniformArray(uint program,int location,int* outData) override;

	virtual void SetVertexAttribute(uint index,float x) override;
	virtual void SetVertexAttribute(uint index,const Point2F& pos) override;
	virtual void SetVertexAttribute(uint index,const Point3F& pos) override;
	virtual void SetVertexAttribute(uint index,const Point4F& pos) override;

	virtual void SetVertexAttributeArray1(uint index,const float* data) override;
	virtual void SetVertexAttributeArray2(uint index,const float* data) override;
	virtual void SetVertexAttributeArray3(uint index,const float* data) override;
	virtual void SetVertexAttributeArray4(uint index,const float* data) override;

	virtual int GetVertexAttributeLocation(uint program,StringRef name) override;

	virtual void SetVertexAttributePointer(uint index,uint componentCount,GraphicsDataType type,bool isNormalized,uint stride,const void* data) override;
	virtual void GetVertexAttributePointer(uint index,void** outData) override;

	virtual void GetActiveAttributeName(uint program,uint index,int& outSize,uint& outDataType,HeapString& outName) override;
	virtual void GetActiveUniformName(uint program,uint index,int& outSize,uint& outDataType,HeapString& outName) override;
	virtual void GetAttachedShaders(uint program,uint maxCount,int& outCount,uint* outShaders) override;
	virtual void GetShaderPrecisionFormat(GraphicsShaderType shaderType,GraphicsShaderPrecisionType precesionType,int* outRange,int* outPrecision) override;

	virtual void GetVertexAttributeValue(uint index, GraphicsVertexAttributeParameter parameter, float* outParams) override;
	virtual void GetVertexAttributeValue(uint index, GraphicsVertexAttributeParameter parameter, int* outParams) override;

	virtual void ReleaseShaderCompiler()const override;
#pragma endregion Shader
#pragma region Extension
public:
	virtual bool IsExtensionSupported(StringRef extension)const override;


private:
	void LoadExtensions();
#ifdef MEUDSA_WINDOWS
#ifdef GL_EXT_multi_draw_arrays
	PFNGLMULTIDRAWARRAYSEXTPROC glMultiDrawArraysEXT ;
	PFNGLMULTIDRAWELEMENTSEXTPROC glMultiDrawElementsEXT;
#endif

#ifdef GL_OES_mapbuffer
	PFNGLMAPBUFFEROESPROC glMapBufferOES;
	PFNGLUNMAPBUFFEROESPROC glUnmapBufferOES;
	PFNGLGETBUFFERPOINTERVOESPROC glGetBufferPointervOES;
#endif

#ifdef GL_OES_vertex_array_object
	PFNGLBINDVERTEXARRAYOESPROC glBindVertexArrayOES;
	PFNGLDELETEVERTEXARRAYSOESPROC glDeleteVertexArraysOES;
	PFNGLGENVERTEXARRAYSOESPROC glGenVertexArraysOES;
	PFNGLISVERTEXARRAYOESPROC glIsVertexArrayOES;
#endif

#ifdef GL_IMG_multisampled_render_to_texture
	PFNGLRENDERBUFFERSTORAGEMULTISAMPLEIMGPROC glRenderbufferStorageMultisampleIMG;
	PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEIMGPROC glFramebufferTexture2DMultisampleIMG;
#endif

#if defined(GL_EXT_discard_framebuffer)&&GL_EXT_discard_framebuffer==1
	PFNGLDISCARDFRAMEBUFFEREXTPROC glDiscardFramebufferEXT;
#endif


#endif

#pragma endregion Extension

#pragma region OpenGL ES 3.0
#pragma region Frame buffer
public:
	virtual void ReadBuffer(GraphicsColorBuffers buffer) const override;	//select a color buffer source for pixels
	virtual void SetDrawBufferTargets(uint count, const GraphicsColorBuffers* buffers)const override;	//Specifies a list of color buffers to be drawn into
	virtual void BlitFrameBuffer(const Rect2I& srcRect, const Rect2I& destRect, GraphicsBufferComponentMask mask, GraphicsTextureMagFilter filter)const override;	//copy a block of pixels from the read framebuffer to the draw framebuffer
	virtual void SetRenderBufferMultipleSampleStorage(GraphicsRenderBufferInternalFormat format, uint sampleCount, const Size2U& size)const override;//establish data storage, format, dimensions and sample count of a renderbuffer object's imageconst override;
	virtual void AttachTextureLayerToFrameBuffer(GraphicsFrameBufferType frameBuffer, GraphicsAttachment attachment, uint texture, int level, int layer)const override;
	virtual void InvalidateFramebuffer(uint numAttachments, const GraphicsAttachment* attachments)const override;
	virtual void InvalidateSubFramebuffer(uint numAttachments, const GraphicsAttachment* attachments, const Rect2U& rect)const override;
	virtual void GetInternalFormatParameter(GraphicsInternalFormat internalFormat, GraphicsInternalFormatParameterName name, uint bufferSize, int* outParam)const override;

#pragma endregion Frame buffer

#pragma region Texture
public:
	virtual void LoadTexture3D(GraphicsTextureTarget textureTarget, int level, GraphicsInternalFormat internalformat, const Size3U& size, int border, GraphicsPixelFormat format, GraphicsPixelDataType type, const void *pixels)const override;
	virtual void LoadSubTexture3D(GraphicsTextureTarget textureTarget, int level, const CubeI& rect, GraphicsPixelFormat format, GraphicsPixelDataType type, const void *pixels)const override;
	virtual void CopySubTexture3D(GraphicsTextureTarget textureTarget, int level, const Point3I& offset, const Rect2I& rect)const override;
	virtual void LoadCompressedTexture3D(GraphicsTextureTarget textureTarget, int level, GraphicsInternalFormat internalformat, const Size3U& size, int border, uint imageSize, const void *pixels)const override;
	virtual void LoadCompressedSubTexture3D(GraphicsTextureTarget textureTarget, int level, GraphicsInternalFormat internalformat, const CubeI& rect, uint imageSize, const void *pixels)const override;
	virtual void SetTextureStorage2D(GraphicsTextureTarget textureTarget, uint level, GraphicsInternalFormat internalformat, const Size2U& size)const override;
	virtual void SetTextureStorage3D(GraphicsTextureTarget textureTarget, uint level, GraphicsInternalFormat internalformat, const Size3U& size)const override;
#pragma endregion Texture

#pragma region Query
public:
	virtual void GenQueries(uint count, uint* outQueries)const override;
	virtual void DeleteQueries(uint count, uint* queries)const override;
	virtual bool IsQuery(uint id)const override;
	virtual void BeginQuery(GraphicsQueryTarget target, uint query)const override;
	virtual void EndQuery(uint query)const override;
	virtual int GetQueryParameter(GraphicsQueryTarget target, GraphicsQueryParameter parameter)const override;
	virtual uint GetQueryObjectParameter(uint query, GraphicsQueryObjectParameter parameter)const override;
#pragma endregion Query

#pragma region Buffer
public:
	virtual void* MapBufferRange(GraphicsBufferType bufferType, int offset, uint length, GraphicsMapBufferMask mask)const override;
	virtual bool UnmapBuffer(GraphicsBufferType bufferType)const override;
	virtual void GetBufferPointer(GraphicsBufferType bufferType, GraphicsBufferPointerName name, void** outResult)const override;
	virtual void FlushMappedBufferRange(GraphicsBufferType bufferType, int offset, uint length)const override;
	virtual void BindBufferToBuffer(GraphicsBindBufferTarget target, uint index, uint buffer)const override;	//bind a buffer object to an indexed buffer target
	virtual void BindBufferRangeToBuffer(GraphicsBindBufferTarget target, uint index, uint buffer, int offset, uint length)const override;	//bind a range within a buffer object to an indexed buffer target
	virtual void ClearBuffer(GraphicsBufferClearMask clearMask, int drawBuffer, const int* val)const override;
	virtual void ClearBuffer(GraphicsBufferClearMask clearMask, int drawBuffer, const uint* val)const override;
	virtual void ClearBuffer(GraphicsBufferClearMask clearMask, int drawBuffer, const float* val)const override;
	virtual void ClearBuffer(GraphicsBufferClearMask clearMask, int drawBuffer, float depth, int stencil)const override;
	virtual void CopyBufferSubData(GraphicsBufferType fromTarget, uint fromOffset, GraphicsBufferType toTarget, uint toOffset, uint size)const override;
	virtual int64 GetBufferParameter64(GraphicsBufferType bufferType, GraphicsBufferParameter parameter)const override;
#pragma endregion Buffer

#pragma region Uniform
public:
	virtual void SetUniformMatrix23(int location, uint count, const float* data, bool isTransposed = false)const override;
	virtual void SetUniformMatrix32(int location, uint count, const float* data, bool isTransposed = false)const override;
	virtual void SetUniformMatrix24(int location, uint count, const float* data, bool isTransposed = false)const override;
	virtual void SetUniformMatrix42(int location, uint count, const float* data, bool isTransposed = false)const override;
	virtual void SetUniformMatrix34(int location, uint count, const float* data, bool isTransposed = false)const override;
	virtual void SetUniformMatrix43(int location, uint count, const float* data, bool isTransposed = false)const override;
	virtual void GetUniformIndices(uint program, uint uniformCount, const char* const* uniformNames, uint* outUniformIndices)const override;
	virtual void GetActiveUniformParameter(uint program, uint uniformCount, const uint* uniformIndices, GraphicsUniformParameterName name, int* outParam)const override;
	virtual uint GetUniformBlockIndex(uint program, const char* uniformBlockName)const override;
	virtual void GetActiveUniformBlockParameter(uint program, uint uniformBlockIndex, GraphicsUniformBlockParameterName name, int* outParam)const override;
	virtual void GetActiveUniformBlockName(uint program, uint uniformBlockIndex, uint outNameBufferSize, uint& outLength, char* outName)const override;
	virtual void SetUniformBlockBinding(uint program, uint uniformBlockIndex, uint uniformBlockBinding)const override;

	virtual void GetUniformArray(uint program, int location, uint* outData)const override;

	virtual void SetUniform(int location, uint x)const override;
	virtual void SetUniform(int location, uint x, uint y)const override;
	virtual void SetUniform(int location, uint x, uint y, uint z)const override;
	virtual void SetUniform(int location, uint x, uint y, uint z, uint w)const override;

	virtual void SetUniformArray1(int location, uint count, const uint* data)const override;
	virtual void SetUniformArray2(int location, uint count, const uint* data)const override;
	virtual void SetUniformArray3(int location, uint count, const uint* data)const override;
	virtual void SetUniformArray4(int location, uint count, const uint* data)const override;
#pragma endregion Uniform

#pragma region VertexArray
public:
	virtual void BindVertexArray(uint id)const override;
	virtual void DeleteVertexArrays(uint count, uint* arrays)const override;
	virtual void GenVertexArrays(uint count, uint* outArrays)const override;
	virtual bool IsVertexArray(uint id)const override;

	virtual void SetVertexAttributeIntegerPointer(uint index, uint componentCount, GraphicsIntegerDataType type, uint stride, const void* data)const override;
	virtual void GetVertexAttributeValueInt(uint index, GraphicsVertexAttributeParameter parameter, int* outParams)const override;
	virtual void GetVertexAttributeValueUInt(uint index, GraphicsVertexAttributeParameter parameter, uint* outParams)const override;

	virtual void SetVertexAttribute(uint index, const Point4I& pos)const override;
	virtual void SetVertexAttribute(uint index, const Point4U& pos)const override;

	virtual void SetVertexAttributeArray4(uint index, const int* data)const override;
	virtual void SetVertexAttributeArray4(uint index, const uint* data)const override;
	virtual void SetVertexAttributeDivisor(uint index, uint divisor)const override;
#pragma endregion VertexArray

#pragma region Transform feedback
public:
	virtual void BeginTransformFeedback(GraphicsTransformFeedbackPrimitiveMode mode)const override;
	virtual void EndTransformFeedback()const override;
	virtual void SetTransformFeedbackVaryings(uint program, uint count, const char* const* varyings, GraphicsTransformFeedbackBufferMode bufferMode)const override;
	virtual void GetTransformFeedbackVaryings(uint program, uint index, uint outVaryingNameBufferSize, char* outVaryingName, uint& outVaryingNameLength, uint& outVaryingType, uint& outVaryingSize)const override;
	virtual void BindTransformFeedback(uint id)const override;
	virtual void DeleteTransformFeedbacks(uint count, const uint* ids)const override;
	virtual void GenTransformFeedbacks(uint count, uint* outIds)const override;
	virtual bool IsTransformFeedback(uint id)const override;
	virtual void PauseTransformFeedback()const override;
	virtual void ResumeTransformFeedback()const override;
#pragma endregion Transform feedback

#pragma region Program
public:
	virtual int GetFragDataLocation(uint program, const char* name)const override;	//query the bindings of color numbers to user-defined varying out variables
	virtual void GetProgramBinary(uint program, uint outBufferSize, uint& outLength, uint& outBinaryFormat, void* outBinary)const override;
	virtual void LoadProgramBinary(uint program, uint outbinaryFormat, const void* binary, uint length)const override;
	virtual void SetProgramParamter(uint program, GraphicsProgramParameterName name, int val)const override;
#pragma endregion Program

#pragma region Draw
public:
	virtual void DrawArraysInstanced(GraphicsDrawMode mode, int first, uint count, uint instanceCount)const override;
	virtual void DrawIndicesInstanced(GraphicsDrawMode mode, uint count, GraphicsDataType type, const void* indices, uint instanceCount)const override;
	virtual void DrawIndicesRange(GraphicsDrawMode mode, uint start, uint end, uint count, GraphicsDataType type, const void* indices)const override;
#pragma endregion Draw

#pragma region Sync
public:
	virtual intp CreateSync(GraphicsSyncCondition condition)const override;
	virtual bool IsSync(intp sync)const override;
	virtual void DeleteSync(intp sync)const override;
	virtual void ClientWaitSync(intp sync, GraphicsSyncMask mask, uint64 timeout)const override;
	virtual void WaitSync(intp sync, GraphicsSyncMask mask, uint64 timeout)const override;
	virtual void GetSyncParameter(intp sync, GraphicsSyncParameterName name, uint outBufferSize, uint& outLength, int* outValues)const override;
#pragma endregion Sync

#pragma region Sampler
public:
	virtual void GenSamplers(uint count, uint* outSamplers)const override;
	virtual void DeleteSamplers(uint count, const uint* samplers)const override;
	virtual bool IsSampler(uint sampler)const override;
	virtual void BindSampler(GraphicsTextureUnits unit, uint sampler)const override;

	virtual void SetSamplerParameter(uint sampler, GraphicsSamplerParameterName name, int val)const override;
	virtual void SetSamplerParameter(uint sampler, GraphicsSamplerParameterName name, float val)const override;
	virtual void SetSamplerParameterArray(uint sampler, GraphicsSamplerParameterName name, const int* values)const override;
	virtual void SetSamplerParameterArray(uint sampler, GraphicsSamplerParameterName name, const float* values)const override;

	virtual void GetSamplerParameter(uint sampler, GraphicsSamplerParameterName name, int* outParam)const override;
	virtual void GetSamplerParameter(uint sampler, GraphicsSamplerParameterName name, float* outParam)const override;
#pragma endregion Sampler

#pragma region Get
protected:
	virtual bool TryGetIntegerWithIndex(GraphicsIntegerName name, uint index, int& outVal)const override;
	virtual bool TryGetInteger64(GraphicsIntegerName name, int64& outVal)const override;
	virtual bool TryGetInteger64WithIndex(GraphicsIntegerName name, uint index, int64& outVal)const override;
	virtual bool TryGetStringWithIndex(GraphicsStringName name, uint index, StringRef& outVal)const override;
#pragma endregion Get

#pragma endregion OpenGL ES 3.0
	
};

MEDUSA_END;