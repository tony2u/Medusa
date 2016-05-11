// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Resource/Model/Light/BaseLightModelNode.h"
#include "Geometry/Color3.h"


MEDUSA_BEGIN;
class PODLightModelNode:public BaseLightModelNode
{
public:
	PODLightModelNode(StringRef name);
	virtual ~PODLightModelNode(void);
	virtual GraphicsLightType LightType() const{return Type;}
	virtual ILight* CreateLight()const;

public:

	int			TargetObjectIndex;		/*!< Index of the target object */
	Color3F			Color;	/*!< Light Color (0.0f -> 1.0f for each channel) */
	GraphicsLightType		Type;			/*!< Light type (point, directional, spot etc.) */
	float			ConstantAttenuation;	/*!< Constant attenuation */
	float			LinearAttenuation;		/*!< Linear atternuation */
	float			QuadraticAttenuation;	/*!< Quadratic attenuation */
	float			FalloffAngle;			/*!< Falloff angle (in radians) */
	float			FalloffExponent;		/*!< Falloff exponent */
};

MEDUSA_END;