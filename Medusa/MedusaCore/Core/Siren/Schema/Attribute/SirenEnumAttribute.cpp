// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "SirenEnumAttribute.h"
#include "Core/IO/Stream/IStream.h"
#include "Core/Log/Log.h"

MEDUSA_BEGIN;

SirenEnumAttribute::~SirenEnumAttribute(void)
{

}

bool SirenEnumAttribute::OnLoaded()
{
	StringPropertySet copy = mKeyValues;
	if (mKeyValues.Has("Generate"))
	{
		MEDUSA_FLAG_ADD(mMode, SirenEnumGenerateMode::Generate);
		copy.RemoveKey("Generate");
	}

	if (mKeyValues.Has("Suppress"))
	{
		MEDUSA_FLAG_ADD(mMode, SirenEnumGenerateMode::Suppress);
		MEDUSA_FLAG_REMOVE(mMode, SirenEnumGenerateMode::Generate);

		copy.RemoveKey("Suppress");

	}

	if (mKeyValues.Has("CustomEnum"))
	{
		MEDUSA_FLAG_ADD(mMode, SirenEnumGenerateMode::CustomEnum);
		copy.RemoveKey("CustomEnum");

	}

	if (mKeyValues.Has("CustomFlag"))
	{
		MEDUSA_FLAG_ADD(mMode, SirenEnumGenerateMode::CustomFlag);
		copy.RemoveKey("CustomFlag");

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

bool SirenEnumAttribute::LoadFrom(IStream& stream)
{
	mMode = stream.Read<SirenEnumGenerateMode>();
	mDir = stream.ReadString();
	return true;
}

bool SirenEnumAttribute::SaveTo(IStream& stream) const
{
	stream.Write(mMode);
	stream.WriteString(mDir);
	return true;
}


MEDUSA_END;

