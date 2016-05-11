// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "OpenGLES3Render.h"
#include "Core/Log/Log.h"
#include "Geometry/Size3.h"
#include "Geometry/Rect2.h"
#include "Geometry/Cube.h"
#include "Geometry/Point4.h"

MEDUSA_BEGIN;

OpenGLES3Render::OpenGLES3Render(void)
{

}


OpenGLES3Render::~OpenGLES3Render(void)
{
}

#pragma region OpenGL ES 3.0

#pragma region Frame buffer

void OpenGLES3Render::ReadBuffer(GraphicsColorBuffers buffer)const
{
	glReadBuffer((uint)buffer);
	AssertSuccess();
}

void OpenGLES3Render::SetDrawBufferTargets(uint count, const GraphicsColorBuffers* buffers) const
{
	glDrawBuffers(count, (const uint*)buffers);
	AssertSuccess();
}


void OpenGLES3Render::BlitFrameBuffer(const Rect2I& srcRect, const Rect2I& destRect, GraphicsBufferComponentMask mask, GraphicsTextureMagFilter filter) const
{
	glBlitFramebuffer(srcRect.Left(), srcRect.Bottom(), srcRect.Right(), srcRect.Top(), destRect.Left(), destRect.Bottom(), destRect.Right(), destRect.Top(), (int)mask, (uint)filter);
	AssertSuccess();
}

void OpenGLES3Render::SetRenderBufferMultipleSampleStorage(GraphicsRenderBufferInternalFormat format, uint sampleCount, const Size2U& size) const
{
	glRenderbufferStorageMultisample((uint)GraphicsFrameBufferType::RenderBuffer, sampleCount, (uint)format, size.Width, size.Height);
	AssertSuccess();
}

void OpenGLES3Render::AttachTextureLayerToFrameBuffer(GraphicsFrameBufferType frameBuffer, GraphicsAttachment attachment, uint texture, int level, int layer) const
{
	glFramebufferTextureLayer((uint)frameBuffer, (uint)attachment, texture, level, layer);
	AssertSuccess();

}

void OpenGLES3Render::InvalidateFramebuffer(uint numAttachments, const GraphicsAttachment* attachments) const
{
	glInvalidateFramebuffer((uint)GraphicsFrameBufferType::FrameBuffer, numAttachments, (const uint*)attachments);
	AssertSuccess();

}

void OpenGLES3Render::InvalidateSubFramebuffer(uint numAttachments, const GraphicsAttachment* attachments, const Rect2U& rect) const
{
	glInvalidateSubFramebuffer((uint)GraphicsFrameBufferType::FrameBuffer, numAttachments, (const uint*)attachments, rect.Origin.X, rect.Origin.Y, rect.Size.Width, rect.Size.Height);
	AssertSuccess();
}

void OpenGLES3Render::GetInternalFormatParameter(GraphicsInternalFormat internalFormat, GraphicsInternalFormatParameterName name, uint bufferSize, int* outParam) const
{
	glGetInternalformativ((uint)GraphicsFrameBufferType::RenderBuffer, (uint)internalFormat, (uint)name, bufferSize, outParam);
	AssertSuccess();
}




#pragma endregion Frame buffer

#pragma region Texture
void OpenGLES3Render::LoadTexture3D(GraphicsTextureTarget textureTarget, int level, PixelType pixelType, const Size3U& size, int border, const void *pixels) const
{
	glTexImage3D((uint)textureTarget, level, (uint)pixelType.InternalFormat(), size.Width, size.Height, size.Depth, border, (uint)pixelType.Format(), (int)pixelType.DataType(), pixels);
	AssertSuccess();
}

void OpenGLES3Render::LoadSubTexture3D(GraphicsTextureTarget textureTarget, int level, const CubeI& rect, PixelType pixelType, const void *pixels) const
{
	glTexSubImage3D((uint)textureTarget, level, rect.Origin.X, rect.Origin.Y, rect.Origin.Z, rect.Size.Width, rect.Size.Height, rect.Size.Depth, (uint)pixelType.Format(), (int)pixelType.DataType(), pixels);
	AssertSuccess();
}

void OpenGLES3Render::CopySubTexture3D(GraphicsTextureTarget textureTarget, int level, const Point3I& offset, const Rect2I& rect) const
{
	glCopyTexSubImage3D((uint)textureTarget, level, offset.X, offset.Y, offset.Z, rect.Origin.X, rect.Origin.Y, rect.Size.Width, rect.Size.Height);
	AssertSuccess();
}

