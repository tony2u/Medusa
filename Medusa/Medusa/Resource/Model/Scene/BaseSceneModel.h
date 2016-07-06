// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Resource/Model/BaseMultipleModel.h"
#include "Resource/Model/IModelNode.h"
#include "Core/Memory/MemoryData.h"
#include "Core/Collection/List.h"
#include "Resource/Model/Mesh/IMesh.h"
#include "Resource/Material/IMaterial.h"
#include "Resource/Light/ILight.h"
#include "Resource/Camera/Camera.h"
#include "Resource/Timeline/ITimelineModel.h"


MEDUSA_BEGIN;

class BaseSceneModel:public BaseMultipleModel<IMaterial>
{
public:
	BaseSceneModel(const FileIdRef& fileId);
	virtual ~BaseSceneModel(void);
public:
	List<IModelNode*>& Nodes() { return mNodes; }
	List<BaseLightModelNode*>& Lights()  { return mLights; }
	List<BaseCameraModelNode*>& Cameras()  { return mCameras; }

	void AddLight(BaseLightModelNode* light);
	void AddCamera(BaseCameraModelNode* camera);
	void AddVirtualNode(VirtualModelNode* node);

	virtual Share<ITimelineModel> CreateSkeletonTimelineModel()const { return nullptr; }
	virtual Share<ITimelineModel> CreateCameraTimelineModel(StringRef name)const { return nullptr; }
	virtual Share<ITimelineModel> CreateLightTimelineModel(StringRef name)const { return nullptr; }

	virtual Share<Camera> CreateCamera(const FileIdRef& fileId, const Size2F& winSize)const { return nullptr; }
	virtual Share<ILight> CreateLight(const FileIdRef& fileId)const{return nullptr;}

	virtual void UpdateWorldMatrixRecursively(const Matrix4& parentWorldMatrix=Matrix4::Identity);

protected:
	List<IModelNode*> mNodes;	//all nodes
	List<BaseLightModelNode*> mLights;
	List<BaseCameraModelNode*> mCameras;
	List<VirtualModelNode*> mVirtualNodes;

	MemoryData mUserData;
};

MEDUSA_END;