// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "Graphics/State/IRenderState.h"
#include "Graphics/GraphicsTypes.h"

MEDUSA_BEGIN;

class PixelStoreRenderState:public IRenderState
{
	MEDUSA_DECLARE_RTTI;

public:
	PixelStoreRenderState();
	virtual ~PixelStoreRenderState();
	virtual void Apply()const override;

	virtual PixelStoreRenderState* Clone()const override;
	virtual bool Equals(const IRenderState& state)const override;
	virtual RenderStateType Type()const override {return GetTypeIdStatic();}
	static RenderStateType GetTypeIdStatic(){return RenderStateType::PixelStore;}

	int PackAlignment() const { return mPackAlignment; }
	void SetPackAlignment(int val) { RETURN_IF_EQUAL(mPackAlignment, val); mPackAlignment = val; OnStateChanged(); }

	int UnpackAlignment() const { return mUnpackAlignment; }
	void SetUnpackAlignment(int val) {
		RETURN_IF_EQUAL(mUnpackAlignment, val); mUnpackAlignment = val; OnStateChanged();
	}

	static PixelStoreRenderState* Current();
protected:
	int  mPackAlignment;
	int  mUnpackAlignment;
};


MEDUSA_END;