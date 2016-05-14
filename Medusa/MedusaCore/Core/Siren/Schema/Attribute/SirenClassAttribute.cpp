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

	if (mKeyValues.Has("Generate"))
	{
		MEDUSA_FLAG_ADD(mMode, SirenClassGenerateMode::Generate);
		copy.RemoveKey("Generate");
	}

	if (mKeyValues.Has("Suppress"))
	{
		MEDUSA_FLAG_ADD(mMode, SirenClassGenerateMode::Suppress);
		MEDUSA_FLAG_REMOVE(mMode, SirenClassGenerateMode::Generate);

		copy.RemoveKey("Suppress");
	}

	if (mKeyValues.Has("Embeded"))
	{
		MEDUSA_FLAG_ADD(mMode, SirenClassGenerateMode::Embeded);
		copy.RemoveKey("Embeded");
	}

	if (mKeyValues.Has("SuppressCompare"))
	{
		MEDUSA_FLAG_ADD(mMode, SirenClassGenerateMode::SuppressCompare);
		copy.RemoveKey("SuppressCompare");
	}

	if (mKeyValues.Has("SuppressCopy"))
	{
		MEDUSA_FLAG_ADD(mMode, SirenClassGenerateMode::SuppressCopy);
		copy.RemoveKey("SuppressCopy");
	}

	if (mKeyValues.Has("SirenConfig"))
	{
		MEDUSA_FLAG_ADD(mMode, SirenClassGenerateMode::SirenConfig);
		copy.RemoveKey("SirenConfig");
	}

	if (mKeyValues.Has("Dir"))
	{
		mDir = mKeyValues.Get("Dir");
		copy.RemoveKey("Dir");
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

