// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "Core/Pattern/Object/MapObjectFactory.h"
#include "Core/String/StringRef.h"
#include "MedusaPreDeclares.h"
#include "Core/Command/EventArg/IEventArg.h"
#include "Node/NodeDefines.h"
#include "Node/Layer/ILayer.h"

MEDUSA_BEGIN;

class LayerFactory:public MapObjectFactory<StringRef,ILayer*(const StringRef&,const IEventArg&)>
{
public:
	using BaseType = MapObjectFactory<StringRef, ILayer*(const StringRef&, const IEventArg&)>;
private:
	LayerFactory(){}
	~LayerFactory(){}
public:
	static LayerFactory& Instance()
	{
		static LayerFactory factory;
		return factory;
	}

	
	template<typename T>
	T* Create(const IEventArg& e = IEventArg::Empty, LayerCreateFlags createFlags = LayerCreateFlags::None) { return (T*)Create(T::ClassNameStatic(), T::EditorFileNameStatic(), e, createFlags); }
	ILayer* Create(const StringRef& className, const FileIdRef& editorFile, const IEventArg& e = IEventArg::Empty, LayerCreateFlags createFlags = LayerCreateFlags::None);

};

MEDUSA_END;