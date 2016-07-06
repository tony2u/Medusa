// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "SocketPeer.h"
#include "Core/Log/Log.h"
#include "Core/Event/Service/ServiceDefines.h"   

MEDUSA_BEGIN;

SocketPeer::SocketPeer(const StringRef& host/*=StringRef::Empty*/, ushort port/*=0*/)
	:mHost(host), mPort(port)
{

}

SocketPeer::~SocketPeer(void)
{
}


void SocketPeer::SetProperties(const StringPropertySet& val)
{
	mProperties = val;
	OnPropertiesChanged();
}

void SocketPeer::AddAttribute(const StringRef& name, const StringRef& val)
{
	mProperties.Set(name, val);
	OnPropertiesChanged();
}

bool SocketPeer::LoopForever()
{
	return mLoop.LoopForever();
}

bool SocketPeer::LoopOnce()
{
	return mLoop.LoopOnce();
}



void SocketPeer::OnPropertiesChanged()
{
	StringRef host = mProperties.Get(ServicePropertyNames::Host);
	if (!host.IsEmpty())
	{
		mHost = host;
	}
	ushort port = (uint16_t)mProperties.GetOptionalT(ServicePropertyNames::Port, 0);
	mPort = port;

	StringRef pollerName = mProperties.Get(ServicePropertyNames::Poller);
	if (!pollerName.IsEmpty())
	{
		mPollerName = pollerName;
	}
	StringRef connectioName = mProperties.Get(ServicePropertyNames::Connection);
	if (!connectioName.IsEmpty())
	{
		mConnectionName = connectioName;
	}


}

MEDUSA_END;