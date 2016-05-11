// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "Graphics/State/IRenderState.h"
#include "Geometry/Color4.h"



MEDUSA_BEGIN;

/*
DestColor*DestFactor (blendEquation) SrcColor*SrcFactor

*/

class BlendRenderState:public IRenderState
{
	MEDUSA_DECLARE_RTTI;


public:
	BlendRenderState(bool blendEnabled=false);
	virtual ~BlendRenderState();

	virtual void Apply()const override;

	virtual BlendRenderState* Clone()const override;
	virtual void CopyFrom(const IRenderState& other)override;

	virtual bool Equals(const IRenderState& state)const override;
	virtual RenderStateType Type()const override {return GetTypeIdStatic();}
	static RenderStateType GetTypeIdStatic(){return RenderStateType::Blend;}


	bool IsEnabled() const { return mEnabled; }
	bool Enable(bool val);
	GraphicsBlendSrcFunc SrcRGBFunc() const { return mSrcRGBFunc; }
	bool SetSrcRGBFunc(GraphicsBlendSrcFunc val);
	GraphicsBlendSrcFunc SrcAlphaFunc() const { return mSrcAlphaFunc; }
	bool SetSrcAlphaFunc(GraphicsBlendSrcFunc val);
	GraphicsBlendDestFunc DestRGBFunc() const { return mDestRGBFunc; }
	bool SetDestRGBFunc(GraphicsBlendDestFunc val);
	GraphicsBlendDestFunc DestAlphaFunc() const { return mDestAlphaFunc; }
	bool SetDestAlphaFunc(GraphicsBlendDestFunc val);
	GraphicsBlendEquation BlendRGBEquation() const { return mBlendRGBEquation; }
	bool SetBlendRGBEquation(GraphicsBlendEquation val);
	GraphicsBlendEquation BlendAlphaEquation() const { return mBlendAlphaEquation; }
	bool SetBlendAlphaEquation(GraphicsBlendEquation val);

	const Color4F& BlendColor() const { return mBlendColor; }
	bool SetBlendColor(const Color4F& val);

	bool SetBlendFunc(GraphicsBlendSrcFunc srcFunc, GraphicsBlendDestFunc destFunc);
	static BlendRenderState* Current();	//OpenGL default blend src is one-zero, which is not valid for blend
	static BlendRenderState* Default();
	virtual intp HashCode() const override;

protected:
	bool mEnabled;
	GraphicsBlendSrcFunc mSrcRGBFunc;
	GraphicsBlendSrcFunc mSrcAlphaFunc;	
	GraphicsBlendDestFunc mDestRGBFunc;
	GraphicsBlendDestFunc mDestAlphaFunc;
	GraphicsBlendEquation mBlendRGBEquation;
	GraphicsBlendEquation mBlendAlphaEquation;
	Color4F mBlendColor;
	
};


MEDUSA_END;