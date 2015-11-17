// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Rendering/Batch/CustomDrawMeshRenderBatch.h"
#include "Resource/Model/IModel.h"
#include "Resource/Model/Mesh/IMesh.h"
#include "Rendering/IRenderable.h"
#include "Core/Log/Log.h"
#include "Rendering/RenderingStatics.h"

MEDUSA_BEGIN;


CustomDrawMeshRenderBatch::CustomDrawMeshRenderBatch():IRenderBatch(RenderingStrategy::CustomDrawMesh),mNode(nullptr)
{

}


CustomDrawMeshRenderBatch::~CustomDrawMeshRenderBatch()
{
	Clear();
}

bool CustomDrawMeshRenderBatch::Initialize()
{
	return true;
}

bool CustomDrawMeshRenderBatch::Uninitialize()
{
	Clear();
	return true;
}


void CustomDrawMeshRenderBatch::Clear()
{
	if (mNode!=nullptr)
	{
		mNode->SetBatch(nullptr);
	}
	mNode=nullptr;
}

void CustomDrawMeshRenderBatch::Apply()
{
	IMesh* mesh=mNode->Mesh();

	if (mesh!=nullptr)
	{
		mesh->Apply();
	}
}

void CustomDrawMeshRenderBatch::Restore()
{
	IMesh* mesh=mNode->Mesh();

	if (mesh!=nullptr)
	{
		mesh->Restore();
	}
}

void CustomDrawMeshRenderBatch::AddNode( IRenderable* node )
{
	mNode=node;
	mModelMatrix=node->WorldMatrix();
}

void CustomDrawMeshRenderBatch::PrepareDraw()
{

}

void CustomDrawMeshRenderBatch::Draw(IRenderQueue& renderQueue, RenderingFlags renderingFlags/*=RenderingFlags::None*/)
{
	IMesh* mesh=mNode->Mesh();
	if (mesh!=nullptr)
	{
		mesh->Draw(renderQueue, renderingFlags);
		RenderingStatics::Instance().CountOriginalAndBatchDraw();
	}
}

void CustomDrawMeshRenderBatch::FinishDraw()
{
	mNode=nullptr;
}

MEDUSA_END;