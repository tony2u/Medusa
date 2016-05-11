// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Collection/BitArray.h"
#include "Graphics/GraphicsTypes.h"
#include "Geometry/Color4.h"
#include "Geometry/Rect2.h"
#include "Geometry/Range.h"
#include "Core/Collection/Stack.h"
#include "Core/Collection/Array.h"
#include "Core/Collection/Dictionary.h"
#include "Core/Pattern/IInitializable.h"
#include "Resource/Model/Mesh/MeshComponents.h"
#include "Graphics/PixelType.h"


MEDUSA_BEGIN;

class IRender :public IInitializable
{
public:
	IRender(void);
	virtual ~IRender(void);
public:
	bool AssertSuccess()const;
	bool IsSuccess()const;

	void PrintAll()const;
#pragma region Helpers
public:
	virtual bool Initialize();


	virtual void Finish() = 0;
	virtual void Flush() = 0;
	virtual GraphicsErrorCode GetError()const = 0;

	virtual void Clear(GraphicsBufferComponentMask clearMasks)const = 0;

#pragma endregion Helpers


#pragma region Set Values
	virtual void Hint(GraphicsHintMode mode) = 0;
	virtual void SetClearColor(const Color4F& color) = 0;
	virtual void SetBlendColor(const Color4F& color) = 0;

	virtual void SetLineWidth(float width) = 0;

	virtual void SetViewPort(const Rect2I& rect) = 0;
	virtual void SetScissorBox(const Rect2I& rect) = 0;


	virtual void SetBlendFunc(GraphicsBlendSrcFunc srcFactor, GraphicsBlendDestFunc destFactor) = 0;
	virtual void SetBlendFuncSeparate(GraphicsBlendSrcFunc srcRGBFactor, GraphicsBlendSrcFunc srcAlphaFactor, GraphicsBlendDestFunc destRGBFactor, GraphicsBlendDestFunc destAlphaFactor) = 0;


	virtual void SetBlendEquation(GraphicsBlendEquation equation) = 0;
	virtual void SetBlendEquationSeparate(GraphicsBlendEquation rgbEquation, GraphicsBlendEquation alphaEquation) = 0;

	virtual void SetFrontFace(GraphicsFrontFace frontFace) = 0;
	virtual void SetDepthRange(const RangeF& depthRange) = 0;
	virtual void SetDepthFunc(GraphicsFuncType func) = 0;
	virtual void SetClearDepth(float depth) = 0;
	virtual void SetStencilClearValue(int val) = 0;
	virtual void SetColorMask(GraphicsColorMask colorMask) = 0;

	virtual GraphicsFrameBufferStatus CheckFrameBufferStatus()const = 0;
	virtual void SetPixelStore(GraphicsPixelStoreParameter parameter, int val) = 0;
	virtual void SetPolygonOffset(float scaleFactor, float unit) = 0;
	virtual void SetSampleCoverage(float val, bool isInvert) = 0;	//0-1
	virtual void SetStencilFunc(GraphicsFuncType func, int refValue, uint readMask) = 0;
	virtual void SetStencilFuncSeparate(GraphicsFace face, GraphicsFuncType func, int refValue, uint readMask) = 0;
	virtual void SetStencilWriteMask(uint mask) = 0;
	virtual void SetStencilWriteMaskSeparate(GraphicsFace face, uint mask) = 0;
	virtual void SetStencilOperation(GraphicsStencilOperation testFail, GraphicsStencilOperation testPassDepthFail, GraphicsStencilOperation testPassDepthPass) = 0;
	virtual void SetStencilOperationSeparate(GraphicsFace face, GraphicsStencilOperation testFail, GraphicsStencilOperation testPassDepthFail, GraphicsStencilOperation testPassDepthPass) = 0;
protected:
	virtual bool TryGetInteger(GraphicsIntegerName name, int& outVal)const = 0;
	virtual bool TryGetIntegerArray(GraphicsIntegerArrayName name, int* params)const = 0;
	virtual bool TryGetBoolean(GraphicsBooleanName name, bool& outVal)const = 0;
	virtual bool TryGetBooleanArray(GraphicsBooleanArrayName name, bool* params)const = 0;
	virtual bool TryGetFloat(GraphicsFloatName name, float& outVal)const = 0;
	virtual bool TryGetFloatArray(GraphicsFloatArrayName name, float* params)const = 0;
	virtual bool TryGetString(GraphicsStringName name, StringRef& outVal)const = 0;

#pragma endregion Set Values

#pragma region Enable/Disable
public:
	virtual void EnableDepthWrite(bool isEnable) = 0;
	virtual void CullFace(GraphicsFace face) = 0;


