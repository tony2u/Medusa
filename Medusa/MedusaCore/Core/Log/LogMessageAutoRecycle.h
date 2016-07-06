// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "LogMessagePool.h"


MEDUSA_BEGIN;

template<typename T>
struct LogMessageAutoRecycle :public INonCopyable
{
	using ItemType = TLogMessage<T>;
	LogMessageAutoRecycle(ItemType* val)
		:mItem(val)
	{
	}
	~LogMessageAutoRecycle()
	{
		if (mItem != nullptr)
		{
			TLogMessagePool<T>::Instance().Recycle(mItem);
		}
	}

	LogMessageAutoRecycle(LogMessageAutoRecycle&& val)
		:mItem(val)
	{
		val.mItem = nullptr;
	}
	LogMessageAutoRecycle& operator=(LogMessageAutoRecycle&&) = delete;

private:
	ItemType* mItem;
};


MEDUSA_END;
