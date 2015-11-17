// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "Graphics/State/IRenderState.h"
#include "Graphics/GraphicsFuncType.h"
#include "Graphics/GraphicsStencilOperation.h"
MEDUSA_BEGIN;

class DepthStencilRenderState:public IRenderState
{
	MEDUSA_DECLARE_RTTI;


public:
	DepthStencilRenderState();
	virtual ~DepthStencilRenderState();
	virtual void Apply()const override;
	virtual DepthStencilRenderState* Clone()const override;
	virtual bool Equals(const IRenderState& state)const override;
	virtual RenderStateType Type()const override {return GetTypeIdStatic();}
	static RenderStateType GetTypeIdStatic(){return RenderStateType::DepthStencil;}

	bool IsDepthTestEnabled() const { return mDepthTestEnabled; }
	void EnableDepthTest(bool val) { RETURN_IF_EQUAL(mDepthTestEnabled, val); mDepthTestEnabled = val; OnStateChanged(); }
	bool IsDepthWriteEnabled() const { return mDepthWritable; }
	void EnableDepthWrite(bool val) { RETURN_IF_EQUAL(mDepthWritable, val); mDepthWritable = val; OnStateChanged();}
	GraphicsFuncType DepthFunc() const { return mDepthFunc; }
	void SetDepthFunc(GraphicsFuncType val) {
		RETURN_IF_EQUAL(mDepthFunc, val); mDepthFunc = val; OnStateChanged();
	}
	float DepthClearValue() const { return mDepthClearValue; }
	void SetDepthClearValue(float val) {
		RETURN_IF_EQUAL(mDepthClearValue, val); mDepthClearValue = val; OnStateChanged();
	}

	bool IsStencilTestEnabled() const { return mStencilTestEnabled; }
	void EnableStencilTest(bool val) {
		RETURN_IF_EQUAL(mStencilTestEnabled, val); mStencilTestEnabled = val; OnStateChanged();
	}
	int StencilClearValue() const { return mStencilClearValue; }
	void SetStencilClearValue(int val) {
		RETURN_IF_EQUAL(mStencilClearValue, val); mStencilClearValue = val; OnStateChanged();
	}

	GraphicsStencilOperation FrontStencilFailOp() const { return mFrontStencilFailOp; }
	void SetFrontStencilFailOp(GraphicsStencilOperation val) {
		RETURN_IF_EQUAL(mFrontStencilFailOp, val); mFrontStencilFailOp = val; OnStateChanged();
	}
	GraphicsStencilOperation FrontStencilDepthFailOp() const { return mFrontStencilDepthFailOp; }
	void SetFrontStencilDepthFailOp(GraphicsStencilOperation val) {
		RETURN_IF_EQUAL(mFrontStencilDepthFailOp, val); mFrontStencilDepthFailOp = val; OnStateChanged();
	}
	GraphicsStencilOperation FrontStencilPassOp() const { return mFrontStencilPassOp; }
	void SetFrontStencilPassOp(GraphicsStencilOperation val) {
		RETURN_IF_EQUAL(mFrontStencilPassOp, val); mFrontStencilPassOp = val; OnStateChanged();
	}
	GraphicsFuncType FrontStencilFunc() const { return mFrontStencilFunc; }
	void SetFrontStencilFunc(GraphicsFuncType val) {
		RETURN_IF_EQUAL(mFrontStencilFunc, val); mFrontStencilFunc = val; OnStateChanged();
	}
	int FrontRefValue() const { return mFrontRefValue; }
	void SetFrontRefValue(int val) {
		RETURN_IF_EQUAL(mFrontRefValue, val); mFrontRefValue = val; OnStateChanged();
	}
	int FrontReadMask() const { return mFrontReadMask; }
	void SetFrontReadMask(int val) {
		RETURN_IF_EQUAL(mFrontReadMask, val); mFrontReadMask = val; OnStateChanged();
	}
	int FrontWriteMask() const { return mFrontWriteMask; }
	void SetFrontWriteMask(int val) {
		RETURN_IF_EQUAL(mFrontWriteMask, val); mFrontWriteMask = val; OnStateChanged();
	}

	void SetFrontStencilFunc(GraphicsFuncType func, int refVal, int readMask) {
		RETURN_IF_EQUAL(mFrontStencilFunc, func); RETURN_IF_EQUAL(mFrontRefValue, refVal); RETURN_IF_EQUAL(mFrontReadMask, readMask); mFrontStencilFunc = func; mFrontRefValue = refVal; mFrontReadMask = readMask; OnStateChanged();
	}
	void SetFrontStencilOperation(GraphicsStencilOperation testFail, GraphicsStencilOperation testPassDepthFail, GraphicsStencilOperation testPassDepthPass) {
		RETURN_IF_EQUAL(mFrontStencilFailOp, testFail); RETURN_IF_EQUAL(mFrontStencilDepthFailOp, testPassDepthFail); RETURN_IF_EQUAL(mFrontStencilPassOp, testPassDepthPass); mFrontStencilFailOp = testFail; mFrontStencilDepthFailOp = testPassDepthFail; mFrontStencilPassOp = testPassDepthPass; OnStateChanged();
	}