	virtual void EnableFeature(GraphicsFeatures feature, bool isEnable) = 0;
	virtual bool IsFeatureEnabled(GraphicsFeatures feature) = 0;


#pragma endregion Enable/Disable


#pragma region Drawing Primitives
public:
	virtual void DrawArrays(GraphicsDrawMode mode, int first, uint count)const = 0;
	virtual void DrawIndices(GraphicsDrawMode mode, uint count, GraphicsDataType type, const void* indices)const = 0;
	virtual void DrawIndices(GraphicsDrawMode mode, const ICollection<ushort>& indices)const = 0;
	virtual void DrawIndices(GraphicsDrawMode mode, const ICollection<byte>& indices)const = 0;
	virtual void DrawIndices(GraphicsDrawMode mode, const ICollection<uint>& indices)const = 0;

	//GL_POINTS
	virtual void DrawPoints(uint pointCount = 1)const = 0;

	//GL_LINES
	virtual void DrawLines(uint pointCount, const ICollection<ushort>* indices = nullptr)const = 0;

	//GL_LINE_STRIP
	virtual void DrawLinesStrip(uint pointCount, const ICollection<ushort>* indices = nullptr)const = 0;

	//GL_LINE_LOOP 
	virtual void DrawLinesLoop(uint pointCount, const ICollection<ushort>* indices = nullptr)const = 0;

	//GL_TRIANGLES
	virtual void DrawTriangles(uint pointCount, const ICollection<ushort>* indices = nullptr)const = 0;

	//GL_TRIANGLE_STRIP
	virtual void DrawTriangleStrip(uint pointCount, const ICollection<ushort>* indices = nullptr)const = 0;

	//GL_TRIANGLE_FAN
	virtual void DrawTrianglesFan(uint pointCount, const ICollection<ushort>* indices = nullptr)const = 0;

#pragma endregion Drawing Primitives

#pragma region Texture Objects
public:
	uint GenTexture();
	virtual void GenTextures(uint count, uint* outBuffers) = 0;

	void DeleteTexture(uint texture);
	virtual void DeleteTextures(uint count, uint* textures) = 0;

	virtual void BindTexture(GraphicsTextureType textureType, uint texture) = 0;	//texture=0 to detach
	virtual void ActivateTexture(GraphicsTextureUnits textureUnit) = 0;

	virtual void GenerateTextureMipmap(GraphicsTextureType textureType)const = 0;

	virtual bool IsTexture(uint texture)const = 0;
	virtual void LoadTexture(GraphicsTextureTarget textureTarget, int level, PixelType pixelType, const Size2U& size, int border, const void *pixels)const = 0;
	virtual void LoadSubTexture(GraphicsTextureTarget textureTarget, int level, const Rect2I& rect, PixelType pixelType, const void *pixels)const = 0;

	virtual void LoadCompressedTexture(GraphicsTextureTarget textureTarget, int level, PixelType pixelType, const Size2U& size, int border, uint imageSize, const void *pixels)const = 0;
	virtual void LoadCompressedSubTexture(GraphicsTextureTarget textureTarget, int level, PixelType pixelType, const Rect2I& rect, uint imageSize, const void *pixels)const = 0;
	virtual void CopyTexture(GraphicsTextureTarget textureTarget, int level, PixelType pixelType, const Rect2I& rect, int border)const = 0;
	virtual void CopySubTexture(GraphicsTextureTarget textureTarget, int level, const Point2I& offset, const Rect2I& rect)const = 0;

	virtual void SetTextureMinFilter(GraphicsTextureType textureType, GraphicsTextureMinFilter minFilter) = 0;
	virtual void SetTextureMagFilter(GraphicsTextureType textureType, GraphicsTextureMagFilter magFilter) = 0;
	virtual void SetTextureWrapS(GraphicsTextureType textureType, GraphicsTextureWrapMode wrapS) = 0;
	virtual void SetTextureWrapT(GraphicsTextureType textureType, GraphicsTextureWrapMode wrapT) = 0;

	virtual int GetTextureParamter(GraphicsTextureType textureType, GraphicsTextureParameter parameter) = 0;

protected:
	virtual bool TryGetTextureParamter(GraphicsTextureType textureType, GraphicsTextureParameter parameter, int& outVal) = 0;

#pragma endregion Texture Objects

#pragma region Buffer Objects
public:
	virtual bool IsBuffer(uint bufferObject)const = 0;
	virtual bool IsFrameBuffer(uint bufferObject)const = 0;
	virtual bool IsRenderBuffer(uint bufferObject)const = 0;

