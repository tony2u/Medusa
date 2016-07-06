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
	if (mKeyValues.RemoveKey("Optional"))
	{
		MEDUSA_FLAG_ADD(mMode, SirenFieldGenerateMode::Optional);
	}

	if (mKeyValues.RemoveKey("?"))
	{
		MEDUSA_FLAG_ADD(mMode, SirenFieldGenerateMode::Optional);
	}

	if (mKeyValues.RemoveKey("+"))
	{
		MEDUSA_FLAG_REMOVE(mMode, SirenFieldGenerateMode::Optional);
	}

	if (mKeyValues.RemoveKey("ForceKeyToPtr"))
	{
		MEDUSA_FLAG_ADD(mMode, SirenFieldGenerateMode::ForceKeyToPtr);
	}

	if (mKeyValues.RemoveKey("ForceValueToPtr"))
	{
		MEDUSA_FLAG_ADD(mMode, SirenFieldGenerateMode::ForceValueToPtr);
	}

	if (mKeyValues.RemoveKey("AddDictionaryMethods"))
	{
		MEDUSA_FLAG_ADD(mMode, SirenFieldGenerateMode::AddDictionaryMethods);
	}

	if (mKeyValues.RemoveKey("SuppressMethod"))
	{
		MEDUSA_FLAG_ADD(mMode, SirenFieldGenerateMode::SuppressMethod);
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
	RETURN_FALSE_IF_FALSE(ISirenAttribute::LoadFrom(stream));
	mMode = stream.Read<SirenFieldGenerateMode>();
	return true;
}

bool SirenFieldAttribute::SaveTo(IStream& stream) const
{
	RETURN_FALSE_IF_FALSE(ISirenAttribute::SaveTo(stream));
	stream.Write(mMode);
	return true;
}

MEDUSA_END;