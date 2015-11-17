// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/String/HeapString.h"
#include "Core/Collection/Dictionary.h"
#include "Core/Collection/List.h"


MEDUSA_BEGIN;

class SkeletonAvatarModel
{
public:
	SkeletonAvatarModel(const StringRef& name);
	~SkeletonAvatarModel();

	StringRef Name() const { return mName; }

	void AddSlotAttachment(SkeletonSlotModel* slot, ISkeletonAttachmentModel* attchement);
	ISkeletonAttachmentModel* FindAttachment(SkeletonSlotModel* slot, const StringRef& attchementName)const;
	ISkeletonAttachmentModel* FindAttachment(const StringRef& attchementName)const;


protected:
	HeapString mName;
	Dictionary<SkeletonSlotModel*, List<ISkeletonAttachmentModel*>* > mSlotAttachmentDict;

	
};

MEDUSA_END;
