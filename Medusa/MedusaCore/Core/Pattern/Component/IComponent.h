// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaCorePreDeclares.h"
#include "Core/Pattern/RTTI/RTTIObject.h"
#include "Core/Pattern/StaticConstructor.h"
#include "Core/Pattern/Runnable/DefaultRunnable.h"

MEDUSA_BEGIN;


#define MEDUSA_DECLARE_COMPONENT(className,baseClassName) 				   \
	MEDUSA_RTTI(className,baseClassName);	\
private:													   \
	const static StaticConstructor mStaticConstructor;		   

#define MEDUSA_IMPLEMENT_COMPONENT(className,baseClassName) 																 \
	const StaticConstructor className::mStaticConstructor([]{ComponentFactory::Instance().Register<className>(#className);});						

class IComponent :public RTTIObject, public DefaultRunnable
{
	MEDUSA_RTTI_ROOT(IComponent);
public:
	IComponent(const StringRef& name = StringRef::Empty, int priority = 0, void* userData = nullptr);
	virtual ~IComponent() {}
public:
	StringRef Name() const { return mName; }
	void SetName(const StringRef& val) { mName = val; }

	int Priority() const { return mPriority; }
	void SetPriority(int val) { mPriority = val; }

	void* UserData() const { return mUserData; }
	void SetUserData(void* val) { mUserData = val; }

	IEntity* Entity() const { return mEntity; }
	void SetEntity(IEntity* val) { mEntity = val; }

	int Compare(const IComponent& val)const { return mPriority - val.Priority(); }
public:
	virtual bool Update(float dt);
	virtual bool AcceptEvent(IEventArg& eventArg) { return true; }
	virtual bool Enter() { return true; }
	virtual bool Exit() { return true; }
	virtual bool UpdateLogic() { return true; }
	virtual bool ResetLogic() { return true; }

protected:
	HeapString mName;
	int mPriority;
	void* mUserData;
	IEntity* mEntity;
	

};

	

MEDUSA_END;