// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once

#include "MedusaCorePreDeclares.h"
#include "Core/Pattern/Component/IComponent.h"
#include "Core/Pattern/Component/ComponentFactory.h"
#include "Core/Collection/SortedList.h"


MEDUSA_BEGIN;

class IEntity
{
	typedef SortedList < IComponent*,DefaultCompare,CustomCompareForPointer > ComponentList;
public:
	IEntity();
	virtual ~IEntity();
public:
	IComponent* FindComponent(const StringRef& name)const;

	template<typename T>
	T* FindComponent()const
	{
		for(IComponent* component: mComponents)
		{
			if (component->IsA<T>())
			{
				return (T*)component;
			}
		}

		return nullptr;
	}

	template<typename T>
	bool HasComponent()const { return FindComponent<T>() != nullptr; }
	bool HasComponents()const { return !mComponents.IsEmpty(); }

	IComponent* AddComponent(IComponent* component)
	{
		MEDUSA_ASSERT_NOT_NULL(component, "");
		mComponents.Add(component);
		component->SetEntity(this);
		return component;
	}


	IComponent* AddComponent(const StringRef& name, int priority = 0, void* userData = nullptr)
	{
		IComponent* component = ComponentFactory::Instance().Create(name, name, priority, userData);
		RETURN_NULL_IF_NULL(component);
		AddComponent(component);
		return component;
	}

	template<typename T>
	T* AddComponent(int priority = 0, void* userData = nullptr)
	{
		T* component = (T*)ComponentFactory::Instance().Create<T>(priority, userData);
		RETURN_NULL_IF_NULL(component);
		AddComponent(component);
		return component;
	}

	IComponent* FindOrCreateComponent(const StringRef& name, int priority = 0, void* userData = nullptr)
	{
		IComponent* component = FindComponent(name);
		if (component==nullptr)
		{
			component = AddComponent(name, priority, userData);
		}
		return component;
	}

	template<typename T>
	T* FindOrCreateComponent(int priority = 0, void* userData = nullptr)
	{
		T* component = FindComponent<T>();
		if (component == nullptr)
		{
			component = AddComponent<T>(priority, userData);
		}
		return component;
	}

	IComponent* RemoveComponent(const StringRef& name);

	template<typename T>
	T* RemoveComponent()
	{
		uintp count = mComponents.Count();
		FOR_EACH_SIZE(i, count)
		{
			IComponent* component = mComponents[i];
			if (component->IsA<T>())
			{
				mComponents.RemoveAt(i);
				component->SetEntity(nullptr);
				return (T*)component;

			}
		}

		return nullptr;
	}

	bool StartComponent(const StringRef& name);

	template<typename T>
	bool StartComponent()
	{
		T* val = FindComponent<T>();
		RETURN_FALSE_IF_NULL(val);
		return val->Start();
	}

	bool StopComponent(const StringRef& name);

	template<typename T>
	bool StopComponent()
	{
		T* val = FindComponent<T>();
		RETURN_FALSE_IF_NULL(val);
		return val->Stop();
	}

	bool PauseComponent(const StringRef& name);

	template<typename T>
	bool PauseComponent()
	{
		T* val = FindComponent<T>();
		RETURN_FALSE_IF_NULL(val);
		return val->Pause();
	}
	bool ResumeComponent(const StringRef& name);

	template<typename T>
	bool ResumeComponent()
	{
		T* val = FindComponent<T>();
		RETURN_FALSE_IF_NULL(val);
		return val->Resume();
	}
	bool ResetComponent(const StringRef& name);

	template<typename T>
	bool ResetComponent()
	{
		T* val = FindComponent<T>();
		RETURN_FALSE_IF_NULL(val);
		return val->Reset();
	}

	bool RestartComponent(const StringRef& name);

	template<typename T>
	bool RestartComponent()
	{
		T* val = FindComponent<T>();
		RETURN_FALSE_IF_NULL(val);
		return val->Restart();
	}
	void PauseAllComponents();
	void ResumeAllComponents();
	void ResetAllComponents();
	void RestartAllComponents();

	void StartAllComponents();
	void StopAllComponents();

public:
	bool UpdateComponents(float dt);
	bool AcceptComponentEvent(IEventArg& e);
	bool EnterComponents();
	bool ExitComponents();
	bool UpdateComponentsLogic();
	bool ResetComponentsLogic();


protected:
	ComponentList mComponents;

};

MEDUSA_END;