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

class StringPool :public Singleton < StringPool >
{
	friend class Singleton < StringPool > ;
private:
	StringPool() {}
	~StringPool();
public:
	bool Initialize();
	bool Uninitialize();
public:
	HeapString& Create(const char* str, uint length);
private:
	HashSet<HeapString> mItems;
	ReadWriteLock mLock;
};
MEDUSA_END;
