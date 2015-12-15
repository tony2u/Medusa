// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "Core/Pattern/Object/MapObjectFactory.h"
#include "Core/String/StringRef.h"
#include "MedusaPreDeclares.h"
#include "Node/Layer/LayerPushFlags.h"
#include "Node/Layer/LayerPopFlags.h"
#include "Node/Layer/LayerCreateFlags.h"
#include "Node/Layer/LayerDeleteFlags.h"
#include "Core/Command/EventArg/IEventArg.h"

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

	
	template<typename T>
	T* CreateLayer(const IEventArg& e = IEventArg::Empty, LayerCreateFlags createFlags = LayerCreateFlags::None) { return (T*)CreateLayer(T::ClassNameStatic(), T::EditorFileNameStatic(), e, createFlags); }
	ILayer* CreateLayer(const StringRef& className, const StringRef& editorFile, const IEventArg& e = IEventArg::Empty, LayerCreateFlags createFlags = LayerCreateFlags::None);

};

MEDUSA_END;