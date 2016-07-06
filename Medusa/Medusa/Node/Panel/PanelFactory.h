// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaPreDeclares.h"
#include "Core/Pattern/Object/MapObjectFactory.h"
#include "Core/String/StringRef.h"
#include "IPanel.h"
#include "Core/Pattern/Singleton.h"

MEDUSA_BEGIN;

class PanelFactory :public MapObjectFactory<PanelType, IPanel*(), SafeEnumHashCoder>,public Singleton<PanelFactory>
{
	PanelFactory();
	~PanelFactory() {}
	friend class Singleton<PanelFactory>;
public:
	using MapObjectFactory<PanelType, IPanel*(), SafeEnumHashCoder>::Create;
};


MEDUSA_END;