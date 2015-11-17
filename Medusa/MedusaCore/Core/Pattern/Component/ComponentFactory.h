// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once


#include "MedusaCorePreDeclares.h"
#include "Core/Pattern/Component/IComponent.h"
#include "Core/Pattern/Object/MapObjectFactory.h"
#include "Core/Pattern/Singleton.h"

MEDUSA_BEGIN;


class ComponentFactory :public MapObjectFactory < StringRef, IComponent*(StringRef name, int priority, void* userData) >, public Singleton < ComponentFactory >
{
	friend class Singleton < ComponentFactory > ;
	ComponentFactory() {}
	~ComponentFactory() {}
public:
	using MapObjectFactory<StringRef, IComponent*(StringRef name,int priority, void* userData)>::Create;
public:
	template<typename T>
	T* Create(int priority = 0, void* userData = nullptr)
	{
		return (T*)Create(T::ClassNameStatic(), T::ClassNameStatic(), priority, userData);
	}

	IComponent* Create(StringRef name, int priority = 0, void* userData = nullptr)
	{
		return Create(name, name, priority, userData);
	}
};




MEDUSA_END;