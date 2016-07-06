// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Node/INode.h"
#include "Core/Event/EventArg/IEventArg.h"
#include "Node/INode.h"
#include "Core/IO/FileDefines.h"

MEDUSA_BEGIN;

class INodeEditor
{
public:
	virtual ~INodeEditor(void) {}
	virtual StringRef Name()const = 0;
	virtual FileType Extension()const = 0;
	virtual StringRef ExtensionString()const = 0;


	bool IsEnabled() const { return mEnabled; }
	void Enable(bool val) { mEnabled = val; }
public:
	virtual INode* Create(const StringRef& className, const FileIdRef& editorFile, const FileIdRef& scriptFile,const IEventArg& e = IEventArg::Empty, NodeCreateFlags flags = NodeCreateFlags::None) = 0;

	template<typename T>
	T* Create(const IEventArg& e = IEventArg::Empty, NodeCreateFlags flags = NodeCreateFlags::None)
	{
		INode* node = this->Create(T::ClassNameStatic(), T::EditorFileNameStatic(), T::ScriptFileNameStatic(), e,flags);
		MEDUSA_ASSERT(node->IsExactly(T::ClassStatic()), "Inconsistent className in editor file");
		return (T*)node;
	}

	static NodeCreateFlags GetChildrenCreateFlags(NodeCreateFlags val);
protected:
	bool mEnabled = true;

};

MEDUSA_END;
