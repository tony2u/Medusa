// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "IndexGraphicsBuffer.h"

MEDUSA_BEGIN;

#ifdef MEDUSA_GLES

void IndexGraphicsBuffer::AdjustData(size_t fromIndex, short delta)
{
	size_t count=this->mItems.Count();
    RETURN_IF_ZERO(count);

	FOR_EACH_SIZE_BEGIN_END(i,fromIndex,count-1)
	{
		this->mItems[i]+=delta;
	}
}


#else

void IndexGraphicsBuffer::AdjustData(size_t fromIndex, int delta)
{
	size_t count=this->mItems.Count();
	RETURN_IF_ZERO(count);

	FOR_EACH_SIZE_BEGIN_END(i,fromIndex,count-1)
	{
		this->mItems[i]+=delta;
	}
}

#endif

MEDUSA_END;