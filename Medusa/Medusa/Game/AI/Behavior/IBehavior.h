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
	MEDUSA_RTTI_ROOT(IBehavior);
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


#define MEDUSA_DECLARE_BEHAVIOR(className,baseClassName)													\
		MEDUSA_RTTI(className,baseClassName);\
private:																				\
	const static StaticConstructor mStaticConstructor;							

#define MEDUSA_IMPLEMENT_BEHAVIOR(className) 																					 \
	const StaticConstructor className::mStaticConstructor([]{BehaviorFactory::Instance().Register<className>(#className);});			


MEDUSA_END;
