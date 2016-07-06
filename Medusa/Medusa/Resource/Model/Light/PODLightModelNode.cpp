// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "PODLightModelNode.h"
#include "Resource/Light/DirectionalLight.h"
#include "Resource/Light/PointLight.h"
#include "Resource/Light/SpotLight.h"


MEDUSA_BEGIN;


PODLightModelNode::PODLightModelNode(StringRef name)
	:BaseLightModelNode(name),TargetObjectIndex(0),Color(Color3F::White),Type(GraphicsLightType::Directional),ConstantAttenuation(0.f),LinearAttenuation(0.f),QuadraticAttenuation(0.f),FalloffAngle(0.f),FalloffExponent(0.f)
{
}


PODLightModelNode::~PODLightModelNode(void)
{
}

Share<ILight> PODLightModelNode::CreateLight() const
{
	switch (Type)
	{
	case GraphicsLightType::Directional:
		return new DirectionalLight(mName);
		break;
	case GraphicsLightType::Point:
		return new PointLight(mName);
		break;
	case GraphicsLightType::Spot:
		{
			Share<SpotLight> light= new SpotLight(mName);
			light->SetCutoff(FalloffAngle);
			light->SetExponent(FalloffExponent);
			light->SetConstantAttenuation(ConstantAttenuation);
			light->SetLinearAttenuation(LinearAttenuation);
			light->SetQuadraticAttenuation(QuadraticAttenuation);
			return light;
		}
		
		break;
	default:
		break;
	}

	return nullptr;
}


MEDUSA_END;