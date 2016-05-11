// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Graphics/GraphicsTypes.h"
#include "Geometry/Point3.h"
#include "Geometry/Color3.h"
#include "Core/String/HeapString.h"
#include "Resource/IResource.h"

MEDUSA_BEGIN;
class ILight:public IResource
{
public:
	ILight(const FileIdRef& fileId=FileIdRef::Empty);
	virtual ~ILight(void){}
	virtual GraphicsLightType LightType()const=0;
	virtual ResourceType Type()const{return ResourceType::Light;}
	static ResourceType ClassGetResourceType(){return ResourceType::Light;}

	bool IsEnabled() const { return mIsEnabled; }
	void SetIsEnabled(bool val){mIsEnabled=val;}

	const Point3F& Position() const { return mPosition; }
	void SetPosition(const Point3F& val) { mPosition = val; }

	const Point3F& Direction() const { return mDirection; }
	void SetDirection(const Point3F& val) { mDirection = val; }

	virtual bool IsVisible()const{return false;}
	const Color3F& DiffuseColor() const { return mDiffuseColor; }
	void SetDiffuseColor(const Color3F& val) { mDiffuseColor = val; }

	const Color3F& SpecularColor() const { return mSpecularColor; }
	void SetSpecularColor(const Color3F& val) { mSpecularColor = val; }

	const Color3F& AmbientColor() const { return mAmbientColor; }
	void SetAmbientColor(const Color3F& val) { mAmbientColor = val; }

	void SetColor(const Color3F& val){mAmbientColor=mDiffuseColor=mSpecularColor=val;}
protected:
	bool mIsEnabled;

	Point3F mDirection;
	Point3F mPosition;

	Color3F mAmbientColor;
	Color3F mDiffuseColor;
	Color3F mSpecularColor;
};

MEDUSA_END;
