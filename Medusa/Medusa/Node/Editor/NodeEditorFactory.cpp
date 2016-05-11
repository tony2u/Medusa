// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "NodeEditorFactory.h"
#include "Node/Editor/TieldLayerEditor.h"
#include "Core/IO/FileInfo.h"
#include "Core/Log/Log.h"
#include "Core/IO/FileIdRef.h"

MEDUSA_BEGIN;

NodeEditorFactory::NodeEditorFactory()
{
	
}

NodeEditorFactory::~NodeEditorFactory()
{
	Uninitialize();
}

bool NodeEditorFactory::Initialize()
{
	Uninitialize();
	Register<TieldLayerEditor>();

	return true;
}

bool NodeEditorFactory::Uninitialize()
{
	SAFE_DELETE_DICTIONARY_VALUE(mEditors);
	
	return true;
}

void NodeEditorFactory::Register(INodeEditor* editor)
{
	mEditors.TryAdd(editor->Type(), editor);
}

INodeEditor* NodeEditorFactory::FindEditor(const StringRef& type) const
{
	return mEditors.GetOptional(type, nullptr);
}

INodeEditor* NodeEditorFactory::FindEditor(FileType type) const
{
	for(auto& kv : mEditors )
	{
		INodeEditor* editor = kv.Value;
		if (editor != nullptr&& editor->Extension() == type)
		{
			return editor;
		}
	}

	return nullptr;
}


INodeEditor* NodeEditorFactory::FindEditorEnabled(FileType type) const
{
	for (auto& kv : mEditors)
	{
		INodeEditor* editor = kv.Value;
		if (editor != nullptr&&editor->IsEnabled() && editor->Extension() == type)
		{
			return editor;
		}
	}

	return nullptr;
}


INode* NodeEditorFactory::Create(const StringRef& className, const FileIdRef& editorFile, const IEventArg& e /*= IEventArg::Empty*/) const
{
	RETURN_NULL_IF_EMPTY(editorFile);

	INodeEditor* editor = nullptr;
	auto type = FileInfo::ExtractType(editorFile.Name);
	editor = FindEditorEnabled(type);

	if (editor == nullptr)
	{
		Log::FormatError("Cannot create layer:{}", editorFile.Name);
		return nullptr;
	}

	INode* node= editor->Create(className, editorFile, e);
	return node;
}

MEDUSA_END;