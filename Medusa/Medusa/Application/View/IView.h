// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"		  
#include "Geometry/Size2.h"
#include "Core/String/HeapString.h"
#include "Core/Pattern/IInitializable.h"
#include "Core/Pattern/RTTI/RTTIObject.h"
#include "Core/Pattern/Runnable/DefaultRunnable.h"

MEDUSA_BEGIN;

class IView :public IInitializable, public RTTIObject,public DefaultRunnable
{
	MEDUSA_RTTI_ROOT(IView);

public:
	IView(StringRef name=StringRef::Empty);
	virtual ~IView(void);
public:
	virtual void Resize(const Size2F& newSize){}

	IWindow* Parent() const { return mParent; }
	void SetParent(IWindow* val) { mParent = val; }

	const Size2F& Size() const { return mSize; }
	void SetSize(const Size2F& val) { mSize = val; }

protected:
	HeapString mName;
	IWindow* mParent;
	Size2F mSize;

};

MEDUSA_END;
