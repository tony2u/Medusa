// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "ScrollComponent.h"
#include "Node/INode.h"
#include "Core/Event/EventArg/UserDataEventArg.h"
#include "Geometry/Scroll/StaticScrollMathModel.h"

MEDUSA_BEGIN;


ScrollComponent::ScrollComponent(const StringRef& name /*= StringRef::Empty*/, int priority /*= 0*/, void* userData /*= nullptr*/)
	: IComponent(name, priority, userData),  mIsReverse(false)
{
	mScrollModel = new StaticScrollMathModel();
}


ScrollComponent::~ScrollComponent(void)
{
	SAFE_DELETE(mScrollModel);
}

void ScrollComponent::SetScrollModel(IScrollMathModel* val)
{
	SAFE_ASSIGN(mScrollModel, val);
}

bool ScrollComponent::Initialize(const Rect2F& container, const Rect2F& window, ScrollDirection direction /*= ScrollDirection::HorizontalFromLeft*/, bool isReverse /*= false*/)
{
	mIsReverse = isReverse;
	mScrollModel->SetDirection(direction);
	mScrollModel->Initialize(container, window);
	mScrollModel->OnScrollEvent += Bind(&ScrollComponent::OnScroll, this);

	return true;
}

void ScrollComponent::OnScroll()
{
	Point3F movement = mScrollModel->Movement();
	mScrollModel->ApplyMovement();
	INode* node = (INode*)mEntity;
	if (mIsReverse)
	{
		movement *= -1.f;
	}
	node->Move(movement);
}

bool ScrollComponent::Update(float dt)
{
	RETURN_FALSE_IF_FALSE(IComponent::Update(dt));
	RETURN_FALSE_IF_FALSE(mScrollModel->UpdateModel(dt));
	
	return true;
}



MEDUSA_IMPLEMENT_COMPONENT(ScrollComponent, IComponent);
MEDUSA_END;
