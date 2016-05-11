// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#ifdef MEDUSA_SCRIPT

#include "Core/Pattern/Component/IScriptComponent.h"
#include "Core/Script/ScriptDefines.h"
#include "Node/Input/InputDefines.h"

MEDUSA_BEGIN;

class NodeScriptComponent:public IScriptComponent
{
	MEDUSA_DECLARE_COMPONENT;
public:
	NodeScriptComponent(const StringRef& name = StringRef::Empty, int priority = 0, void* userData = nullptr);
	virtual ~NodeScriptComponent(void);

public:
	virtual bool Update(float dt)override;
	virtual bool HandleEvent(InputEventType type, StringRef handlerName, INode* sender, IEventArg* e) override;

	virtual bool Enter()override;
	virtual bool Exit()override;
	virtual bool UpdateLogic() override;
	virtual bool ResetLogic() override;

	bool HasMethod(StringRef name)const;
protected:
	virtual void OnScriptObjectChanged() override;
protected:
	ScriptObject mUpdateMethod;
	ScriptObject mEnterMethod;
	ScriptObject mExitMethod;
	ScriptObject mUpdateLogicMethod;
	ScriptObject mResetLogicMethod;


};


MEDUSA_END;

#endif