// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Pattern/IInitializable.h"
#include "Core/String/HeapString.h"
#include "SkeletonAttachmentType.h"

MEDUSA_BEGIN;


class ISkeletonAttachmentModel :public IInitializable
{
public:
	ISkeletonAttachmentModel(const StringRef& name);
	virtual ~ISkeletonAttachmentModel();
	virtual SkeletonAttachmentType Type()const = 0;

	StringRef Name() const { return mName; }

	virtual bool Initialize() { return true; }
	virtual IMesh* GetMesh(){ return nullptr; }

protected:
	HeapString mName;

};

MEDUSA_END;
