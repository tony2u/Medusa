// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Rendering/RenderingObject.h"
#include "Resource/Model/Mesh/IMesh.h"
#include "Resource/Material/IMaterial.h"

MEDUSA_BEGIN;

RenderingObject::RenderingObject(const Share<IMesh>& mesh /*= nullptr*/, const Share<IMaterial>& material /*= nullptr*/)
	:mMesh(mesh),mMaterial(material)
{
	
}

RenderingObject::RenderingObject(const RenderingObject& val)
	:mMesh(val.mMesh),mMaterial(val.mMaterial)
{
	
}

RenderingObject& RenderingObject::operator=(const RenderingObject& val)
{
	if (this!=&val)
	{
		mMesh = val.mMesh;
		mMaterial = val.mMaterial;
	}
	
	return *this;
}

RenderingObject::RenderingObject(RenderingObject&& val)
	:mMesh(val.mMesh), mMaterial(val.mMaterial)
{
	val.mMesh = nullptr;
	val.mMaterial = nullptr;
}

RenderingObject& RenderingObject::operator=(RenderingObject&& val)
{
	if (this != &val)
	{
		mMesh = nullptr;
		mMaterial = nullptr;

		mMesh = val.mMesh;
		mMaterial = val.mMaterial;

		val.mMesh = nullptr;
		val.mMaterial = nullptr;
	}
	return *this;
}

RenderingObject::~RenderingObject()
{
	mMesh = nullptr;
	mMaterial = nullptr;
}

void RenderingObject::SetMesh(const Share<IMesh>& val)
{
	mMesh = val;
}

void RenderingObject::SetMaterial(const Share<IMaterial>& val)
{
	mMaterial = val;
}

bool RenderingObject::IsValid() const
{
	return mMesh != nullptr&&mMesh->IsValid()&&mMaterial != nullptr&&mMaterial->Effect() != nullptr;
}

bool RenderingObject::IsBlend() const
{
	return  (mMesh != nullptr&&mMesh->HasBlend()) || (mMaterial != nullptr&&mMaterial->IsBlendEnabled());
}

void RenderingObject::UnregisterMeshChanged(const Delegate<void(RenderableChangedFlags)>& val)
{
	RETURN_IF_NULL(mMesh);
	mMesh->OnMeshChanged -= val;
}

void RenderingObject::UnregisterMaterialChanged(const Delegate<void(RenderableChangedFlags)>& val)
{
	RETURN_IF_NULL(mMaterial);
	mMaterial->OnMaterialChanged -= val;
}

void RenderingObject::RegisterMaterialChanged(const Delegate<void(RenderableChangedFlags)>& val)
{
	RETURN_IF_NULL(mMesh);
	mMesh->OnMeshChanged += val;
}

void RenderingObject::RegisterMeshChanged(const Delegate<void(RenderableChangedFlags)>& val)
{
	RETURN_IF_NULL(mMaterial);
	mMaterial->OnMaterialChanged += val;
}

const RenderingObject RenderingObject::Empty;

MEDUSA_END;

