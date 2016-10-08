// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "TestPreCompiled.h"
#include "TableBoxLayer.h"


TableBoxLayer::TableBoxLayer(StringRef name/*=StringRef::Empty*/, const IEventArg& e/*=IEventArg::Empty*/) :BaseCaseLayer(name, e)
{



}

TableBoxLayer::~TableBoxLayer(void)
{
}

bool TableBoxLayer::Initialize()
{
	RETURN_FALSE_IF_FALSE(BaseCaseLayer::Initialize());

	List<FileId> strItems;

	FOR_EACH_SIZE(i, 1000)
	{
		strItems.NewAdd() = "test2.png";
	}

	auto dataSource = DataSourceFactory::Instance().CreateFileIdList("testList2", strItems);
	TableBox* box = NodeFactory::Instance().CreateTableBox();
	box->SetStretch(Medusa::Stretch::Fill);
	auto binding = box->BindTo<SpriteTemplate>(dataSource);
	auto nodeTemplate = (SpriteTemplate*)binding->GetTemplate(0);
	//nodeTemplate->SetAnchor(AnchorPoint::MiddleCenter);
	//nodeTemplate->SetDock(DockPoint::MiddleCenter);
	
	//listBox->SetVerticalScrollBarVisibility(ScrollBarVisibility::Disabled);
	//listBox->SetHorizontalScrollBarVisibility(ScrollBarVisibility::Disabled);
	AddChild(box);

	box->OnItemSelected += Bind(&TableBoxLayer::OnItemSelected, this);
	box->OnItemUnselected += Bind(&TableBoxLayer::OnItemUnselected, this);
	box->OnItemClicked += Bind(&TableBoxLayer::OnItemClicked, this);
	return true;
}


void TableBoxLayer::OnItemSelected(TableBox& sender,const TableBoxItem& item)
{
	Log::FormatInfo("Select:{}",(uint)item.Index);
}

void TableBoxLayer::OnItemUnselected(TableBox& sender,const TableBoxItem& item)
{
	Log::FormatInfo("UnSelect:{}",(uint)item.Index);

}

void TableBoxLayer::OnItemClicked(TableBox& sender,const TableBoxItem& item)
{
	Log::FormatInfo("Click:{}",(uint)item.Index);
}



MEDUSA_IMPLEMENT_NODE(TableBoxLayer);

