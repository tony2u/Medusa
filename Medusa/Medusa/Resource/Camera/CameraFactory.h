// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/String/StringRef.h"
#include "Core/Pattern/Singleton.h"
#include "Resource/BaseResourceFactory.h"
#include "Resource/Camera/Camera.h"

MEDUSA_BEGIN;

class CameraFactory:public Singleton<CameraFactory>,public BaseResourceFactory<Camera>
{
	friend class Singleton<CameraFactory>;
public:
	CameraFactory();
	~CameraFactory();
public:
	virtual bool Initialize();
	virtual bool Uninitialize();
public:
	Camera* CreateDefault(StringRef name,bool isOrtho = false,bool isResizeable=true, ResourceShareType shareType = ResourceShareType::Share);

	Camera* CreateDefault(StringRef name, const Size2F& winSize, bool isOrtho = false, bool isResizeable = true,ResourceShareType shareType = ResourceShareType::Share);
	Camera* CreateFromModel(StringRef name, StringRef modelName, const Size2F& winSize, bool isResizeable = true,ResourceShareType shareType = ResourceShareType::Share);

	void Resize(const Size2F& newSize);

protected:
	List<Camera*> mResizeableCameras;
};

MEDUSA_END;