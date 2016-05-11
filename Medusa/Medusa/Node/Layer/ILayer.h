// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Node/INode.h"
#include "Core/Pattern/StaticConstructor.h"
#include "Core/Command/EventArg/IEventArg.h"
#include "Core/IO/FileIdRef.h"


MEDUSA_BEGIN;

#define MEDUSA_DECLARE_LAYER_ROOT(className) 													\
		MEDUSA_DECLARE_RTTI;\
public:																				\
	virtual const FileIdRef& EditorFileName()const{return mEditorFileName;}									\
	static const FileIdRef& EditorFileNameStatic(){return mEditorFileName;}									\
	virtual const FileIdRef& ScriptFileName()const{return mScriptFileName;}									\
	static const FileIdRef& ScriptFileNameStatic(){return mScriptFileName;}									\
private:																				\
	const static FileIdRef mEditorFileName;							\
	const static FileIdRef mScriptFileName;							\
	const static StaticConstructor mStaticConstructor;							\
	static void SelfRegisterStaticCallback();

#define MEDUSA_DECLARE_LAYER(className) 													\
		MEDUSA_DECLARE_RTTI;\
public:																				\
	virtual const FileIdRef& EditorFileName()const override{return mEditorFileName;}									\
	static const FileIdRef& EditorFileNameStatic(){return mEditorFileName;}									\
	virtual const FileIdRef& ScriptFileName()const override{return mScriptFileName;}									\
	static const FileIdRef& ScriptFileNameStatic(){return mScriptFileName;}									\
private:																				\
	const static FileIdRef mEditorFileName;							\
	const static FileIdRef mScriptFileName;							\
	const static StaticConstructor mStaticConstructor;							\
	static void SelfRegisterStaticCallback();

#define MEDUSA_IMPLEMENT_LAYER(className,baseClassName,editorFile,scriptFile) 																					 \
	MEDUSA_IMPLEMENT_RTTI(className,baseClassName);\
	const FileIdRef className::mEditorFileName=editorFile;					 \
	const FileIdRef className::mScriptFileName=scriptFile;					 \
	const StaticConstructor className::mStaticConstructor(SelfRegisterStaticCallback);					 \
	void className::SelfRegisterStaticCallback(){LayerFactory::Instance().Register<className>(#className);}

class ILayer :public INode
{
	MEDUSA_DECLARE_LAYER(ILayer);
public:
	ILayer(StringRef name=StringRef::Empty,const IEventArg& e=IEventArg::Empty);
	virtual ~ILayer(void);
	virtual bool Initialize()override;
};


MEDUSA_END;

