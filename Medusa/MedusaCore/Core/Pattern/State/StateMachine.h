// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Collection/Stack.h"

MEDUSA_BEGIN;

class StateMachine
{
public:
	StateMachine();
	~StateMachine(void);
public:
	bool Initialize(StringRef modelName);

	StateMachineModel* Model() const { return mModel; }
	void SetModel(StateMachineModel* val) { mModel = val; }

	void Reset(void* sender);

	IState* Current() const { return mCurrentStates.TopOr(nullptr); }

	IState* Get(uint index)const;

	template<typename T>
	IState* Get()const
	{
		return Get(T::Index);
	}
	IState* Find(StringRef name)const;

	void Start(void* sender);

	void Push(void* sender, IState* val);
	template<typename T>
	void Push(void* sender)
	{
		Push(sender, Get(T::Index));
	}
	void Push(void* sender, StringRef name);

	void ReplaceTo(void* sender, IState* val);
	template<typename T>
	void ReplaceTo(void* sender)
	{
		ReplaceTo(sender, Get(T::Index));
	}
	void ReplaceTo(void* sender, StringRef name);

	template<typename T>
	bool IsActive()const
	{
		return IsActive(Get(T::Index));
	}
	bool IsActive(StringRef name)const;
	bool IsActive(IState* val)const;
	bool IsActive(uint index)const;
public:
	void Update(void* sender, float dt);
	void ReceiveEvent(void* sender, IEventArg& e);
private:
	StateMachineModel* mModel;
	Stack<IState*> mCurrentStates;

};

MEDUSA_END;
