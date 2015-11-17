// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaPreDeclares.h"
#include "Core/String/HeapString.h"
#include "Graphics/GraphicsTypes.h"
#include "Resource/IResource.h"

MEDUSA_BEGIN;

class IShader:public IResource
{
public:
	IShader(const FileIdRef& fileId=FileIdRef::Empty);
	virtual ~IShader();
	virtual ResourceType Type()const{return ResourceType::Shader;}
	static ResourceType ClassGetResourceType(){return ResourceType::Shader;}

	virtual bool Compare(const IShader& shader)const;

	virtual GraphicsShaderType ShaderType()const=0;
	using IResource::Initialize;
	bool Initialize(StringRef source,const List<HeapString>* defines=nullptr);
	virtual bool Uninitialize();
	bool IsValid() const { return mShader!=0; }
	uint Shader() const { return mShader; }
	virtual void Apply();
	virtual void Restore();


protected:
	uint mShader;
};



struct STLMapShaderLessPtr
{
	bool operator()(const IShader* t1, const IShader* t2)const
	{
		return t1->Compare(*t2);
	}
};

MEDUSA_END;