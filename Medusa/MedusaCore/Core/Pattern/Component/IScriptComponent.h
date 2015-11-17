// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Pattern/Component/IComponent.h"

MEDUSA_BEGIN;

class IScriptComponent:public IComponent
{
public:
	IScriptComponent(const StringRef& name = StringRef::Empty, int priority = 0, void* userData = nullptr);
	~IScriptComponent(void);

	ScriptObject* GetScriptObject() const { return mScriptObject; }
	void SetScriptObject(ScriptObject* val) { mScriptObject = val; }

public:
	virtual bool Update(float dt)override;
	virtual bool AcceptEvent(IEventArg& eventArg) override;
protected:
	ScriptObject* mScriptObject;
	
};

MEDUSA_END;
