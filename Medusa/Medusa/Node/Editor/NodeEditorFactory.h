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
	void Register() { Register(new T()); }
	void Register(INodeEditor* editor);

	const Dictionary<HeapString, INodeEditor*>& Editors() const { return mEditors; }
public:
	INodeEditor* Find(FileType type)const;
	INodeEditor* Find(const StringRef& type)const;
	INodeEditor* FindEnabled(FileType type)const;

	bool Enable(FileType type, bool val);
	bool Enable(const StringRef& type, bool val);
	void EnableAll(bool val);

	INode* Create(const StringRef& className, const FileIdRef& editorFile, const FileIdRef& scriptFile, const IEventArg& e = IEventArg::Empty, NodeCreateFlags flags = NodeCreateFlags::None)const;
private:
	Dictionary<HeapString, INodeEditor*> mEditors;	//extension-val

};

MEDUSA_END;