void OpenGLES3Render::LoadCompressedTexture3D(GraphicsTextureTarget textureTarget, int level, PixelType pixelType, const Size3U& size, int border, uint imageSize, const void *pixels) const
{
	glCompressedTexImage3D((uint)textureTarget, level, (uint)pixelType.InternalFormat(), size.Width, size.Width, size.Height, border, imageSize, pixels);
	AssertSuccess();
}

void OpenGLES3Render::LoadCompressedSubTexture3D(GraphicsTextureTarget textureTarget, int level, PixelType pixelType, const CubeI& rect, uint imageSize, const void *pixels) const
{
	glCompressedTexSubImage3D((uint)textureTarget, level, rect.Origin.X, rect.Origin.Y, rect.Origin.Z, rect.Size.Width, rect.Size.Height, rect.Size.Depth, (uint)pixelType.InternalFormat(), imageSize, pixels);
	AssertSuccess();
}

void OpenGLES3Render::SetTextureStorage2D(GraphicsTextureTarget textureTarget, uint level, PixelType pixelType, const Size2U& size) const
{
	glTexStorage2D((uint)textureTarget, level, (uint)pixelType.InternalFormat(), size.Width, size.Height);
	AssertSuccess();
}

void OpenGLES3Render::SetTextureStorage3D(GraphicsTextureTarget textureTarget, uint level, PixelType pixelType, const Size3U& size) const
{
	glTexStorage3D((uint)textureTarget, level, (uint)pixelType.InternalFormat(), size.Width, size.Height, size.Depth);
	AssertSuccess();
}
#pragma endregion Texture

#pragma region Query
void OpenGLES3Render::GenQueries(uint count, uint* outQueries) const
{
	glGenQueries(count, outQueries);
	AssertSuccess();
}

void OpenGLES3Render::DeleteQueries(uint count, uint* queries) const
{
	glDeleteQueries(count, queries);
	AssertSuccess();
}

bool OpenGLES3Render::IsQuery(uint id) const
{
	bool result = glIsQuery(id) == GL_TRUE;
	AssertSuccess();
	return result;
}

void OpenGLES3Render::BeginQuery(GraphicsQueryTarget target, uint query) const
{
	glBeginQuery((uint)target, query);
	AssertSuccess();
}

void OpenGLES3Render::EndQuery(uint query) const
{
	glEndQuery(query);
	AssertSuccess();
}

int OpenGLES3Render::GetQueryParameter(GraphicsQueryTarget target, GraphicsQueryParameter parameter) const
{
	int outVal;
	glGetQueryiv((uint)target, (uint)parameter, &outVal);
	AssertSuccess();
	return outVal;
}

uint OpenGLES3Render::GetQueryObjectParameter(uint query, GraphicsQueryObjectParameter parameter) const
{
	uint outVal;
	glGetQueryObjectuiv(query, (uint)parameter, &outVal);
	AssertSuccess();
	return outVal;
}

#pragma endregion Query

#pragma region Buffer

void* OpenGLES3Render::MapBufferRange(GraphicsBufferType bufferType, int offset, uint length, GraphicsMapBufferMask mask) const
{
	void* p = glMapBufferRange((uint)bufferType, offset, length, (int)mask);
	AssertSuccess();
	return p;
}

bool OpenGLES3Render::UnmapBuffer(GraphicsBufferType bufferType)const
{
	bool result = glUnmapBuffer((uint)bufferType) == GL_TRUE;
	AssertSuccess();
	return result;
}


void OpenGLES3Render::GetBufferPointer(GraphicsBufferType bufferType, GraphicsBufferPointerName name, void** outResult) const
{
	glGetBufferPointerv((uint)bufferType, (uint)name, outResult);
	AssertSuccess();
}


void OpenGLES3Render::FlushMappedBufferRange(GraphicsBufferType bufferType, int offset, uint length) const
{
	glFlushMappedBufferRange((uint)bufferType, offset, length);
	AssertSuccess();
}

void OpenGLES3Render::BindBufferToBuffer(GraphicsBindBufferTarget target, uint index, uint buffer) const
{
	glBindBufferBase((uint)target, index, buffer);
	AssertSuccess();

}

