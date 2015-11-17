// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Core/Pattern/Component/IEntity.h"
#include "Core/Collection/Linq.h"


MEDUSA_BEGIN;


IEntity::IEntity()
	:mSender(nullptr)
{
}

IEntity::~IEntity()
{
	StopAllComponents();
}

void IEntity::ResetAllComponents()
{
	FOR_EACH_ITEM_TO(mComponents, Reset());
}

void IEntity::RestartAllComponents()
{
	FOR_EACH_ITEM_TO(mComponents, Restart());
}
void IEntity::ResumeAllComponents()
{
	FOR_EACH_ITEM_TO(mComponents, Resume());
}



void IEntity::PauseAllComponents()
{
	FOR_EACH_ITEM_TO(mComponents, Pause());
}


void IEntity::StartAllComponents()
{
	RETURN_IF_EMPTY(mComponents);
	size_t count = mComponents.Count();
	FOR_EACH_SIZE(i, count)
	{
		IComponent* component = mComponents[i];
		MEDUSA_ASSERT_NOT_NULL(component, "");
		component->Start();
		if (component->IsDone())
		{
			mCompletedIndices.Add(i);
		}
	}

	Linq::DeleteIndexes(mComponents, mCompletedIndices);
	mCompletedIndices.Clear();
}

void IEntity::StopAllComponents()
{
	RETURN_IF_EMPTY(mComponents);
	FOR_EACH_COLLECTION(i, mComponents)
	{
		IComponent* item = *i;
		item->Stop();
		delete item;
	}
	mComponents.Clear();
}

bool IEntity::AcceptComponentEvent(IEventArg& e)
{
	RETURN_TRUE_IF_EMPTY(mComponents);
	size_t count = mComponents.Count();
	FOR_EACH_SIZE(i, count)
	{
		IComponent* component = mComponents[i];
		MEDUSA_ASSERT_NOT_NULL(component, "");
		component->AcceptEvent(e);
		if (component->IsDone())
		{
			mCompletedIndices.Add(i);
		}
	}

	Linq::DeleteIndexes(mComponents, mCompletedIndices);
	mCompletedIndices.Clear();
	return true;
}

bool IEntity::UpdateComponents(float dt)
{
	RETURN_TRUE_IF_EMPTY(mComponents);

	size_t count = mComponents.Count();
	FOR_EACH_SIZE(i, count)
	{
		IComponent* component = mComponents[i];
		MEDUSA_ASSERT_NOT_NULL(component, "");
		component->Update(dt);
		if (component->IsDone())
		{
			mCompletedIndices.Add(i);
		}
	}

	Linq::DeleteIndexes(mComponents, mCompletedIndices);
	mCompletedIndices.Clear();

	return true;
}

IComponent* IEntity::FindComponent(const StringRef& name)const
{
	FOR_EACH_COLLECTION(i, mComponents)
	{
		IComponent* component = *i;
		if (component->Name() == name)
		{
			return component;
		}
	}
	return nullptr;
}

IComponent* IEntity::RemoveComponent(const StringRef& name)
{
	uintp count = mComponents.Count();
	FOR_EACH_SIZE(i, count)
	{
		IComponent* component = mComponents[i];
		if (component->Name() == name)
		{
			mComponents.RemoveAt(i);
			component->SetEntity(nullptr);
			return component;
		}
	}

	return nullptr;
}

bool IEntity::StopComponent(const StringRef& name)
{
	IComponent* val = RemoveComponent(name);
	bool result = val != nullptr;
	SAFE_DELETE(val);
	return result;
}

bool IEntity::PauseComponent(const StringRef& name)
{
	IComponent* val = FindComponent(name);
	RETURN_FALSE_IF_NULL(val);
	return val->Pause();
}
bool IEntity::ResumeComponent(const StringRef& name)
{
	IComponent* val = FindComponent(name);
	RETURN_FALSE_IF_NULL(val);
	return val->Resume();
}
bool IEntity::ResetComponent(const StringRef& name)
{
	IComponent* val = FindComponent(name);
	RETURN_FALSE_IF_NULL(val);
	return val->Reset();
}
bool IEntity::RestartComponent(const StringRef& name)
{
	IComponent* val = FindComponent(name);
	RETURN_FALSE_IF_NULL(val);
	return val->Restart();
}
MEDUSA_END;

