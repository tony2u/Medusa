// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#ifdef MEDUSA_SQL

#include "Core/Command/ICommand.h"
MEDUSA_BEGIN;


class SqlCommand :public ICommand
{
	MEDUSA_RTTI(SqlCommand,ICommand);
public:
	SqlCommand(SqlConnection* connection=nullptr);
	virtual ~SqlCommand(void);
	SqlConnection* Connection() const { return mConnection; }
	void SetConnection(SqlConnection* val) { mConnection = val; }

	virtual bool OnExecute()override;
protected:
	SqlConnection* mConnection = nullptr;
	
};

MEDUSA_END;
#endif