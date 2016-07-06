// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/IO/IFileLoadSavable.h"
#include "ApplePropertyListNode.h"

MEDUSA_BEGIN;

class ApplePropertyListReader:public IFileLoadSavable
{
public:
	ApplePropertyListReader();
	~ApplePropertyListReader(void);

	static uint CheckFormat(StringRef path);
	const ApplePropertyListNode& Root() const { return mRoot; }

public:
	virtual bool LoadFromData(const FileIdRef& fileId, const MemoryData& data, uint format = 0)override;
	virtual void Unload()override;
protected:
	bool ParseFromXml(const FileIdRef& fileId, const MemoryData& data);
	bool ParseFromBinary(const FileIdRef& fileId, const MemoryData& data);

protected:
	virtual uint OnCheckFormat(StringRef path)const override;
protected:
	ApplePropertyListNode mRoot;
};

MEDUSA_END;
