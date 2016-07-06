// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#ifdef MEDUSA_SQL
#include "Core/String/HeapString.h"
#include "SqlDefines.h"

MEDUSA_BEGIN;


class SqlConectionInfo
{
public:
	SqlConectionInfo() = default;
	SqlConectionInfo(const StringRef& host, const StringRef& user, const StringRef& password, const StringRef& database, ushort port = 3306, const char *unixSocket = nullptr, SqlClientFlags clientFlags = SqlClientFlags::None);
	~SqlConectionInfo(void);
public:
	StringRef Host() const { return mHost; }
	void SetHost(const StringRef& val) { mHost = val; }

	StringRef User() const { return mUser; }
	void SetUser(const StringRef& val) { mUser = val; }

	StringRef Password() const { return mPassword; }
	void SetPassword(const StringRef& val) { mPassword = val; }

	StringRef Database() const { return mDatabase; }
	void SetDatabase(const StringRef& val) { mDatabase = val; }

	ushort Port() const { return mPort; }
	void SetPort(ushort val) { mPort = val; }

	const char* UnixSocket() const { return mUnixSocket; }
	void SetUnixSocket(const char* val) { mUnixSocket = val; }

	SqlClientFlags ClientFlags() const { return mClientFlags; }
	void SetClientFlags(SqlClientFlags val) { mClientFlags = val; }
protected:
	HeapString mHost;
	HeapString mUser;
	HeapString mPassword;
	HeapString mDatabase;
	ushort mPort=0;
	const char* mUnixSocket = nullptr;
	SqlClientFlags mClientFlags = SqlClientFlags::None;
};

MEDUSA_END;
#endif