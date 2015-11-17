// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "Graphics/State/IRenderState.h"
#include "Graphics/GraphicsTypes.h"
#include "Core/Collection/Dictionary.h"

MEDUSA_BEGIN;

class FeatureRenderState:public IRenderState
{
	MEDUSA_DECLARE_RTTI;

public:
	FeatureRenderState();
	virtual ~FeatureRenderState();
	virtual void Apply()const override;
	virtual FeatureRenderState* Clone()const override;
	virtual bool Equals(const IRenderState& state)const override;
	virtual RenderStateType Type()const override {return GetTypeIdStatic();}
	static RenderStateType GetTypeIdStatic(){return RenderStateType::Feature;}

	bool IsEnabled(GraphicsFeatures feature)const{return mFeatures[(uint)feature];}
	void Enable(GraphicsFeatures feature,bool val);

	static FeatureRenderState* Current();

protected:
	Dictionary<uint,bool> mFeatures;
};


MEDUSA_END;