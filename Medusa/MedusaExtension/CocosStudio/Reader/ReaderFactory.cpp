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

