// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaExtensionPreCompiled.h"
#include "ReaderFactory.h"
#include "Core/Log/Log.h"
#include "ButtonReader.h"
#include "LayerReader.h"
#include "ProjectNodeReader.h"
#include "SceneReader.h"
#include "SpriteReader.h"
#include "TextReader.h"
#include "ImageViewReader.h"
#include "NodeReader.h"
#include "SingleNodeReader.h"
#include "TextBMFontReader.h"
#include "TextAtlasReader.h"
#include "LoadingBarReader.h"
#include "TextFieldReader.h"
#include "TiledMapReader.h"
#include "PanelReader.h"
#include "ScrollViewReader.h"
#include "PageViewReader.h"
#include "ListViewReader.h"


MEDUSA_COCOS_BEGIN;


ReaderFactory::ReaderFactory()
{
	Register<ButtonReader>();
	Register<LayerReader>();
	Register<ProjectNodeReader>();
	Register<SceneReader>();
	Register<SpriteReader>();
	Register<TextReader>();
	Register<ImageViewReader>();
	Register<NodeReader>();
	Register<SingleNodeReader>();
	Register<TextBMFontReader>();
	Register<TextAtlasReader>();
	Register<LoadingBarReader>();
	Register<TextFieldReader>();
	Register<TiledMapReader>();
	Register<PanelReader>();
	Register<ScrollViewReader>();
	Register<PageViewReader>();
	Register<ListViewReader>();
}

INodeReader* ReaderFactory::AssertCreate(StringRef name) 
{
	auto reader = Create(name);
	if (reader==nullptr)
	{
		Log::AssertFailedFormat("Invalid cocos reader name:{}", name);
	}
	return reader;

}


MEDUSA_COCOS_END;

