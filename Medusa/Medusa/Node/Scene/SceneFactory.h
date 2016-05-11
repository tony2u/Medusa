// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "Core/Pattern/Object/MapObjectFactory.h"
#include "Core/String/StringRef.h"
#include "Core/Command/EventArg/IEventArg.h"
#include "MedusaPreDeclares.h"
#include "Node/Scene/IScene.h"

MEDUSA_BEGIN;

class SceneFactory :public MapObjectFactory < StringRef, IScene*(const StringRef&, const IEventArg&) >
{
public:
	using BaseType = MapObjectFactory<StringRef, IScene*(const StringRef&, const IEventArg&)>;
private:
	SceneFactory() {}
	~SceneFactory() {}
public:
	static SceneFactory& Instance()
	{
		static SceneFactory factory;
		return factory;
	}

	
	template<typename T>
	T* Create(const IEventArg& e = IEventArg::Empty) { return (T*)Create(T::ClassNameStatic(), T::EditorFileNameStatic(), e); }
	IScene* Create(const StringRef& className, const FileIdRef& editorFile, const IEventArg& e = IEventArg::Empty);
};


MEDUSA_END;