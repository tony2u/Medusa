// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Resource/Model/IModel.h"
#include "Resource/Model/Mesh/IMeshModelNode.h"
#include "Core/Memory/MemoryData.h"
#include "Core/Collection/List.h"

MEDUSA_BEGIN;

template<typename TMaterial>
class BaseMultipleModel:public IModel
{
public:
	BaseMultipleModel(const FileIdRef& fileId):IModel(fileId){}
	virtual ~BaseMultipleModel(void)
	{
		SAFE_DELETE_COLLECTION(mMeshNodes);
		SAFE_RELEASE_COLLECTION(mMaterials);
	}
public:
	List<IMeshModelNode*>& MutableMeshes()  { return mMeshNodes; }
	List<TMaterial*>& MutableMaterials() { return mMaterials; }

	const List<IMeshModelNode*>& Meshes()const  { return mMeshNodes; }
	const List<TMaterial*>& Materials()const { return mMaterials; }

	TMaterial* FirstMaterial(){return mMaterials.First();}
	bool ContainsMaterial(TMaterial* material)const {return mMaterials.Contains(material);}
	bool TryAddMaterial(TMaterial* material)
	{
		if(!mMaterials.Contains(material))
		{
			mMaterials.Add(material);
			material->Retain();
			return true;
		}
		return false;
	}

	void ReleaseAllMaterials()
	{
		SAFE_RELEASE_COLLECTION(mMaterials);
	}

	IMeshModelNode* FindMesh(StringRef name)
	{
		FOR_EACH_COLLECTION(i,mMeshNodes)
		{
			IMeshModelNode* meshNode=*i;
			if (meshNode->Name()==name)
			{
				return (IMeshModelNode*)meshNode;
			}
		}

		return nullptr;
	}
	IMeshModelNode* FindFirstMesh()
	{
		RETURN_NULL_IF_EMPTY(mMeshNodes);
		return mMeshNodes.First();
	}
	
	void RemoveAllMeshes()
	{
		SAFE_DELETE_COLLECTION(mMeshNodes);
	}


	void AddMesh(IMeshModelNode* mesh)
	{
		mMeshNodes.Append(mesh);

	}
	void AddMeshes(const List<IMeshModelNode*>& meshes)
	{
		mMeshNodes.AppendRange(meshes);
	}

	virtual INode* CreateCloneInstance()=0;
	virtual INode* CreateReferenceInstance()=0;

protected:
	List<IMeshModelNode*> mMeshNodes;
	List<TMaterial*> mMaterials;
};

MEDUSA_END;