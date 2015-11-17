// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "ICommand.h"

MEDUSA_BEGIN;

ICommand::~ICommand()
{
	Clear();
}

bool ICommand::Execute()
{
	RETURN_FALSE_IF_FALSE(OnEnter());
	if (!mBeforeCommands.IsEmpty())
	{
		FOR_EACH_COLLECTION(i, mBeforeCommands)
		{
			ICommand* item = *i;
			RETURN_FALSE_IF_FALSE(item->Execute());
		}
	}

	RETURN_FALSE_IF_FALSE(OnExecute());

	if (!mAfterCommands.IsEmpty())
	{
		FOR_EACH_COLLECTION(i, mAfterCommands)
		{
			ICommand* item = *i;
			RETURN_FALSE_IF_FALSE(item->Execute());
		}
	}


	return OnExit();
}

void ICommand::AddBefore(ICommand* command)
{
	SAFE_RETAIN(command);
	mBeforeCommands.Add(command);

}
void ICommand::AddAfter(ICommand* command)
{
	SAFE_RETAIN(command);
	mAfterCommands.Add(command);
}

void ICommand::ClearBefore()
{
	SAFE_RELEASE_COLLECTION(mBeforeCommands);

}
void ICommand::ClearAfter()
{
	SAFE_RELEASE_COLLECTION(mAfterCommands);

}
void ICommand::Clear()
{
	ClearBefore();
	ClearAfter();

}


MEDUSA_IMPLEMENT_RTTI_ROOT(ICommand);

MEDUSA_END;


