// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Pattern/RTTI/RTTIObject.h"
#include "Core/Pattern/StaticConstructor.h"
#include "Core/Collection/List.h"

MEDUSA_BEGIN;


class IState :public RTTIObject
{
	MEDUSA_RTTI_ROOT(IState);
public:
	IState();
	virtual ~IState(void);
public:
	void AddBefore(StateAutoConnector* val);
	void AddAfter(StateAutoConnector* val);
	void AddEvent(StateEventConnector* val);

public:
	virtual void Enter(void* sender);
	virtual void Exit(void* sender);
	virtual uint GetIndex()const { return 0; }

	StateAutoConnector* Update(void* sender, float dt);
	StateEventConnector* ReceiveEvent(void* sender, IEventArg& e);
public:
	virtual bool OnUpdate(void* sender, float dt) { return false; }
	virtual void OnBeforeEvent(void* sender, IEventArg& e) {}
	virtual void OnAfterEvent(void* sender, IEventArg& e) {}

protected:
	List<StateAutoConnector*> mBeforeConnectors;
	List<StateAutoConnector*> mAfterConnectors;
	List<StateEventConnector*> mEventConnectors;

};


#define MEDUSA_DECLARE_STATE(className,baseClassName,index)													\
		MEDUSA_RTTI(className,baseClassName);\
public:\
virtual uint GetIndex()const override { return index; }\
const static uint Index = index;\
private:																				\
	const static StaticConstructor mStaticConstructor;							

#define MEDUSA_IMPLEMENT_STATE(className) 																					 \
	const StaticConstructor className::mStaticConstructor([]{StateFactory::Instance().Register<className>(#className);});					 \



MEDUSA_END;
