// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "RenderPassFactory.h"
#include "Resource/Effect/Pass/RenderPassDescription.h"
#include "Resource/Effect/Pass/Program/BaseProgramRenderPass.h"
#include "Resource/Effect/Pass/RenderPassCreater.h"
#include "Resource/ResourceNames.h"
#include "Resource/Effect/Shader/ShaderFactory.h"

MEDUSA_BEGIN;

RenderPassFactory::RenderPassFactory()
{

}

RenderPassFactory::~RenderPassFactory()
{

}


bool RenderPassFactory::Initialize()
{
	RegisterRenderPassDescription(RenderPassNames::Texture, VertexShaderFiles::Texture, PixelShaderFiles::Texture);
	RegisterRenderPassDescription(RenderPassNames::PositionColor, VertexShaderFiles::Position, PixelShaderFiles::Color);
	RegisterRenderPassDescription(RenderPassNames::POD, VertexShaderFiles::POD, PixelShaderFiles::POD);
	RegisterRenderPassDescription(RenderPassNames::Shape, VertexShaderFiles::Shape, PixelShaderFiles::Shape);

	return true;
}

bool RenderPassFactory::Uninitialize()
{
	Clear();
	SAFE_DELETE_DICTIONARY_VALUE(mRenderPassDescriptions);
	return true;
}


RenderPassDescription* RenderPassFactory::GetRenderPassDescription(StringRef name)
{
	return mRenderPassDescriptions.TryGetValueWithFailed(name, nullptr);
}

void RenderPassFactory::RegisterRenderPassDescription(StringRef name, const FileIdRef& vertexShaderFile, const FileIdRef& pixelShaderFile, int index/*=0*/, const List<HeapString>* defines/*=nullptr*/)
{
	mRenderPassDescriptions.Add(name, new RenderPassDescription(name, vertexShaderFile, pixelShaderFile, index, defines));
}

bool RenderPassFactory::UnregisterRenderPassDescription(StringRef name)
{
	RenderPassDescription* description = mRenderPassDescriptions.TryGetValueWithFailed(name, nullptr);
	if (description != nullptr)
	{
		mRenderPassDescriptions.RemoveKey(name);
		SAFE_DELETE(description);
		return true;
	}

	return false;
}

IRenderPass* RenderPassFactory::CreateRenderPass(const RenderPassDescription& description, const List<HeapString>* defines/*=nullptr*/, ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	return CreateRenderPass(description.Name, description.VertexShaderFile, description.PixelShaderFile, description.Index, defines, shareType);
}

IRenderPass* RenderPassFactory::CreateRenderPass(const FileIdRef& fileId, const FileIdRef& vertexShaderFile, const FileIdRef& pixelShaderFile, int index/*=0*/, const List<HeapString>* defines/*=nullptr*/, ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	IShader* vertexShader = ShaderFactory::Instance().CreateShader(vertexShaderFile, defines);
	IShader* pixelShader = ShaderFactory::Instance().CreateShader(pixelShaderFile, defines);

	return CreateRenderPass(fileId, vertexShader, pixelShader, index, shareType);
}

IRenderPass* RenderPassFactory::CreateRenderPass(const FileIdRef& fileId, IShader* vertexShader, IShader* pixelShader, int index/*=0*/, ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	IRenderPass* pass = Find(fileId);
	RETURN_SELF_IF_NOT_NULL(pass);

	pass = RenderPassCreater::Instance().Create(fileId.Name, fileId, vertexShader, pixelShader, index);
	if (pass == nullptr)
	{
		pass = new BaseProgramRenderPass(fileId, vertexShader, pixelShader, index);
	}

	if (pass != nullptr&&!pass->Initialize())
	{
		SAFE_DELETE(pass);
        return nullptr;
	}

	Add(pass, shareType);
    
	return pass;
}

IRenderPass* RenderPassFactory::CreateRenderPass(const FileIdRef& fileId, const List<HeapString>* defines/*=nullptr*/, ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	IRenderPass* pass = Find(fileId);
	RETURN_SELF_IF_NOT_NULL(pass);

	RenderPassDescription* description = GetRenderPassDescription(fileId.Name);
	RETURN_NULL_IF_NULL(description);

	if (defines != nullptr)
	{
		return CreateRenderPass(*description, defines, shareType);
	}

	if (!description->Defines.IsEmpty())
	{
		return CreateRenderPass(*description, &description->Defines, shareType);
	}

	return CreateRenderPass(*description, nullptr, shareType);

}


MEDUSA_END;