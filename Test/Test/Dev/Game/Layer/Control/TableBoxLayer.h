// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "TestPreDeclares.h"
#include "Game/BaseCaseLayer.h"

class TableBoxLayer :public BaseCaseLayer
{
	MEDUSA_NODE(TableBoxLayer, BaseCaseLayer);
public:
	TableBoxLayer(StringRef name=StringRef::Empty,const IEventArg& e=IEventArg::Empty);
	virtual ~TableBoxLayer(void);
	virtual bool Initialize()override;
protected:
	void OnItemSelected(TableBox& sender,const TableBoxItem& item);
	void OnItemUnselected(TableBox& sender,const TableBoxItem& item);
	void OnItemClicked(TableBox& sender,const TableBoxItem& item);

};

