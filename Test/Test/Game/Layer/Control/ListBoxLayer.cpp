// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "TestPreCompiled.h"
#include "ListBoxLayer.h"


ListBoxLayer::ListBoxLayer(StringRef name/*=StringRef::Empty*/, const IEventArg& e/*=IEventArg::Empty*/) :BaseCaseLayer(name, e)
{



}

ListBoxLayer::~ListBoxLayer(void)
{
}

bool ListBoxLayer::Initialize()
{
	RETURN_FALSE_IF_FALSE(BaseCaseLayer::Initialize());

	List<WHeapString> strItems;

	FOR_EACH_SIZE(i,100)
	{
		WHeapString str=StringParser::ToWString(i);
		strItems.Add(str);
	}

	ListBox* listBox=NodeFactory::Instance().CreateStringListBox(strItems,false);
	listBox->SetStretch(Medusa::Stretch::Fill);
	//listBox->SetVerticalScrollBarVisibility(ScrollBarVisibility::Disabled);
	//listBox->SetHorizontalScrollBarVisibility(ScrollBarVisibility::Disabled);
	StringListDataSource* dataSource=(StringListDataSource*)listBox->DataSource();
	LabelItemTemplate* labelItemTemplate=(LabelItemTemplate*)dataSource->ItemTemplate();
	labelItemTemplate->SetAlignment(Alignment::MiddleCenter);
	AddChild(listBox);

	listBox->OnItemSelected+=Bind(&ListBoxLayer::OnItemSelected,this);
	listBox->OnItemUnselected+= Bind(&ListBoxLayer::OnItemUnselected,this);
	listBox->OnItemClicked+= Bind(&ListBoxLayer::OnItemClicked,this);

	return true;
}


void ListBoxLayer::OnItemSelected(ListBox& sender,const ListBoxItem& item)
{
	Log::FormatInfo("Select:{}",(uint)item.Index);
}

void ListBoxLayer::OnItemUnselected(ListBox& sender,const ListBoxItem& item)
{
	Log::FormatInfo("UnSelect:{}",(uint)item.Index);

}

void ListBoxLayer::OnItemClicked(ListBox& sender,const ListBoxItem& item)
{
	Log::FormatInfo("Click:{}",(uint)item.Index);
}



MEDUSA_IMPLEMENT_LAYER(ListBoxLayer, BaseCaseLayer, StringRef::Empty);

