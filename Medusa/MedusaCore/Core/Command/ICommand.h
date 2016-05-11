// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaCorePreDeclares.h"
#include "Core/Pattern/ISharable.h"
#include "Core/Pattern/RTTI/RTTIObject.h"
#include "Core/Pattern/IInitializable.h"
#include "Core/Collection/List.h"

MEDUSA_BEGIN;

struct ICommand :public ISharableThreadSafe,
	public RTTIObject,
	public IInitializable
{
	MEDUSA_DECLARE_RTTI_ROOT;

public:
	virtual bool OnEnter() { return true; }
	virtual bool OnExecute() { return true; }
	virtual bool OnExit() { return true; }

	virtual ~ICommand();

	bool Execute();
public:
	void AddBefore(ICommand* command);
	void AddAfter(ICommand* command);

	void ClearBefore();
	void ClearAfter();
	void Clear();

protected:
	List<ICommand*> mBeforeCommands;
	List<ICommand*> mAfterCommands;
};

MEDUSA_END;