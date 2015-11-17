// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "TextureProgressBar.h"
#include "Resource/Model/Mesh/MeshFactory.h"
#include "Resource/Model/Mesh/Fixed/TextureQuadMesh.h"
#include "Resource/Material/IMaterial.h"

MEDUSA_BEGIN;


TextureProgressBar::TextureProgressBar(StringRef name, ProgressType progressType, const FileIdRef& textureName, float percent/*=1.f*/)
	:IProgressBar(name, progressType, percent), mTextureName(textureName)
{

}

TextureProgressBar::~TextureProgressBar(void)
{

}

bool TextureProgressBar::Initialize()
{
	TextureQuadMesh* mesh = MeshFactory::Instance().CreateTextureQuadMesh(mTextureName.ToRef());
	this->SetMesh(mesh);
	SetSize(mesh->Size());
	mVertices = mesh->Vertices();
	mTexcoords = mesh->Texcoords();

	OnUpdateMesh();
	return true;
}

void TextureProgressBar::OnUpdateMesh(bool isProgressTypeChanged/*=false*/)
{
	TextureQuadMesh* mesh = (TextureQuadMesh*)mMesh;

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

MEDUSA_IMPLEMENT_RTTI(TextureProgressBar, IProgressBar);

MEDUSA_END;
