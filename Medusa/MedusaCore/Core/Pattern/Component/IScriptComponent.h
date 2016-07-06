// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#ifdef MEDUSA_SCRIPT

#include "Core/Pattern/Component/IComponent.h"
#include "Core/Script/ScriptDefines.h"

MEDUSA_BEGIN;

class IScriptComponent :public IComponent
{
	MEDUSA_DECLARE_COMPONENT(IScriptComponent,IComponent);
public:
	IScriptComponent(const StringRef& name = StringRef::Empty, int priority = 0, void* userData = nullptr);
	virtual ~IScriptComponent(void);

	ScriptObject& GetScriptObject() { return mScriptObject; }
	void SetScriptObject(const ScriptObject& val) { mScriptObject = val; OnScriptObjectChanged(); }

protected:
	virtual void OnScriptObjectChanged() {}
protected:
	ScriptObject mScriptObject;
};


MEDUSA_END;

#endif