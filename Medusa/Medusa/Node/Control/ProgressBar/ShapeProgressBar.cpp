// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "ShapeProgressBar.h"
#include "Resource/Model/Mesh/MeshFactory.h"
#include "Resource/Material/IMaterial.h"
#include "Resource/Model/Mesh/Fixed/ShapeQuadMesh.h"
#include "Node/NodeFactory.h"
MEDUSA_BEGIN;

ShapeProgressBar::ShapeProgressBar(StringRef name, ProgressType progressType, const Size2F& size, const Color4F& color, float percent/*=1.f*/)
	:IProgressBar(name, progressType, percent)
{
	mSize = size;
	mColor = color;
}

ShapeProgressBar::ShapeProgressBar(const StringRef& name /*= StringRef::Empty*/, const IEventArg& e /*= IEventArg::Empty*/)
	: IProgressBar(name, e)
{

}

ShapeProgressBar::~ShapeProgressBar(void)
{

}

bool ShapeProgressBar::Initialize()
{
	auto mesh = MeshFactory::Instance().CreateShapeQuadMesh(mSize.To2D(), mColor);
	this->SetMesh(mesh);
	mVertices = mesh->GetVertices();

	OnUpdateMesh();
	return true;
}

void ShapeProgressBar::OnUpdateMesh(bool isProgressTypeChanged/*=false*/)
{
	auto mesh = mRenderingObject.Mesh().CastPtr<ShapeQuadMesh>();

	if (isProgressTypeChanged)
	{
		mesh->SetVertices(mVertices);
	}

	IProgressBar::BlendVertex(mVertices, mesh->MutableVertices(), mProgressType, mPercent, IsFlipX());
	mesh->OnVertexChanged();
	OnVisitQueueChanged();

}

MEDUSA_IMPLEMENT_NODE(ShapeProgressBar);

MEDUSA_END;
