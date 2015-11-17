// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Node/INode.h"
#include "Core/Command/EventArg/IEventArg.h"
#include "Node/Layer/ILayer.h"

MEDUSA_BEGIN;

enum class SceneEditorType
{
	Custom,
	XAML,
	CocoStudio,

	Count=3
};


class ISceneEditor 
{

public:
	virtual ~ISceneEditor(void){}

	virtual SceneEditorType GetType()const=0;

public:
	virtual ILayer* CreateLayer(const StringRef& layerName,const FileIdRef& editorFile,const IEventArg& e=IEventArg::Empty)=0;

	template<typename T>
	T* CreateLayer(const IEventArg& e=IEventArg::Empty)
	{
		ILayer* layer = this->CreateLayer(T::ClassNameStatic(),T::EditorFileNameStatic(), e);
		MEDUSA_ASSERT(layer->IsExactly(T::ClassStatic()), "Inconsistent className in editor file");
		return (T*)layer;
	}
};

MEDUSA_END;
