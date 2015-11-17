// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/String/StringRef.h"

MEDUSA_BEGIN;

namespace Socket
{
	class ProtocolInfo
	{
	public:
		ProtocolInfo(protoent* inProtoent=nullptr):mProtoent(inProtoent){}
		bool IsValid()const{return mProtoent!=nullptr;}

		static ProtocolInfo GetProtocol(StringRef inProtocolName)
		{
			protoent* result=getprotobyname(inProtocolName.c_str());
			return ProtocolInfo(result);

		}
		static ProtocolInfo GetProtocol(SocketProtocolType::SocketProtocolType_t protocol)
		{
			protoent* result=getprotobynumber(protocol);
			return ProtocolInfo(result);
		}
	public:
		protoent* Protoent()  { return mProtoent; }

		StringRef ProtocolName() const { return mProtoent->p_name; }
		void SetProtocolName(StringRef inNewProtocolName) { mProtoent->p_name = (char*)inNewProtocolName.c_str(); }

		char** Aliases() const { return mProtoent->p_aliases; }
		void SetAliases(char** inNewAliases) { mProtoent->p_aliases = inNewAliases; }

		short ProtocolId() const { return mProtoent->p_proto; }
		void SetProtocolId(short inNewProtocolID) { mProtoent->p_proto = inNewProtocolID; }
	private:
		protoent* mProtoent;	
	};

}

MEDUSA_END;
