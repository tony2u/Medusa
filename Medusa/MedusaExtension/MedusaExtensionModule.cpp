// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaExtensionPreCompiled.h"
#include "MedusaExtensionModule.h"
#include "CocosStudio/BinaryEditor.h"
#include "CocosStudio/JsonEditor.h"
#include "Node/Editor/NodeEditorFactory.h"


MEDUSA_BEGIN;

MedusaExtensionModule::MedusaExtensionModule()
	:IModule("Extension")
{
	
}

bool MedusaExtensionModule::Initialize()
{
	return true;
}

bool MedusaExtensionModule::OnLoad(IEventArg& e /*= IEventArg::Empty*/)
{
	NodeEditorFactory::Instance().Register<Cocos::BinaryEditor>();

	NodeEditorFactory::Instance().Register<Cocos::JsonEditor>();

	return true;
}


MEDUSA_END;

