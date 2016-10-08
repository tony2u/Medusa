// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Pattern/Share.h"
#include "Core/Pattern/Event.h"


MEDUSA_BEGIN;


class IDataBinding
{
public:
	IDataBinding();
	virtual ~IDataBinding(void);
public:
	INode* Node() const { return mNode; }
	void SetNode(INode* val) { mNode = val; }

	bool IsEnabled()const { return mEnabled; }
	void Enable(bool val) { mEnabled = val; }
	virtual bool IsValid()const = 0;

	virtual bool Pull() { return false; }
	virtual bool Push() { return false; }

	Event<void()> OnTotalChanged;
protected:
	bool mEnabled = true;
	INode* mNode=nullptr;
};

MEDUSA_END;
