// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaCorePreDeclares.h"

#include "Core/Module/IModule.h"

MEDUSA_BEGIN;

class MedusaCoreModule :public IModule
{
public:
	MedusaCoreModule();
public:
	virtual bool Initialize() override;
	virtual bool Uninitialize() override { return true; }
	bool BeforeUpdate(float dt);
	bool AfterUpdate(float dt);

protected:
	virtual bool OnLoad(IEventArg& e = IEventArg::Empty) override;
	virtual bool OnUnload(IEventArg& e = IEventArg::Empty) override;
	virtual bool OnReload(IEventArg& e = IEventArg::Empty) override;
};

MEDUSA_END;
