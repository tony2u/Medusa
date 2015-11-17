// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Resource/Model/IModel.h"
#include "Resource/Model/Mesh/MeshModelNode.h"
#include "Node/INode.h"

MEDUSA_BEGIN;

template<typename TMesh,typename TMaterial>
class BaseSingleModel:public IModel
{
public:
	BaseSingleModel(const FileIdRef& fileId):IModel(fileId),mMeshModelNode(fileId.Name),mMaterial(nullptr)
	{
		mMeshModelNode.SetParentModel(this);
	}
	virtual ~BaseSingleModel(void)
	{
		SAFE_RELEASE(mMaterial);
	}

	virtual void UpdateWorldMatrixRecursively(const Matrix& parentWorldMatrix=Matrix::Identity)
	{
		mWorldMatrix=mMatrix.Value();
		mMeshModelNode.UpdateWorldMatrixRecursively(mWorldMatrix.OldValue());
	}
	virtual INode* CreateCloneInstance()
	{
		INode* result=mMeshModelNode.Mesh().CreateCloneInstance();
		if (result!=nullptr)
		{
			result->SetName(Name());
			result->SetMatrix(mMeshModelNode.WorldMatrix());
			if(!result->Initialize())
			{
				SAFE_DELETE(result);
				return nullptr;
			}
		}
		return result;
	}
	virtual INode* CreateReferenceInstance()
	{
		//TODO: add ref
		return nullptr;
	}
protected:
	MeshModelNode<TMesh> mMeshModelNode;
	TMaterial* mMaterial;
};

MEDUSA_END;