	uint GenBuffer()const;
	virtual void GenBuffers(uint count, uint* outBuffers)const = 0;

	void DeleteBuffer(uint bufferObject)const;
	virtual void DeleteBuffers(uint count, uint* buffers)const = 0;

	virtual void BindBuffer(GraphicsBufferType bufferType, uint bufferObject) = 0;	//bufferObject=0 to detach

	virtual void LoadBufferData(GraphicsBufferType bufferType, uint size, void* data, GraphicsBufferUsage usageType)const = 0;
	virtual void ModifyBufferSubData(GraphicsBufferType bufferType, int offset, uint size, const void* data)const = 0;

	uint GenFrameBuffer()const;
	virtual void GenFrameBuffers(uint count, uint* outBuffers)const = 0;

	uint GenRenderBuffer()const;
	virtual void GenRenderBuffers(uint count, uint* outBuffers)const = 0;


	virtual void BindFrameBuffer(uint frameBufferObject) = 0;	//frameBufferObject=0 to detach
	virtual void BindRenderBuffer(uint renderBufferObject) = 0;	//renderBufferObject=0 to detach

	void DeleteFrameBuffer(uint frameBufferObject);
	virtual void DeleteFrameBuffers(uint count, uint* buffers) = 0;

	void DeleteRenderBuffer(uint renderBufferObject);
	virtual void DeleteRenderBuffers(uint count, uint* buffers) = 0;

	virtual void AttachRenderBufferToFrameBuffer(GraphicsAttachment attachment, uint renderBufferObject)const = 0;	//renderBufferObject=0 to detach
	virtual void AttachTextureToFrameBuffer(GraphicsAttachment attachment, GraphicsTextureTarget textureTarget, uint texture, int level)const = 0;	//texture=0 to detach

	virtual int GetBufferParameter(GraphicsBufferType bufferType, GraphicsBufferParameter parameter)const = 0;
	virtual int GetFrameBufferAttachmentParameter(GraphicsAttachment attachment, GraphicsFrameBufferAttachmentParameter parameter)const = 0;
	virtual int GetRenderBufferParameter(GraphicsRenderBufferParameter parameter)const = 0;
	virtual void ReadPixels(GraphicsPixelFormat format, GraphicsPixelDataType dataType, const Rect2I& rect, void* outData) = 0;
	virtual void SetRenderBufferStorage(GraphicsRenderBufferInternalFormat format, const Size2U& size) = 0;
#pragma endregion Buffer Objects

#pragma region Shader
public:
	virtual bool IsShaderBinaryFormatSupported(GraphicsShaderBinaryFormat binaryFormat)const = 0;
	virtual void EnableVertexAttributeArray(uint index, bool isEnabled) = 0;

	virtual uint CreateShader(GraphicsShaderType type) = 0;
	virtual void DeleteShader(uint shader) = 0;
	virtual void SetShaderSource(uint shader, StringRef source) = 0;
	virtual void GetShaderSource(uint shader, HeapString& outSource) = 0;

	virtual void SetShadersBinary(uint count, const uint* shaders, GraphicsShaderBinaryFormat binaryFormat, const void* data, uint length) = 0;
	virtual void SetShaderBinary(uint shader, GraphicsShaderBinaryFormat binaryFormat, const void* data, uint length) = 0;


	virtual void CompileShader(uint shader) = 0;
	virtual void GetShadderInfoLog(uint shader, HeapString& outInfoLog) = 0;
	virtual bool IsShader(uint shader) = 0;
	virtual int GetShaderStatus(uint shader, GraphicsShaderStatus name) = 0;

	virtual uint CreateProgram() = 0;
	virtual void DeleteProgram(uint program) = 0;
	virtual void AttachShader(uint program, uint shader) = 0;
	virtual void DetachShader(uint program, uint shader) = 0;
	virtual void LinkProgram(uint program) = 0;
	virtual void GetProgramInfoLog(uint program, HeapString& outInfoLog) = 0;
	virtual void UseProgram(uint program) = 0;
	virtual bool IsProgram(uint program) = 0;
	virtual void ValidateProgram(uint program) = 0;
	virtual int GetProgramStatus(uint program, GraphicsProgramStatus name) = 0;

