// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "Graphics/State/IRenderState.h"
#include "Graphics/GraphicsTypes.h"
#include "Geometry/Rect2.h"

MEDUSA_BEGIN;

class ProgramRenderState:public IRenderState
{
	MEDUSA_DECLARE_RTTI;
public:
	ProgramRenderState(uint program=0);
	virtual ~ProgramRenderState();
	virtual void Apply()const override;

	virtual ProgramRenderState* Clone()const override;
	virtual void CopyFrom(const IRenderState& other)override;

	virtual bool Equals(const IRenderState& state)const override;
	virtual RenderStateType Type()const override {return GetTypeIdStatic();}
	static RenderStateType GetTypeIdStatic(){return RenderStateType::Program;}

	uint Program() const { return mProgram; }
	void SetProgram(uint val) {RETURN_IF_EQUAL(mProgram, val); mProgram = val; OnStateChanged();}

	static ProgramRenderState* Current();
protected:
	uint mProgram;
};


MEDUSA_END;