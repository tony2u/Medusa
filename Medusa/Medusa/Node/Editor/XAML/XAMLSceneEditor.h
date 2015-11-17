// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Node/Editor/ISceneEditor.h"
#include "Core/Collection/Dictionary.h"
#include "Core/Pattern/StaticConstructor.h"
#include "CoreLib/Common/pugixml/pugixml.hpp"

MEDUSA_BEGIN;

/************************************************************************/
/* 
Create layer from
Page
Window
UserControl
*/
/************************************************************************/

class XAMLSceneEditor:public ISceneEditor
{
	typedef INode* ElementCreator(pugi::xml_node node,INode* parent,const IEventArg& e);
public:
	XAMLSceneEditor();
	virtual ~XAMLSceneEditor(void);

	virtual SceneEditorType GetType()const override{return SceneEditorType::XAML;}

public:
	using ISceneEditor::CreateLayer;
	virtual ILayer* CreateLayer(const StringRef& layerName, const FileIdRef& editorFile, const IEventArg& e = IEventArg::Empty)override;
private:
	static INode* CreateGrid(pugi::xml_node node,INode* parent,const IEventArg& e);
	static INode* CreatePage(pugi::xml_node node,INode* parent,const IEventArg& e);
	static INode* CreateWindowNode(pugi::xml_node node,INode* parent,const IEventArg& e);
	static INode* CreateUserControl(pugi::xml_node node,INode* parent,const IEventArg& e);



	static Dictionary<StringRef,ElementCreator*> mElementCreators;
	static void SelfRegisterStaticCallback();
	const static StaticConstructor mStaticConstructor;
};

MEDUSA_END;
