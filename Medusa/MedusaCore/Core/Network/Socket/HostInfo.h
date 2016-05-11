// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/String/StringRef.h"

MEDUSA_BEGIN;

class HostInfo
{
public:
	HostInfo(addrinfo* inHostent = nullptr) :mHostent(inHostent) {}
	~HostInfo() 
	{
		freeaddrinfo(mHostent);
	}

	bool IsValid()const { return mHostent != nullptr; }

	static HostInfo GetHost(StringRef inHostName)
	{
		addrinfo *res;
		getaddrinfo(inHostName.c_str(), nullptr, nullptr, &res);
		return HostInfo(res);
	}
	

public:
	sockaddr* FirstHostAddress()const { return mHostent->ai_addr; }
private:
	addrinfo* mHostent;
};

MEDUSA_END;
