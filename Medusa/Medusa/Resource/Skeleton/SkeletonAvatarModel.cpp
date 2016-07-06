// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "SkeletonAvatarModel.h"
#include "Resource/Skeleton/Attachment/ISkeletonAttachmentModel.h"

MEDUSA_BEGIN;


SkeletonAvatarModel::SkeletonAvatarModel(const StringRef& name)
	:mName(name)
{

}


SkeletonAvatarModel::~SkeletonAvatarModel(void)
{
	SAFE_DELETE_DICTIONARY_VALUE(mSlotAttachmentDict);
}

void SkeletonAvatarModel::AddSlotAttachment(SkeletonSlotModel* slot, ISkeletonAttachmentModel* attchement)
{
	List<ISkeletonAttachmentModel*>* attchements=mSlotAttachmentDict.GetOptional(slot,nullptr);
	if (attchements==nullptr)
	{
		attchements = new List<ISkeletonAttachmentModel*>();
		mSlotAttachmentDict.Add(slot, attchements);
	}

	attchements->Add(attchement);

}

ISkeletonAttachmentModel* SkeletonAvatarModel::FindAttachment(SkeletonSlotModel* slot, const StringRef& attchementName) const
{
	List<ISkeletonAttachmentModel*>* attchements = mSlotAttachmentDict.GetOptional(slot, nullptr);
	RETURN_NULL_IF_NULL(attchements);

	for(auto attachemnt: *attchements)
	{
		if (attachemnt->Name()==attchementName)
		{
			return attachemnt;
		}
	}

	return nullptr;
}

ISkeletonAttachmentModel* SkeletonAvatarModel::FindAttachment(const StringRef& attchementName) const
{
	for(auto i:mSlotAttachmentDict)
	{
		List<ISkeletonAttachmentModel*>* attchements = i.Value;
		if (attchements!=nullptr)
		{
			for(auto attachemnt: *attchements)
			{
				if (attachemnt->Name() == attchementName)
				{
					return attachemnt;
				}
			}

		}
	}

	return nullptr;
}



MEDUSA_END;