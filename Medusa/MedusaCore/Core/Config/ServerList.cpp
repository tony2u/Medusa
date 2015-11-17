// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"

//SIREN_BODY_INCLUDE_BEGIN
#include "ServerList.h"
//SIREN_BODY_INCLUDE_END
#include "Core/Log/Log.h"
#include "Core/IO/FileSystem.h"
#include "Core/Message/MessageDispatcher.h"
#include "Core/Config/ServerConfig.h"
MEDUSA_BEGIN;

ServerList::ServerList()
{
//SIREN_BODY_CONSTRUCT_BEGIN
//SIREN_BODY_CONSTRUCT_END
}

ServerList::~ServerList()
{
//SIREN_BODY_DESTRUCT_BEGIN
//SIREN_BODY_DESTRUCT_END
}


void ServerList::Unload()
{
	mItems.Clear();
}

const ServerListItem* ServerList::GetServerListItem(uint id)const
{
	return mItems.TryGetValue(id);
}


const ServerListItem* ServerList::GetFirstServerListItem() const
{
	if (mItems.Count() > 0)
	{
		return &(mItems.First()->Value);
	}
	else
	{
		Log::AssertFailed("Server list is empty!!");
		return nullptr;
	}
}

void ServerList::UpdateMessageServer(const ServerConfig& serverConfig, uint serverListId, uint retryTimes, uint retryInternal, uint messageVersion, CoderType sendCoderType, CoderType receiveCoderType, const MemoryByteData& encryptKey) const
{
	const ServerListItem* item = GetServerListItem(serverListId);
	if (item != nullptr)
	{
		MessageDispatcher::Instance().ClearUp();


		FOR_EACH_COLLECTION(i, item->Usages())
		{
			const ServerUsageItem& usageItem = *i;
			const ServerConfigItem* tempItem = serverConfig.GetServerConfigItem(usageItem.ServerId());
			if (tempItem != nullptr)
			{
				MessageDispatcher::Instance().AddMessageServer(tempItem->Type(), (uint)usageItem.Usage(), tempItem->Address(), (ushort)tempItem->Port(), retryTimes, retryInternal, messageVersion, sendCoderType, receiveCoderType, encryptKey);
			}
			else
			{
				Log::AssertFailedFormat("Cannot find server by id:{}", usageItem.ServerId());
			}
		}
	}
	else
	{
		Log::FormatError("Cannot find server list by id:{}", serverListId);
	}
}

void ServerList::InitializeMessageServer(const ServerConfig& serverConfig, uint retryTimes, uint retryInternal, uint messageVersion, CoderType sendCoderType, CoderType receiveCoderType, const MemoryByteData& encryptKey) const
{
	if (mItems.Count() > 0)
	{
		uint serverId = mItems.First()->Value.Id();
		UpdateMessageServer(serverConfig,serverId, retryTimes, retryInternal, messageVersion, sendCoderType, receiveCoderType, encryptKey);
	}

}

int ServerList::GetServerIdWithUsage(uint serverListId, ServerUsageType usageType) const
{
	const ServerListItem* item = GetServerListItem(serverListId);
	if (item != nullptr)
	{
		FOR_EACH_COLLECTION(i, item->Usages())
		{
			const ServerUsageItem& usageItem = *i;
			if (usageItem.Usage() == usageType)
			{
				return usageItem.ServerId();
			}
		}
	}
	return -1;
}

//SIREN_BODY_METADATA_BEGIN
SIREN_METADATA(ServerList, 10);
SIREN_PROPERTY_METADATA_STRUCT(0, ServerList, Items, 5);
//SIREN_BODY_METADATA_END

MEDUSA_END;