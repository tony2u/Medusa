// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "IModelNode.h"
#include "Resource/Model/IModel.h"

MEDUSA_BEGIN;


IModelNode::IModelNode(StringRef name)
	:mName(name)
{
	mParentNode=nullptr;
	mParentModel=nullptr;
}


IModelNode::~IModelNode(void)
{
	mParentNode=nullptr;
	mParentModel=nullptr;
}

void IModelNode::AddChildNode( IModelNode* node )
{
	mNodes.Add(node);
	node->SetParentNode(this);
}

void IModelNode::UpdateWorldMatrixRecursively( const Matrix4& parentWorldMatrix/*=Matrix4::Identity*/ )
{
	mWorldMatrix=mMatrix.Value()*parentWorldMatrix;

	FOR_EACH_COLLECTION(i,mNodes)
	{
		IModelNode* node=*i;
		node->UpdateWorldMatrixRecursively(mWorldMatrix.OldValue());
	}
}


void IModelNode::SetParentModel( IModel* val )
{
	mParentModel=val;
}

void IModelNode::SetParentNode( IModelNode* val )
{
	mParentNode = val; 
	SetParentMoveable(mParentNode);
}


MEDUSA_END;