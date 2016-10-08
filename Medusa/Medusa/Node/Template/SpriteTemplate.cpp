// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "SpriteTemplate.h"
#include "Node/INode.h"
#include "Node/NodeFactory.h"
#include "Node/Sprite/Sprite.h"
#include "Rendering/RenderingObjectFactory.h"

MEDUSA_BEGIN;



Size2F SpriteTemplate::Measure(const FileId& data, const Size2F& limitSize /*= Size2F::Zero*/) const
{
	auto obj= RenderingObjectFactory::Instance().CreateFromTexture(data);
	if (obj.IsValid())
	{
		return obj.Mesh()->Size().To2D();
	}
	return limitSize;
}

INode* SpriteTemplate::Load(const FileId& data, const Size2F& limitSize /*= Size2F::Zero*/,INode* reloadNode /*= nullptr*/)const
{
	if (reloadNode==nullptr)
	{
		reloadNode= NodeFactory::Instance().CreateSprite(data);
	}
	else
	{
		reloadNode->SetRenderingObjectFile(data);
	}
	OnSetupNode(reloadNode);
	return reloadNode;
	
}



MEDUSA_END;