void OpenGLES3Render::BindBufferRangeToBuffer(GraphicsBindBufferTarget target, uint index, uint buffer, int offset, uint length) const
{
	glBindBufferRange((uint)target, index, buffer, offset, length);
	AssertSuccess();
}


void OpenGLES3Render::ClearBuffer(GraphicsBufferClearMask clearMask, int drawBuffer, const int* val) const
{
	glClearBufferiv((uint)clearMask, drawBuffer, val);
	AssertSuccess();
}

void OpenGLES3Render::ClearBuffer(GraphicsBufferClearMask clearMask, int drawBuffer, const uint* val) const
{
	glClearBufferuiv((uint)clearMask, drawBuffer, val);
	AssertSuccess();
}

void OpenGLES3Render::ClearBuffer(GraphicsBufferClearMask clearMask, int drawBuffer, const float* val) const
{
	glClearBufferfv((uint)clearMask, drawBuffer, val);
	AssertSuccess();
}

void OpenGLES3Render::ClearBuffer(GraphicsBufferClearMask clearMask, int drawBuffer, float depth, int stencil) const
{
	glClearBufferfi((uint)clearMask, drawBuffer, depth, stencil);
	AssertSuccess();
}


void OpenGLES3Render::CopyBufferSubData(GraphicsBufferType fromTarget, uint fromOffset, GraphicsBufferType toTarget, uint toOffset, uint size) const
{
	glCopyBufferSubData((uint)fromTarget, (uint)toTarget, fromOffset, toOffset, size);
	AssertSuccess();
}


int64 OpenGLES3Render::GetBufferParameter64(GraphicsBufferType bufferType, GraphicsBufferParameter parameter) const
{
	int64 outVal;
	glGetBufferParameteri64v((uint)bufferType, (uint)parameter, &outVal);
	AssertSuccess();
	return outVal;
}

#pragma endregion Buffer

#pragma region Uniform

void OpenGLES3Render::SetUniformMatrix23(int location, uint count, const float* data, bool isTransposed /*= false*/) const
{
	glUniformMatrix2x3fv(location, count, isTransposed, data);
	AssertSuccess();
}

void OpenGLES3Render::SetUniformMatrix32(int location, uint count, const float* data, bool isTransposed /*= false*/) const
{
	glUniformMatrix3x2fv(location, count, isTransposed, data);
	AssertSuccess();
}

void OpenGLES3Render::SetUniformMatrix24(int location, uint count, const float* data, bool isTransposed /*= false*/) const
{
	glUniformMatrix2x4fv(location, count, isTransposed, data);
	AssertSuccess();
}

void OpenGLES3Render::SetUniformMatrix42(int location, uint count, const float* data, bool isTransposed /*= false*/) const
{
	glUniformMatrix4x2fv(location, count, isTransposed, data);
	AssertSuccess();
}

void OpenGLES3Render::SetUniformMatrix34(int location, uint count, const float* data, bool isTransposed /*= false*/) const
{
	glUniformMatrix3x4fv(location, count, isTransposed, data);
	AssertSuccess();
}

void OpenGLES3Render::SetUniformMatrix43(int location, uint count, const float* data, bool isTransposed /*= false*/) const
{
	glUniformMatrix4x3fv(location, count, isTransposed, data);
	AssertSuccess();
}


void OpenGLES3Render::GetUniformIndices(uint program, uint uniformCount, const char* const* uniformNames, uint* outUniformIndices) const
{
	glGetUniformIndices(program, uniformCount, uniformNames, outUniformIndices);
	AssertSuccess();
}

void OpenGLES3Render::GetActiveUniformParameter(uint program, uint uniformCount, const uint* uniformIndices, GraphicsUniformParameterName name, int* outParam) const
{
	glGetActiveUniformsiv(program, uniformCount, uniformIndices, (uint)name, outParam);
	AssertSuccess();

}

uint OpenGLES3Render::GetUniformBlockIndex(uint program, const char* uniformBlockName) const
{
	uint index = glGetUniformBlockIndex(program, uniformBlockName);
	AssertSuccess();
	return index;
}

void OpenGLES3Render::GetActiveUniformBlockParameter(uint program, uint uniformBlockIndex, GraphicsUniformBlockParameterName name, int* outParam) const
{
	glGetActiveUniformBlockiv(program, uniformBlockIndex, (uint)name, outParam);
	AssertSuccess();
}

