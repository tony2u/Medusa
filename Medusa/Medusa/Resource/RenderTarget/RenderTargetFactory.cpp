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
	mDefault = nullptr;
	mCurrent = nullptr;
}

RenderTargetFactory::~RenderTargetFactory()
{
	Uninitialize();
}

bool RenderTargetFactory::Initialize()
{
	if (mDefault == nullptr)
	{
		mDefault = new DefaultRenderTarget(mDefaultRenderTargetName);
	}

	mCurrent = mDefault;
	return true;
}

bool RenderTargetFactory::Uninitialize()
{
	Clear();
	mDefault = nullptr;
	mCurrent = nullptr;
	return true;
}

void RenderTargetFactory::Clear()
{
	BaseResourceFactory<IRenderTarget>::Clear();
	mDefault = nullptr;
}


void RenderTargetFactory::SetCurrent(const FileIdRef& fileId)
{
	Share<IRenderTarget> renderTarget = Find(fileId);
	if (renderTarget != nullptr)
	{
		mCurrent = renderTarget;
	}
}

Share<CustomRenderTarget> RenderTargetFactory::CreateCustom(const FileIdRef& fileId, bool setCurrent/*=true*/, ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	Share<IRenderTarget> renderTarget = nullptr;
	if (shareType != ResourceShareType::None)
	{
		renderTarget = Find(fileId);
		if (renderTarget!=nullptr)
		{
			return renderTarget.CastPtr<CustomRenderTarget>();
		}
	}



	if (renderTarget == nullptr)
	{
		renderTarget = new CustomRenderTarget(fileId);
		Add(renderTarget, shareType);
	}

	if (setCurrent)
	{
		mCurrent = renderTarget;
	}

	return renderTarget.CastPtr<CustomRenderTarget>();
}



void RenderTargetFactory::ResetToDefault()
{
	mCurrent = mDefault;
}

void RenderTargetFactory::Resize(const Size2F& newSize)
{
	if (mDefault != nullptr)
	{
		mDefault->Resize(newSize);
	}

	for (auto i : mItems)
	{
		auto& target = i.Value;
		target->Resize(newSize);
	}
}

const StringRef RenderTargetFactory::mDefaultRenderTargetName = "Default";

MEDUSA_END;