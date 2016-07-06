// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaPreDeclares.h"
#include "Core/String/HeapString.h"
#include "Graphics/GraphicsTypes.h"
#include "Resource/Effect/Pass/Program/BaseProgramRenderPass.h"

MEDUSA_BEGIN;

class IShaderParameter
{
protected:
	IShaderParameter(BaseProgramRenderPass* renderPass, int location, StringRef name);
	IShaderParameter(StringRef name);

	virtual ~IShaderParameter();
public:
	BaseProgramRenderPass* RenderPass() const { return mRenderPass; }
	void SetRenderPass(BaseProgramRenderPass* val) { mRenderPass = val; }

	int Location() const { return mLocation; }
	void SetLocation(int val) { mLocation = val; }

	StringRef Name() const { return mName; }
	void SetName(StringRef val) { mName = val; }
public:
	void Validate()const;
	void Invalidate();
	bool IsAssigned() const { return mIsAssigned; }
protected:
	void MarkAssigned();
protected:
	BaseProgramRenderPass* mRenderPass = nullptr;	//weak ptr
	int mLocation = -1;
	HeapString mName;
	bool mIsAssigned = false;
};

MEDUSA_END;