// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "Graphics/State/IRenderState.h"
#include "Geometry/Rect2.h"

MEDUSA_BEGIN;

class RasterizerRenderState :public IRenderState
{
	MEDUSA_RTTI(RasterizerRenderState,IRenderState);

public:
	RasterizerRenderState();
	virtual ~RasterizerRenderState();
	virtual void Apply()const override;

	Share<RasterizerRenderState> Clone()const;
	virtual void CopyFrom(const IRenderState& other)override;

	virtual bool Equals(const IRenderState& state)const override;
	virtual RenderStateType Type()const override { return GetTypeIdStatic(); }
	static RenderStateType GetTypeIdStatic() { return RenderStateType::Rasterizer; }

	GraphicsFace CullMode() const { return mCullMode; }
	void SetCullMode(GraphicsFace val) { RETURN_IF_EQUAL(mCullMode, val); mCullMode = val; OnStateChanged(); }

	GraphicsFrontFace FrontFace() const { return mFrontFace; }
	void SetFrontFace(GraphicsFrontFace val) { RETURN_IF_EQUAL(mFrontFace, val); mFrontFace = val; OnStateChanged(); }

	bool IsEnabled() const { return mCullFaceEnabled; }
	void Enable(bool val) { RETURN_IF_EQUAL(mCullFaceEnabled, val); mCullFaceEnabled = val; OnStateChanged(); }

	GraphicsColorMask ColorMask() const { return mColorMask; }
	void SetColorMask(GraphicsColorMask val) { RETURN_IF_EQUAL(mColorMask, val); mColorMask = val; OnStateChanged(); }


	static Share<RasterizerRenderState> Current();
protected:
	bool mCullFaceEnabled;

	GraphicsFace mCullMode;	//default: back
	GraphicsFrontFace mFrontFace;	//default: CCW
	GraphicsColorMask mColorMask;
};


MEDUSA_END;