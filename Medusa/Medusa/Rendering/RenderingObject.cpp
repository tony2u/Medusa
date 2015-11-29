// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Rendering/RenderingObject.h"
#include "Resource/Model/Mesh/IMesh.h"
#include "Resource/Material/IMaterial.h"

MEDUSA_BEGIN;

RenderingObject::RenderingObject(IMesh* mesh /*= nullptr*/, IMaterial* material /*= nullptr*/)
	:mMesh(mesh),mMaterial(material)
{
	SAFE_RETAIN(mMesh);
	SAFE_RETAIN(mMaterial);
}

RenderingObject::RenderingObject(const RenderingObject& val)
	:mMesh(val.mMesh),mMaterial(val.mMaterial)
{
	SAFE_RETAIN(mMesh);
	SAFE_RETAIN(mMaterial);
}

RenderingObject& RenderingObject::operator=(const RenderingObject& val)
{
	if (this!=&val)
	{
		SAFE_ASSIGN_REF(mMesh, val.mMesh);
		SAFE_ASSIGN_REF(mMaterial, val.mMaterial);
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
		SAFE_RELEASE(mMesh);
		SAFE_RELEASE(mMaterial);

		mMesh = val.mMesh;
		mMaterial = val.mMaterial;

		val.mMesh = nullptr;
		val.mMaterial = nullptr;
	}
	return *this;
}

RenderingObject::~RenderingObject()
{
	SAFE_RELEASE(mMesh);
	SAFE_RELEASE(mMaterial);
}

void RenderingObject::SetMesh(IMesh* val)
{
	SAFE_ASSIGN_REF(mMesh, val);
}

void RenderingObject::SetMaterial(IMaterial* val)
{
	SAFE_ASSIGN_REF(mMaterial, val);
}

bool RenderingObject::IsValid() const
{
	return mMesh != nullptr&&mMaterial != nullptr&&mMaterial->Effect() != nullptr;
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

