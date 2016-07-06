// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "SirenEnumAttribute.h"
#include "Core/IO/Stream/IStream.h"
#include "Core/Log/Log.h"

MEDUSA_BEGIN;

SirenEnumAttribute::SirenEnumAttribute(SirenEnumGenerateMode mode, const StringRef& dir)
	:mMode(mode),mDir(dir)
{

}

SirenEnumAttribute::~SirenEnumAttribute(void)
{

}

bool SirenEnumAttribute::OnLoaded()
{
	if (mKeyValues.RemoveKey("Generate"))
	{
		MEDUSA_FLAG_ADD(mMode, SirenEnumGenerateMode::Generate);
	}

	if (mKeyValues.RemoveKey("Suppress"))
	{
		MEDUSA_FLAG_ADD(mMode, SirenEnumGenerateMode::Suppress);
		MEDUSA_FLAG_REMOVE(mMode, SirenEnumGenerateMode::Generate);
	}

	if (mKeyValues.RemoveKey("CustomEnum"))
	{
		MEDUSA_FLAG_ADD(mMode, SirenEnumGenerateMode::CustomEnum);
	}

	if (mKeyValues.RemoveKey("CustomFlag"))
	{
		MEDUSA_FLAG_ADD(mMode, SirenEnumGenerateMode::CustomFlag);
	}

	if (mKeyValues.Has("Dir"))
	{
		mDir = mKeyValues.Get("Dir");
		mKeyValues.RemoveKey("Dir");
	}


	return true;
}
bool SirenEnumAttribute::LoadFrom(IStream& stream)
{
	RETURN_FALSE_IF_FALSE(ISirenAttribute::LoadFrom(stream));
	mMode = stream.Read<SirenEnumGenerateMode>();
	mDir = stream.ReadString();
	return true;
}

bool SirenEnumAttribute::SaveTo(IStream& stream) const
{
	RETURN_FALSE_IF_FALSE(ISirenAttribute::SaveTo(stream));
	stream.Write(mMode);
	stream.WriteString(mDir);
	return true;
}


MEDUSA_END;

