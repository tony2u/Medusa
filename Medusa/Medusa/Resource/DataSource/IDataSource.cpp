// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "IDataSource.h"

MEDUSA_BEGIN;


IDataSource::IDataSource(const FileIdRef& fileId /*= FileIdRef::Empty*/)
	:IResource(fileId)
{
	
}

IDataSource::~IDataSource( void )
{

}

MEDUSA_END;