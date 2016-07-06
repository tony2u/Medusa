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
		for(auto& item: mBeforeCommands)
		{
			RETURN_FALSE_IF_FALSE(item->Execute());
		}
	}

	RETURN_FALSE_IF_FALSE(OnExecute());

	if (!mAfterCommands.IsEmpty())
	{
		for (auto& item : mAfterCommands)
		{
			RETURN_FALSE_IF_FALSE(item->Execute());
		}
	}


	return OnExit();
}

void ICommand::AddBefore(const ShareCommand& command)
{
	mBeforeCommands.Add(command);
	command->SetParent(this);

}
void ICommand::AddAfter(const ShareCommand& command)
{
	mAfterCommands.Add(command);
	command->SetParent(this);
}

void ICommand::ClearBefore()
{
	mBeforeCommands.Clear();

}
void ICommand::ClearAfter()
{
	mAfterCommands.Clear();
}
void ICommand::Clear()
{
	ClearBefore();
	ClearAfter();

}



MEDUSA_END;


