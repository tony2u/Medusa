// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "MedusaCorePreDeclares.h"




MEDUSA_BEGIN;
namespace Socket
{
	class ServiceInfo
	{
	public:
		ServiceInfo(servent* inServent=nullptr):mServent(inServent){}

		static ServiceInfo GetService(StringRef inServiceName,StringRef inProtocolName)
		{
			servent* result=getservbyname(inServiceName.c_str(),inProtocolName.c_str());
			return ServiceInfo(result);

		}
		static ServiceInfo GetService(int inPortID,StringRef inProtocolName)
		{
			servent* result=getservbyport(inPortID,inProtocolName.c_str());
			return ServiceInfo(result);
		}
	public:
		bool IsValid()const{return mServent!=nullptr;}

		StringRef ServiceName() const { return  mServent->s_name; }
		void SetServiceName(StringRef inNewServiceName) { mServent->s_name = (char*)inNewServiceName.c_str(); }

		char** ServiceAliases() const { return  mServent->s_aliases; }
		void SetServiceAliases(char** inNewServiceAliases) { mServent->s_aliases = inNewServiceAliases; }

		short Port() const { return  mServent->s_port; }
		void SetPortID(short inNewPortID) { mServent->s_port = inNewPortID; }

		StringRef ProtocolName() const { return mServent->s_proto; }
		void SetProtocolName(StringRef inNewProtocolName) { mServent->s_proto =(char*) inNewProtocolName.c_str(); }
	private:
		servent* mServent;
	};

}

MEDUSA_END;
