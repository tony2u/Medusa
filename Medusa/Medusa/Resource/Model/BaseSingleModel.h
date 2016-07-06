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
	BaseSingleModel(const FileIdRef& fileId)
		:IModel(fileId),mMeshModelNode(fileId.Name)
	{
		mMeshModelNode.SetParentModel(this);
	}
	virtual ~BaseSingleModel(void)
	{
		
	}

	virtual void UpdateWorldMatrixRecursively(const Matrix4& parentWorldMatrix=Matrix4::Identity)
	{
		mWorldMatrix=mMatrix.Value();
		mMeshModelNode.UpdateWorldMatrixRecursively(mWorldMatrix.OldValue());
	}
	virtual INode* Instantiate(InstantiateMode mode = InstantiateMode::None)const
	{
		INode* result=mMeshModelNode.Mesh().CreateCloneInstance();
		if (result!=nullptr)
		{
			result->SetName(Name());
			result->SetMoveable(mMeshModelNode);
			if(!result->Initialize())
			{
				SAFE_DELETE(result);
				return nullptr;
			}
		}
		return result;
	}
	
protected:
	MeshModelNode<TMesh> mMeshModelNode;
	Share<TMaterial> mMaterial;
};

MEDUSA_END;