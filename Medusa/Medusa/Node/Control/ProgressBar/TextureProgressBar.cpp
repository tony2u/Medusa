// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "TextureProgressBar.h"
#include "Resource/Model/Mesh/MeshFactory.h"
#include "Resource/Model/Mesh/Fixed/TextureQuadMesh.h"
#include "Resource/Material/IMaterial.h"
#include "Resource/Material/MaterialFactory.h"
#include "Rendering/RenderingObjectFactory.h"
#include "Node/NodeFactory.h"

MEDUSA_BEGIN;


TextureProgressBar::TextureProgressBar(StringRef name, ProgressType progressType, const FileIdRef& textureName, float percent/*=1.f*/)
	:IProgressBar(name, progressType, percent), mTextureName(textureName)
{

}

TextureProgressBar::TextureProgressBar(const StringRef& name /*= StringRef::Empty*/, const IEventArg& e /*= IEventArg::Empty*/)
	:IProgressBar(name,e)
{

}

TextureProgressBar::~TextureProgressBar(void)
{

}

bool TextureProgressBar::Initialize()
{

	auto renderingObject = RenderingObjectFactory::Instance().CreateFromTexture(mTextureName);
	RETURN_FALSE_IF_NULL(renderingObject);
	SetRenderingObject(renderingObject);

	auto mesh = renderingObject.Mesh().CastPtr<TextureQuadMesh>();

	SetSize(mesh->Size());
	mVertices = mesh->Vertices();
	mTexcoords = mesh->Texcoords();

	OnUpdateMesh();
	return true;
}

void TextureProgressBar::OnUpdateMesh(bool isProgressTypeChanged/*=false*/)
{
	auto mesh = mRenderingObject.Mesh().CastPtr<TextureQuadMesh>();

	if (isProgressTypeChanged)
	{
		mesh->SetVertices(mVertices);
		mesh->SetTexcoords(mTexcoords);
	}

	IProgressBar::BlendVertex(mVertices, mesh->MutableVertices(), mProgressType, mPercent, IsFlipX());
	mesh->OnVertexChanged();

	IProgressBar::BlendTexcoord(mTexcoords, mesh->MutableTexcoords(), mProgressType, mPercent, IsFlipX());
	mesh->OnTexcoordChanged();
	OnVisitQueueChanged();


}

MEDUSA_IMPLEMENT_NODE(TextureProgressBar);

MEDUSA_END;
