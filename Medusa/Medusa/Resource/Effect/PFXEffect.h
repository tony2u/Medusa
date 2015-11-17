// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "Resource/Effect/IEffect.h"
#include "Core/Memory/MemoryData.h"
MEDUSA_BEGIN;

class PFXEffect:public IEffect
{
public:
	PFXEffect(const FileIdRef& fileId);
	virtual ~PFXEffect();
	
	static PFXEffect* CreateFromFile(const FileIdRef& fileId);
	static PFXEffect* CreateFromData(const FileIdRef& fileId,MemoryByteData data);
	static PFXEffect* CreateFromLines(const FileIdRef& fileId,const List<HeapString>& lines);
};


MEDUSA_END;