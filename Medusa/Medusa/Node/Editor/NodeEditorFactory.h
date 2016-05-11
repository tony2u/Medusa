// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Pattern/Singleton.h"
#include "INodeEditor.h"
#include "Core/Pattern/IInitializable.h"
#include "Core/IO/FileDefines.h"
#include "Core/Collection/Dictionary.h"

MEDUSA_BEGIN;

class NodeEditorFactory :public Singleton<NodeEditorFactory>, IInitializable
{
	friend class Singleton<NodeEditorFactory>;
	NodeEditorFactory();
	~NodeEditorFactory();
public:
	virtual bool Initialize()override;
	virtual bool Uninitialize()override;
public:
	template<typename T>
	void Register(){ Register(new T());}

	void Register(INodeEditor* editor);
public:
	INodeEditor* FindEditor(FileType type)const;
	INodeEditor* FindEditor(const StringRef& type)const;
	INodeEditor* FindEditorEnabled(FileType type)const;

	INode* Create(const StringRef& className, const FileIdRef& editorFile, const IEventArg& e = IEventArg::Empty)const;
private:
	Dictionary<HeapString, INodeEditor*> mEditors;

};

MEDUSA_END;