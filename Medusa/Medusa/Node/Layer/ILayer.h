// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Node/INode.h"
#include "Core/Pattern/StaticConstructor.h"
#include "Core/Command/EventArg/IEventArg.h"


MEDUSA_BEGIN;

#define MEDUSA_DECLARE_LAYER_ROOT(className) 													\
		MEDUSA_DECLARE_RTTI;\
public:																				\
	virtual const StringRef& EditorFileName()const{return mEditorFileName;}									\
	static const StringRef& EditorFileNameStatic(){return mEditorFileName;}									\
private:																				\
	const static StringRef mEditorFileName;							\
	const static StaticConstructor mStaticConstructor;							\
	static void SelfRegisterStaticCallback();

#define MEDUSA_DECLARE_LAYER(className) 													\
		MEDUSA_DECLARE_RTTI;\
public:																				\
	virtual const StringRef& EditorFileName()const override{return mEditorFileName;}									\
	static const StringRef& EditorFileNameStatic(){return mEditorFileName;}									\
private:																				\
	const static StringRef mEditorFileName;							\
	const static StaticConstructor mStaticConstructor;							\
	static void SelfRegisterStaticCallback();

#define MEDUSA_IMPLEMENT_LAYER(className,baseClassName,editorFile) 																					 \
	MEDUSA_IMPLEMENT_RTTI(className,baseClassName);\
	const StringRef className::mEditorFileName=editorFile;					 \
	const StaticConstructor className::mStaticConstructor(SelfRegisterStaticCallback);					 \
	void className::SelfRegisterStaticCallback(){LayerFactory::Instance().Register<className>(#className);}

class ILayer :public INode
{
	MEDUSA_DECLARE_LAYER_ROOT(ILayer);
public:
	ILayer(StringRef name=StringRef::Empty,const IEventArg& e=IEventArg::Empty);
	virtual ~ILayer(void);
	virtual bool Initialize()override;
};


MEDUSA_END;



#ifdef MEDUSA_SCRIPT
MEDUSA_SCRIPT_BEGIN;
void RegisterILayer(asIScriptEngine* engine);

template <class T>
void RegisterILayer_Methods(asIScriptEngine* engine, const char* typeName)
{
	RegisterINode_Methods<ILayer>(engine, typeName);
}

MEDUSA_SCRIPT_END;
#endif