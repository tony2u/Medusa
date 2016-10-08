// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "DataSourceFactory.h"
#include "Core/Log/Log.h"
#include "TListDataSource.h"
MEDUSA_BEGIN;

DataSourceFactory::DataSourceFactory()
{

}

DataSourceFactory::~DataSourceFactory()
{
	
}

bool DataSourceFactory::Initialize()
{
	return true;
}

bool DataSourceFactory::Uninitialize()
{
	Clear();
	return true;
}




Share<WStringListDataSource> DataSourceFactory::CreateWStringList(const FileIdRef& fileId, const List<WHeapString>& strItems, bool isSingleLine /*= true*/, ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	Share<WStringListDataSource> result;
	if (shareType != ResourceShareType::None)
	{
		auto item= Find(fileId);
		result = item.CastPtr<WStringListDataSource>();
		RETURN_SELF_IF_NOT_NULL(result);
	}

	result = new WStringListDataSource(strItems,fileId);
	Add(result, shareType);
	return result;
}

Share<FileIdListDataSource> DataSourceFactory::CreateFileIdList(const FileIdRef& fileId, const List<FileId>& items, ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	Share<FileIdListDataSource> result;
	if (shareType != ResourceShareType::None)
	{
		auto item = Find(fileId);
		result = item.CastPtr<FileIdListDataSource>();
		RETURN_SELF_IF_NOT_NULL(result);
	}

	result = new FileIdListDataSource(items, fileId);
	Add(result, shareType);
	return result;
}


MEDUSA_END;