void OpenGLES3Render::GetActiveUniformBlockName(uint program, uint uniformBlockIndex, uint outNameBufferSize, uint& outLength, char* outName) const
{
	glGetActiveUniformBlockName(program, uniformBlockIndex, outNameBufferSize, (int*)&outLength, outName);
	AssertSuccess();
}

void OpenGLES3Render::SetUniformBlockBinding(uint program, uint uniformBlockIndex, uint uniformBlockBinding) const
{
	glUniformBlockBinding(program, uniformBlockIndex, uniformBlockBinding);
	AssertSuccess();
}
void OpenGLES3Render::GetUniformArray(uint program, int location, uint* outData) const
{
	glGetUniformuiv(program, location, outData);
	AssertSuccess();
}

void OpenGLES3Render::SetUniform(int location, uint x)const
{
	glUniform1ui(location, x);
	AssertSuccess();
}

void OpenGLES3Render::SetUniform(int location, uint x, uint y)const
{
	glUniform2ui(location, x, y);
	AssertSuccess();
}

void OpenGLES3Render::SetUniform(int location, uint x, uint y, uint z)const
{
	glUniform3ui(location, x, y, z);
	AssertSuccess();
}

void OpenGLES3Render::SetUniform(int location, uint x, uint y, uint z, uint w)const
{
	glUniform4ui(location, x, y, z, w);
	AssertSuccess();
}

void OpenGLES3Render::SetUniformArray1(int location, uint count, const uint* data)const
{
	glUniform1uiv(location, count, data);
	AssertSuccess();
}

void OpenGLES3Render::SetUniformArray2(int location, uint count, const uint* data)const
{
	glUniform2uiv(location, count, data);
	AssertSuccess();
}

void OpenGLES3Render::SetUniformArray3(int location, uint count, const uint* data)const
{
	glUniform3uiv(location, count, data);
	AssertSuccess();
}

void OpenGLES3Render::SetUniformArray4(int location, uint count, const uint* data)const
{
	glUniform4uiv(location, count, data);
	AssertSuccess();
}

#pragma endregion Uniform

#pragma region VertexArray

void OpenGLES3Render::BindVertexArray(uint id) const
{
	glBindVertexArray(id);
	AssertSuccess();
}

void OpenGLES3Render::DeleteVertexArrays(uint count, uint* arrays) const
{
	glDeleteVertexArrays(count, arrays);
	AssertSuccess();

}

void OpenGLES3Render::GenVertexArrays(uint count, uint* outArrays) const
{
	glGenVertexArrays(count, outArrays);
	AssertSuccess();

}

bool OpenGLES3Render::IsVertexArray(uint id) const
{
	bool result = glIsVertexArray(id) == GL_TRUE;
	AssertSuccess();
	return result;
}


void OpenGLES3Render::SetVertexAttributeIntegerPointer(uint index, uint componentCount, GraphicsIntegerDataType type, uint stride, const void* data)const
{
	glVertexAttribIPointer(index, componentCount, (uint)type, stride, data);
	AssertSuccess();
}

void OpenGLES3Render::GetVertexAttributeValueInt(uint index, GraphicsVertexAttributeParameter parameter, int* outParams) const
{
	glGetVertexAttribIiv(index, (uint)parameter, outParams);
	AssertSuccess();
}

void OpenGLES3Render::GetVertexAttributeValueUInt(uint index, GraphicsVertexAttributeParameter parameter, uint* outParams) const
{
	glGetVertexAttribIuiv(index, (uint)parameter, outParams);
	AssertSuccess();
}

void OpenGLES3Render::SetVertexAttribute(uint index, const Point4I& pos) const
{
	glVertexAttribI4i(index, pos.X, pos.Y, pos.Z, pos.W);
	AssertSuccess();
}

void OpenGLES3Render::SetVertexAttribute(uint index, const Point4U& pos) const
{
	glVertexAttribI4ui(index, pos.X, pos.Y, pos.Z, pos.W);
	AssertSuccess();
}

void OpenGLES3Render::SetVertexAttributeArray4(uint index, const int* data) const
{
	glVertexAttribI4iv(index, data);
	AssertSuccess();
}

void OpenGLES3Render::SetVertexAttributeArray4(uint index, const uint* data) const
{
	glVertexAttribI4uiv(index, data);
	AssertSuccess();
}


