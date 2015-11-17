// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "TestPreDeclares.h"
#include "Node/Layer/ILayer.h"
#include "Core/String/StringRef.h"
#include "Core/Collection/List.h"

class TestLayer:public ILayer
{
	MEDUSA_DECLARE_LAYER(TestLayer);
public:
	TestLayer(StringRef name=StringRef::Empty,const IEventArg& e=IEventArg::Empty);
	virtual ~TestLayer(void);
	virtual bool Initialize()override;
protected:
	void OnItemClicked(ListBox& sender,const ListBoxItem& item);
private:
	List<WHeapString> mItems;

};

