// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Graphics/Render/OpenGLES2Render.h"

MEDUSA_BEGIN;
class OpenGLES3Render :public OpenGLES2Render
{
public:
	OpenGLES3Render(void);
	virtual ~OpenGLES3Render(void);

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