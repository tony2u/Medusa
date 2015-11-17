// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "ILayer.h"
#include "Core/Command/EventArg/IEventArg.h"
#include "Node/Layer/LayerFactory.h"
#include "Graphics/ResolutionAdapter.h"
#include "Core/Script/ScriptDefines.h"


MEDUSA_BEGIN;

ILayer::ILayer(StringRef name/*=StringRef::Empty*/, const IEventArg& e/*=IEventArg::Empty*/) :INode(name)
{
	mSize = ResolutionAdapter::Instance().WinSize();
	SetStretch(Stretch::Fill);
	SetSizeToContent(SizeToContent::WidthAndHeight);
	Start();
}


ILayer::~ILayer(void)
{
}

bool ILayer::Initialize()
{
	return true;
}


MEDUSA_IMPLEMENT_LAYER(ILayer, INode, StringRef::Empty);


MEDUSA_END;


#ifdef MEDUSA_SCRIPT
#include "CoreLib/Common/angelscript.h"

MEDUSA_SCRIPT_BEGIN;

void RegisterILayer(asIScriptEngine* engine)
{
	int r2;
	r2 = engine->RegisterObjectType(MACRO_TO_STRING(ILayer), sizeof(ILayer), asOBJ_REF | asOBJ_NOCOUNT); MEDUSA_ASSERT_SILENT(r2 >= 0);
	MEDUSA_SCRIPT_REGISTER_NODE_NEW_DELETE(engine, ILayer);

	MEDUSA_SCRIPT_REGISTER_CAST_BASE_DERIVED(engine, INode, ILayer);

	RegisterILayer_Methods<ILayer>(engine, MACRO_TO_STRING(ILayer));

}

MEDUSA_SCRIPT_END;
#endif