	virtual void BindUniformLocation(uint program, int index, StringRef name) = 0;	//called before link
	virtual int GetUniformLocation(uint program, StringRef name) = 0;

	virtual void SetUniform(int location, int x) = 0;
	virtual void SetUniform(int location, int x, int y) = 0;
	virtual void SetUniform(int location, int x, int y, int z) = 0;
	virtual void SetUniform(int location, int x, int y, int z, int w) = 0;

	virtual void SetUniform(int location, float x) = 0;
	virtual void SetUniform(int location, float x, float y) = 0;
	virtual void SetUniform(int location, float x, float y, float z) = 0;
	virtual void SetUniform(int location, float x, float y, float z, float w) = 0;


	virtual void SetUniformArray1(int location, uint count, const float* data) = 0;
	virtual void SetUniformArray2(int location, uint count, const float* data) = 0;
	virtual void SetUniformArray3(int location, uint count, const float* data) = 0;
	virtual void SetUniformArray4(int location, uint count, const float* data) = 0;

	virtual void SetUniformArray1(int location, uint count, const int* data) = 0;
	virtual void SetUniformArray2(int location, uint count, const int* data) = 0;
	virtual void SetUniformArray3(int location, uint count, const int* data) = 0;
	virtual void SetUniformArray4(int location, uint count, const int* data) = 0;

	virtual void SetUniformMatrix2(int location, uint count, const float* data, bool isTransposed = false) = 0;
	virtual void SetUniformMatrix3(int location, uint count, const float* data, bool isTransposed = false) = 0;
	virtual void SetUniformMatrix4(int location, uint count, const float* data, bool isTransposed = false) = 0;

	virtual void GetUniformArray(uint program, int location, float* outData) = 0;
	virtual void GetUniformArray(uint program, int location, int* outData) = 0;

	virtual void SetVertexAttribute(uint index, float x) = 0;
	virtual void SetVertexAttribute(uint index, const Point2F& pos) = 0;
	virtual void SetVertexAttribute(uint index, const Point3F& pos) = 0;
	virtual void SetVertexAttribute(uint index, const Point4F& pos) = 0;

	virtual void SetVertexAttributeArray1(uint index, const float* data) = 0;
	virtual void SetVertexAttributeArray2(uint index, const float* data) = 0;
	virtual void SetVertexAttributeArray3(uint index, const float* data) = 0;
	virtual void SetVertexAttributeArray4(uint index, const float* data) = 0;

	virtual int GetVertexAttributeLocation(uint program, StringRef name) = 0;

	virtual void SetVertexAttributePointer(uint index, uint componentCount, GraphicsDataType type, bool isNormalized, uint stride, const void* data) = 0;
	virtual void GetVertexAttributePointer(uint index, void** outData) = 0;

	virtual void GetActiveAttributeName(uint program, uint index, int& outSize, uint& outDataType, HeapString& outName) = 0;
	virtual void GetActiveUniformName(uint program, uint index, int& outSize, uint& outDataType, HeapString& outName) = 0;
	virtual void GetAttachedShaders(uint program, uint maxCount, int& outCount, uint* outShaders) = 0;
	virtual void GetShaderPrecisionFormat(GraphicsShaderType shaderType, GraphicsShaderPrecisionType precesionType, int* outRange, int* outPrecision) = 0;

	virtual void GetVertexAttributeValue(uint index, GraphicsVertexAttributeParameter parameter, float* outParams) = 0;
	virtual void GetVertexAttributeValue(uint index, GraphicsVertexAttributeParameter parameter, int* outParams) = 0;

	virtual void ReleaseShaderCompiler()const = 0;
#pragma endregion Shader
#pragma region Extension
public:
	virtual bool IsExtensionSupported(StringRef extension)const = 0;

#pragma endregion Extension
#pragma region Easy
public:
	int GetInteger(GraphicsIntegerName name)const;
	void GetIntegerArray(GraphicsIntegerArrayName name, int* params)const;
	bool GetBoolean(GraphicsBooleanName name)const;
	void GetBooleanArray(GraphicsBooleanArrayName name, bool* params)const;
	float GetFloat(GraphicsFloatName name)const;
	void GetFloatArray(GraphicsFloatArrayName name, float* params)const;
	StringRef GetString(GraphicsStringName name)const;

