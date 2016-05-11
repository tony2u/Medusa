// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/String/StringRef.h"
#include "SocketDefines.h"

MEDUSA_BEGIN;

class AddressInfo
{
public:
	AddressInfo(void)
	{
		Memory::ClearZero(&mAddress);
		SetAddressFamily(SocketAddressFamily::TCPIP);
	}
	AddressInfo(const sockaddr_in& inSockaddr) :mAddress(inSockaddr) { SetAddressFamily(SocketAddressFamily::TCPIP); }
	AddressInfo(const sockaddr& inSockaddr) :mAddress(*(sockaddr_in*)(&inSockaddr)) { SetAddressFamily(SocketAddressFamily::TCPIP); }

	static bool IsIPAddress(StringRef inAddress)
	{
		//IP address format:<ddd.ddd.ddd.ddd>
		RETURN_FALSE_IF_EMPTY(inAddress);
		in_addr sAddr; // IPv4地址结构体
		int r=inet_pton((int)SocketAddressFamily::TCPIP, inAddress.c_str(), &sAddr);
		return r > 0;	//<=0 means error
	}


	static bool IsPort(StringRef inValue)
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
public:
	const sockaddr_in& TCPIPAddress() const { return mAddress; }
	void SetTCPIPAddress(const sockaddr_in& inNewTCPIPAdress) { mAddress = inNewTCPIPAdress; }

	const sockaddr& GenearlAddress()const { return *(sockaddr*)&mAddress; }
	sockaddr* GenearlAddressPtr()const { return (sockaddr*)&mAddress; }
	void SetGeneralAddress(const sockaddr& inNewGeneralAddress) { mAddress = *(sockaddr_in*)(&inNewGeneralAddress); }

	unsigned short Port() const { return mAddress.sin_port; }
	unsigned int Address() const { return mAddress.sin_addr.s_addr; }
	SocketAddressFamily AddressFamily() const { return (SocketAddressFamily)mAddress.sin_family; }
	void SetAddressFamily(SocketAddressFamily inNewAddressType) { mAddress.sin_family = (ushort)inNewAddressType; }
	void SetPortID(unsigned short inNewPortID) { mAddress.sin_port = inNewPortID; }
	void SetAddress(unsigned int inNewAddress) { mAddress.sin_addr.s_addr = inNewAddress; }
	void SetAddress(in_addr inNewAddress) { mAddress.sin_addr = inNewAddress; }
private:
	sockaddr_in mAddress;

};

MEDUSA_END;
