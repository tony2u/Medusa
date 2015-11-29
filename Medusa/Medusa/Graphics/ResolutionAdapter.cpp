// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "ResolutionAdapter.h"
#include "Resource/Camera/Camera.h"
#include "Application/Application.h"
#include "Node/INode.h"
#include "Resource/RenderTarget/RenderTargetFactory.h"
#include "Application/ApplicationStatics.h"
#include "Node/Scene/SceneManager.h"
#include "Node/Scene/IScene.h"
#include "Resource/Camera/CameraFactory.h"

MEDUSA_BEGIN;

ResolutionAdapter::ResolutionAdapter()
	:mDefaultCamera2D(nullptr),
	mDefaultCamera3D(nullptr),
	mWinSize(Size2F::Zero),
	mWinRect(Rect2F::Zero),
	mIsLayoutUpdating(false)
{
}

ResolutionAdapter::~ResolutionAdapter(void)
{
	SAFE_RELEASE(mDefaultCamera2D);
	SAFE_RELEASE(mDefaultCamera3D);

}


bool ResolutionAdapter::Initialize(const Size2F& winSize)
{
	mWinSize = winSize;
	mWinRect.Size = mWinSize;
	
	return true;
}


bool Medusa::ResolutionAdapter::InitializeCameras()
{
	mDefaultCamera2D = CameraFactory::Instance().CreateDefault(MEDUSA_PREFIX(Default2D), true, true, ResourceShareType::Share);

	mDefaultCamera3D = CameraFactory::Instance().CreateDefault(MEDUSA_PREFIX(Default3D), false, true, ResourceShareType::Share);
	return true;
}

bool ResolutionAdapter::Uninitialize()
{
	return true;
}

void ResolutionAdapter::SetWinSize(const Size2F& val)
{
	RETURN_IF_EQUAL(mWinSize, val);
	mWinSize = val;
	mWinRect.Size = mWinSize;

	
	FOR_EACH_COLLECTION(i, SceneManager::Instance().MutableScenes())
	{
		IScene* scene = *i;
		scene->SetSize(mWinSize);
		TryAddDirytNode(scene);
	}

	RenderTargetFactory::Instance().Resize(mWinSize);
	ApplicationStatics::Instance().Resize(mWinSize);

	CameraFactory::Instance().Resize(mWinSize);
	Application::Instance().Redraw();
}


bool ResolutionAdapter::IsLayoutDirty() const
{
	return !mDirtyNodes.IsEmpty();
}


bool ResolutionAdapter::TryAddDirytNode(INode* node)
{
	RETURN_FALSE_IF_TRUE(mIsLayoutUpdating);
	return mDirtyNodes.TryAdd(node);
}

bool ResolutionAdapter::IsNodeLayoutDirty(INode* node) const
{
	return mDirtyNodes.Contains(node);
}

bool ResolutionAdapter::IsTopDirtyNode(INode* node) const
{
	INode* parent = node->Parent();
	while (parent != nullptr)
	{
		RETURN_FALSE_IF(IsNodeLayoutDirty(parent));
		parent = parent->Parent();
	}

	return true;
}


void ResolutionAdapter::UpdateLayout()
{
	RETURN_IF_FALSE(IsLayoutDirty());

	mIsLayoutUpdating = true;
	//generate dirty nodes
	FOR_EACH_COLLECTION(i, mDirtyNodes)
	{
		INode* node = *i;
		if (IsTopDirtyNode(node))
		{
			mDirtyList.Add(node);
		}
	}
	mDirtyNodes.Clear();

	FOR_EACH_COLLECTION(i, mDirtyList)
	{
		INode* node = *i;
		node->UpdateLayout();
	}

	mDirtyList.Clear();
	mIsLayoutUpdating = false;
}

bool ResolutionAdapter::TryRemoveDirytNode(INode* node)
{
	RETURN_FALSE_IF_FALSE(IsLayoutDirty());
	return mDirtyNodes.Remove(node);
}



MEDUSA_END;