	void DrawRect(const Rect2F& rect, ShaderAttribute* vertexArray);
	void DrawTextureRect(const Rect2F& rect, const Rect2F& textureRect, ShaderAttribute* vertexArray, ShaderAttribute* texCoordArray);

#pragma endregion Easy
#pragma region OpenGL ES 3.0
#pragma region Frame buffer
public:
	virtual void ReadBuffer(GraphicsColorBuffers buffer) const = 0;	//select a color buffer source for pixels
	virtual void SetDrawBufferTargets(uint count, const GraphicsColorBuffers* buffers)const = 0;	//Specifies a list of color buffers to be drawn into
	virtual void BlitFrameBuffer(const Rect2I& srcRect, const Rect2I& destRect, GraphicsBufferComponentMask mask, GraphicsTextureMagFilter filter)const = 0;	//copy a block of pixels from the read framebuffer to the draw framebuffer
	virtual void SetRenderBufferMultipleSampleStorage(GraphicsRenderBufferInternalFormat format, uint sampleCount, const Size2U& size)const = 0;//establish data storage, format, dimensions and sample count of a renderbuffer object's imageconst =0;
	virtual void AttachTextureLayerToFrameBuffer(GraphicsFrameBufferType frameBuffer, GraphicsAttachment attachment, uint texture, int level, int layer)const = 0;
	virtual void InvalidateFramebuffer(uint numAttachments, const GraphicsAttachment* attachments)const = 0;
	virtual void InvalidateSubFramebuffer(uint numAttachments, const GraphicsAttachment* attachments, const Rect2U& rect)const = 0;
	virtual void GetInternalFormatParameter(GraphicsInternalFormat internalFormat, GraphicsInternalFormatParameterName name, uint bufferSize, int* outParam)const = 0;

#pragma endregion Frame buffer

#pragma region Texture
public:
	virtual void LoadTexture3D(GraphicsTextureTarget textureTarget, int level, PixelType pixelType, const Size3U& size, int border,  const void *pixels)const = 0;
	virtual void LoadSubTexture3D(GraphicsTextureTarget textureTarget, int level, const CubeI& rect, PixelType pixelType, const void *pixels)const = 0;
	virtual void CopySubTexture3D(GraphicsTextureTarget textureTarget, int level, const Point3I& offset, const Rect2I& rect)const = 0;
	virtual void LoadCompressedTexture3D(GraphicsTextureTarget textureTarget, int level, PixelType pixelType, const Size3U& size, int border, uint imageSize, const void *pixels)const = 0;
	virtual void LoadCompressedSubTexture3D(GraphicsTextureTarget textureTarget, int level, PixelType pixelType, const CubeI& rect, uint imageSize, const void *pixels)const = 0;
	virtual void SetTextureStorage2D(GraphicsTextureTarget textureTarget, uint level, PixelType pixelType, const Size2U& size)const = 0;
	virtual void SetTextureStorage3D(GraphicsTextureTarget textureTarget, uint level, PixelType pixelType, const Size3U& size)const = 0;
#pragma endregion Texture

#pragma region Query
public:
	virtual void GenQueries(uint count, uint* outQueries)const = 0;
	virtual void DeleteQueries(uint count, uint* queries)const = 0;
	virtual bool IsQuery(uint id)const = 0;
	virtual void BeginQuery(GraphicsQueryTarget target, uint query)const = 0;
	virtual void EndQuery(uint query)const = 0;
	virtual int GetQueryParameter(GraphicsQueryTarget target, GraphicsQueryParameter parameter)const = 0;
	virtual uint GetQueryObjectParameter(uint query, GraphicsQueryObjectParameter parameter)const = 0;
#pragma endregion Query

#pragma region Buffer
public:
	virtual void* MapBufferRange(GraphicsBufferType bufferType, int offset, uint length, GraphicsMapBufferMask mask)const = 0;
	virtual bool UnmapBuffer(GraphicsBufferType bufferType)const = 0;
	virtual void GetBufferPointer(GraphicsBufferType bufferType, GraphicsBufferPointerName name, void** outResult)const = 0;
	virtual void FlushMappedBufferRange(GraphicsBufferType bufferType, int offset, uint length)const = 0;
	virtual void BindBufferToBuffer(GraphicsBindBufferTarget target, uint index, uint buffer)const = 0;	//bind a buffer object to an indexed buffer target
	virtual void BindBufferRangeToBuffer(GraphicsBindBufferTarget target, uint index, uint buffer, int offset, uint length)const = 0;	//bind a range within a buffer object to an indexed buffer target
	virtual void ClearBuffer(GraphicsBufferClearMask clearMask, int drawBuffer, const int* val)const = 0;
	virtual void ClearBuffer(GraphicsBufferClearMask clearMask, int drawBuffer, const uint* val)const = 0;
	virtual void ClearBuffer(GraphicsBufferClearMask clearMask, int drawBuffer, const float* val)const = 0;
	virtual void ClearBuffer(GraphicsBufferClearMask clearMask, int drawBuffer, float depth, int stencil)const = 0;
	virtual void CopyBufferSubData(GraphicsBufferType fromTarget, uint fromOffset, GraphicsBufferType toTarget, uint toOffset, uint size)const = 0;
	virtual int64 GetBufferParameter64(GraphicsBufferType bufferType, GraphicsBufferParameter parameter)const = 0;
#pragma endregion Buffer

#pragma region Uniform
public:
	virtual void SetUniformMatrix23(int location, uint count, const float* data, bool isTransposed = false)const = 0;
	virtual void SetUniformMatrix32(int location, uint count, const float* data, bool isTransposed = false)const = 0;
	virtual void SetUniformMatrix24(int location, uint count, const float* data, bool isTransposed = false)const = 0;
	virtual void SetUniformMatrix42(int location, uint count, const float* data, bool isTransposed = false)const = 0;
	virtual void SetUniformMatrix34(int location, uint count, const float* data, bool isTransposed = false)const = 0;
	virtual void SetUniformMatrix43(int location, uint count, const float* data, bool isTransposed = false)const = 0;
	virtual void GetUniformIndices(uint program, uint uniformCount, const char* const* uniformNames, uint* outUniformIndices)const = 0;
	virtual void GetActiveUniformParameter(uint program, uint uniformCount, const uint* uniformIndices, GraphicsUniformParameterName name, int* outParam)const = 0;
	virtual uint GetUniformBlockIndex(uint program, const char* uniformBlockName)const = 0;
	virtual void GetActiveUniformBlockParameter(uint program, uint uniformBlockIndex, GraphicsUniformBlockParameterName name, int* outParam)const = 0;
	virtual void GetActiveUniformBlockName(uint program, uint uniformBlockIndex, uint outNameBufferSize, uint& outLength, char* outName)const = 0;
	virtual void SetUniformBlockBinding(uint program, uint uniformBlockIndex, uint uniformBlockBinding)const = 0;

