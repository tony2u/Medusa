// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Pattern/ISharable.h"
#include "Core/Pattern/IInitializable.h"
#include "Core/IO/FileId.h"
#include "Resource/ResourceType.h"

MEDUSA_BEGIN;


class IResource :public ISharableThreadSafe, public IInitializable
{
public:
	IResource(const FileIdRef& fileId);
	virtual ~IResource(void) {}
	virtual ResourceType Type()const = 0;

	StringRef Name() const { return mFileId.Name; }
	void SetName(const StringRef& name) { mFileId.Name = name; }
	bool HasName()const { return !mFileId.Name.IsEmpty(); }
	FileIdRef GetFileId()const { return mFileId.ToRef(); }
	uint Id() const { return mId; }

	virtual INode* Instantiate(NodeInstantiateInfo* instantiateInfo = nullptr)const { return nullptr; }
protected:
	FileId mFileId;
	uint mId;
};
MEDUSA_END;