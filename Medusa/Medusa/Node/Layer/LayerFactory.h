// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "Core/Pattern/Object/MapObjectFactory.h"
#include "Core/String/StringRef.h"
#include "MedusaPreDeclares.h"

MEDUSA_BEGIN;

class LayerFactory:public MapObjectFactory<StringRef,ILayer*(const StringRef&,const IEventArg&)>
{
public:
	using MapObjectFactory<StringRef,ILayer*(const StringRef&,const IEventArg&)>::Create;
private:
	LayerFactory(){}
	~LayerFactory(){}
public:
	static LayerFactory& Instance()
	{
		static LayerFactory factory;
		return factory;
	}

};


MEDUSA_END;