	virtual void GetUniformArray(uint program, int location, uint* outData)const = 0;

	virtual void SetUniform(int location, uint x)const = 0;
	virtual void SetUniform(int location, uint x, uint y)const = 0;
	virtual void SetUniform(int location, uint x, uint y, uint z)const = 0;
	virtual void SetUniform(int location, uint x, uint y, uint z, uint w)const = 0;

	virtual void SetUniformArray1(int location, uint count, const uint* data)const = 0;
	virtual void SetUniformArray2(int location, uint count, const uint* data)const = 0;
	virtual void SetUniformArray3(int location, uint count, const uint* data)const = 0;
	virtual void SetUniformArray4(int location, uint count, const uint* data)const = 0;
#pragma endregion Uniform

#pragma region VertexArray
public:
	virtual void BindVertexArray(uint id)const = 0;
	virtual void DeleteVertexArrays(uint count, uint* arrays)const = 0;
	virtual void GenVertexArrays(uint count, uint* outArrays)const = 0;
	virtual bool IsVertexArray(uint id)const = 0;

	virtual void SetVertexAttributeIntegerPointer(uint index, uint componentCount, GraphicsIntegerDataType type, uint stride, const void* data)const = 0;
	virtual void GetVertexAttributeValueInt(uint index, GraphicsVertexAttributeParameter parameter, int* outParams)const = 0;
	virtual void GetVertexAttributeValueUInt(uint index, GraphicsVertexAttributeParameter parameter, uint* outParams)const = 0;

	virtual void SetVertexAttribute(uint index, const Point4I& pos)const = 0;
	virtual void SetVertexAttribute(uint index, const Point4U& pos)const = 0;

