// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/String/HeapString.h"
#include "Core/Collection/List.h"
#include "Geometry/Point2.h"
#include "Geometry/PointPath2.h"

MEDUSA_BEGIN;

class IStrokeTemplate
{
public:
	IStrokeTemplate(const StringRef& name = StringRef::Empty);
	IStrokeTemplate(HeapString&& name);
	virtual ~IStrokeTemplate() = default;
public:
	StringRef Name() const { return mName; }
	void SetName(const StringRef& name) { mName = name; }
	bool HasName()const { return !mName.IsEmpty(); }
protected:
	HeapString mName;
};

MEDUSA_END;
