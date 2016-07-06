// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Pattern/Event.h"
#include "Core/Pattern/ISharable.h"
#include "Core/Pattern/RTTI/RTTIObject.h"

MEDUSA_BEGIN;

class IDataSource:public ISharableThreadSafe,public RTTIObject
{
	MEDUSA_RTTI_ROOT(IDataSource);
public:
	typedef Event<void (const IDataSource&)> DataChangedEvent;
	DataChangedEvent OnDataChanged;
public:
	IDataSource();
	virtual ~IDataSource(void);

	virtual void PrepareForCommit();
	virtual void Commit();
protected:
	virtual void FireDataChangedEvent();
protected:
	bool mIsChanging;
};

MEDUSA_END;
