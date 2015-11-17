// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaCorePreDeclares.h"
#include "Core/Pattern/Singleton.h"
#include "Core/Threading/ReadWriteLock.h"
#include "Core/Collection/HashSet.h"
#include "Core/String/HeapString.h"

MEDUSA_BEGIN;

class WStringPool :public Singleton < WStringPool >
{
	friend class Singleton < WStringPool > ;
private:
	WStringPool() {}
	~WStringPool();
public:
	bool Initialize();
	bool Uninitialize();
public:
	WHeapString Create(const wchar_t* str, uint length);
private:
	HashSet<WHeapString> mItems;
	ReadWriteLock mLock;
};
MEDUSA_END;
