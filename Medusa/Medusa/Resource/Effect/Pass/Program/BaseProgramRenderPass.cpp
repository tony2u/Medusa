// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Resource/Effect/Pass/Program/BaseProgramRenderPass.h"
#include "Rendering/RenderingContext.h"
#include "Resource/Effect/Shader/Vertex/BaseVertexShader.h"
#include "Resource/Effect/Shader/Pixel/BasePixelShader.h"
#include "Rendering/Batch/IRenderBatch.h"
#include "Graphics/State/ProgramRenderState.h"
#include "Graphics/State/RenderStateMachine.h"
#include "Resource/Effect/Shader/Parameter/ShaderAttribute.h"
#include "Resource/Effect/Shader/Parameter/ShaderConstant.h"
#include "Resource/Effect/Shader/Parameter/ShaderConstantInitializer.h"
#include "Core/Log/Log.h"
#include "Resource/ResourceNames.h"


MEDUSA_BEGIN;

BaseProgramRenderPass::BaseProgramRenderPass( const FileIdRef& fileId,IShader* vertexShader,IShader* pixelShader ,int index/*=0*/)
	:IRenderPass(fileId,index),mVertexShader(vertexShader),mPixelShader(pixelShader)
{
	mManagedAttributes.SetAll(nullptr);

	mProgramState=new ProgramRenderState(0);
	mProgramState->Retain();

	SAFE_RETAIN(mVertexShader);
	SAFE_RETAIN(mPixelShader);
}

BaseProgramRenderPass::~BaseProgramRenderPass()
{
	if (mProgramState->Program()!=0)
	{
		Render::Instance().DeleteProgram(mProgramState->Program());
		mProgramState->SetProgram(0);
		mIsLinked=false;
	}

	SAFE_DELETE_DICTIONARY_VALUE(mUniforms);
	SAFE_DELETE_DICTIONARY_VALUE(mAttributes);

	SAFE_RELEASE(mProgramState);

	SAFE_RELEASE(mVertexShader);
	SAFE_RELEASE(mPixelShader);
}

void BaseProgramRenderPass::Apply()
{
	IRenderPass::Apply();
	RenderStateMachine::Instance().Push(mProgramState);

	if (mVertexShader!=nullptr)
	{
		mVertexShader->Apply();
	}

	if (mPixelShader!=nullptr)
	{
		mPixelShader->Apply();
	}

	
}


void BaseProgramRenderPass::Restore()
{
	if (mVertexShader!=nullptr)
	{
		mVertexShader->Restore();
	}

	if (mPixelShader!=nullptr)
	{
		mPixelShader->Restore();
	}
	RenderStateMachine::Instance().Pop(mProgramState);

	IRenderPass::Restore();
}

bool BaseProgramRenderPass::Initialize()
{
	if (mProgramState->Program()!=0)
	{
		Uninitialize();
	}

	uint newProgram=Render::Instance().CreateProgram();
	RETURN_FALSE_IF_ZERO(newProgram);
	mProgramState->SetProgram(newProgram);
	if (mVertexShader!=nullptr)
	{
		Render::Instance().AttachShader(newProgram,mVertexShader->Shader());
	}

	if (mPixelShader!=nullptr)
	{
		Render::Instance().AttachShader(newProgram,mPixelShader->Shader());
	}

	if (!IsLinked())
	{
		Link();
	}

	return true;	
}

bool BaseProgramRenderPass::Uninitialize()
{
	if (mProgramState->Program()!=0)
	{
		Render::Instance().DeleteProgram(mProgramState->Program());
		mProgramState->SetProgram(0);
		mIsLinked=false;
	}

	SAFE_DELETE_DICTIONARY_VALUE(mUniforms);
	SAFE_DELETE_DICTIONARY_VALUE(mAttributes);
	return true;

}


void BaseProgramRenderPass::UpdateShaderVariables( RenderingStep step )
{
	FOR_EACH_COLLECTION(i,mUniforms)
	{
		ShaderConstant* uniform=i->Value;
		ShaderConstantInitializer::Instance().Update(step,*uniform);
	}
}

