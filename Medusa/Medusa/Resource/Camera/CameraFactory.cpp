// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "CameraFactory.h"
#include "Resource/Camera/Camera.h"
#include "Resource/Model/ModelFactory.h"
#include "Resource/Model/Scene/BaseSceneModel.h"
#include "Graphics/ResolutionAdapter.h"

MEDUSA_BEGIN;

CameraFactory::CameraFactory()
{

}

CameraFactory::~CameraFactory()
{

}

bool CameraFactory::Initialize()
{
	return true;
}

bool CameraFactory::Uninitialize()
{
	Clear();
	mResizeableCameras.Clear();
	return true;
}

Camera* CameraFactory::CreateDefault(StringRef name, bool isOrtho /*= false*/, bool isResizeable /*= true*/,ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	Size2F winSize = ResolutionAdapter::Instance().WinSize();
	return CreateDefault(name, winSize, isOrtho, isResizeable,shareType);
}

Camera* CameraFactory::CreateDefault(StringRef name, const Size2F& winSize, bool isOrtho/*=false*/, bool isResizeable /*= true*/, ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	Camera* camera = Find(name);
	RETURN_SELF_IF_NOT_NULL(camera);

	if (camera == nullptr)
	{
		camera = new Camera(name);
		camera->ResetDefault(winSize, isOrtho);
		Add(camera, shareType);

		if (isResizeable)
		{
			mResizeableCameras.Add(camera);
		}
	}

	return camera;
}


Camera* CameraFactory::CreateFromModel(StringRef name, StringRef modelName, const Size2F& winSize, bool isResizeable /*= true*/, ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	Camera* camera = Find(name);
	RETURN_SELF_IF_NOT_NULL(camera);

	if (camera == nullptr)
	{
		BaseSceneModel* model = (BaseSceneModel*)ModelFactory::Instance().Create(modelName);
		if (model != nullptr)
		{
			camera = model->CreateCamera(name, winSize);
			Add(camera, shareType);
			if (isResizeable)
			{
				mResizeableCameras.Add(camera);
			}
		}
	}


	return camera;
}

void CameraFactory::Resize(const Size2F& newSize)
{
	FOR_EACH_ITEM_TO(mResizeableCameras,Resize(newSize));
}


MEDUSA_END;

