// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "ISirenType.h"
#include "Core/IO/Stream/IStream.h"

MEDUSA_BEGIN;

ISirenType::ISirenType()
{
	
}

ISirenType::ISirenType(const StringRef& name)
	:mName(name),mFullName(name)
{

}


ISirenType::~ISirenType(void)
{

}


bool ISirenType::LoadFrom(IStream& stream)
{
	mName = stream.ReadString();
	return true;
}

bool ISirenType::SaveTo(IStream& stream) const
{
	stream.WriteString(mName);
	return true;
}

MEDUSA_END;