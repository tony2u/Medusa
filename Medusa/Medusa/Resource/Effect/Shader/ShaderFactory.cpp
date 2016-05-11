// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "ShaderFactory.h"
#include "Resource/Effect/Shader/Vertex/BaseVertexShader.h"
#include "Resource/Effect/Shader/Pixel/BasePixelShader.h"
#include "Resource/Effect/Shader/ShaderCreater.h"

#include "Core/IO/FileSystem.h"
#include "Core/IO/FileInfo.h"
MEDUSA_BEGIN;

ShaderFactory::ShaderFactory()
{

}

ShaderFactory::~ShaderFactory()
{
	
}
bool ShaderFactory::Initialize()
{
	return true;
}

bool ShaderFactory::Uninitialize()
{
	Clear();
	return true;
}


IShader* ShaderFactory::CreateShader( const FileIdRef& fileId,const List<HeapString>* defines/*=nullptr*/,ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	IShader* result = nullptr;
	if (shareType != ResourceShareType::None)
	{
		result = Find(fileId);
		RETURN_SELF_IF_NOT_NULL(result);
	}

	

	result=ShaderCreater::Instance().Create(fileId.Name,fileId);
	if (result==nullptr)
	{
		switch(FileInfo::ExtractType(fileId.Name))
		{
		case FileType::fsh:
			result=new BasePixelShader(fileId);
			break;
		case FileType::vsh:
			result=new BaseVertexShader(fileId);
			break;
		default:
			MEDUSA_ASSERT_FAILED("Unsupported shader file type");
            return nullptr;
		}
	}

	MemoryData data= FileSystem::Instance().ReadAllData(fileId);
	if (data.IsNull())
	{
		Log::FormatError("Cannot find:{}-{}", fileId.Name, fileId.Order);
        delete result;
		return nullptr;
	}
	StringRef str(data.Cast<char>());
	if(result->Initialize(str,defines))
	{
		Add(result, shareType);

		return result;
	}
	else
	{
		SAFE_DELETE(result);
	}

	return nullptr;

}

MEDUSA_END;