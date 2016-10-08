// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "BaseMovementComponent.h"
#include "Node/INode.h"

MEDUSA_BEGIN;

BaseMovementComponent::BaseMovementComponent(const StringRef& name /*= StringRef::Empty*/, int priority /*= 0*/, void* userData /*= nullptr*/)
	:IComponent(name, priority, userData)
{

}


Point3F BaseMovementComponent::Position() const
{
	INode* node = (INode*)mEntity;
	return node->Position();
}

void BaseMovementComponent::SetPosition(const Point3F& val)
{
	INode* node = (INode*)mEntity;
	OnPositionChanged(node->Position(), val);
	node->SetPosition(val);
}

void BaseMovementComponent::SetPosition(const Point2F& val)
{
	INode* node = (INode*)mEntity;
	OnPositionChanged(node->Position(), val);
	node->SetPosition(val);
}


MEDUSA_IMPLEMENT_COMPONENT(BaseMovementComponent, IComponent);

MEDUSA_END;
