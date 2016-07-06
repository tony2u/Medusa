// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Event/EventArg/IEventArg.h"
#include "Node/NodeDefines.h"


MEDUSA_BEGIN;

class BaseKeyEventArg:public IEventArg
{
	MEDUSA_RTTI(BaseKeyEventArg,IEventArg);
public:
	BaseKeyEventArg(uint keyData,uint status);
	virtual ~BaseKeyEventArg(void){}
	void SetKey(Keys val) { mKeyData = val; }

	bool Alt(){return ((int)mKeyData & (int)Keys::Alt) == (int)Keys::Alt;}
	bool Control(){return ((int)mKeyData & (int)Keys::Control) == (int)Keys::Control;}
	bool Shift(){return ((int)mKeyData & (int)Keys::Shift) == (int)Keys::Shift;}


	Keys KeyCode() const { return (Keys)((int)mKeyData&(int)Keys::KeyCode); }
	Keys Modifiers() const { return (Keys)((int)mKeyData&~(int)Keys::KeyCode); }
	Keys KeyData() const { return mKeyData; }

	int KeyValue()const{return (int)((int)mKeyData&(int)Keys::KeyCode); }
protected:
	Keys mKeyData;
	uint mStatus;
};

MEDUSA_END;