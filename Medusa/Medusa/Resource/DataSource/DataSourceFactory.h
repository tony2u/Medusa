// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/String/StringRef.h"
#include "Core/Pattern/Singleton.h"
#include "Resource/BaseResourceFactory.h"
#include "Resource/DataSource/IDataSource.h"

MEDUSA_BEGIN;

class DataSourceFactory:public Singleton<DataSourceFactory>,public BaseResourceFactory<IDataSource>
{
	friend class Singleton<DataSourceFactory>;
public:
	DataSourceFactory();
	~DataSourceFactory();
public:
	virtual StringRef Name()const override { return "DataSourceFactory"; }

	virtual bool Initialize();
	virtual bool Uninitialize();

	Share<WStringListDataSource> CreateWStringList(const FileIdRef& fileId, const List<WHeapString>& strItems, bool isSingleLine = true, ResourceShareType shareType = ResourceShareType::Share);
	Share<FileIdListDataSource> CreateFileIdList(const FileIdRef& fileId, const List<FileId>& items,ResourceShareType shareType = ResourceShareType::Share);


};

MEDUSA_END;