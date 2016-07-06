// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Rendering/Command/IRenderingCommand.h"

MEDUSA_BEGIN;



class BaseBatchRenderingCommand :public IRenderingCommand
{
	
	MEDUSA_RTTI(BaseBatchRenderingCommand,IRenderingCommand);
public:
	BaseBatchRenderingCommand();
	~BaseBatchRenderingCommand(void);

	virtual bool Initialize() override;
	virtual bool Uninitialize() override;

	
};

MEDUSA_END;
