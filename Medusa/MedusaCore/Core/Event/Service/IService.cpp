// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "IService.h"
#include "Core/Command/ICommand.h"
#include "Core/Pattern/AutoIncreaseId.h"

MEDUSA_BEGIN;

IService::IService(const StringRef& options /*= StringRef::Empty*/)
{
	mProperties.Parse(options);
}

IService::~IService()
{
}

bool IService::Start()
{
	mState = ServiceState::Running;
	return true;
}

bool IService::Stop()
{
	mState = ServiceState::None;
	return true;
}


void IService::SetProperties(const StringPropertySet& val)
{
	mProperties = val;
}

void IService::AddAttribute(const StringRef& name, const StringRef& val)
{
	mProperties.Set(name, val);
}


MEDUSA_END;
