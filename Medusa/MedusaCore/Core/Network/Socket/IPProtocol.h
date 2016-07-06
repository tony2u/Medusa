// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/String/StringRef.h"
#include "SocketDefines.h"
MEDUSA_BEGIN;

class IPProtocol
{
public:
	IPProtocol(protoent* val = nullptr) :mProtoent(val) {}
	bool IsValid()const { return mProtoent != nullptr; }

	static IPProtocol GetProtocol(StringRef val)
	{
		protoent* result = getprotobyname(val.c_str());
		return IPProtocol(result);

	}
	static IPProtocol GetProtocol(SocketProtocolType protocol)
	{
		protoent* result = getprotobynumber((int)protocol);
		return IPProtocol(result);
	}
	static IPProtocol GetProtocol(SocketType socketType)
	{
		return GetProtocol(GetProtocolType(socketType));
	}

	static SocketProtocolType GetProtocolType(SocketType socketType)
	{
		if (socketType == SocketType::TCP)
		{
			return SocketProtocolType::TCP;
		}
		else if (socketType == SocketType::UDP)
		{
			return SocketProtocolType::UDP;
		}
		return SocketProtocolType::TCP;
	}

	static const char* GetProtocolName(SocketType socketType)
	{
		if (socketType == SocketType::TCP)
		{
			return "tcp";
		}
		else if (socketType == SocketType::UDP)
		{
			return "udp";
		}
		return nullptr;
	}

public:
	protoent* Protoent() { return mProtoent; }

	StringRef ProtocolName() const { return mProtoent->p_name; }
	void SetProtocolName(StringRef val) { mProtoent->p_name = (char*)val.c_str(); }

	char** Aliases() const { return mProtoent->p_aliases; }
	void SetAliases(char** val) { mProtoent->p_aliases = val; }

	short ProtocolId() const { return mProtoent->p_proto; }
	void SetProtocolId(short val) { mProtoent->p_proto = val; }
private:
	protoent* mProtoent;
};
MEDUSA_END;
