// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/String/StringRef.h"

MEDUSA_BEGIN;

namespace Socket
{
	class HostInfo
	{
	public:
		HostInfo(hostent* inHostent=nullptr):mHostent(inHostent){}

		bool IsValid()const{return mHostent!=nullptr;}

		static HostInfo GetHost(StringRef inHostName)
		{
			hostent* result=gethostbyname(inHostName.c_str());
			return HostInfo(result);
		}
		static HostInfo GetHost(StringRef inAddress,int inAddressLength,int inAddressType)
		{
			hostent* result=gethostbyaddr(inAddress.c_str(),inAddressLength,inAddressType);
			return HostInfo(result);
		}

	public:
		hostent* Hostent() { return mHostent; }

		StringRef HostName()const  {return mHostent->h_name;}
		void SetHostName(StringRef inNewHostName) { mHostent->h_name=(char*)inNewHostName.c_str(); }

		char** HostAliases()const  {return mHostent->h_aliases;}
		void SetHostAlias(char** inNewHostAlias) { mHostent->h_aliases=inNewHostAlias; }

		short HostAddressType()const  { return mHostent->h_addrtype; }
		void SetHostAddressType(short val) { mHostent->h_addrtype=val; }

		short HostAddressSize()const  { return mHostent->h_length; }
		void SetHostAddressSize(short inNewHostAddressSize) { mHostent->h_length = inNewHostAddressSize; }

		char** HostAddressList()const  {return mHostent->h_addr_list;}
		void SetHostAddressList(char** inHostAddressList) { mHostent->h_addr_list=inHostAddressList; }

		char* FirstHostAddress()const{return mHostent->h_addr_list[0];}
		void SetFirstHostAddress(char* inNewHostAddress) { mHostent->h_addr_list[0]=inNewHostAddress; }
	private:
		hostent* mHostent;
	};
}

MEDUSA_END;
