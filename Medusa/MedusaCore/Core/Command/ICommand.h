// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaCorePreDeclares.h"
#include "Core/Pattern/ISharable.h"
#include "Core/Pattern/RTTI/RTTIObject.h"
#include "Core/Pattern/IInitializable.h"
#include "Core/Collection/List.h"
#include "Core/Pattern/INonCopyable.h"
#include "Core/Pattern/Share.h"

MEDUSA_BEGIN;

struct ICommand :public ISharableThreadSafe, public RTTIObject, public IInitializable
{
	MEDUSA_RTTI_ROOT(ICommand);
public:
	ICommand(uint fromServiceId = 0, uint toServcieId = 0)
		:mFromService(fromServiceId),
		mToService(toServcieId)
	{
	}
	virtual ~ICommand();

public:
	uint& MutableFromService() { return mFromService; }
	uint FromService() const { return mFromService; }
	void SetFromService(uint val) { mFromService = val; }

	uint& MutableToService() { return mToService; }
	uint ToService() const { return mToService; }
	void SetToService(uint val) { mToService = val; }
public:
	virtual bool OnEnter() { return true; }
	virtual bool OnExecute() { return true; }
	virtual bool OnExit() { return true; }
	bool Execute();
public:
	ICommand* Parent() const { return mParent; }
	void SetParent(ICommand* val) { mParent = val; }

	void AddBefore(const ShareCommand& command);
	void AddAfter(const ShareCommand& command);

	void ClearBefore();
	void ClearAfter();
	void Clear();

protected:
	uint mFromService = 0;
	uint mToService = 0;

	ICommand* mParent = nullptr;
	List<ShareCommand> mBeforeCommands;
	List<ShareCommand> mAfterCommands;
};


//[PRE_DECLARE_BEGIN]
typedef Share<ICommand> ShareCommand;
//[PRE_DECLARE_END]

MEDUSA_END;