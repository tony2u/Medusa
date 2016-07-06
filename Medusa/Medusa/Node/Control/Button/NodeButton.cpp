// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "NodeButton.h"
#include "Node/NodeFactory.h"

MEDUSA_BEGIN;


NodeButton::NodeButton(StringRef name,
							 INode* normalNode,
							 INode* selectedNode/*=nullptr*/,
							 INode* disabledNode/*=nullptr*/,
							 INode* disabledSelectedNode/*=nullptr*/)
							 :IButton(name),
							 mNormalNode(normalNode),
							 mSelectedNode(selectedNode),
							 mDisabledNode(disabledNode),
							 mDisabledSelectedNode(disabledSelectedNode)
{
	bool hasSize = false;
	if (mNormalNode!=nullptr)
	{
		InitNode(mNormalNode);
		mNormalNode->SetName(MEDUSA_PREFIX(Normal));
		
		AddChild(mNormalNode);
		mNormalNode->SetVisible(false);
		SetSize(mNormalNode->Size());	//default to normal size
		hasSize = true;
	}
	if (mSelectedNode != nullptr)
	{
		InitNode(mSelectedNode);
		mSelectedNode->SetName(MEDUSA_PREFIX(Selected));

		AddChild(mSelectedNode);
		mSelectedNode->SetVisible(false);
		if (!hasSize)
		{
			SetSize(mSelectedNode->Size());
			hasSize = true;
		}
	}
	if (mDisabledNode != nullptr)
	{
		InitNode(mDisabledNode);
		mDisabledNode->SetName(MEDUSA_PREFIX(Disabled));

		AddChild(mDisabledNode);
		mDisabledNode->SetVisible(false);
		if (!hasSize)
		{
			SetSize(mDisabledNode->Size());
			hasSize = true;
		}
	}
	if (mDisabledSelectedNode != nullptr)
	{
		InitNode(mDisabledSelectedNode);
		mDisabledSelectedNode->SetName(MEDUSA_PREFIX(DisabledSelected));

		AddChild(mDisabledSelectedNode);
		mDisabledSelectedNode->SetVisible(false);
		if (!hasSize)
		{
			SetSize(mDisabledSelectedNode->Size());
			//hasSize = true;
		}
	}
}

NodeButton::NodeButton(StringRef name /*= StringRef::Empty*/, const IEventArg& e /*= IEventArg::Empty*/)
	:IButton(name,e)
{

}

NodeButton::~NodeButton(void)
{

}

bool NodeButton::Initialize()
{
	OnUpdateNode();

	return true;
}


void NodeButton::SetDisabledSelectedNode(INode* val, bool updateSize /*= false*/)
{
	RETURN_IF_EQUAL(mDisabledSelectedNode, val);
	DeleteChild(mDisabledSelectedNode);
	mDisabledSelectedNode = val;
	if (mDisabledSelectedNode!=nullptr)
	{
		InitNode(mDisabledSelectedNode);
		mDisabledSelectedNode->SetName(MEDUSA_PREFIX(DisabledSelected));

		AddChild(mDisabledSelectedNode);
		mDisabledSelectedNode->SetVisible(false);
	}

	if (mButtonState == ButtonState::DisabledSelected)
	{
		OnUpdateNode();
		if (updateSize&&mDisabledSelectedNode!=nullptr)
		{
			SetSize(mDisabledSelectedNode->Size());
		}
	}

	
}

void NodeButton::SetDisabledNode(INode* val, bool updateSize /*= false*/)
{
	RETURN_IF_EQUAL(mDisabledNode, val);
	DeleteChild(mDisabledNode);
	mDisabledNode = val;
	if (mDisabledNode != nullptr)
	{
		InitNode(mDisabledNode);

		mDisabledNode->SetName(MEDUSA_PREFIX(Disabled));

		AddChild(mDisabledNode);
		mDisabledNode->SetVisible(false);
	}
	if (mButtonState == ButtonState::Disabled)
	{
		OnUpdateNode();
		if (updateSize&&mDisabledNode != nullptr)
		{
			SetSize(mDisabledNode->Size());
		}
	}
}

