// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "SirenClassAttribute.h"
#include "Core/IO/Stream/IStream.h"
#include "Core/Log/Log.h"

MEDUSA_BEGIN;

SirenClassAttribute::~SirenClassAttribute(void)
{
	
}


bool SirenClassAttribute::OnLoaded()
{
	StringPropertySet copy = mKeyValues;

	if (mKeyValues.ContainsKey(StringRef("Generate")))
	{
		MEDUSA_FLAG_ADD(mMode, SirenClassGenerateMode::Generate);
		copy.RemoveKey(StringRef("Generate"));
	}

	if (mKeyValues.ContainsKey(StringRef("Suppress")))
	{
		MEDUSA_FLAG_ADD(mMode, SirenClassGenerateMode::Suppress);
		MEDUSA_FLAG_REMOVE(mMode, SirenClassGenerateMode::Generate);

		copy.RemoveKey(StringRef("Suppress"));
	}

	if (mKeyValues.ContainsKey(StringRef("Embeded")))
	{
		MEDUSA_FLAG_ADD(mMode, SirenClassGenerateMode::Embeded);
		copy.RemoveKey(StringRef("Embeded"));
	}

	if (mKeyValues.ContainsKey(StringRef("SuppressCompare")))
	{
		MEDUSA_FLAG_ADD(mMode, SirenClassGenerateMode::SuppressCompare);
		copy.RemoveKey(StringRef("SuppressCompare"));
	}

	if (mKeyValues.ContainsKey(StringRef("SuppressCopy")))
	{
		MEDUSA_FLAG_ADD(mMode, SirenClassGenerateMode::SuppressCopy);
		copy.RemoveKey(StringRef("SuppressCopy"));
	}

	if (mKeyValues.ContainsKey(StringRef("SirenConfig")))
	{
		MEDUSA_FLAG_ADD(mMode, SirenClassGenerateMode::SirenConfig);
		copy.RemoveKey(StringRef("SirenConfig"));
	}

	if (mKeyValues.ContainsKey(StringRef("Dir")))
	{
		mDir = mKeyValues.Get(StringRef("Dir"));
		copy.RemoveKey(StringRef("Dir"));
	}

	for (auto& keyValuePair : copy)
	{
		Log::FormatError("Invalid attribute:{}={}", keyValuePair.Key, keyValuePair.Value);
	}

	return true;
}

bool SirenClassAttribute::LoadFrom(IStream& stream)
{
	mMode = stream.Read<SirenClassGenerateMode>();
	mDir = stream.ReadString();

	return true;
}

bool SirenClassAttribute::SaveTo(IStream& stream) const
{
	stream.Write(mMode);
	stream.WriteString(mDir);
	return true;
}
MEDUSA_END;

