// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaPreDeclares.h"

MEDUSA_BEGIN;

class IPlayer
{
public:
	IPlayer();
	virtual ~IPlayer();
public:
	bool IsChanged() const { return mIsChanged; }
	void MarkChanged() { mIsChanged = true; }

	virtual bool Save(bool isForceToSave = false);
	virtual void ResetToDefault();
	virtual void Update(float dt);
protected:
	bool mIsChanged=false;
};


MEDUSA_END;