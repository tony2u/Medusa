// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Event/Loop/EventLoop.h"
#include "Core/Pattern/Property/StringPropertySet.h"

MEDUSA_BEGIN;


class SocketPeer
{
public:
	SocketPeer(const StringRef& host=StringRef::Empty, ushort port=0);
	virtual ~SocketPeer(void);

	virtual bool IsClient()const = 0;
	const StringPropertySet& Properties() const { return mProperties; }
	void SetProperties(const StringPropertySet& val);
	void AddAttribute(const StringRef& name, const StringRef& val);

	EventLoop& MutableLoop() { return mLoop; }

	virtual bool Start() { return true; }
	virtual bool Stop() { return true; }
	bool LoopForever();
	bool LoopOnce();


	StringRef Host() const { return mHost; }
	void SetHost(const StringRef& val) { mHost = val; }

	ushort Port() const { return mPort; }
	void SetPort(ushort val) { mPort = val; }

	StringRef PollerName() const { return mPollerName; }
	void SetPollerName(const StringRef& val) { mPollerName = val; }

	template<typename T>
	void SetPollerType()
	{
		mPollerName = T::ClassNameStatic();
	}

	StringRef ConnectionName() const { return mConnectionName; }
	void SetConnectionName(StringRef val) { mConnectionName = val; }

	template<typename T>
	void SetConnectionType()
	{
		mConnectionName = T::ClassNameStatic();
	}

	virtual SocketChannel* Channel() = 0;
public:
	

protected:
	virtual void OnPropertiesChanged();

protected:
	StringPropertySet mProperties;
	EventLoop mLoop;
	HeapString mHost;
	ushort mPort = 0;
	HeapString mPollerName;
	HeapString mConnectionName;

	
};

MEDUSA_END;
