// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "ParallaxScrollComponent.h"
#include "ParallaxComponent.h"

#include "Node/INode.h"

MEDUSA_BEGIN;


ParallaxScrollComponent::ParallaxScrollComponent(const StringRef& name /*= StringRef::Empty*/, int priority /*= 0*/, void* userData /*= nullptr*/)
	: ScrollComponent(name, priority, userData)
{
	mParallaxComponent = new ParallaxComponent(name);
	mParallaxComponent->EnableReverse(true);
}


ParallaxScrollComponent::~ParallaxScrollComponent(void)
{
	SAFE_DELETE(mParallaxComponent);
}


void ParallaxScrollComponent::OnScroll()
{
	ScrollComponent::OnScroll();
	INode* node = (INode*)mEntity;
	const Point3F& curPos = node->Position();
	mParallaxComponent->SetPosition(curPos);
}


void ParallaxScrollComponent::EnableParallax(INode* node, const Point3F& ratio /*= Point3F::One*/, const Point3F& offset /*= Point3F::Zero*/)
{
	mParallaxComponent->EnableParallax(node, ratio, offset);
}


void ParallaxScrollComponent::DisableParallax(INode* node)
{
	mParallaxComponent->DisableParallax(node);
}

void ParallaxScrollComponent::DisableAllParallax()
{
	mParallaxComponent->DisableAllParallax();
}



MEDUSA_IMPLEMENT_COMPONENT(ParallaxScrollComponent, ScrollComponent);
MEDUSA_END;
