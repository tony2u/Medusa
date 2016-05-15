// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "NodeEditorFactory.h"
#include "Node/Editor/TieldLayerEditor.h"
#include "Core/IO/FileInfo.h"
#include "Core/Log/Log.h"
#include "Core/IO/FileIdRef.h"
#include "Application/Settings/ApplicationSettings.h"
#include "Core/IO/FileSystem.h"

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

INodeEditor* NodeEditorFactory::Find(const StringRef& type) const
{
	return mEditors.GetOptional(type, nullptr);
}

INodeEditor* NodeEditorFactory::Find(FileType type) const
{
	for (auto& kv : mEditors)
	{
		INodeEditor* editor = kv.Value;
		if (editor != nullptr&& editor->Extension() == type)
		{
			return editor;
		}
	}

	return nullptr;
}


INodeEditor* NodeEditorFactory::FindEnabled(FileType type) const
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


bool NodeEditorFactory::Enable(FileType type, bool val)
{
	auto editor = Find(type);
	RETURN_FALSE_IF_NULL(editor);
	editor->Enable(val);
	return true;
}

bool NodeEditorFactory::Enable(const StringRef& type, bool val)
{
	auto editor = Find(type);
	RETURN_FALSE_IF_NULL(editor);
	editor->Enable(val);
	return true;
}

void NodeEditorFactory::EnableAll(bool val)
{
	for (auto kv : mEditors)
	{
		kv.Value->Enable(val);
	}
}

INode* NodeEditorFactory::Create(const StringRef& className, const FileIdRef& editorFile, const IEventArg& e /*= IEventArg::Empty*/, NodeCreateFlags flags /*= NodeCreateFlags::None*/) const
{
	RETURN_NULL_IF_EMPTY(editorFile);

	INodeEditor* editor = nullptr;
	auto type = FileInfo::ExtractType(editorFile.Name);
	if (type != FileType::None)
	{
		editor = FindEnabled(type);
		if (editor == nullptr)
		{
			Log::FormatError("Cannot create layer:{}", editorFile.Name);
			return nullptr;
		}

		INode* node = editor->Create(className, editorFile, e, flags);
		return node;
	}
	else
	{
		//no extension,use applicate node editors to find
		const auto nodeEditors = ApplicationSettings::Instance().NodeEditors();
		if (nodeEditors.IsEmpty())
		{
			Log::FormatError("Cannot have pure editor file name:{} without extension when editors not specified. Fixed:Set ApplicationSettings::Instance().NodeEditors().", editorFile.Name);
			return nullptr;
		}

		FileId editorFileId;
		editorFileId.Order = editorFile.Order;
		for (auto& editorExtension : nodeEditors)
		{
			type = FileInfo::CheckFileType(editorExtension);
			editor = Find(type);
			if (editor != nullptr)
			{
				editorFileId.Name = editorFile.Name + editorExtension;
				if (FileSystem::Instance().Exists(editorFileId))
				{
					return editor->Create(className, editorFileId, e, flags);
				}
				editor = nullptr;	//reset to null
			}
		}

		Log::FormatError("Cannot create layer:{}", editorFile.Name);
	}
	return nullptr;
}

MEDUSA_END;