// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Pattern/ISharable.h"
#include "Core/Pattern/StaticConstructor.h"
#include "Core/Pattern/RTTI/RTTIObject.h"

MEDUSA_BEGIN;

struct IPredicate :public ISharableSingleThread, public RTTIObject
{
	MEDUSA_DECLARE_RTTI_ROOT;
public:
	bool EvaluateBool(void* p)const { return Evaluate(p) > 0; }
	virtual int Evaluate(void* p)const = 0;
	IPredicate();
	virtual ~IPredicate();
	void Add(const IPredicate* item);
	void Clear();

	uint Id() const { return mId; }
	void SetId(uint val) { mId = val; }

	StringRef Paramter() const { return mParamter; }
	void SetParamter(const StringRef& val) { mParamter = val; }
	virtual bool Initialize() { return true; }
protected:
	uint mId;
	
	HeapString mParamter;
	List<const IPredicate*> mItems;
};

#define MEDUSA_DECLARE_PREDICATE 													\
		MEDUSA_DECLARE_RTTI;\
private:																				\
	const static StaticConstructor mStaticConstructor;							\
	static void SelfRegisterStaticCallback();

#define MEDUSA_IMPLEMENT_PREDICATE(className,baseClassName) 																					 \
	MEDUSA_IMPLEMENT_RTTI(className,baseClassName);\
	const StaticConstructor className::mStaticConstructor(SelfRegisterStaticCallback);					 \
	void className::SelfRegisterStaticCallback(){PredicateFactory::Instance().Register<className>(#className);}

MEDUSA_END;
