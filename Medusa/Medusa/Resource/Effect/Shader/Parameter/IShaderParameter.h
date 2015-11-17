// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaPreDeclares.h"

#include "Core/String/HeapString.h"
#include "Graphics/GraphicsTypes.h"

MEDUSA_BEGIN;

class IShaderParameter
{
protected:
	IShaderParameter(BaseProgramRenderPass* renderPass,int location,StringRef name);
	virtual ~IShaderParameter();
public:
	BaseProgramRenderPass* RenderPass() const { return mRenderPass; }
	int Location() const { return mLocation; }
	StringRef Name() const { return mName; }

public:
	void Validate()const;
	void Invalidate();
	bool IsAssigned() const { return mIsAssigned; }

protected:
	void MarkAssigned();
protected:
	BaseProgramRenderPass* mRenderPass;
	int mLocation;
	HeapString mName;
	bool mIsAssigned;
};

MEDUSA_END;