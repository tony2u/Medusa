// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaPreDeclares.h"
#include "IResourceManageable.h"
#include "ResourceType.h"

MEDUSA_BEGIN;

template<typename TKey,typename TValue>
class IResourceFactory :public IResourceManageable
{
public:
	virtual bool Remove(const TKey& fileId){return false;}
	virtual TValue Find(const TKey& fileId)const{return nullptr;}
	virtual bool Add(TValue val, ResourceShareType shareType = ResourceShareType::Share) { return false; }


};

MEDUSA_END;