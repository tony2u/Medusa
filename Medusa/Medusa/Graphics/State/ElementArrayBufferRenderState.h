// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "Graphics/State/BaseBufferRenderState.h"

MEDUSA_BEGIN;

class ElementArrayBufferRenderState:public BaseBufferRenderState
{
	MEDUSA_RTTI(ElementArrayBufferRenderState,BaseBufferRenderState);
public:
	ElementArrayBufferRenderState(uint buffer=0);
	virtual ~ElementArrayBufferRenderState();
	virtual void Apply()const override;

	virtual GraphicsBufferType BufferType() const  override { return GraphicsBufferType::Elements; }

	virtual RenderStateType Type()const override {return GetTypeIdStatic();}
	static RenderStateType GetTypeIdStatic(){return RenderStateType::ElementArrayBuffer;}
	Share<ElementArrayBufferRenderState> Clone()const;
	virtual void CopyFrom(const IRenderState& other)override;

	static Share<ElementArrayBufferRenderState> Current();
};


MEDUSA_END;