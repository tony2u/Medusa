// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/String/StringRef.h"
#include "SocketDefines.h"

MEDUSA_BEGIN;



class IPAddress
{
public:
	IPAddress(void) {}
	IPAddress(StringRef ip, ushort port, bool isIP6 = false);
	IPAddress(const sockaddr_in& val):mAddress(val) {}
	IPAddress(const sockaddr_in6& val) :mAddress6(val) {}


	static IPAddress Resolve(StringRef host);
	static bool IsIP(StringRef val);
	static bool IsIP6(StringRef val);

	static bool IsPort(StringRef inValue);


	static IPAddress Local(SOCKET socket);
	static IPAddress Remote(SOCKET socket);
public:
	const sockaddr& Genearl()const { return *(sockaddr*)&mAddress; }
	sockaddr* GenearlPtr()const { return (sockaddr*)&mAddress; }
	const sockaddr_in& IP()const { return mAddress; }
	const sockaddr_in6& IP6()const { return mAddress6; }


	SocketAddressFamily Family() const;
	unsigned short Port() const;
	HeapString IPString()const;

	bool IsIP()const { return Family() == SocketAddressFamily::IP; }
	bool IsIP6()const { return Family() == SocketAddressFamily::IP6; }

	void SetGenearlAddress(const sockaddr& val) { *(sockaddr*)&mAddress = val; }

	HeapString ToString()const;
private:
	union
	{
		sockaddr_in mAddress;
		sockaddr_in6 mAddress6;
	};

};

static_assert(sizeof(IPAddress) == sizeof(struct sockaddr_in6), "");
static_assert(offsetof(sockaddr_in, sin_family) == 0, "Invalid offset");
static_assert(offsetof(sockaddr_in6, sin6_family) == 0, "Invalid offset");
static_assert(offsetof(sockaddr_in, sin_port) == sizeof(ushort), "Invalid offset");
static_assert(offsetof(sockaddr_in6, sin6_port) == sizeof(ushort), "Invalid offset");

MEDUSA_END;
