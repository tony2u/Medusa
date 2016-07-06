// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "Graphics/State/IRenderState.h"
#include "Graphics/GraphicsTypes.h"
#include "Geometry/Rect2.h"

MEDUSA_BEGIN;

class BaseBufferRenderState:public IRenderState
{
	MEDUSA_RTTI(BaseBufferRenderState,IRenderState);
public:
	BaseBufferRenderState(uint buffer=0);
	virtual ~BaseBufferRenderState();
	virtual bool Equals(const IRenderState& state)const override;

	uint Buffer() const { return mBuffer; }
	void SetBuffer(uint val) { RETURN_IF_EQUAL(mBuffer, val); mBuffer = val; OnStateChanged(); }

	virtual GraphicsBufferType BufferType() const=0;
	virtual intp HashCode() const override { return mBuffer; }

protected:
	uint mBuffer;
	
};


MEDUSA_END;