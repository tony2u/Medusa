// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "IPAddress.h"
#include "Core/System/BitConverter.h"
#include "Core/Log/Log.h"

MEDUSA_BEGIN;



IPAddress::IPAddress(StringRef ip, ushort port, bool isIP6 /*= false*/)
{
	if (isIP6)
	{
		Memory::ClearZero(&mAddress6);
		mAddress6.sin6_family = (int)SocketAddressFamily::IP6;
		mAddress6.sin6_port = BitConverter::HostToNetwork(port);
		if (!ip.IsEmpty())	//0.0.0.0 or "" to bind to any local ip
		{
			if (inet_pton(mAddress6.sin6_family, ip.c_str(), &mAddress6.sin6_addr) <= 0)
			{
				Log::AssertFailedFormat("Invalid ip6:{}", ip);
			}
		}
		
	}
	else
	{
		Memory::ClearZero(&mAddress);
		mAddress.sin_family = (int)SocketAddressFamily::IP;
		mAddress.sin_port = BitConverter::HostToNetwork(port);

		if (!ip.IsEmpty())
		{
			if (inet_pton(mAddress.sin_family, ip.c_str(), &mAddress.sin_addr) <= 0)
			{
				Log::AssertFailedFormat("Invalid ip:{}", ip);
			}
		}
		
	}
}

IPAddress IPAddress::Resolve(StringRef host)
{
	addrinfo* hostent;
	getaddrinfo(host.c_str(), nullptr, nullptr, &hostent);
	IPAddress result;
	result.mAddress.sin_family = hostent->ai_protocol == IPPROTO_IPV6 ? (int)SocketAddressFamily::IP6 : (int)SocketAddressFamily::IP;
	result.mAddress.sin_addr = *reinterpret_cast<in_addr*>(hostent->ai_addr);
	freeaddrinfo(hostent);
	return result;
}

bool IPAddress::IsIP(StringRef val)
{
	//IP address format:<ddd.ddd.ddd.ddd>
	RETURN_FALSE_IF_EMPTY(val);
	in_addr sAddr; // IPv4地址结构体
	int r = inet_pton((int)SocketAddressFamily::IP, val.c_str(), &sAddr);
	return r > 0;	//<=0 means error
}


bool IPAddress::IsIP6(StringRef val)
{
	RETURN_FALSE_IF_EMPTY(val);
	in6_addr sAddr; // IPv6地址结构体
	int r = inet_pton((int)SocketAddressFamily::IP6, val.c_str(), &sAddr);
	return r > 0;	//<=0 means error
}

HeapString IPAddress::ToString() const
{
	if (IsIP())
	{
		HeapString str(INET_ADDRSTRLEN + 5);
		::inet_ntop(AF_INET, (void*)&mAddress.sin_addr, str.c_str(), static_cast<socklen_t>(INET_ADDRSTRLEN));
		str.ForceUpdateLength();
		str.AppendFormat(":{}", Port());
		return str;
	}
	else
	{
		HeapString str(INET6_ADDRSTRLEN + 5);
		::inet_ntop(AF_INET, (void*)&mAddress6.sin6_addr, str.c_str(), static_cast<socklen_t>(INET_ADDRSTRLEN));
		str.ForceUpdateLength();
		str.AppendFormat(":{}", Port());

		return str;
	}
}

bool IPAddress::IsPort(StringRef inValue)
{
	//Port format:<d*>
	RETURN_FALSE_IF_EMPTY(inValue);

	size_t length = inValue.Length();
	for (size_t i = 0; i < length; i++)
	{
		if (!isdigit(inValue[i]))
		{
			return false;
		}
	}
	return true;
}



IPAddress IPAddress::Local(SOCKET socket)
{
	sockaddr_in6 localaddr;
	Memory::ClearZero(&localaddr);
	socklen_t addrlen = static_cast<socklen_t>(sizeof(localaddr));
	if (::getsockname(socket, (sockaddr*)(&localaddr), &addrlen) < 0)
	{
		Log::AssertFailed("Failed to IPAddress::Local");
	}
	return IPAddress(localaddr);
}

IPAddress IPAddress::Remote(SOCKET socket)
{
	sockaddr_in6 localaddr;
	Memory::ClearZero(&localaddr);
	socklen_t addrlen = static_cast<socklen_t>(sizeof(localaddr));
	if (::getpeername(socket, (sockaddr*)(&localaddr), &addrlen) < 0)
	{
		Log::AssertFailed("Failed to IPAddress::Local");
	}
	return IPAddress(localaddr);
}

unsigned short IPAddress::Port() const
{
	return BitConverter::NetworkToHost(mAddress.sin_port);
}

HeapString IPAddress::IPString() const
{
	if (IsIP())
	{
		HeapString str(INET_ADDRSTRLEN + 5);
		::inet_ntop(AF_INET, (void*)&mAddress.sin_addr, str.c_str(), static_cast<socklen_t>(INET_ADDRSTRLEN));
		str.ForceUpdateLength();

		return str;
	}
	else
	{
		HeapString str(INET6_ADDRSTRLEN + 5);
		::inet_ntop(AF_INET, (void*)&mAddress6.sin6_addr, str.c_str(), static_cast<socklen_t>(INET_ADDRSTRLEN));
		str.ForceUpdateLength();

		return str;
	}
}

SocketAddressFamily IPAddress::Family() const
{
	return (SocketAddressFamily)mAddress.sin_family;
}


MEDUSA_END;

