// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Collection/List.h"
#include "Core/String/HeapString.h"

MEDUSA_BEGIN;

class StateMachineModel
{
public:
	StateMachineModel();
	~StateMachineModel(void);
public:
	void Initialize(uint size);
	StringRef Name() const { return mName; }
	void SetName(StringRef val) { mName = val; }
	IState* DefaultState() const { return mDefaultState; }
	void SetDefaultState(IState* val) { mDefaultState = val; }
	const List<IState*>& States() const { return mStates; }

	IState* Register(IState* state);
	template<typename T>
	IState* Register()
	{
		return Register(T::ClassStatic().Name());
	}

	IState* Register(StringRef name);

	IState* Get(uint index)const { return mStates[index]; }

	template<typename T>
	IState* Get()const
	{
		return Get(T::Index);
	}
	IState* Find(StringRef name)const;
	IState* SmartFind(StringRef name)const;


private:
	HeapString mName;
	List<IState*> mStates;
	IState* mDefaultState;
	
};

MEDUSA_END;