void BaseProgramRenderPass::Link()
{
	RETURN_IF(mProgramState->Program()==0||mIsLinked);
	SAFE_DELETE_DICTIONARY_VALUE(mUniforms);
	SAFE_DELETE_DICTIONARY_VALUE(mAttributes);

	uint program=mProgramState->Program();
	Render::Instance().LinkProgram(program);
	int outLinkStatus=Render::Instance().GetProgramStatus(program,GraphicsProgramStatus::LinkStatus);

	if (!outLinkStatus)
	{
		//link error
		int outInfoLogLength=Render::Instance().GetProgramStatus(program,GraphicsProgramStatus::InfoLogLength);

		HeapString infoLog((size_t)outInfoLogLength+1,true);
		Render::Instance().GetProgramInfoLog(program,infoLog);
		Log::FormatError("Failed to link effect:{}",infoLog.Buffer());
		Uninitialize();
		return ;
	}

	Render::Instance().ValidateProgram(program);
	int outValidateStatus=Render::Instance().GetProgramStatus(program,GraphicsProgramStatus::ValidateStatus);

	if (!outValidateStatus)
	{
		//link error
		int outInfoLogLength=Render::Instance().GetProgramStatus(program,GraphicsProgramStatus::InfoLogLength);

		HeapString infoLog((size_t)outInfoLogLength+1,true);
		Render::Instance().GetProgramInfoLog(program,infoLog);
		Log::FormatError("Failed to validate effect:{}",infoLog.Buffer());
		Uninitialize();
		return;
	}
	RenderStateMachine::Instance().Push(mProgramState);

	//add all uniforms
	uint uniformCount=(uint)Render::Instance().GetProgramStatus(program,GraphicsProgramStatus::ActiveUniformCount);
	uint maxUniformNameLength=(uint)Render::Instance().GetProgramStatus(program,GraphicsProgramStatus::MaxActiveUniformNameLength);
	HeapString outName((size_t)maxUniformNameLength+1,true);
	FOR_EACH_SIZE(i,uniformCount)
	{
		int outSize;
		uint outDataType;
		Render::Instance().GetActiveUniformName(program,static_cast<uint>(i),outSize,outDataType,outName);
		int index= Render::Instance().GetUniformLocation(program,outName);	//NOTE: Cannot use i as index
		ShaderConstant* uniform=new ShaderConstant(this,index,outName,(GraphicsUniformDataType)outDataType);
		mUniforms.Add(outName,uniform);
	}

	if(!mUniforms.ContainsOtherKey(ShaderConstantNames::WorldViewProjectMatrix,ShaderConstantNames::WorldViewProjectMatrix.HashCode()))
	{
		mFlags|=RenderPassFlags::SuppressWorldViewProjectMatrixUniform;
	}

	//add all attributes
	uint attributeCount=(uint)Render::Instance().GetProgramStatus(program,GraphicsProgramStatus::ActiveAttributeCount);
	uint maxAttributeNameLength=(uint)Render::Instance().GetProgramStatus(program,GraphicsProgramStatus::MaxActiveAttributeNameLength);
	outName.ReserveLength(maxAttributeNameLength);
	FOR_EACH_SIZE(i,attributeCount)
	{
		int outSize;
		uint outDataType;

		Render::Instance().GetActiveAttributeName(program,static_cast<uint>(i),outSize,outDataType,outName);
		int index= Render::Instance().GetVertexAttributeLocation(program,outName);	//NOTE: Cannot use i as index

		ShaderAttribute* attribute=new ShaderAttribute(this,index,outName,(GraphicsAttributeDataType)outDataType);
		mAttributes.Add(outName,attribute);
		TryAddToManagedAttributes(outName, attribute);
	}
	RenderStateMachine::Instance().Pop(mProgramState);

	mIsLinked=true;
}


ShaderConstant* BaseProgramRenderPass::GetConstant(const StringRef& name)const
{
	return mUniforms.TryGetValueWithFailed(name,nullptr);
}

ShaderAttribute* BaseProgramRenderPass::GetAttribute(const StringRef& name)const
{
	return mAttributes.TryGetValueWithFailed(name,nullptr);
}


ShaderAttribute* BaseProgramRenderPass::GetAttributeByIndex(ShaderAttributeIndex index) const
{
	return mManagedAttributes[(uint)index];
}

void BaseProgramRenderPass::Validate()
{
	FOR_EACH_COLLECTION(i,mUniforms)
	{
		const ShaderConstant* uniform=i->Value;
		uniform->Validate();
	}

	FOR_EACH_COLLECTION(i,mAttributes)
	{
		const ShaderAttribute* attribute=i->Value;
		attribute->Validate();
	}
}

void BaseProgramRenderPass::Invalidate()
{
	FOR_EACH_COLLECTION(i,mUniforms)
	{
		ShaderConstant* uniform=i->Value;
		uniform->Invalidate();
	}

	FOR_EACH_COLLECTION(i,mAttributes)
	{
		ShaderAttribute* attribute=i->Value;
		attribute->Invalidate();
	}
}

bool BaseProgramRenderPass::TryAddToManagedAttributes(const StringRef& name, ShaderAttribute* val)
{
	if (name==ShaderAttributeNames::VertexArray)
	{
		mManagedAttributes[(uint)ShaderAttributeIndex::VertexArray] = val;
	}
	else if (name == ShaderAttributeNames::TexCoordArray)
	{
		mManagedAttributes[(uint)ShaderAttributeIndex::TexCoordArray] = val;
	}
	else if (name == ShaderAttributeNames::ColorArray)
	{
		mManagedAttributes[(uint)ShaderAttributeIndex::ColorArray] = val;
	}
	else if (name == ShaderAttributeNames::NormalArray)
	{
		mManagedAttributes[(uint)ShaderAttributeIndex::NormalArray] = val;
	}
	else if (name == ShaderAttributeNames::TangentArray)
	{
		mManagedAttributes[(uint)ShaderAttributeIndex::TangentArray] = val;
	}
	else
	{
		return false;
	}

	return true;
}



MEDUSA_END;