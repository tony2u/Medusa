// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "ISirenAttribute.h"
#include "Core/String/StringParser.h"
#include "Core/Log/Log.h"
#include "Core/IO/Stream/IStream.h"

MEDUSA_BEGIN;

ISirenAttribute::ISirenAttribute()
{

}

ISirenAttribute::ISirenAttribute(const StringPropertySet& val)
	:mKeyValues(val)
{

}

ISirenAttribute::~ISirenAttribute(void)
{

}

bool ISirenAttribute::Load(const StringRef& str)
{
	RETURN_FALSE_IF_FALSE(mKeyValues.Parse(str));
	return OnLoaded();
}

bool ISirenAttribute::AddAttribute(StringRef name, StringRef val)
{
	mKeyValues.Set(name, val);
	return true;
}


bool ISirenAttribute::LoadFrom(IStream& stream)
{
	uint32 count = stream.Read<uint32>();
	FOR_EACH_SIZE(i, count)
	{
		HeapString key= stream.ReadString();
		HeapString value = stream.ReadString();
		mKeyValues.Add(key, value);
	}

	return true;
}

bool ISirenAttribute::SaveTo(IStream& stream) const
{
	stream.Write((uint32)mKeyValues.Count());
	for (auto& pair:mKeyValues)
	{
		stream.WriteString(pair.Key);
		stream.WriteString(pair.Value);
	}
	return true;
}

MEDUSA_END;