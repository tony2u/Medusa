// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Command/ICommand.h"
#include "Core/Pattern/IInitializable.h"

MEDUSA_BEGIN;



class IRenderingCommand:public ICommand
{
	MEDUSA_RTTI(IRenderingCommand,ICommand);
public:
	IRenderingCommand();
	~IRenderingCommand(void);

};

MEDUSA_END;
