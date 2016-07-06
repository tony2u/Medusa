// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "IButton.h"

MEDUSA_BEGIN;

class NodeButton :public IButton
{
	MEDUSA_NODE(NodeButton, IButton);
public:
	NodeButton(StringRef name = StringRef::Empty, const IEventArg& e = IEventArg::Empty);
	NodeButton(StringRef name, INode* normalNode, INode* selectedNode = nullptr, INode* disabledNode = nullptr, INode* disabledSelectedNode = nullptr);
	virtual ~NodeButton(void);
	virtual bool Initialize()override;

	INode* NormalNode() const { return mNormalNode; }
	void SetNormalNode(INode* val, bool updateSize = false);

	INode* SelectedNode() const { return mSelectedNode; }
	void SetSelectedNode(INode* val, bool updateSize = false);

	INode* DisabledNode() const { return mDisabledNode; }
	void SetDisabledNode(INode* val, bool updateSize = false);

	INode* DisabledSelectedNode() const { return mDisabledSelectedNode; }
	void SetDisabledSelectedNode(INode* val, bool updateSize = false);
protected:
	void OnUpdateNode();
	virtual void OnButtonStateChanged()override;
	void InitNode(INode* node);
protected:
	INode* mNormalNode = nullptr;
	INode* mSelectedNode = nullptr;
	INode* mDisabledNode = nullptr;
	INode* mDisabledSelectedNode = nullptr;

};

MEDUSA_END;
