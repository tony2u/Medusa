// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaExtensionPreDeclares.h"
#include "CocosStudio/CocosDefines.h"
//[PRE_DECLARE_NAMESPCAE] Cocos
#include "Core/Pattern/Singleton.h"
#include "Core/Pattern/Object/StaticObjectFactory.h"
#include "INodeReader.h"

MEDUSA_COCOS_BEGIN;

class ReaderFactory :public Singleton < ReaderFactory >, public StaticObjectFactory < StringRef, INodeReader*() >
{
	friend class Singleton < ReaderFactory > ;
	ReaderFactory();
	~ReaderFactory(void) {}
public:
	using StaticObjectFactory<StringRef, INodeReader*()>::Register;
	using StaticObjectFactory<StringRef, INodeReader*()>::Create;

	template < typename T >
	void Register()
	{
		Register<T>(T::ClassStatic().Name());
	}

	template < typename T >
	T* Create()
	{
		return (T*)Create(T::ClassStatic().Name());
	}

	INodeReader* AssertCreate(StringRef name);
};

MEDUSA_COCOS_END;