	GraphicsStencilOperation BackStencilFailOp() const { return mBackStencilFailOp; }
	void SetBackStencilFailOp(GraphicsStencilOperation val) {
		RETURN_IF_EQUAL(mBackStencilFailOp, val); mBackStencilFailOp = val; OnStateChanged();
	}
	GraphicsStencilOperation BackStencilDepthFailOp() const { return mBackStencilDepthFailOp; }
	void SetBackStencilDepthFailOp(GraphicsStencilOperation val) {
		RETURN_IF_EQUAL(mBackStencilDepthFailOp, val); mBackStencilDepthFailOp = val; OnStateChanged();
	}
	GraphicsStencilOperation BackStencilPassOp() const { return mBackStencilPassOp; }
	void SetBackStencilPassOp(GraphicsStencilOperation val) {
		RETURN_IF_EQUAL(mBackStencilPassOp, val); mBackStencilPassOp = val; OnStateChanged();
	}
	GraphicsFuncType BackStencilFunc() const { return mBackStencilFunc; }
	void SetBackStencilFunc(GraphicsFuncType val) {
		RETURN_IF_EQUAL(mBackStencilFunc, val); mBackStencilFunc = val; OnStateChanged();
	}
	int BackRefValue() const { return mBackRefValue; }
	void SetBackRefValue(int val) {
		RETURN_IF_EQUAL(mBackRefValue, val); mBackRefValue = val; OnStateChanged();
	}
	int BackReadMask() const { return mBackReadMask; }
	void SetBackReadMask(int val) {
		RETURN_IF_EQUAL(mBackReadMask, val); mBackReadMask = val; OnStateChanged();
	}
	int BackWriteMask() const { return mBackWriteMask; }
	void SetBackWriteMask(int val) {
		RETURN_IF_EQUAL(mBackWriteMask, val); mBackWriteMask = val; OnStateChanged();
	}

	void SetBackStencilFunc(GraphicsFuncType func, int refVal, int readMask) {
		RETURN_IF_EQUAL(mBackStencilFunc, func); RETURN_IF_EQUAL(mBackRefValue, refVal); RETURN_IF_EQUAL(mBackReadMask, readMask); mBackStencilFunc = func; mBackRefValue = refVal; mBackReadMask = readMask; OnStateChanged();
	}
	void SetBackStencilOperation(GraphicsStencilOperation testFail, GraphicsStencilOperation testPassDepthFail, GraphicsStencilOperation testPassDepthPass) {
		RETURN_IF_EQUAL(mBackStencilFailOp, testFail); RETURN_IF_EQUAL(mBackStencilDepthFailOp, testPassDepthFail); RETURN_IF_EQUAL(mBackStencilPassOp, testPassDepthPass); mBackStencilFailOp = testFail; mBackStencilDepthFailOp = testPassDepthFail; mBackStencilPassOp = testPassDepthPass; OnStateChanged();
	}

	void SetStencilFunc(GraphicsFuncType func,int refVal,int readMask){SetFrontStencilFunc(func,refVal,readMask);SetBackStencilFunc(func,refVal,readMask);}
	void SetStencilOperation(GraphicsStencilOperation testFail,GraphicsStencilOperation testPassDepthFail,GraphicsStencilOperation testPassDepthPass){SetFrontStencilOperation(testFail,testPassDepthFail,testPassDepthPass);SetBackStencilOperation(testFail,testPassDepthFail,testPassDepthPass);}


	static DepthStencilRenderState* Current();

protected:
	bool mDepthTestEnabled=false;
	bool mDepthWritable = false;
	GraphicsFuncType mDepthFunc = GraphicsFuncType::GreaterOrEqual;
	float mDepthClearValue=1.f;
	
	bool mStencilTestEnabled = false;
	int mStencilClearValue=0;

	GraphicsStencilOperation mFrontStencilFailOp= GraphicsStencilOperation::Increase;
	GraphicsStencilOperation  mFrontStencilDepthFailOp= GraphicsStencilOperation::Increase;
	GraphicsStencilOperation  mFrontStencilPassOp= GraphicsStencilOperation::Increase;
	GraphicsFuncType mFrontStencilFunc = GraphicsFuncType::GreaterOrEqual;
	int mFrontRefValue=0;
	int mFrontReadMask=0;
	int mFrontWriteMask=0;
	

	GraphicsStencilOperation mBackStencilFailOp= GraphicsStencilOperation::Increase;
	GraphicsStencilOperation  mBackStencilDepthFailOp= GraphicsStencilOperation::Increase;
	GraphicsStencilOperation  mBackStencilPassOp= GraphicsStencilOperation::Increase;
	GraphicsFuncType mBackStencilFunc = GraphicsFuncType::GreaterOrEqual;
	int mBackRefValue=0;
	int mBackReadMask=0;
	int mBackWriteMask=0;


	
};


MEDUSA_END;