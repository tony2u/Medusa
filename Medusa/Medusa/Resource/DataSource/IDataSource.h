// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Resource/IResource.h"
#include "Core/Pattern/Event.h"

MEDUSA_BEGIN;

class IDataSource:public IResource
{
public:
	IDataSource(const FileIdRef& fileId = FileIdRef::Empty);
	virtual ~IDataSource(void);

	virtual ResourceType Type()const { return ResourceType::DataSource; }
	static ResourceType ClassGetResourceType() { return ResourceType::DataSource; }

	Event<void()> OnTotalChanged;
};

MEDUSA_END;
