// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#ifdef MEDUSA_SQL
#include "SqlConectionInfo.h"

MEDUSA_BEGIN;



SqlConectionInfo::SqlConectionInfo(const StringRef& host, const StringRef& user, const StringRef& password, const StringRef& database, ushort port/*= 3306*/, const char *unixSocket /*= nullptr*/, SqlClientFlags clientFlags /*= SqlClientFlags::None*/)
	:mHost(host),
	mUser(user),
	mPassword(password),
	mDatabase(database),
	mPort(port),
	mUnixSocket(unixSocket),
	mClientFlags(clientFlags)
{

}

SqlConectionInfo::~SqlConectionInfo(void)
{
	
}

MEDUSA_END;

#endif