	virtual void SetVertexAttributeArray4(uint index, const int* data)const = 0;
	virtual void SetVertexAttributeArray4(uint index, const uint* data)const = 0;
	virtual void SetVertexAttributeDivisor(uint index, uint divisor)const = 0;
#pragma endregion VertexArray

#pragma region Transform feedback
public:
	virtual void BeginTransformFeedback(GraphicsTransformFeedbackPrimitiveMode mode)const = 0;
	virtual void EndTransformFeedback()const = 0;
	virtual void SetTransformFeedbackVaryings(uint program, uint count, const char* const* varyings, GraphicsTransformFeedbackBufferMode bufferMode)const = 0;
	virtual void GetTransformFeedbackVaryings(uint program, uint index, uint outVaryingNameBufferSize, char* outVaryingName, uint& outVaryingNameLength, uint& outVaryingType, uint& outVaryingSize)const = 0;
	virtual void BindTransformFeedback(uint id)const = 0;
	virtual void DeleteTransformFeedbacks(uint count, const uint* ids)const = 0;
	virtual void GenTransformFeedbacks(uint count, uint* outIds)const=0;
	virtual bool IsTransformFeedback(uint id)const = 0;
	virtual void PauseTransformFeedback()const = 0;
	virtual void ResumeTransformFeedback()const = 0;
#pragma endregion Transform feedback



#pragma region Program
public:
	virtual int GetFragDataLocation(uint program, const char* name)const = 0;	//query the bindings of color numbers to user-defined varying out variables
	virtual void GetProgramBinary(uint program, uint outBufferSize, uint& outLength, uint& outBinaryFormat, void* outBinary)const = 0;
	virtual void LoadProgramBinary(uint program, uint outbinaryFormat, const void* binary, uint length)const = 0;
	virtual void SetProgramParamter(uint program, GraphicsProgramParameterName name, int val)const = 0;
#pragma endregion Program

#pragma region Draw
public:
	virtual void DrawArraysInstanced(GraphicsDrawMode mode, int first, uint count, uint instanceCount)const = 0;
	virtual void DrawIndicesInstanced(GraphicsDrawMode mode, uint count, GraphicsDataType type, const void* indices, uint instanceCount)const=0;
	virtual void DrawIndicesRange(GraphicsDrawMode mode, uint start, uint end, uint count, GraphicsDataType type, const void* indices)const = 0;
#pragma endregion Draw

#pragma region Sync
public:
	virtual intp CreateSync(GraphicsSyncCondition condition)const = 0;
	virtual bool IsSync(intp sync)const = 0;
	virtual void DeleteSync(intp sync)const = 0;
	virtual void ClientWaitSync(intp sync, GraphicsSyncMask mask, uint64 timeout)const = 0;
	virtual void WaitSync(intp sync, GraphicsSyncMask mask, uint64 timeout)const = 0;
	virtual void GetSyncParameter(intp sync, GraphicsSyncParameterName name, uint outBufferSize, uint& outLength, int* outValues)const = 0;
#pragma endregion Sync

#pragma region Sampler
public:
	virtual void GenSamplers(uint count, uint* outSamplers)const = 0;
	virtual void DeleteSamplers(uint count, const uint* samplers)const = 0;
	virtual bool IsSampler(uint sampler)const = 0;
	virtual void BindSampler(GraphicsTextureUnits unit, uint sampler)const = 0;

	virtual void SetSamplerParameter(uint sampler, GraphicsSamplerParameterName name, int val)const = 0;
	virtual void SetSamplerParameter(uint sampler, GraphicsSamplerParameterName name, float val)const = 0;
	virtual void SetSamplerParameterArray(uint sampler, GraphicsSamplerParameterName name, const int* values)const = 0;
	virtual void SetSamplerParameterArray(uint sampler, GraphicsSamplerParameterName name, const float* values)const = 0;

	virtual void GetSamplerParameter(uint sampler, GraphicsSamplerParameterName name, int* outParam)const = 0;
	virtual void GetSamplerParameter(uint sampler, GraphicsSamplerParameterName name, float* outParam)const = 0;
#pragma endregion Sampler

#pragma region Get
protected:
	virtual bool TryGetIntegerWithIndex(GraphicsIntegerName name, uint index, int& outVal)const = 0;
	virtual bool TryGetInteger64(GraphicsIntegerName name, int64& outVal)const = 0;
	virtual bool TryGetInteger64WithIndex(GraphicsIntegerName name, uint index, int64& outVal)const = 0;
	virtual bool TryGetStringWithIndex(GraphicsStringName name, uint index, StringRef& outVal)const = 0;
#pragma endregion Get

#pragma endregion OpenGL ES 3.0

#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
protected:
	//bool
	bool mBlendEnabled;
	bool mCullFaceEnabled;
	bool mDepthTestEnabled;
	bool mScissorTestEnabled;
	bool mStencilTestEnabled;
	bool mDepthWritableEnabled;
	bool mDitherEnabled;
	bool mPolygonOffsetFillEnabled;
	bool mSampleAlphaToCoverageEnabled;
	bool mSampleCoverageEnabled;
	bool mSampleCoverageInvertEnabled;
	bool mHasShaderCompilerEnabled;

