// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "XAMLSceneEditor.h"
#include "Core/IO/FileSystem.h"
#include "Node/Layer/LayerFactory.h"

MEDUSA_BEGIN;
XAMLSceneEditor::XAMLSceneEditor()
{
}

XAMLSceneEditor::~XAMLSceneEditor(void)
{

}

ILayer* XAMLSceneEditor::CreateLayer(const StringRef& layerName, const FileIdRef& editorFile, const IEventArg& e/*=IEventArg::Empty*/)
{
	MemoryByteData fileData = FileSystem::Instance().ReadAllData(editorFile);
	if (fileData.IsNull())
	{
		//not use editor file to create layer
		ILayer* layer = LayerFactory::Instance().Create(layerName, layerName, e);
		Log::AssertNotNullFormat(layer, "Cannot create layer by name:{}", layerName.c_str());
		layer->Initialize();

		return layer;
	}


	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_buffer(fileData.Data(), fileData.Size());
	if (!result)
	{
		Log::AssertFailedFormat("Cannot parse xml:{} because {}", editorFile.Name.c_str(), result.description());
		return nullptr;
	}

	pugi::xml_node pageNode = doc.first_child();
	StringRef nodeName = pageNode.name();
	ElementCreator* creator = mElementCreators.TryGetValueWithFailed(nodeName, nullptr);
	if (creator != nullptr)
	{
		ILayer* layer=(ILayer*)creator(pageNode, nullptr, e);
		Log::AssertFormat(layer != nullptr, "Cannot create Layer by File:{}", editorFile.Name.c_str());
        if(layer!=nullptr)
        {
            layer->Initialize();
        }
		return layer;

	}
	return nullptr;
}

INode* XAMLSceneEditor::CreatePage(pugi::xml_node node, INode* parent, const IEventArg& e)
{
	StringRef className = node.attribute("x:Class").value();
	StringRef name = node.attribute("x:Name").value();
	float width = node.attribute("Width").as_float();
	float height = node.attribute("Height").as_float();

	ILayer* layer = LayerFactory::Instance().Create(className, name, e);

	if (layer == nullptr)
	{
		Log::AssertFailedFormat("Cannot create layer:{}", className.c_str());
		return nullptr;
	}

	layer->SetSize(Size2F(width, height));

	FOR_EACH_COLLECTION_STL(i, node.children())
	{
		pugi::xml_node child = *i;
		StringRef childName = child.name();
		ElementCreator* creator = mElementCreators.TryGetValueWithFailed(childName, nullptr);
		if (creator != nullptr)
		{
			INode* childNode = creator(child, layer, e);
			if (childNode != nullptr)
			{
				layer->AddChild(childNode);
			}
			else
			{
				/*SAFE_DELETE(layer);
				return nullptr;*/
			}
		}
	}

	layer->Initialize();
	return layer;
}

INode* XAMLSceneEditor::CreateWindowNode(pugi::xml_node node, INode* parent, const IEventArg& e)
{
	StringRef className = node.attribute("xmlns:local").value();
	StringRef name = node.attribute("Title").value();
	float width = node.attribute("Width").as_float();
	float height = node.attribute("Height").as_float();

	ILayer* layer = LayerFactory::Instance().Create(className, name, e);

	if (layer == nullptr)
	{
		Log::AssertFailedFormat("Cannot create layer:{}", className.c_str());
		return nullptr;
	}

	layer->SetSize(Size2F(width, height));

	FOR_EACH_COLLECTION_STL(i, node.children())
	{
		pugi::xml_node child = *i;
		StringRef childName = child.name();
		ElementCreator* creator = mElementCreators.TryGetValueWithFailed(childName, nullptr);
		if (creator != nullptr)
		{
			INode* childNode = creator(child, layer, e);
			if (childNode != nullptr)
			{
				layer->AddChild(childNode);
			}
			else
			{
				/*SAFE_DELETE(layer);
				return nullptr;*/
			}
		}
	}

	layer->Initialize();
	return layer;
}

INode* XAMLSceneEditor::CreateUserControl(pugi::xml_node node, INode* parent, const IEventArg& e)
{
	StringRef className = node.attribute("x:Class").value();
	StringRef name = node.attribute("x:Name").value();
	float width = node.attribute("Width").as_float();
	float height = node.attribute("Height").as_float();

	ILayer* layer = LayerFactory::Instance().Create(className, name, e);

	if (layer == nullptr)
	{
		Log::AssertFailedFormat("Cannot create layer:{}", className.c_str());
		return nullptr;
	}

	layer->SetSize(Size2F(width, height));

	FOR_EACH_COLLECTION_STL(i, node.children())
	{
		pugi::xml_node child = *i;
		StringRef childName = child.name();
		ElementCreator* creator = mElementCreators.TryGetValueWithFailed(childName, nullptr);
		if (creator != nullptr)
		{
			INode* childNode = creator(child, layer, e);
			if (childNode != nullptr)
			{
				layer->AddChild(childNode);
			}
			else
			{
				/*SAFE_DELETE(layer);
				return nullptr;*/
			}
		}
	}

	layer->Initialize();
	return layer;
}


INode* XAMLSceneEditor::CreateGrid(pugi::xml_node node, INode* parent, const IEventArg& e)
{
	return nullptr;
}


Dictionary<StringRef, XAMLSceneEditor::ElementCreator*> XAMLSceneEditor::mElementCreators;

void XAMLSceneEditor::SelfRegisterStaticCallback()
{
	mElementCreators.Add("Page", CreatePage);
	mElementCreators.Add("Window", CreateWindowNode);
	mElementCreators.Add("UserControl", CreateUserControl);

	mElementCreators.Add("Grid", CreateGrid);
}


const StaticConstructor XAMLSceneEditor::mStaticConstructor(SelfRegisterStaticCallback);


MEDUSA_END;
