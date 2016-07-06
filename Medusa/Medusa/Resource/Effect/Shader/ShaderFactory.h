// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/String/StringRef.h"
#include "Core/Pattern/Singleton.h"
#include "Resource/BaseResourceFactory.h"
#include "Resource/Effect/Shader/IShader.h"

MEDUSA_BEGIN;

class ShaderFactory:public Singleton<ShaderFactory>,public BaseResourceFactory<IShader>
{
	friend class Singleton<ShaderFactory>;
public:
	ShaderFactory();
	~ShaderFactory();
public:
	virtual bool Initialize();
	virtual bool Uninitialize();
public:
	Share<IShader> CreateShader(const FileIdRef& fileId,const List<HeapString>* defines=nullptr,ResourceShareType shareType = ResourceShareType::Share);

};

MEDUSA_END;