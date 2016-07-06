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
	using MaterialType = Share<TMaterial>;
public:
	BaseMultipleModel(const FileIdRef& fileId):IModel(fileId){}
	virtual ~BaseMultipleModel(void)
	{
		SAFE_DELETE_COLLECTION(mMeshNodes);
		mMaterials.Clear();
	}
public:
	List<IMeshModelNode*>& MutableMeshes()  { return mMeshNodes; }
	List<MaterialType>& MutableMaterials() { return mMaterials; }

	const List<IMeshModelNode*>& Meshes()const  { return mMeshNodes; }
	const List<MaterialType>& Materials()const { return mMaterials; }

	const MaterialType& FirstMaterial(){return mMaterials.First();}
	bool ContainsMaterial(const MaterialType& material)const {return mMaterials.Contains(material);}
	bool TryAddMaterial(const MaterialType& material)
	{
		if(!mMaterials.Contains(material))
		{
			mMaterials.Add(material);
			return true;
		}
		return false;
	}

	void ReleaseAllMaterials()
	{
		mMaterials.Clear();
	}

	IMeshModelNode* FindMesh(StringRef name)
	{
		for(auto meshNode:mMeshNodes)
		{
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

protected:
	List<IMeshModelNode*> mMeshNodes;
	List<MaterialType> mMaterials;
};

MEDUSA_END;