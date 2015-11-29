// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "BaseSceneModel.h"
#include "Resource/Model/Light/BaseLightModelNode.h"
#include "Resource/Model/Camera/BaseCameraModelNode.h"
#include "Resource/Model/Virtual/VirtualModelNode.h"
#include "Resource/Material/IMaterial.h"
#include "Core/Log/Log.h"

MEDUSA_BEGIN;


BaseSceneModel::BaseSceneModel(const FileIdRef& fileId):BaseMultipleModel(fileId)
{
}


BaseSceneModel::~BaseSceneModel(void)
{
	SAFE_DELETE_COLLECTION(mNodes);
}

void BaseSceneModel::UpdateWorldMatrixRecursively( const Matrix4& parentWorldMatrix/*=Matrix4::Identity*/ )
{
	BaseMultipleModel::UpdateWorldMatrixRecursively(parentWorldMatrix);

	FOR_EACH_COLLECTION(i,mNodes)
	{
		IModelNode* node=*i;
		node->UpdateWorldMatrixRecursively(mWorldMatrix.OldValue());
	}
}



void BaseSceneModel::AddLight( BaseLightModelNode* light )
{
	mNodes.Add(light);
	mLights.Add(light);
	light->SetParentModel(this);
}

void BaseSceneModel::AddCamera( BaseCameraModelNode* camera )
{
	mNodes.Add(camera);
	mCameras.Add(camera);
	camera->SetParentModel(this);
}

void BaseSceneModel::AddVirtualNode( VirtualModelNode* node )
{
	mNodes.Add(node);
	mVirtualNodes.Add(node);
	node->SetParentModel(this);
}


INode* BaseSceneModel::CreateCloneInstance()
{
	return nullptr;
}

INode* BaseSceneModel::CreateReferenceInstance()
{
	return nullptr;
}


MEDUSA_END;