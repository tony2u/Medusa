// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Geometry/Moveable/DefaultMoveable.h"
#include "Resource/IResource.h"

#include "Rendering/RenderingFlags.h"
#include "ModelLoadingOptions.h"


MEDUSA_BEGIN;

//.quad,.font.pod
enum class ModelType { Unknown, quad, font, pod };


class IModel:public DefaultMoveable,public IResource
{
public:
	IModel(const FileIdRef& fileId=FileIdRef::Empty);
	virtual ~IModel(void);
	virtual ResourceType Type()const{return ResourceType::Model;}
	static ResourceType ClassGetResourceType(){return ResourceType::Model;}
	ModelType GetType() const { return mType; }

	virtual bool Initialzie(ModelLoadingOptions loadingOptions=ModelLoadingOptions::None){return true;}
	

 	virtual void CustomDraw(IRenderable* node,RenderingFlags renderingFlags=RenderingFlags::None);
 	virtual void BatchDraw(IRenderable* node,IRenderBatch* batch,RenderingFlags renderingFlags=RenderingFlags::None);

	virtual void UpdateWorldMatrixRecursively(const Matrix& parentWorldMatrix=Matrix::Identity){}

	virtual INode* CreateCloneInstance()=0;
	virtual INode* CreateReferenceInstance()=0;

protected:
	ModelType mType;

};

MEDUSA_END;