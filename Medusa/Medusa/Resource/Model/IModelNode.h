// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/String/HeapString.h"
#include "Core/Geometry/Moveable/DefaultMoveable.h"
#include "Core/Collection/List.h"

MEDUSA_BEGIN;

enum class ModelNodeType { Light, Camera, Mesh, Bone, Virtual };



class IModelNode:public DefaultMoveable
{
public:
	IModelNode(StringRef name);
	virtual ~IModelNode(void);
	virtual ModelNodeType Type()const=0;

	StringRef Name() const { return mName; }
	void SetName(StringRef val) { mName = val; }

	virtual bool Initialzie(){return true;}

	IModelNode* Parent() const { return mParentNode; }
	void SetParentNode(IModelNode* val);

	IModel* Model() const { return mParentModel; }
	void SetParentModel(IModel* val);

	void AddChildNode(IModelNode* node);

	virtual void UpdateWorldMatrixRecursively(const Matrix4& parentWorldMatrix=Matrix4::Identity);

	virtual INode* CreateCloneInstance() { return nullptr; }
	virtual INode* CreateReferenceInstance() { return nullptr; }
protected:
	HeapString mName;
	List<IModelNode*> mNodes;
	IModelNode* mParentNode;
	IModel* mParentModel;

};

MEDUSA_END;