void NodeButton::SetSelectedNode(INode* val, bool updateSize /*= false*/)
{
	RETURN_IF_EQUAL(mSelectedNode, val);
	DeleteChild(mSelectedNode);
	mSelectedNode = val;
	if (mSelectedNode != nullptr)
	{
		InitNode(mSelectedNode);
		mSelectedNode->SetName(MEDUSA_PREFIX(Selected));

		AddChild(mSelectedNode);
		mSelectedNode->SetVisible(false);
	}
	if (mButtonState == ButtonState::Selected)
	{
		OnUpdateNode();
		if (updateSize&&mSelectedNode != nullptr)
		{
			SetSize(mSelectedNode->Size());
		}
	}
}

void NodeButton::SetNormalNode(INode* val, bool updateSize /*= false*/)
{
	RETURN_IF_EQUAL(mNormalNode, val);
	DeleteChild(mNormalNode);
	mNormalNode = val;
	if (mNormalNode != nullptr)
	{
		InitNode(mNormalNode);
		mNormalNode->SetName(MEDUSA_PREFIX(Normal));

		AddChild(mNormalNode);
		mNormalNode->SetVisible(false);
	}
	if (mButtonState == ButtonState::Normal)
	{
		OnUpdateNode();
		if (updateSize&&mNormalNode != nullptr)
		{
			SetSize(mNormalNode->Size());
		}
	}
}


void NodeButton::OnUpdateNode()
{
	switch (mButtonState)
	{
		case ButtonState::Normal:
			if (mNormalNode!=nullptr)
			{
				mNormalNode->SetVisible(true);
			}
			if (mSelectedNode != nullptr)
			{
				mSelectedNode->SetVisible(false);
			}
			if (mDisabledNode != nullptr)
			{
				mDisabledNode->SetVisible(false);
			}
			if (mDisabledSelectedNode != nullptr)
			{
				mDisabledSelectedNode->SetVisible(false);
			}
			break;
		case ButtonState::Selected:
			if (mNormalNode != nullptr)
			{
				mNormalNode->SetVisible(false);
			}
			if (mSelectedNode != nullptr)
			{
				mSelectedNode->SetVisible(true);
			}
			if (mDisabledNode != nullptr)
			{
				mDisabledNode->SetVisible(false);
			}
			if (mDisabledSelectedNode != nullptr)
			{
				mDisabledSelectedNode->SetVisible(false);
			}
			break;
		case ButtonState::Disabled:
			if (mNormalNode != nullptr)
			{
				mNormalNode->SetVisible(false);
			}
			if (mSelectedNode != nullptr)
			{
				mSelectedNode->SetVisible(false);
			}
			if (mDisabledNode != nullptr)
			{
				mDisabledNode->SetVisible(true);
			}
			if (mDisabledSelectedNode != nullptr)
			{
				mDisabledSelectedNode->SetVisible(false);
			}
			break;
		case ButtonState::DisabledSelected:
			if (mNormalNode != nullptr)
			{
				mNormalNode->SetVisible(false);
			}
			if (mSelectedNode != nullptr)
			{
				mSelectedNode->SetVisible(false);
			}
			if (mDisabledNode != nullptr)
			{
				mDisabledNode->SetVisible(false);
			}
			if (mDisabledSelectedNode != nullptr)
			{
				mDisabledSelectedNode->SetVisible(true);
			}
			break;
	}
}

void NodeButton::OnButtonStateChanged()
{
	OnUpdateNode();
}

void NodeButton::InitNode(INode* node)
{
	node->EnableManaged(true);
	node->SetDock(DockPoint::MiddleCenter);
	node->SetAnchorPoint(AnchorPoint::MiddleCenter);
}

MEDUSA_IMPLEMENT_NODE(NodeButton);
MEDUSA_END;
