// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Resource/Model/Mesh/IMeshModelNode.h"
#include "Node/Sprite/Sprite.h"

MEDUSA_BEGIN;


template<typename TMesh>
class MeshModelNode:public IMeshModelNode
{
public:
	MeshModelNode(StringRef name):IMeshModelNode(name)
	{
		mMesh.Retain();
	}
	virtual ~MeshModelNode(void){}

	virtual const IMesh* BaseMeshPtr() const { return &mMesh; }
	virtual IMesh* MutableBaseMeshPtr() { return &mMesh; }

	const TMesh& Mesh() const { return mMesh; }
	TMesh& MutableMesh()  { return mMesh; }

	virtual void CustomDraw(RenderingFlags renderingFlags=RenderingFlags::None){}
	virtual void Apply(){}
	virtual void Restore(){}

	virtual INode* CreateCloneInstance() override
	{
		Sprite* sprite = new Sprite(this->mName);
		sprite->SetMoveable(*this);
		sprite->SetMesh(&mMesh);
		sprite->SetMaterial(mMaterial);
		sprite->Initialize();

		for (auto* node:this->mNodes)
		{
			auto* child = node->CreateCloneInstance();
			sprite->AddChild(child);
		}

		return sprite; 
	}
	virtual INode* CreateReferenceInstance() { return nullptr; }
protected:
	TMesh mMesh;
};

MEDUSA_END;