void OpenGLES3Render::SetVertexAttributeDivisor(uint index, uint divisor) const
{
	glVertexAttribDivisor(index, divisor);
	AssertSuccess();
}
#pragma endregion VertexArray

#pragma region Transform feedback

void OpenGLES3Render::BeginTransformFeedback(GraphicsTransformFeedbackPrimitiveMode mode) const
{
	glBeginTransformFeedback((uint)mode);
	AssertSuccess();
}

void OpenGLES3Render::EndTransformFeedback() const
{
	glEndTransformFeedback();
	AssertSuccess();
}

void OpenGLES3Render::SetTransformFeedbackVaryings(uint program, uint count, const char* const* varyings, GraphicsTransformFeedbackBufferMode bufferMode) const
{
	glTransformFeedbackVaryings(program, count, varyings, (uint)bufferMode);
	AssertSuccess();
}

void OpenGLES3Render::GetTransformFeedbackVaryings(uint program, uint index, uint outVaryingNameBufferSize, char* outVaryingName, uint& outVaryingNameLength, uint& outVaryingType, uint& outVaryingSize) const
{
	glGetTransformFeedbackVarying(program, index, outVaryingNameBufferSize, (int*)&outVaryingNameLength, (int*)&outVaryingSize, &outVaryingType, outVaryingName);
	AssertSuccess();
}

void OpenGLES3Render::BindTransformFeedback(uint id) const
{
	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, id);
	AssertSuccess();
}

void OpenGLES3Render::DeleteTransformFeedbacks(uint count, const uint* ids) const
{
	glDeleteTransformFeedbacks(count, ids);
	AssertSuccess();
}

void OpenGLES3Render::GenTransformFeedbacks(uint count, uint* outIds)const
{
	glGenTransformFeedbacks(count, outIds);
	AssertSuccess();
}

bool OpenGLES3Render::IsTransformFeedback(uint id) const
{
	bool r = glIsTransformFeedback(id) == GL_TRUE;
	AssertSuccess();
	return r;
}

void OpenGLES3Render::PauseTransformFeedback() const
{
	glPauseTransformFeedback();
	AssertSuccess();

}

void OpenGLES3Render::ResumeTransformFeedback() const
{
	glResumeTransformFeedback();
	AssertSuccess();

}

#pragma endregion Transform feedback

#pragma region Program


int OpenGLES3Render::GetFragDataLocation(uint program, const char* name) const
{
	int result = glGetFragDataLocation(program, name);
	AssertSuccess();
	return result;
}

void OpenGLES3Render::GetProgramBinary(uint program, uint outBufferSize, uint& outLength, uint& outBinaryFormat, void* outBinary) const
{
	glGetProgramBinary(program, outBufferSize, (int*)&outLength, &outBinaryFormat, outBinary);
	AssertSuccess();
}

void OpenGLES3Render::LoadProgramBinary(uint program, uint outbinaryFormat, const void* binary, uint length) const
{
	glProgramBinary(program, outbinaryFormat, binary, length);
	AssertSuccess();
}

void OpenGLES3Render::SetProgramParamter(uint program, GraphicsProgramParameterName name, int val) const
{
	glProgramParameteri(program, (uint)name, val);
	AssertSuccess();

}

#pragma endregion Program

#pragma region Draw

void OpenGLES3Render::DrawIndicesRange(GraphicsDrawMode mode, uint start, uint end, uint count, GraphicsDataType type, const void* indices) const
{
	glDrawRangeElements((uint)mode, start, end, count, (uint)type, indices);
	AssertSuccess();
}

void OpenGLES3Render::DrawArraysInstanced(GraphicsDrawMode mode, int first, uint count, uint instanceCount) const
{
	glDrawArraysInstanced((uint)mode, first, count, instanceCount);
	AssertSuccess();
}

void OpenGLES3Render::DrawIndicesInstanced(GraphicsDrawMode mode, uint count, GraphicsDataType type, const void* indices, uint instanceCount) const
{
	glDrawElementsInstanced((uint)mode, count, (uint)type, indices, instanceCount);
	AssertSuccess();
}


#pragma endregion Draw

#pragma region Sync


intp OpenGLES3Render::CreateSync(GraphicsSyncCondition condition) const
{
	intp r = (intp)glFenceSync((uint)condition, 0);
	AssertSuccess();
	return r;
}

