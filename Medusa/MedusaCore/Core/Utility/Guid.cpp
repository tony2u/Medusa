// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Core/Utility/Guid.h"
#include "Core/Log/Log.h"

MEDUSA_BEGIN;

Guid Guid::NewGuid()
{
	Guid guid;
#ifdef WIN32
#ifdef MEDUSA_ENABLE_VLD
	Log::AssertFailed("CoCreateGuid conflict with vld, don't know why.");
	UN_USED(guid);
#else
	::CoCreateGuid((GUID*)&guid);
#endif
#else
	uuid_generate(reinterpret_cast<unsigned char *>(&guid));
#endif

	return guid;
}

Guid::StringType Guid::ToString() const
{
	Guid::StringType buf;
#ifdef WIN32
	_snprintf_s(buf.StackBuffer(),
		buf.Size(),
		"%X%X%X%X%X%X%X%X%X%X%X",
		Data1, Data2, Data3,
		Data4[0], Data4[1],
		Data4[2], Data4[3],
		Data4[4], Data4[5],
		Data4[6], Data4[7]);
#else
	snprintf(buf.StackBuffer(),
		buf.Size(),
		"%lX%hX%hX%hhX%hhX%hhXl%X%X%X%X%X",
		Data1, Data2, Data3,
		Data4[0], Data4[1],
		Data4[2], Data4[3],
		Data4[4], Data4[5],
		Data4[6], Data4[7]);
#endif
	buf.ForceUpdateLength();
	return buf;
}

MEDUSA_END;