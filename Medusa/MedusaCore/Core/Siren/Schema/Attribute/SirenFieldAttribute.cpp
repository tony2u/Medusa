// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "SirenFieldAttribute.h"
#include "Core/IO/Stream/IStream.h"
#include "Core/Log/Log.h"

MEDUSA_BEGIN;


SirenFieldAttribute::~SirenFieldAttribute(void)
{

}


bool SirenFieldAttribute::IsRequired() const
{
	return !MEDUSA_FLAG_HAS(mMode, SirenFieldGenerateMode::Optional);
}


bool SirenFieldAttribute::OnLoaded()
{
	StringPropertySet copy = mKeyValues;
	if (mKeyValues.Has("Optional"))
	{
		MEDUSA_FLAG_ADD(mMode, SirenFieldGenerateMode::Optional);
		copy.RemoveKey("Optional");
	}

	if (mKeyValues.Has("ForceKeyToPtr"))
	{
		MEDUSA_FLAG_ADD(mMode, SirenFieldGenerateMode::ForceKeyToPtr);
		copy.RemoveKey("ForceKeyToPtr");
	}

	if (mKeyValues.Has("ForceValueToPtr"))
	{
		MEDUSA_FLAG_ADD(mMode, SirenFieldGenerateMode::ForceValueToPtr);
		copy.RemoveKey("ForceValueToPtr");
	}

	if (mKeyValues.Has("AddDictionaryMethods"))
	{
		MEDUSA_FLAG_ADD(mMode, SirenFieldGenerateMode::AddDictionaryMethods);
		copy.RemoveKey("AddDictionaryMethods");
	}

	if (mKeyValues.Has("SuppressMethod"))
	{
		MEDUSA_FLAG_ADD(mMode, SirenFieldGenerateMode::SuppressMethod);
		copy.RemoveKey("SuppressMethod");
	}

	for (auto& keyValuePair : copy)
	{
		Log::FormatError("Invalid attribute:{}={}", keyValuePair.Key, keyValuePair.Value);
	}

	return true;
}

StringRef SirenFieldAttribute::Modifier() const
{
	if (IsRequired())
	{
		return "Required";
	}
	return "Optional";
}

bool SirenFieldAttribute::LoadFrom(IStream& stream)
{
	mMode = stream.Read<SirenFieldGenerateMode>();
	return true;
}

bool SirenFieldAttribute::SaveTo(IStream& stream) const
{
	stream.Write(mMode);
	return true;
}

MEDUSA_END;