	GraphicsColorMask mColorWriteMask;

	//int
	GraphicsTextureUnits mActiveTexture;
	int	mAlphaBits;
	int	mBlueBits;
	int	mGreenBits;
	int	mRedBits;
	int	mDepthBits;
	int	mStencilBits;
	int	mSubPixelBits;
	uint	mArrayBufferBinding;
	uint	mElementArrayBufferBinding;
	uint	mFrameBufferBinding;
	uint	mRenderBufferBinding;
	GraphicsBlendDestFunc	mBlendDestAlphaFunc;
	GraphicsBlendDestFunc	mBlendDestRGBFunc;
	GraphicsBlendEquation	mBlendAlphaEquation;
	GraphicsBlendEquation	mBlendRGBEquation;
	GraphicsBlendSrcFunc	mBlendSrcAlphaFunc;
	GraphicsBlendSrcFunc	mBlendSrcRGBFunc;
	GraphicsFace	mCullFaceMode;
	uint	mCurrentProgram;
	GraphicsFuncType	mDepthFunc;
	GraphicsFrontFace	mFrontFace;
	GraphicsHintMode	mGenerateMipmapHint;
	GraphicsInternalFormat	mImplementionColorReadFormat;
	GraphicsPixelDataType	mImplementionColorReadType;
	int	mMaxCombinedTextureUnitCount;
	int	mMaxFragmentTextureUnitCount;
	int	mMaxVertexTextureUnitCount;
	int	mMaxCubeMapTextureSize;
	int	mMaxFragmentUniformCount;
	int	mMaxVaryingCount;
	int	mMaxVetextAttributeCount;
	int	mMaxRenderBufferSize;
	int	mMaxTextureSize;
	int	mMaxVertexUnifromCount;
	int	mCompressedTextureFormatCount;
	int	mShaderBinaryFormatCount;
	int	mPackAlignment;
	int	mUnpackAlignment;
	int	mSampleBufferCount;
	int	mSampleCoverageMaskSize;
	GraphicsStencilOperation	mStencilBackFailOperation;
	GraphicsFuncType	mStencilBackFunc;
	GraphicsStencilOperation	mStencilBackPassDepthFailOperation;
	GraphicsStencilOperation	mStencilBackPassDepthPassOperation;
	int	mStencilBackRefValue;
	uint	mStencilBackValueMask;
	uint	mStencilBackWriteMask;
	int	mStencilClearValue;
	GraphicsStencilOperation	mStencilFailOperation;
	GraphicsFuncType	mStencilFunc;
	GraphicsStencilOperation	mStencilPassDepthFailOperation;
	GraphicsStencilOperation	mStencilPassDepthPassOperation;
	int	mStencilRefValue;
	uint	mStencilValueMask;
	uint	mStencilWriteMask;


	List<uint>	mTextureBindings;
	List<uint>	mCubeMapTextureBindings;

	RangeI mAliasedLineWidthRange;
	RangeI mAliasedPointSizeRange;
	List<GraphicsInternalFormat> mCompressedTextureFormats;
	List<GraphicsShaderBinaryFormat> mShaderBinaryFormats;
	Size2U mMaxViewportDimensions;
	Rect2I mScissorBox;
	Rect2I mViewport;

	//float values

	float mDepthClearValue;
	float mLineWidth;
	float mPolygonOffsetFactor;
	float mPolygonOffsetUnit;
	float mSampleCoverage;

	Color4F mBlendColor;
	Color4F mClearColor;
	RangeF mDepthRange;

	//string  values
	StringRef mVendor;
	StringRef mRenderer;
	StringRef mVersion;
	StringRef mShaderLanguageVersion;
	StringRef mExtensions;

	//texture parameters

	Dictionary<uint, SamplerRenderState*> mSamplerRenderStateDict;

	GraphicsTextureMinFilter mDefaultTextureMinFilter;
	GraphicsTextureMagFilter mDefaultTextureMagFilter;
	GraphicsTextureWrapMode mDefaultTextureWrapS;
	GraphicsTextureWrapMode mDefaultTextureWrapT;

	GraphicsTextureMinFilter mDefaultCubeMapMinFilter;
	GraphicsTextureMagFilter mDefaultCubeMapMagFilter;
	GraphicsTextureWrapMode mDefaultCubeMapWrapS;
	GraphicsTextureWrapMode mDefaultCubeMapWrapT;
#endif

};

MEDUSA_END;
