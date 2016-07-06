// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/String/StringRef.h"
#include "Core/Pattern/Singleton.h"
#include "Resource/BaseResourceFactory.h"
#include "Resource/Light/ILight.h"

MEDUSA_BEGIN;

/*
In World Space:

v:	viewer vector
l:	light direction
n:	normal vector
r:	reflect vector r=2(n.l)n-l
h:	half vector h=(v+l)/|v+l|


Gamb:	ambient color of global
Sspec:	specular color of light
Sdiff:	diffuse color of light

Mspec:	specular color of material
Mdiff:	diffuse color of material
Mamb:	ambient color of material
Memi:	emission color of material

Attenuation = 1.0/(ConstantAttenuation + LinearAttenuation * D + QuadraticAttenuation * D*D;

Single light:
LightColor=GlobalAmbientColor+EmissionColor+(AmbientColor+DiffuseColor+SpecularColor) * SpotEffect * Attenuation
AmbientColor=Gamb*Mamb
DiffuseColor=max((n.l),0)*Sdiff*Mdiff
SpecularColor=max((v.r),0)^Mgls*Sspec*Mspec			also could be max((n.h),0)^Mgls*Sspec*Mspec to remove recalculate r
EmissionColor=Memi

Multiple light:
LightColor=GlobalAmbientColor+EmissionColor+((AmbientColor+DiffuseColor+SpecularColor) * SpotEffect * Attenuation)1...n
*/
class LightFactory:public Singleton<LightFactory>,public BaseResourceFactory<ILight>
{
	friend class Singleton<LightFactory>;
public:
	LightFactory();
	~LightFactory();
public:
	virtual bool Initialize();
	virtual bool Uninitialize();
public:
	Share<DirectionalLight> CreateDirectionalLight(const FileIdRef& fileId,bool setDefault=true,bool enabled=true,ResourceShareType shareType = ResourceShareType::Share);
	Share<SpotLight> CreateSpotLight(const FileIdRef& fileId,bool setDefault=true,bool enabled=true,ResourceShareType shareType = ResourceShareType::Share);
	Share<ILight> CreateLightFromModel(const FileIdRef& fileId,const FileIdRef& modelFileId,bool setDefault=true,bool enabled=true,ResourceShareType shareType = ResourceShareType::Share);

	Share<ILight> GetCurrentLight()const{return mCurrentLight;}
	Share<ILight> SetCurrentLight(const FileIdRef& fileId);
private:
	Share<ILight> mCurrentLight;

};

MEDUSA_END;