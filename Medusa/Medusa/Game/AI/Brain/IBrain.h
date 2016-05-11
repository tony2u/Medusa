// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Collection/Dictionary.h"
#include "Game/AI/Behavior/IBehavior.h"
#include "Core/Command/EventArg/IEventArg.h"
#include "Core/Pattern/ISharable.h"
#include "Core/Pattern/RTTI/RTTIObject.h"
#include "Core/Pattern/StaticConstructor.h"

MEDUSA_BEGIN;


class IBrain :public ISharableSingleThread,public RTTIObject
{
public:
	MEDUSA_DECLARE_RTTI_ROOT;
public:
	IBrain();
	virtual ~IBrain(void);
public:
	virtual const IBehavior* Behave(IBrainBody& brainBody, void* sender);
	virtual const IBehavior* ReceiveEvent(IBrainBody& brainBody, void* sender, IEventArg& e);
public:
	IBrainMemory* Memory() const { return mMemory; }
	void SetMemory(IBrainMemory* val);

	IBehavior* RootBehavior() const { return mRootBehavior; }
	void SetRootBehavior(IBehavior* val);

	template<typename TEventArg2>
	bool RegisterEventBehavior(IBehavior* val)
	{
		const RTTIClass* rttiClass = &TEventArg2::ClassStatic();
		return RegisterEventBehavior(rttiClass->Name(), val);
	}

	bool RegisterEventBehavior(const StringRef& eventName, IBehavior* val);

	StringRef Paramter() const { return mParamter; }
	void SetParamter(const StringRef& val) { mParamter = val; }
	virtual bool Initialize() { return true; }
protected:
	HeapString mParamter;
	IBrainMemory* mMemory;

	IBehavior* mRootBehavior;
	Dictionary<HeapString, IBehavior*> mEventBehaviorDict;
};


#define MEDUSA_DECLARE_BRAIN													\
		MEDUSA_DECLARE_RTTI;\
private:																				\
	const static StaticConstructor mStaticConstructor;							\
	static void SelfRegisterStaticCallback();

#define MEDUSA_IMPLEMENT_BRAIN(className,baseClassName) 																					 \
	MEDUSA_IMPLEMENT_RTTI(className,baseClassName);\
	const StaticConstructor className::mStaticConstructor(SelfRegisterStaticCallback);					 \
	void className::SelfRegisterStaticCallback(){BrainFactory::Instance().Register<className>(#className);}


MEDUSA_END;
