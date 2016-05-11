// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Pattern/ISharable.h"
#include "Core/Pattern/RTTI/RTTIObject.h"
#include "Core/Pattern/StaticConstructor.h"
#include "Core/String/HeapString.h"

MEDUSA_BEGIN;


class IBehavior :public ISharableSingleThread, public RTTIObject
{
	MEDUSA_DECLARE_RTTI_ROOT;
public:
	IBehavior();
	virtual ~IBehavior(void);

	virtual const IBehavior* Behave(IBrainBody& brainBody, void* sender)const;
	virtual const IBehavior* ReceiveEvent(IBrainBody& brainBody, void* sender, IEventArg& e)const;

	virtual bool LoadFromXmlNode(const pugi::xml_node& node);

	StringRef Paramter() const { return mParamter; }
	void SetParamter(const StringRef& val) { mParamter = val; }
	virtual bool Initialize() { return true; }
	virtual bool Enter(IBrainBody& brainBody, void* sender)const { return true; }
	virtual void Exit(IBrainBody& brainBody, void* sender)const {}
	virtual bool Update(IBrainBody& brainBody, void* sender, float dt)const { return false; }
protected:
	HeapString mParamter;
};


#define MEDUSA_DECLARE_BEHAVIOR													\
		MEDUSA_DECLARE_RTTI;\
private:																				\
	const static StaticConstructor mStaticConstructor;							\
	static void SelfRegisterStaticCallback();

#define MEDUSA_IMPLEMENT_BEHAVIOR(className,baseClassName) 																					 \
	MEDUSA_IMPLEMENT_RTTI(className,baseClassName);\
	const StaticConstructor className::mStaticConstructor(SelfRegisterStaticCallback);					 \
	void className::SelfRegisterStaticCallback(){BehaviorFactory::Instance().Register<className>(#className);}


MEDUSA_END;
