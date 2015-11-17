// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Resource/Effect/Shader/IShader.h"
#include "Rendering/RenderingContext.h"
#include "Core/Log/Log.h"
#include "Core/Collection/List.h"

MEDUSA_BEGIN;

IShader::IShader(const FileIdRef& fileId/*=FileId::Empty*/):IResource(fileId),mShader(0)
{

}

IShader::~IShader()
{
	Uninitialize();
}

bool IShader::Compare( const IShader& shader ) const
{
	return true;
}

bool IShader::Initialize(StringRef source,const List<HeapString>* defines/*=nullptr*/)
{
	if (mShader!=0)
	{
		Uninitialize();
	}
	
	mShader=Render::Instance().CreateShader(ShaderType());
	if (defines==nullptr||defines->IsEmpty())
	{
		Render::Instance().SetShaderSource(mShader,source);
	}
	else
	{
		HeapString tempSource;
		FOR_EACH_COLLECTION(i,*defines)
		{
			tempSource+=*i;
		}

		tempSource+=source;

		Render::Instance().SetShaderSource(mShader,tempSource);

	}
	Render::Instance().CompileShader(mShader);

	int outShaderCompiled=Render::Instance().GetShaderStatus(mShader,GraphicsShaderStatus::CompileStatus);
	
	if (!outShaderCompiled)
	{
		//compile error
		int outInfoLogLength=Render::Instance().GetShaderStatus(mShader,GraphicsShaderStatus::InfoLogLength);
		
		HeapString infoLog((size_t)outInfoLogLength+1);

		Render::Instance().GetShadderInfoLog(mShader,infoLog);
		Log::FormatError("Failed to compile shader:{},Error:{}",mFileId.Name.c_str(),infoLog.Buffer());
		Uninitialize();
	}

	return IsValid();
}

bool IShader::Uninitialize()
{
	if (mShader!=0)
	{
		Render::Instance().DeleteShader(mShader);
		mShader=0;
	}

	return true;
}

void IShader::Apply()
{

}

void IShader::Restore()
{

}



MEDUSA_END;