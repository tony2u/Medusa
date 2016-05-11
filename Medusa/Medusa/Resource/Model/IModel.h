// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Geometry/Moveable/DefaultMoveable.h"
#include "Resource/IResource.h"
#include "ModelLoadingOptions.h"
#include "Rendering/RenderingTypes.h"

MEDUSA_BEGIN;

//.quad,.font.pod
enum class ModelType { Unknown, quad, font, pod };


class IModel :public DefaultMoveable, public IResource
{
public:
	IModel(const FileIdRef& fileId = FileIdRef::Empty);
	virtual ~IModel(void);
	virtual ResourceType Type()const { return ResourceType::Model; }
	static ResourceType ClassGetResourceType() { return ResourceType::Model; }
	ModelType GetType() const { return mType; }

	virtual bool Initialize(ModelLoadingOptions loadingOptions = ModelLoadingOptions::None) { return true; }


	virtual void CustomDraw(IRenderable* node, RenderingFlags renderingFlags = RenderingFlags::None);
	virtual void BatchDraw(IRenderable* node, IRenderBatch* batch, RenderingFlags renderingFlags = RenderingFlags::None);

	virtual void UpdateWorldMatrixRecursively(const Matrix4& parentWorldMatrix = Matrix4::Identity) {}

	virtual INode* Instantiate(InstantiateMode mode=InstantiateMode::None) const{ return nullptr; }

protected:
	ModelType mType;

};

MEDUSA_END;