// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "TestPreDeclares.h"
#include "Game/BaseCaseLayer.h"

class ListBoxLayer :public BaseCaseLayer
{
	MEDUSA_NODE(ListBoxLayer, BaseCaseLayer);
public:
	ListBoxLayer(StringRef name=StringRef::Empty,const IEventArg& e=IEventArg::Empty);
	virtual ~ListBoxLayer(void);
	virtual bool Initialize()override;
protected:
	void OnItemSelected(ListBox& sender,const ListBoxItem& item);
	void OnItemUnselected(ListBox& sender,const ListBoxItem& item);
	void OnItemClicked(ListBox& sender,const ListBoxItem& item);

};

