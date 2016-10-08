// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Pattern/Runnable/DefaultRunnable.h"
#include "Core/Pattern/IClone.h"
#include "Core/String/HeapString.h"

MEDUSA_BEGIN;

enum class ActionType
{
	Instant,
	Finite,
	Infinite
};

class IAction :public IClone<IAction>, public DefaultRunnable
{
public:
	IAction(const StringRef& name = StringRef::Empty) :mName(name) {}

	virtual ~IAction(void) {}
	virtual ActionType Type()const = 0;

public:
	virtual bool Update(float dt, float blend = 1.f)
	{
		return true;	//return true to continue next actions
	}

	bool ForceUpdate(float dt)
	{
		return Update(dt);
	}

	bool IsDead()const { return !mKeepAlive && IsDone(); }
	bool IsAlive()const { return mKeepAlive || !IsDone(); }
	bool IsKeepAlive()const {return mKeepAlive;}
	void KeepAlive(bool val = true) { mKeepAlive = val; }

	void* Target() const { return mTarget; }
	void SetTarget(void* val) { mTarget = val; }

	int Tag() const { return mTag; }
	void SetTag(int val) { mTag = val; }

	bool HasName()const { return !mName.IsEmpty(); }
	StringRef Name() const { return mName; }
	void SetName(const StringRef& val) { mName = val; }

	virtual IAction* FindActionByTagRecursively(int tag)const { return nullptr; }
	virtual IAction* FindActionByNameRecursively(const StringRef& name) const { return nullptr; }

	virtual bool Initialize(void* target)
	{
		mTarget = target;
		return true;
	}
	virtual IAction* Reverse()const { MEDUSA_ASSERT_NOT_IMPLEMENT(); return nullptr; }
	virtual float ElapsedExceed()const { return 0.f; }

protected:
	virtual void BuildClone(IAction& obj) override
	{
		obj.mTarget = mTarget;
		obj.mTag = mTag;
		obj.mName = mName;
		obj.mKeepAlive = mKeepAlive;
	}
protected:
	void* mTarget = nullptr;
	int mTag = 0;
	HeapString mName;
	bool mKeepAlive = false;	//won't be deleted after done

};
MEDUSA_END;
