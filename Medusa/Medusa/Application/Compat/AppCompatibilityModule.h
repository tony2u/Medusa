// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaPreDeclares.h"
#include "Core/Module/IModule.h"
#include "AppCompatibility.h"

MEDUSA_BEGIN;

class AppCompatibilityModule:public IModule
{
public:
	AppCompatibilityModule();
	virtual ~AppCompatibilityModule();

	AppCompatibility& MutableData() { return mCompatibility; }

public:
	virtual bool Initialize() override;
	virtual bool Uninitialize() override { return true; }
protected:
	virtual bool OnLoad(IEventArg& e = IEventArg::Empty) override;
	virtual bool OnUnload(IEventArg& e = IEventArg::Empty) override;
	virtual bool OnReload(IEventArg& e = IEventArg::Empty) override;

	AppCompatibility mCompatibility;
};


MEDUSA_END;