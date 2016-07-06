// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "SirenClassAttribute.h"
#include "Core/IO/Stream/IStream.h"
#include "Core/Log/Log.h"

MEDUSA_BEGIN;

SirenClassAttribute::SirenClassAttribute(SirenClassGenerateMode mode, const StringRef& dir)
	:mMode(mode), mDir(dir)
{

}

SirenClassAttribute::~SirenClassAttribute(void)
{
	
}





bool SirenClassAttribute::OnLoaded()
{
	if (mKeyValues.RemoveKey("Generate"))
	{
		MEDUSA_FLAG_ADD(mMode, SirenClassGenerateMode::Generate);
	}

	if (mKeyValues.RemoveKey("Suppress"))
	{
		MEDUSA_FLAG_ADD(mMode, SirenClassGenerateMode::Suppress);
		MEDUSA_FLAG_REMOVE(mMode, SirenClassGenerateMode::Generate);

	}

	if (mKeyValues.RemoveKey("Embeded"))
	{
		MEDUSA_FLAG_ADD(mMode, SirenClassGenerateMode::Embeded);
	}

	if (mKeyValues.RemoveKey("SuppressCompare"))
	{
		MEDUSA_FLAG_ADD(mMode, SirenClassGenerateMode::SuppressCompare);
	}

	if (mKeyValues.RemoveKey("SuppressCopy"))
	{
		MEDUSA_FLAG_ADD(mMode, SirenClassGenerateMode::SuppressCopy);
	}

	if (mKeyValues.RemoveKey("SirenConfig"))
	{
		MEDUSA_FLAG_ADD(mMode, SirenClassGenerateMode::SirenConfig);
	}

	if (mKeyValues.Has("Dir"))
	{
		mDir = mKeyValues.Get("Dir");
		mKeyValues.RemoveKey("Dir");
	}

	return true;
}


bool SirenClassAttribute::LoadFrom(IStream& stream)
{
	RETURN_FALSE_IF_FALSE(ISirenAttribute::LoadFrom(stream));
	mMode = stream.Read<SirenClassGenerateMode>();
	mDir = stream.ReadString();
	return true;
}

bool SirenClassAttribute::SaveTo(IStream& stream) const
{
	RETURN_FALSE_IF_FALSE(ISirenAttribute::SaveTo(stream));
	stream.Write(mMode);
	stream.WriteString(mDir);
	return true;
}

MEDUSA_END;

