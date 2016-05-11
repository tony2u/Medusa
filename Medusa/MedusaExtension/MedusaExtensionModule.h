// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaExtensionPreDeclares.h"
#include "Core/Module/IModule.h"

MEDUSA_BEGIN;


class MedusaExtensionModule :public IModule
{
public:
	MedusaExtensionModule();
public:
	virtual bool Initialize() override;
	virtual bool Uninitialize() override { return true; }
protected:
	virtual bool OnLoad(IEventArg& e = IEventArg::Empty) override;

};

MEDUSA_END;
