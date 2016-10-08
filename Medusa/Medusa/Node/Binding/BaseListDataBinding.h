// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "IDataBinding.h"
#include "Geometry/Size2.h"
#include "Core/Pattern/Event.h"

MEDUSA_BEGIN;


class BaseListDataBinding :public IDataBinding
{
public:
	Event<void(size_t index)> OnItemAdded;
	Event<void(size_t index)> OnItemRemoved;
	Event<void(size_t index)> OnItemUpdated;
public:
	bool IsFixedSize()const { return mIsFixedSize; }
	void EnableFixedSize(bool val) { mIsFixedSize = val; }

	virtual size_t Count()const = 0;
	virtual int GetTemplateTag(size_t index)const = 0;
	virtual bool HasMultipleTag()const = 0;

	virtual Size2F GetFixedSize(const Size2F& limitSize = Size2F::Zero)const { return Size2F::Zero; }

	virtual Size2F Measure(size_t index, const Size2F& limitSize = Size2F::Zero)const { return Size2F::Zero; }
	virtual INode* Load(size_t index, const Size2F& limitSize = Size2F::Zero, INode* reloadNode = nullptr) const { return reloadNode; }
protected:
	bool mIsFixedSize = true;

};

MEDUSA_END;
