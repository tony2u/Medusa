// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "Node/Panel/ScrollPanel.h"
MEDUSA_BEGIN;

/* 
??????????????
??????????????
*/
class ListPanel :public ScrollPanel
{
	MEDUSA_DECLARE_RTTI;

public:
	ListPanel(StringRef name = StringRef::Empty, ScrollDirection direction = ScrollDirection::VerticalFromTop);
	virtual ~ListPanel(void);
	virtual bool Initialize() override;
public:
	virtual void SetScrollDirection(ScrollDirection direction) override;
public:
    virtual void AddChild(INode* node)override;
    virtual bool RemoveChild(INode* node)override;
    virtual void RemoveAllChilds(NodeRemoveFlags flags = NodeRemoveFlags::OnlyChildren)override;
    virtual bool DeleteChild(INode* node)override;
    virtual void DeleteAllChilds(NodeRemoveFlags flags = NodeRemoveFlags::OnlyChildren)override;
    virtual void Clear(NodeRemoveFlags flags = NodeRemoveFlags::OnlyChildren)override;
    

	INode* GetItemByIndex(uint index)const;
	virtual bool InsertItemAt(uint index,INode* item);
	virtual INode* RemoveItemAt(uint index);
	virtual bool DeleteItemAt(uint index);

	virtual bool RefreshAll();
	virtual bool RefreshItem(uint index);
public:
	virtual void SetDataSource(IDataSource* dataSource) override;

protected:
	virtual bool ArrangeChildren(const Rect2F& limitRect=Rect2F::Zero,NodeLayoutArrangeFlags arrangeFlags=NodeLayoutArrangeFlags::None)override;
	virtual void OnUpdateTargetBoundingBox();

	virtual void OnInitializeTargetBoundingBox() override;
protected:
	List<INode*> mItems;
};

MEDUSA_END;
