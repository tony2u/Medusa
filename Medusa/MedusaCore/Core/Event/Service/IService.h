// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "ServiceDefines.h"
#include "Core/Pattern/Property/StringPropertySet.h"
#include "Core/Pattern/RTTI/RTTIObject.h"

MEDUSA_BEGIN;

class IService:public RTTIObject
{
	MEDUSA_RTTI_ROOT(IService);
public:
	IService(const StringRef& options=StringRef::Empty);
	virtual ~IService();
public:
	uint Id() const { return mId; }
	void SetId(uint val) { mId = val; }

	virtual bool Start();
	virtual bool Stop();
	virtual void Update(float dt) {}

	const StringPropertySet& Properties() const { return mProperties; }
	virtual void SetProperties(const StringPropertySet& val);
	virtual void AddAttribute(const StringRef& name, const StringRef& val);

	virtual bool Submit(const ShareCommand& command) = 0;
protected:
	uint mId=0;
	StringPropertySet mProperties;
	std::atomic<ServiceState> mState = ServiceState::None;

};



MEDUSA_END;
