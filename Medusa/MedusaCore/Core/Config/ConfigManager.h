// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Collection/List.h"
#include "Core/Pattern/IInitializable.h"

MEDUSA_BEGIN;


class ConfigManager :public IInitializable
{
public:
	ConfigManager();
	~ConfigManager(void);

	virtual bool Uninitialize() override;

	void Load(IFileLoadable* item);
	void Clear();

	template<typename T>
	T* Load(const FileIdRef& fileId, uint format = (uint)-1)
	{
		T* item = new T();
		if (!item->LoadFromFileSystem(fileId, format))
		{
			delete item;
			return nullptr;
		}
		mItems.Add(item);
		return item;
	}
protected:
	List<IFileLoadable*> mItems;
};

MEDUSA_END;
