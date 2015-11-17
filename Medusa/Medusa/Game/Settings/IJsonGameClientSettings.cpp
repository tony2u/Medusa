// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "IJsonGameClientSettings.h"

MEDUSA_BEGIN;
IJsonGameClientSettings::IJsonGameClientSettings(const FileIdRef& fileId)
{

}

IJsonGameClientSettings::~IJsonGameClientSettings()
{
	
}

void* IJsonGameClientSettings::GetAddress(const StringRef& name) const
{
	return nullptr;
}

StringRef IJsonGameClientSettings::UpdateServerConfigName() const
{
	return StringRef::Empty;

}

StringRef IJsonGameClientSettings::UpdateServerUrl() const
{
	return StringRef::Empty;

}



MEDUSA_END;
