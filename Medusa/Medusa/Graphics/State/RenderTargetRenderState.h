// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "Graphics/State/IRenderState.h"
#include "Graphics/GraphicsTypes.h"
#include "Geometry/Rect2.h"
#include "Geometry/Color4.h"

MEDUSA_BEGIN;

class RenderTargetRenderState:public IRenderState
{
	MEDUSA_DECLARE_RTTI;
public:
	RenderTargetRenderState(uint frameBuffer,const Rect2I& viewPort,const Color4F& clearColor,bool isDefault=false);
	RenderTargetRenderState();
	virtual ~RenderTargetRenderState();
	virtual void Apply()const override;

	virtual RenderTargetRenderState* Clone()const override;
	virtual void CopyFrom(const IRenderState& other)override;

	virtual bool Equals(const IRenderState& state)const override;
	virtual RenderStateType Type()const override {return GetTypeIdStatic();}
	static RenderStateType GetTypeIdStatic(){return RenderStateType::RenderTarget;}

	uint FrameBuffer() const { return mFrameBuffer; }
	void SetFrameBuffer(uint val) {RETURN_IF_EQUAL(mFrameBuffer, val); mFrameBuffer = val; OnStateChanged();}

	const Rect2I& ViewPort() const { return mViewPort; }
	void SetViewPort(const Rect2I& val) {RETURN_IF_EQUAL(mViewPort, val); mViewPort = val; OnStateChanged();}

	const Color4F& ClearColor() const { return mClearColor; }
	void SetClearColor(const Color4F& val) {RETURN_IF_EQUAL(mClearColor, val); mClearColor = val; OnStateChanged();}

	static RenderTargetRenderState* Current(bool isDefault=false);
protected:
	uint mFrameBuffer;
	Rect2I mViewPort;
	Color4F mClearColor;
	bool mIsDefault;
};


MEDUSA_END;