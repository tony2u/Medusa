// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "ParallaxComponent.h"
#include "Node/INode.h"

MEDUSA_BEGIN;


ParallaxComponent::ParallaxComponent(const StringRef& name /*= StringRef::Empty*/, int priority /*= 0*/, void* userData /*= nullptr*/)
	: IComponent(name, priority, userData), mPosition(Point3F::Zero), mIsReverse(false)
{

}

ParallaxComponent::~ParallaxComponent(void)
{

}

void ParallaxComponent::SetPosition(const Point3F& val)
{
	mPosition = val;
	if (!mIsReverse)
	{
		for(auto i: mItems)
		{
			INode* node = i.Key;
			const ParallaxInfo& info = i.Value;
			Point3F pos = info.Offset + info.Ratio*mPosition;
			node->SetPosition(pos);
		}
	}
	else
	{
		for (auto i : mItems)
		{
			INode* node = i.Key;
			const ParallaxInfo& info = i.Value;
			Point3F pos = info.Offset + info.Ratio*mPosition - mPosition;
			node->SetPosition(pos);
		}
	}
	

}

void ParallaxComponent::EnableParallax(INode* node, const Point3F& ratio /*= Point3F::One*/, const Point3F& offset /*= Point3F::Zero*/)
{
	ParallaxInfo* info = mItems.TryGet(node);
	if (info == nullptr)
	{
		ParallaxInfo& newInfo = mItems.NewAdd(node);
		info = &newInfo;
	}
	info->Ratio = ratio;
	info->Offset = offset;
}


void ParallaxComponent::DisableParallax(INode* node)
{
	mItems.RemoveKey(node);
}

void ParallaxComponent::DisableAllParallax()
{
	mItems.Clear();
}




MEDUSA_IMPLEMENT_COMPONENT(ParallaxComponent, IComponent);

MEDUSA_END;