bool OpenGLES3Render::IsSync(intp sync) const
{
	bool r = glIsSync((GLsync)sync) == GL_TRUE;
	AssertSuccess();
	return r;
}

void OpenGLES3Render::DeleteSync(intp sync) const
{
	glDeleteSync((GLsync)sync);
	AssertSuccess();
}

void OpenGLES3Render::ClientWaitSync(intp sync, GraphicsSyncMask mask, uint64 timeout) const
{
	glClientWaitSync((GLsync)sync, (int)mask, timeout);
	AssertSuccess();
}

void OpenGLES3Render::WaitSync(intp sync, GraphicsSyncMask mask, uint64 timeout) const
{
	glWaitSync((GLsync)sync, (int)mask, timeout);
	AssertSuccess();
}

void OpenGLES3Render::GetSyncParameter(intp sync, GraphicsSyncParameterName name, uint outBufferSize, uint& outLength, int* outValues) const
{
	glGetSynciv((GLsync)sync, (uint)name, outBufferSize, (int*)&outLength, outValues);
	AssertSuccess();
}


#pragma endregion Sync

#pragma region Sampler


void OpenGLES3Render::GenSamplers(uint count, uint* outSamplers) const
{
	glGenSamplers(count, outSamplers);
	AssertSuccess();
}

void OpenGLES3Render::DeleteSamplers(uint count, const uint* samplers) const
{
	glDeleteSamplers(count, samplers);
	AssertSuccess();
}

bool OpenGLES3Render::IsSampler(uint sampler) const
{
	bool r = glIsSampler(sampler) == GL_TRUE;
	AssertSuccess();
	return r;
}

void OpenGLES3Render::BindSampler(GraphicsTextureUnits unit, uint sampler) const
{
	glBindSampler((uint)unit, sampler);
	AssertSuccess();

}

void OpenGLES3Render::SetSamplerParameter(uint sampler, GraphicsSamplerParameterName name, int val) const
{
	glSamplerParameteri(sampler, (uint)name, val);
	AssertSuccess();

}

void OpenGLES3Render::SetSamplerParameter(uint sampler, GraphicsSamplerParameterName name, float val) const
{
	glSamplerParameterf(sampler, (uint)name, val);
	AssertSuccess();
}

void OpenGLES3Render::SetSamplerParameterArray(uint sampler, GraphicsSamplerParameterName name, const int* values) const
{
	glSamplerParameteriv(sampler, (uint)name, values);
	AssertSuccess();
}

void OpenGLES3Render::SetSamplerParameterArray(uint sampler, GraphicsSamplerParameterName name, const float* values) const
{
	glSamplerParameterfv(sampler, (uint)name, values);
	AssertSuccess();
}

void OpenGLES3Render::GetSamplerParameter(uint sampler, GraphicsSamplerParameterName name, int* outParam) const
{
	glGetSamplerParameteriv(sampler, (uint)name, outParam);
	AssertSuccess();
}

void OpenGLES3Render::GetSamplerParameter(uint sampler, GraphicsSamplerParameterName name, float* outParam) const
{
	glGetSamplerParameterfv(sampler, (uint)name, outParam);
	AssertSuccess();
}


#pragma endregion Sampler

#pragma region Get


bool OpenGLES3Render::TryGetIntegerWithIndex(GraphicsIntegerName name, uint index, int& outVal) const
{
	glGetIntegeri_v((uint)name, index, &outVal);
	return IsSuccess();
}

bool OpenGLES3Render::TryGetInteger64(GraphicsIntegerName name, int64& outVal) const
{
	glGetInteger64v((uint)name, &outVal);
	return IsSuccess();
}

bool OpenGLES3Render::TryGetInteger64WithIndex(GraphicsIntegerName name, uint index, int64& outVal) const
{
	glGetInteger64i_v((uint)name, index, &outVal);
	return IsSuccess();
}


bool OpenGLES3Render::TryGetStringWithIndex(GraphicsStringName name, uint index, StringRef& outVal) const
{
	const byte* str = glGetStringi((uint)name, index);
	outVal.ForceSetBuffer((const char*)str);
	outVal.ForceUpdateLength();

	return IsSuccess();
}

#pragma endregion Get

#pragma endregion OpenGL ES 3.0


MEDUSA_END;
