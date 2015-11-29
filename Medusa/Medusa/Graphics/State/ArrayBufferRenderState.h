// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "Graphics/State/BaseBufferRenderState.h"

MEDUSA_BEGIN;

class ArrayBufferRenderState:public BaseBufferRenderState
{
	MEDUSA_DECLARE_RTTI;
public:
	ArrayBufferRenderState(uint buffer=0);
	virtual ~ArrayBufferRenderState();
	virtual void Apply()const override;

	virtual GraphicsBufferType BufferType() const override { return GraphicsBufferType::Array; }

	virtual RenderStateType Type()const override {return GetTypeIdStatic();}
	
	static RenderStateType GetTypeIdStatic(){return RenderStateType::Array;}

	virtual ArrayBufferRenderState* Clone()const override;
	virtual void CopyFrom(const IRenderState& other)override;

	static ArrayBufferRenderState* Current();
};


MEDUSA_END;