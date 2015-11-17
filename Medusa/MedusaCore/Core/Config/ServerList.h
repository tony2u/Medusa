// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Siren/SirenHeader.h"

//SIREN_HEADER_INCLUDE_BEGIN
#include "Core/Config/ServerListItem.h"
//SIREN_HEADER_INCLUDE_END
#include "Core/Pattern/Singleton.h"
#include "Core/Coder/CoderType.h"
#include "Core/Siren/ISirenConfig.h"
MEDUSA_BEGIN;

class ServerList :public ISirenConfig<ServerList>
{
	friend class Singleton<ServerList>;
public:
	struct Schema;
	ServerList();
	~ServerList();

//SIREN_HEADER_METHOD_BEGIN
public:
	SIREN_METHOD_DICTIONARY(uint, ServerListItem, Items);
//SIREN_HEADER_METHOD_END

	virtual void Unload();

	const ServerListItem* GetServerListItem(uint id)const;
	const ServerListItem* GetFirstServerListItem()const;

	uintp GetServerCount()const { return mItems.Count(); }
	void UpdateMessageServer(const ServerConfig& serverConfig, uint serverListId, uint retryTimes, uint retryInternal, uint messageVersion, CoderType sendCoderType, CoderType receiveCoderType, const MemoryByteData& encryptKey)const;

	void InitializeMessageServer(const ServerConfig& serverConfig,uint retryTimes, uint retryInternal, uint messageVersion, CoderType sendCoderType, CoderType receiveCoderType, const MemoryByteData& encryptKey)const;

	int GetServerIdWithUsage(uint serverListId, ServerUsageType usageType)const;
//SIREN_HEADER_FIELD_BEGIN
protected:
	Dictionary<uint, ServerListItem> mItems;
//SIREN_HEADER_FIELD_END
};

//SIREN_HEADER_SCHEMA_BEGIN
struct ServerList::Schema
{
	SIREN_PROPERTY_DICTIONARY(0, 0, Required, ServerList, uint, ServerListItem, mItems);
	SIREN_PROPERTIES_1(void,ServerList);
};//SIREN_HEADER_SCHEMA_END

MEDUSA_END;