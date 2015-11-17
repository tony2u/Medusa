// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Graphics/State/FeatureRenderState.h"
#include "Graphics/Render/Render.h"
#include "Rendering/RenderingContext.h"
#include "Core/Collection/Linq.h"

MEDUSA_BEGIN;
FeatureRenderState::FeatureRenderState()
{
	
}

FeatureRenderState::~FeatureRenderState()
{

}

void FeatureRenderState::Apply()const
{
	IRender& render= Render::Instance();
	FOR_EACH_COLLECTION(i,mFeatures)
	{
		GraphicsFeatures feature=(GraphicsFeatures)i->Key;
		bool isEnabled=i->Value;
		render.EnableFeature(feature,isEnabled);
	}
}

FeatureRenderState* FeatureRenderState::Clone() const
{
	FeatureRenderState* state=new FeatureRenderState();
	FOR_EACH_COLLECTION(i,mFeatures)
	{
		GraphicsFeatures feature=(GraphicsFeatures)i->Key;
		bool isEnabled=i->Value;
		state->Enable(feature,isEnabled);
	}

	return state;
}

bool FeatureRenderState::Equals( const IRenderState& state ) const
{
	RETURN_FALSE_IF_FALSE(IRenderState::Equals(state));
	const FeatureRenderState& val=(const FeatureRenderState&)state;
	return Linq::IsEqual(mFeatures,val.mFeatures);
}

void FeatureRenderState::Enable(GraphicsFeatures feature, bool val)
{
	bool* origin = mFeatures.TryGetValue((uint)feature);
	if (origin!=NULL)
	{
		if (*origin==val)
		{
			return;
		}
		*origin = val;
		OnStateChanged();
	}
	else
	{
		mFeatures.Add((uint)feature, val);
	}

}

FeatureRenderState* FeatureRenderState::Current()
{
	IRender& render=Render::Instance();

	FeatureRenderState* state=new FeatureRenderState();
	state->Enable(GraphicsFeatures::Blend,render.IsFeatureEnabled(GraphicsFeatures::Blend));
	state->Enable(GraphicsFeatures::CullFace,render.IsFeatureEnabled(GraphicsFeatures::CullFace));
	state->Enable(GraphicsFeatures::DepthTest,render.IsFeatureEnabled(GraphicsFeatures::DepthTest));
	state->Enable(GraphicsFeatures::ScissorTest,render.IsFeatureEnabled(GraphicsFeatures::ScissorTest));
	state->Enable(GraphicsFeatures::StencilTest,render.IsFeatureEnabled(GraphicsFeatures::StencilTest));
	state->Enable(GraphicsFeatures::Dither,render.IsFeatureEnabled(GraphicsFeatures::Dither));
	state->Enable(GraphicsFeatures::PolygonOffsetFill,render.IsFeatureEnabled(GraphicsFeatures::PolygonOffsetFill));
	state->Enable(GraphicsFeatures::SampleAlphaToCoverage,render.IsFeatureEnabled(GraphicsFeatures::SampleAlphaToCoverage));
	state->Enable(GraphicsFeatures::SampleCoverage,render.IsFeatureEnabled(GraphicsFeatures::SampleCoverage));

	return state;
}

MEDUSA_IMPLEMENT_RTTI(FeatureRenderState,IRenderState);

MEDUSA_END;