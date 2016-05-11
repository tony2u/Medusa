// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "RenderTargetFactory.h"
#include "Resource/RenderTarget/DefaultRenderTarget.h"
#include "Resource/RenderTarget/CustomRenderTarget.h"
MEDUSA_BEGIN;

RenderTargetFactory::RenderTargetFactory()
{
	mDefault=nullptr;
	mCurrent=nullptr;
}

RenderTargetFactory::~RenderTargetFactory()
{
	
}

bool RenderTargetFactory::Initialize()
{
	if (mDefault==nullptr)
	{
		mDefault = new DefaultRenderTarget(mDefaultRenderTargetName);
	}

	mCurrent=mDefault;
	return true;
}

bool RenderTargetFactory::Uninitialize()
{
	Clear();
	SAFE_RELEASE(mDefault);
	return true;
}

void RenderTargetFactory::Clear()
{
	BaseResourceFactory<IRenderTarget>::Clear();
	SAFE_RELEASE(mDefault);
}


void RenderTargetFactory::SetCurrent( const FileIdRef& fileId )
{
	IRenderTarget* renderTarget= Find(fileId);
	if (renderTarget!=nullptr)
	{
		mCurrent=renderTarget;
	}
}

CustomRenderTarget* RenderTargetFactory::CreateCustom( const FileIdRef& fileId,bool setCurrent/*=true*/ ,ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	CustomRenderTarget* renderTarget = nullptr;
	if (shareType != ResourceShareType::None)
	{
		renderTarget = (CustomRenderTarget*)Find(fileId);
		RETURN_SELF_IF_NOT_NULL(renderTarget);
	}



	if (renderTarget==nullptr)
	{
		renderTarget=new CustomRenderTarget(fileId);
		Add(renderTarget, shareType);
	}

	if (setCurrent)
	{
		mCurrent=renderTarget;
	}

	return renderTarget;
}



void RenderTargetFactory::ResetToDefault()
{
	mCurrent=mDefault;
}

void RenderTargetFactory::Resize(const Size2F& newSize)
{
	if (mDefault!=nullptr)
	{
		mDefault->Resize(newSize);
	}

	FOR_EACH_COLLECTION(i, mItems)
	{
		IRenderTarget* target = i->Value;
		target->Resize(newSize);
	}
}

const StringRef RenderTargetFactory::mDefaultRenderTargetName="Default";

MEDUSA_END;